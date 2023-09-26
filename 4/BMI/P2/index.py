from distutils.command.config import config
import os, os.path
import re
import math
import pickle
from collections import OrderedDict
from typing import Collection, Dict
import zipfile
import shutil
from abc import ABC, abstractmethod
from urllib.request import urlopen
from bs4 import BeautifulSoup


def tf(freq):
    return 1 + math.log2(freq) if freq > 0 else 0

def idf(df, n):
    return math.log2((n + 1) / (df + 0.5))

class BasicParser:
    @staticmethod
    def parse(text):
        return re.findall(r"[^\W\d_]+|\d+", text.lower())


class Config(object):
  # variables de clase
  NORMS_FILE = "docnorms.dat"
  PATHS_FILE = "docpaths.dat"
  INDEX_FILE = "serialindex.dat"
  DICTIONARY_FILE = "dictionary.dat"
  POSTINGS_FILE = "postings.dat"


class Index:
    def __init__(self, dir=None):
        self.docmap = []
        self.modulemap = {}
        if dir: self.open(dir)

    def add_doc(self, path):
        self.docmap.append(path)  # Assumed to come in order
    
    def doc_module(self, docid):
        if docid in self.modulemap:
            return self.modulemap[docid]
        return None
    
    def doc_vector(self, doc_id):
        pass

    def ndocs(self):
        return len(self.docmap)

    def all_terms(self):
        return list()

    def all_terms_with_freq(self):
        pass

    def total_freq(self, term):
        freq = 0
        for posting in self.postings(term):
            freq += posting[1]
        return freq

    def doc_path(self, docid):
        return self.docmap[docid]

    def term_freq(self, term, docID):
        post = self.postings(term)
        if post is None: return 0
        for posting in post:
            if posting[0] == docID:
                return posting[1]
        return 0

    def doc_freq(self, term):
        return len(self.postings(term))

    def postings(self, term):
        # used in more efficient implementations
        return list()

    def positional_postings(self, term):
        # used in positional implementations
        return list()

    def save(self, dir):
        if not self.modulemap: self.compute_modules()
        p = os.path.join(dir, Config.NORMS_FILE)
        with open(p, 'wb') as f:
            pickle.dump(self.modulemap, f)      

    def open(self, dir):
        try:
            p = os.path.join(dir, Config.NORMS_FILE)
            with open(p, 'rb') as f:
                self.modulemap = pickle.load(f)
        except OSError:
            # the file may not exist the first time
            pass
    
    def compute_modules(self):
        for term in self.all_terms():
            idf_score = idf(self.doc_freq(term), self.ndocs())
            post = self.postings(term)
            if post is None: continue
            for docid, freq in post:
                if docid not in self.modulemap: self.modulemap[docid] = 0
                self.modulemap[docid] += math.pow(tf(freq) * idf_score, 2)
        for docid in range(self.ndocs()):
            self.modulemap[docid] = math.sqrt(self.modulemap[docid]) if docid in self.modulemap else 0


class Builder:
    def __init__(self, dir, parser=BasicParser()):
        if os.path.exists(dir): shutil.rmtree(dir)
        os.makedirs(dir)
        self.parser = parser

    def build(self, path):
        if zipfile.is_zipfile(path):
            self.index_zip(path)
        elif os.path.isdir(path):
            self.index_dir(path)
        else:
            self.index_url_file(path)

    def index_zip(self, filename):
        file = zipfile.ZipFile(filename, mode='r', compression=zipfile.ZIP_DEFLATED)
        for name in sorted(file.namelist()):
            with file.open(name, "r", force_zip64=True) as f:
                self.index_document(name, BeautifulSoup(f.read().decode("utf-8"), "html.parser").text)
        file.close()

    def index_dir(self, dir):
        for subdir, dirs, files in os.walk(dir):
            for file in sorted(files):
                path = os.path.join(dir, file)
                with open(path, "r") as f:
                    self.index_document(path, f.read())

    def index_url_file(self, file):
        with open(file, "r") as f:
            self.index_urls(line.rstrip('\n') for line in f)

    def index_urls(self, urls):
        for url in urls:
            self.index_document(url, BeautifulSoup(urlopen(url).read().decode("utf-8"), "html.parser").text)
            
    def index_document(self, path, text):
        pass

    def commit(self):
        pass


class RAMIndex(Index):
    def __init__(self, dir=None):
        self.terms_dict = {}
        super().__init__(dir)

    def postings(self, term):
        return self.terms_dict[term]

    def all_terms(self):
        return self.terms_dict.keys()

    def save(self, dir):
        p = os.path.join(dir, Config.DICTIONARY_FILE)
        with open(p, 'wb') as f:
            pickle.dump(self.terms_dict, f)
        super().save(dir)

    def open(self, dir):
        super().open(dir)
        try:
            p = os.path.join(dir, Config.DICTIONARY_FILE)
            with open(p, 'rb') as f:
                self.terms_dict = pickle.load(f)
        except OSError:
            # the file may not exist the first time
            pass


