from abc import ABC, abstractmethod
import math
import heapq

class UndirectedSocialNetwork:
    def __init__(self, file, delimiter='\t', parse=0):
        self.net = {}
        self.edges = 0
        f = open(file, "r")
        lines = f.readlines()

        """ Por cada linea conectamos los usuarios depediendo del parser que se introduzca"""
        for line in lines:
            u, v = line.split(delimiter)
            if parse != 0:
                u = parse(u)
                v = parse(v)
            else:
                u = u.rstrip()
                v = v.rstrip()
            
            if u not in self.net:
                self.net[u] = set()
            if v not in self.net:
                self.net[v] = set()
            if u in self.net[v] and v in self.net[u]:
                continue

            self.net[u].add(v)
            self.net[v].add(u)
            self.edges += 1

        f.close()

    def users(self):
        return list(self.net.keys())

    def contacts(self, user):
        return self.net[user]

    def degree(self, user):
        return len(self.net[user])

    def add_contact(self, u, v):
        if u not in self.net:
            self.net[u] = set()
        if v not in self.net:
            self.sn[v] = set()

        self.net[u].add(v)
        self.net[v].add(u)
        self.edges += 1

    def connected(self, u, v):
        if u in self.net[v] or v in self.net[u]:
            return True
        else:
            return False

    def nedges(self):
        return self.edges


class Metric(ABC):
    def __init__(self, test, cutoff):
        self.test = test
        self.cutoff = cutoff
        
    def __repr__(self):
        return type(self).__name__ + ("@" + str(self.cutoff) if self.cutoff != math.inf else "")

    @abstractmethod
    def compute_all(self, network):
        """" Compute metric on all users or edges of network """


class LocalMetric(Metric):
    def __init__(self, topn):
        self.topn = topn

    @abstractmethod
    def compute(self, network, element):
        """" Compute metric on one user or edge of network """

class UserClusteringCoefficient(LocalMetric): # or LocalMetric? or other useful intermediate class?
    def compute(self, network, element):
        grado = network.degree(element)
        """Den = numero de vecinos si todos estan conectados"""
        den = (grado * (grado - 1)) / 2
        if den == 0:
            return 0
        num = 0
        """Checkear si ls vecinos estan conectados y sumar si lo estan"""
        vecinos = list(network.contacts(element))
        for i in range(len(vecinos)):
            for j in range(i + 1, len(vecinos)):
                if vecinos[j] in network.contacts(vecinos[i]):
                    num += 1
        return num / den

    def compute_all(self, network):
        """Devolver lo que tiene mas valor en la metrica en un ranking"""
        rank = Ranking(self.topn)
        for u in network.users():
            score = self.compute(network, u)
            rank.add(u, score)
        return rank

    def __repr__(self):
        return type(self).__name__ + ("@" + str(self.topn) if self.topn != math.inf else "")

class AvgUserMetric(Metric): # or LocalMetric? or other useful intermediate class?
    def __init__(self, metric):
        self.metric = metric

    def compute_all(self, network):
        ret = 0
        for user in network.users():
            ret += self.metric.compute(network, user)
        return ret / len(network.users())
    pass

class Embeddedness(LocalMetric): # or LocalMetric? or other useful intermediate class?
    """Calcular los Jaccard"""
    def compute(self, network, element):
        interseccion = (network.contacts(element[0]) - set([element[1]])
                 ) & (network.contacts(element[1]) - set([element[0]]))
        union = (network.contacts(element[0]) - set([element[1]])
                 ) | (network.contacts(element[1]) - set([element[0]]))

        if len(union) == 0:
            return 0

        return len(interseccion) / len(union)

    def compute_all(self, network):
        rank = Ranking(self.topn)
        newSet = set()
        for u in network.users():
            for v in network.users():
                if v in newSet or v == u:
                    continue
                score = self.compute(network, (u, v))
                rank.add((u, v), score)
            newSet.add(u)
        return rank

    def __repr__(self):
        return type(self).__name__ + ("@" + str(self.topn) if self.topn != math.inf else "")

class ClusteringCoefficient(Metric): # or LocalMetric? or other useful intermediate class?
    def compute_all(self, network):
        triangulos = 0
        tuplas = 0
        """Calcular el numero de tuplas de tres y los triangulos que se forman.
        El return sera la division de los triangulos por las tuplas"""
        for u in network.users():
            for v in network.contacts(u):
                for x in network.contacts(v):
                    if x == u:
                        continue
                    tuplas += 1
                    if u in network.contacts(x):
                        triangulos += 1

        return triangulos / tuplas

class Assortativity(Metric): # or LocalMetric? or other useful intermediate class?
    def compute_all(self, network):
        total1 = 0
        total2 = 0
        total3 = 0
        metrica = set()
        """Calcular el valor total de la suma para cada usuario"""
        for u in network.users():
            for v in network.contacts(u):
                if v in metrica:
                    continue
                total1 += network.degree(u) * network.degree(v)
            metrica.add(u)
            total2 += math.pow(network.degree(u), 2)
            total3 += math.pow(network.degree(u), 3)

        num_edges = network.nedges()
        return (4 * num_edges * total1 - math.pow(total2, 2)) / (2 * num_edges * total3 - math.pow(total2, 2))

class Ranking:
    class ScoredUser:
        """
        Clase utilizada para gestionar las comparaciones que se realizan dentro del heap
        """

        def __init__(self, element):
            self.element = element

        def __lt__(self, other):
            """
            En primer lugar se compara el score. En caso de que sean iguales (mismo score),
            se compara usando el userid (se colocará más arriba el elemento con un userid menor).
            """
            return self.element[0] < other.element[0] if self.element[0] != other.element[0] \
                else self.element[1] > other.element[1]

        def __eq__(self, other):
            return self.element == other.element

        def __str__(self):
            return str(self.element)

        def __repr__(self):
            return self.__str__()

    def __init__(self, topn):
        self.heap = []
        self.topn = topn
        self.changed = 0

    def add(self, user, score):
        scored_user = self.ScoredUser((score, user))
        if len(self.heap) < self.topn:
            heapq.heappush(self.heap, scored_user)
            self.changed = 1
        elif scored_user > self.heap[0]:
            heapq.heappop(self.heap)
            heapq.heappush(self.heap, scored_user)
            self.changed = 1

    def __iter__(self):
        if self.changed:
            self.ranking = []
            h = self.heap.copy()
            while h:
                self.ranking.append(heapq.heappop(h).element[::-1])
            self.changed = 0
        return reversed(self.ranking)

    def __repr__(self):
        r = "<"
        for user, score in self:
            r += str(user) + ":" + str(score) + " "
        return r[0:-1] + ">"