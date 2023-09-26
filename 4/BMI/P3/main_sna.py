import datetime
import time
from metrics import *

def main_sna():
    test_network("graphs/small1.csv", ",", 5, 6, 4, int)
    test_network("graphs/small2.csv", ",", 5, 3, 5, int)
    test_network("graphs/small3.csv", ",", 5, "a", "b")
    test_network("graphs/twitter.csv", ",", 5, "el_pais", "ElviraLindo")
    test_network("graphs/facebook_combined.txt", " ", 5, 9, 3, int)
    # test_network("graphs/barabasi.csv", ",", 5, 1, 2, int) # uno de los grafos creados en Ejercicio 5
    # test_network("graphs/erdos.csv", ",", 5, 1, 2, int) # el otro grafo creado en Ejercicio 5


def test_network(file, delimiter, topn, u, v, parse=0):
    print("==================================================\nTesting " + file + " network")
    network = UndirectedSocialNetwork(file, delimiter=delimiter, parse=parse)
    print(len(network.users()), "users and", network.nedges(), "contact relationships")
    print("User", u, "has", network.degree(u), "contacts")

    # Métricas de usuarios
    print("-------------------------")
    test_metric(UserClusteringCoefficient(topn), network, u)

    # Métricas de arcos
    print("-------------------------")
    test_metric(Embeddedness(topn), network, (u, v))

    # Métricas globales de red
    print("-------------------------")
    #test_global_metric(ClusteringCoefficient(), network)
    #test_global_metric(AvgUserMetric(UserClusteringCoefficient()), network)
    #test_global_metric(Assortativity(), network)

    # Otros tests?
    #student_test_sna(network)


def test_metric(metric, network, example):
    start = time.process_time()
    print(metric, ":", metric.compute_all(network))
    print(str(metric) + "(" + str(example) + ") =", metric.compute(network, example))
    timer2(start)


def test_global_metric(metric, network):
    start = time.process_time()
    print(metric, "=", metric.compute_all(network))
    timer2(start)


def timer2(start):
    print("--> elapsed time:", datetime.timedelta(seconds=round(time.process_time() - start)), "<--")

main_sna()