class RAMIndexBuilder(Builder):
    # Your new code here (exercise 2.2) #
    def __init__(self, dir_path, parser=BasicParser()):
        super().__init__(dir_path, parser)
        self.path = dir_path
        self.index = RAMIndex(dir_path)

    def index_document(self, path, text):
        doc_id = self.index.ndocs()

        self.index.add_doc(path)

        text = BasicParser.parse(text)
        term_freq: Dict = {}

        for term in text:
            if self.index.terms_dict.get(term) is None:
                term_freq[term] = 0
                self.index.terms_dict[term] = []

            elif term_freq.get(term) is None:
                term_freq[term] = 0

            term_freq[term] += 1

        for term in term_freq.keys():
            self.index.terms_dict[term].append(
                [doc_id, term_freq[term]])

    def commit(self):
        self.index.save(self.path)  
        f = open(self.path + Config.INDEX_FILE, "wb")
        pickle.dump(self.index, f)


class DiskIndex(Index):
    # Your new code here (exercise 3*) #
    def __init__(self, dir_path=None):
        self.postings_dict = {}
        self.postings_path = os.path.join(dir_path, Config.POSTINGS_FILE)
        self.count = 0
        self.terms_dict: Dict = {}
        super().__init__(dir_path)
        
    def postings(self, term):
        postings_ret: Dict = {}
        f = open(Config.DICTIONARY_FILE, 'r')
        f.seek(self.terms_dict[term])

        doc_amount, raw_postings = f.readline().strip().split("=")
        raw_postings = raw_postings.split(" ")

        for i in range(0, int(doc_amount) * 2, 2):
            postings_ret.append(
                [int(raw_postings[i]), int(raw_postings[i+1])])

        f.close()
        return postings_ret

    def all_terms(self):
        return self.terms_dict.keys()

    def doc_freq(self, term):
        f = open(self.postings_path, 'r')
        f.seek(self.terms_dict[term])
        result = f.readline().split('-')[0]
        f.close()
        return int(result)

    def save(self, dir_path):
        f = open(os.path.join(dir_path, Config.PATHS_FILE), 'wb')
        pickle.dump(self.docmap, f)
        f.close()
        
        f = open(os.path.join(dir_path, Config.POSTINGS_FILE), 'w')
        for term, postings in self.postings_dict.items():
                self.terms_dict[term] = f.tell()
                n_postings = len(postings)
                f.write(str(n_postings) + "-")
                for p in postings:
                    f.write(str(p[0]) + " ")
                    f.write(str(p[1]) + " ")
                f.write("\n")
        f.close()
        
        f = open(os.path.join(dir_path, Config.DICTIONARY_FILE), 'wb')
        self.terms_dict = OrderedDict(sorted(self.terms_dict.items()))
        pickle.dump(self.terms_dict, f)
        f.close

        super().save(dir_path)


    def open(self, dir_path):
        super().open(dir_path)
        self.postings_dict = {}
        try:
            f = open(os.path.join(dir_path, Config.PATHS_FILE), 'rb')
            self.docmap = pickle.load(f)
            f.close()
            f = open(os.path.join(dir_path, Config.DICTIONARY_FILE), 'rb')
            self.terms_dict = pickle.load(f)
            f.close()
        except OSError:
            print("File doesnt exist")
            pass


class DiskIndexBuilder(Builder):
    # Your new code here (exercise 3*) #
    def __init__(self, dir_path, parser=BasicParser()):
        super().__init__(dir_path, parser)
        self.path = dir_path
        self.index = DiskIndex(dir_path)

    def index_document(self, path, text):
        doc_id = self.index.ndocs()

        self.index.add_doc(path)

        text = BasicParser.parse(text)
        term_freq: Dict = {}

        for term in text:
            if self.index.terms_dict.get(term) is None:
                term_freq[term] = 0
                self.index.terms_dict[term] = []

            elif term_freq.get(term) is None:
                term_freq[term] = 0

            term_freq[term] += 1

        for term in term_freq.keys():
            self.index.terms_dict[term].append(
                [doc_id, term_freq[term]])

    def commit(self):
        self.index.save(self.path)  
        f = open(self.path + Config.INDEX_FILE, "wb")
        pickle.dump(self.index, f)
        f.close()


class PositionalIndex(RAMIndex):
    # Your new code here (exercise 5*) #
    # Note that it may be better to inherit from a different class
    # if your index extends a particular type of index
    # For example: PositionalIndex(RAMIndex)
    def __init__(self, dir_path=None):
        self.terms_dict = {}
        super().__init__(dir_path)
    
    def positional_postings(self, term):
        dict = self.terms_dict[term]
        returned_postings = [] 
        for doc, pos in dict.items():
            returned_postings.append(tuple((doc, pos))) 
        
        return returned_postings

    def postings(self, term):
        dict = self.terms_dict[term]
        returned_postings = []
        for doc, pos in dict.items():
            returned_postings.append((doc, len(pos)))
        return returned_postings


class PositionalIndexBuilder(RAMIndexBuilder):
    # Your new code here (exercise 5*) #
    # Same note as for PositionalIndex
    def __init__(self, dir_path, parser=BasicParser()):
        super().__init__(dir_path, parser)
        self.index = PositionalIndex(dir_path)

    def index_document(self, path, text):
        doc_id = self.index.ndocs()

        self.index.add_doc(path)

        text = BasicParser.parse(text)
        term_freq: Dict = {}

        for pos, term in enumerate(text):
            if self.index.terms_dict.get(term) is None:
                term_freq[term] = []
                self.index.terms_dict[term] = []

            elif term_freq.get(term) is None:
                term_freq[term] = []

            term_freq[term].append(pos)

        for term in term_freq.keys():
            self.index.terms_dict[term][doc_id] = term_freq[term]