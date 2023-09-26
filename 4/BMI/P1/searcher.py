import math
from abc import ABC, abstractmethod
from typing import Dict, List


def tf(freq):
    return 1 + math.log2(freq) if freq > 0 else 0


def idf(df, n):
    return math.log2((n + 1) / (df + 0.5))


def calc_module(index):
    array_modules: List = []
    idf_values: Dict = {}

    for t in index.all_terms():
        idf_values[t] = idf(index.doc_freq(t), index.ndocs())

    for doc_id in range(index.ndocs()):
        doc_tf_sum = 0
        for doc_inf_term, doc_inf_freq in index.doc_vector(doc_id):
            if doc_inf_term in idf_values:
                doc_tf_sum += (tf(doc_inf_freq) * idf_values[doc_inf_term]) ** 2

        array_modules.append(math.sqrt(doc_tf_sum))

    return array_modules


class Searcher(ABC):
    def __init__(self, index):
        self.index = index

    @abstractmethod
    def search(self, query, limit):
        """ Returns a list of documents built as a pair of path and score """
        pass


class VSMDotProductSearcher(Searcher):
    def __init__(self, index):
        self.index = index

    def search(self, query, limit):
        # Parseamos y eliminamos mayusculas, dividimos por espacios
        qterms = query.lower().split(' ')
        results: List = []

        for doc_id in range(self.index.ndocs()):
            tf_idf = 0
            for q_word in qterms:
                tf_idf += self.score(q_word, doc_id)
            if tf_idf > 0:
                results.append([self.index.doc_path(doc_id), tf_idf])
        results.sort(key=lambda results: results[1], reverse=True)
        return results[0:limit]

    def score(self, term, doc_id):
        return tf(self.index.term_freq(term, doc_id)) * idf(self.index.doc_freq(term), self.index.ndocs())


class VSMCosineSearcher(VSMDotProductSearcher):
    def __init__(self, index):
        self.index = index
        self.module = calc_module(index)

    def score(self, term, doc_id):
        return (tf(self.index.term_freq(term, doc_id)) * idf(self.index.doc_freq(term), self.index.ndocs())) / self.module[doc_id]
