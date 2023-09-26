from typing import List
import whoosh
from whoosh.fields import Schema, TEXT, ID
from whoosh.formats import Format
from whoosh.qparser import QueryParser
import os, os.path
import shutil
from bs4 import BeautifulSoup
from zipfile import ZipFile
from urllib.request import urlopen
from index import Builder, Index
from searcher import Searcher

# A schema in Whoosh is the set of possible fields in a document in
# the search space. We just define a simple 'Document' schema, with
# a path (a URL or local pathname) and a content.
SimpleDocument = Schema(
        path=ID(stored=True),
        content=TEXT(phrase=False))
ForwardDocument = Schema(
        path=ID(stored=True),
        content=TEXT(phrase=False,vector=Format))
PositionalDocument = Schema(
        path=ID(stored=True),
        content=TEXT(phrase=True))

class WhooshBuilder(Builder):
    def __init__(self, dir, schema=SimpleDocument):
        super().__init__(dir)
        self.whoosh_writer = whoosh.index.create_in(dir, schema).writer(procs=1, limitmb=16384, multisegment=True)
        self.dir = dir
    """ def __init__(self, dir):
        if os.path.exists(dir): shutil.rmtree(dir)
        os.makedirs(dir)
        self.writer = whoosh.index.create_in(dir, Document).writer() """
    
    def index_document(self, p, text):
        self.whoosh_writer.add_document(path=p, content=text)
    """ def build(self, collection):
        if os.path.isfile(collection):
            # Check if it is a normal file or zip file or a folder#
            if collection.endswith(".txt"):
                with open(collection) as file:
                    url_list = file.readlines()
                    for url in url_list:
                        self.writer.add_document(path=url, content=BeautifulSoup(urlopen(url).read(), "lxml").text)
                return
            elif collection.endswith(".zip"):
                url_zip_list = ZipFile(collection, 'r')
                for urls in url_zip_list.namelist():
                        self.writer.add_document(path=urls, content=BeautifulSoup(url_zip_list.read(urls), "lxml").text)
                return

        else:
            # Folder
            dir_urls = os.listdir(collection)
            for document in sorted(dir_urls):
                path = os.path.join(collection, document)
                with open(path, 'r') as url:
                    self.writer.add_document(path=path, content=url.read()) """

    def commit(self):
        self.whoosh_writer.commit()
        index = WhooshIndex(self.dir)
        index.save(self.dir)


class WhooshForwardBuilder(WhooshBuilder):
    def __init__(self, dir):
        super().__init__(dir, ForwardDocument)

    def commit(self):
        self.whoosh_writer.commit()
        index = WhooshForwardIndex(self.dir)
        index.save(self.dir)


class WhooshPositionalBuilder(WhooshBuilder):
    def __init__(self, dir):
        super().__init__(dir, PositionalDocument)

    def commit(self):
        self.whoosh_writer.commit()
        index = WhooshPositionalIndex(self.dir)
        index.save(self.dir)


class WhooshIndex(Index):
    def __init__(self, dir):
        super().__init__(dir)
        self.whoosh_reader = whoosh.index.open_dir(dir).reader() 

    def doc_vector(self, doc_id):
        vector: List = []
        raw_vec = self.reader.vector_as("frequency", doc_id, "content")

        for t in raw_vec:
            term = t[0]
            freq = t[1]
            vector.append((term, freq))

        return vector

    def ndocs(self):
        return self.whoosh_reader.doc_count()

    def all_terms(self):
        return list(self.whoosh_reader.field_terms("content"))
    """ def all_terms(self):
        terms = self.reader.all_terms()
        list_terms: List = []
        for fieldname, text in terms:
            if fieldname == "content":
                list_terms.append(text.decode("utf-8"))

        return list_terms """

    def all_terms_with_freq(self):
        list_terms = self.all_terms()
        terms_freq: List = []
        for term in list_terms:
            terms_freq.append((term, self.total_freq(term)))

        return terms_freq

    def total_freq(self, term):
        return self.whoosh_reader.frequency("content", term)

    def doc_path(self, doc_id):
        return self.whoosh_reader.stored_fields(doc_id)['path']

    def term_freq(self, term, doc_id):
        counter = self.reader.vector(doc_id, "content")
        counter.skip_to(term)
        return counter.value_as("frequency") if counter.id() == term else 0

    def doc_freq(self, term):
        return self.whoosh_reader.doc_frequency("content", term)

    def postings(self, term):
        return self.whoosh_reader.postings("content", term).items_as("frequency") \
            if self.doc_freq(term) > 0 else []
    """ def postings(self, word):
        res: List = []
        try:
            pr = self.reader.postings("content", word)
        except Exception:
            return res

        cont = 0

        for cont in range(self.ndocs()):
            try:
                pr.skip_to(cont)
                if pr.id() == cont:
                    freq = self.term_freq(word, cont)
                    res.append((cont, freq))
            except Exception:
                pass

        return res """


class WhooshForwardIndex(WhooshIndex):
    def term_freq(self, term, docID) -> int:
        if self.whoosh_reader.has_vector(docID, "content"):
            v = self.whoosh_reader.vector(docID, "content")
            v.skip_to(term)
            if v.id() == term:
                return v.value_as("frequency")
        return 0



class WhooshPositionalIndex(WhooshIndex):
    def positional_postings(self, term):
        return self.whoosh_reader.postings("content", term).items_as("positions") \
            if self.doc_freq(term) > 0 else []


class WhooshSearcher(Searcher):

    def __init__(self, dir):
        self.whoosh_index = whoosh.index.open_dir(dir)
        self.whoosh_searcher = self.whoosh_index.searcher()
        self.qparser = QueryParser("content", schema=self.whoosh_index.schema)

    def search(self, query, cutoff):
        return map(lambda scoredoc: (self.doc_path(scoredoc[0]), scoredoc[1]),
                   self.whoosh_searcher.search(self.qparser.parse(query), limit=cutoff).items())

    def doc_path(self, docid):
        return self.whoosh_index.reader().stored_fields(docid)['path']
    """ def search(self, query, cutoff):
            #Returns a list of documents built as a pair of path and score
            list_docs: List = []
            counter = 0
            for docid, score in self.searcher.search(self.qparser.parse(query)).items():
                if counter > cutoff:
                    break
                doc_path = self.index.reader().stored_fields(docid)['path']
                list_docs.append((doc_path, score))
                counter = counter + 1

            return list_docs """

    def doc_path(self, docid):
        return self.whoosh_index.reader().stored_fields(docid)['path']