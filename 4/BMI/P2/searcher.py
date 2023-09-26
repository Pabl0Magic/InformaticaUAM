import math
import heapq
from abc import ABC, abstractmethod
from typing import Dict, List
from P2.whooshmethods import WhooshPositionalIndex
from index import BasicParser

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


class SearchRanking:
    # TODO: to be implemented as heap (exercise 1.3) #
    def __init__(self, cutoff):
        self.ranking: List = [] # implementation as list, not as heap! TO BE MODIFIED
        heapq.heapify(self.ranking)
        self.cutoff = cutoff

    def push(self, docid, score):
        #self.ranking.append((docid, score))
        heapq.heappush(self.ranking, (score,docid))

    def __iter__(self):
        min_l = min(len(self.ranking), self.cutoff)
        ## sort ranking
        self.ranking.sort(key=lambda tup: tup[1], reverse=True)
        return iter(self.ranking[0:min_l])


class SlowVSMSearcher(Searcher):
    
    def __init__(self, index, parser=BasicParser()):
        super().__init__(index, parser)

    def search(self, query, cutoff):
        qterms = self.parser.parse(query)
        ranking = SearchRanking(cutoff)

        for docid in range(self.index.ndocs()):
            score = self.score(docid, qterms)
            if score:
                ranking.push(self.index.doc_path(docid), score)
        return ranking

    def score(self, docid, qterms):
        prod = 0
        for term in qterms:
            prod += tf(self.index.term_freq(term, docid)) \
                    * idf(self.index.doc_freq(term), self.index.ndocs())
        mod = self.index.doc_module(docid)
        if mod:
            return prod / mod
        return 0

class TermBasedVSMSearcher(Searcher):
    def __init__(self, index, parser=BasicParser()):
        super().__init__(index, parser)

    def search(self, query, cutoff):
        qterms = self.parser.parse(query)
        ranking = SearchRanking(cutoff)
        postingVal: Dict = {}

        for term in qterms:
            for docid, _ in self.index.postings(term):
                if docid not in postingVal.keys():
                    postingVal[docid] = []
                postingVal[docid].append(term)

        for docid in postingVal.keys():
            score = self.score(docid, postingVal[docid])
            if score:
                ranking.push(self.index.doc_path(docid), score)

        return ranking

    def score(self, docid, qterms):
        prod = 0
        for term in qterms:
            product += tf(self.index.term_freq(term, docid)) \
                    * idf(self.index.doc_freq(term), self.index.ndocs())

        mod = self.index.doc_module(docid)
        if mod:
            return prod / mod
         
        return 0

class DocBasedVSMSearcher(Searcher):
    # Your new code here (exercise 1.2*) #
    def __init__(self, index, parser=BasicParser()):
        super().__init__(index, parser)

    def search(self, query, cutoff):
        q_terms = self.parser.parse(query)
        posting_list = []
        ndocs = self.index.ndocs()
        rank = SearchRanking(cutoff)
        score = [0] * ndocs
        index = [0] * len(q_terms)

        # Recuperar lista de postings # 
        for q in q_terms:
            posting_list += [[p for p in self.index.postings(q)]]
        
        heap = []
        heapq.heapify(heap)
        #Tras crear un min heap, iteramos consecutivamente en orden de docID 
        for q in range(len(q_terms)):
            heapq.heappush(heap, (posting_list[q][index[q]], q))
            index[q] += 1 
        
        docActual = heapq.nsmallest(1, heap)[0][0][0]
        try:
            # Obtenemos elemento, docID, frecuencia y el score (que sumaremos en el caso de haber más en el mismo docID)
            while(1):
                element = heapq.heappop(heap)
                docID = element[0][0]
                freq = element[0][1]
                q = element[1]
                partial_score = tf(freq) * idf(self.index.doc_freq(q_terms[q]), ndocs)

                # Cuando cambiamos de docID, sumaremos todos los scores parciales #
                if docID != docActual:
                    score[docActual] /= self.index.doc_module(docActual)
                    # Tras hacer la operación del módulo, si el heap está incompleto se añade directamente el docID y su score
                    if len(rank.ranking) < rank.cutoff:
                        rank.push(self.index.doc_path(
                            docActual), rank[docActual])
                    # Si el heap está completo, entonces hay que ver si el score total es mayor que el menor del heap (ya que es un min heap)
                    elif score > heapq.nsmallest(1, rank.ranking)[0][0]:
                        rank.push(self.index.doc_path(
                            docActual), rank[docActual])

                    docActual = docID
                rank[docActual] += partial_score

                # Si no se llega al número de índices de la lista de posting, entonces se añade al heap de índices
                if index[q] < len(posting_list[q]):
                    heapq.heappush(heap, (posting_list[q][index[q]], q))
                    index[q] += 1

        # El heap se ha vaciado
        except Exception:  
            score[docActual] /= self.index.doc_module(docActual)
            if len(rank.ranking) < rank.cutoff:
                rank.push(self.index.doc_path(docActual), score[docActual])
            elif score > heapq.nsmallest(1, rank.ranking)[0][0]:
                rank.push(self.index.doc_path(docActual), score[docActual])

        return rank

class ProximitySearcher(Searcher):
    def __init__(self, index, parser=BasicParser()):
        super().__init__(index, parser)
    
    def search(self, query, cutoff):
        q_terms = self.parser.parse(query)
        rank = SearchRanking(cutoff)
        new_doc_ids = set()
        final_positions = {}

        for doc_id, _ in self.index.postings(q_terms[0]):
            new_doc_ids.add(doc_id)

        if len(q_terms) > 1:
            for term in q_terms[1:]:
                old_doc_ids = set()
                for doc_id, _ in self.index.postings(term):
                    old_doc_ids.add(doc_id)
                new_doc_ids &= old_doc_ids

        for term in q_terms:
            term_clean_positions = {}
            term_positions = self.index.positional_postings(term)
            for doc_positions in term_positions:
                if doc_positions[0] in new_doc_ids:
                    term_clean_positions[doc_positions[0]] = doc_positions[1]
            final_positions[term] = term_clean_positions

        for doc_id in new_doc_ids:
            rank.push(self.index.doc_path(doc_id), 
                         self.score(final_positions, doc_id, q_terms))

        return rank

    def score(self, final_positions, doc_id, q_terms):
        pos_list = []
        q_len = len(q_terms)

        for term in q_terms: 
            pos_list.append(final_positions[term][doc_id] + [math.inf])

        if q_len == 1:
            return float(len(pos_list[0]) - 1)

        a = - 1
        score = 0
        p = [0] * q_len
        b = max([t_list[0] for t_list in pos_list])

        while b != math.inf:
            i = 0
            for j in range(q_len):
                while pos_list[j][p[j]+1] <= b:
                    p[j] += 1
                if pos_list[j][p[j]] < pos_list[i][p[i]]:
                    i = j
            a = pos_list[i][p[i]]
            score += 1 / (b - a - q_len + 2)
            b = pos_list[i][p[i]+1]
            
        return score


class PagerankDocScorer():
    def __init__(self, graphfile, r, n_iter):
        self.n_iter = n_iter

        f = open(graphfile, "r")
        lines = f.read().splitlines()
        f.close()

        self.nodes = set()  # Elementos sin ordenar y sin repetir #
        self.outs = {}  # Clave: nodo, valor: lista de a quienes apunta #
        self.toFromNodes = {}  # Clave: nodo, valor: lista de quienes le apuntan #

        # Voy viendo donde apunta cada nodo y almacenando los nodos #
        for line in lines:
            ele = line.split('\t')
            self.nodes.add(ele[0])
            self.nodes.add(ele[1])

            # Comprobar salidas de cada nodo #
            try:
                self.outs[ele[0]].append(ele[1])
            except:
                self.outs[ele[0]] = [ele[1]]

            try:
                self.toFromNodes[ele[1]].append(ele[0])
            except:
                self.toFromNodes[ele[1]] = [ele[0]]

            # Sumideros #
            try:
                if self.outs[ele[1]]:
                    pass
            except:
                self.outs[ele[1]] = []

            try:
                if self.toFromNodes[ele[0]]:
                    pass
            except:
                self.toFromNodes[ele[0]] = []

        # Guardamos los sumideros #
        self.sumideros = []
        for node in self.outs.keys():
            if len(self.outs[node]) == 0:
                self.sumideros.append(node)

        self.n = len(self.nodes)
        self.r = r

    def rank(self, cutoff):
        p1 = self.r / self.n
        p2 = 1 - self.r
        res = []
        pageRankActual = {}
        pageRankAnterior = {}
        

        # Inicializar valores (se omite la division entre N) #
        for n in self.nodes:
            pageRankAnterior[n] = 1

        # Computar el PageRank iterativamente #
        for epoc in range(self.n_iter):
            for n in self.nodes:
                sum = 0
                # Se suma cada nodo que va hacia el que iteramos y luego se suman los sumideros #
                for origin in self.toFromNodes[n]:
                    sum += pageRankAnterior[origin] / len(self.outs[origin])
                    
                for i in self.sumideros:
                    sum += pageRankAnterior[i] / self.n

                pageRankActual[n] = p1 + p2 * sum

            # Guardamos valores PageRank #
            for n in pageRankActual.keys():
                pageRankAnterior[n] = pageRankActual[n]

        # Ordenamos según PageRank #
        ordered = dict(sorted(pageRankActual.items(),
                              key=lambda item: item[1], reverse=True))
        aux = 0
        for k, v in ordered.items():
            res.append((k, v))
            aux += 1
            if aux == cutoff:
                break
        # Devolvemos una lista [(nodo, pageRankScore), (nodo, pageRankScore), etc] #
        return res
