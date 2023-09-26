from math import sqrt
from typing import OrderedDict
from abc import ABC, abstractmethod
import random
import heapq

class Ratings:
    def __init__(self, file="", delim='\t'):
        with open(file, "r") as f:
            line = f.readline()
            """Linea: Usuario Item Rating"""
            # Crear un diccionario que, para cada usuario, guarde item y el rating = user[item: rating] #
            # Crear diccionario para encontrar rating en funcion del item (funciones item e item_users) = item[user: rating] #
            self.ratings = self.create_dict_user(line, delim)
            self.itemRating = self.create_dict_item(line, delim)
    
    def create_dict_user(self, line, delim='\t'):
        ratings_dict = OrderedDict()

        for l in line:
            column = l.split(delim)
            user = column[0]
            item = column[1]
            rating = column[2]

            # Se actualiza el diccionario si no tiene un usuario, un item o un rating #
            if user not in ratings_dict:
                ratings_dict[user] = {}
            if item not in ratings_dict:
                ratings_dict[user][item] = rating
        
        return ratings_dict

    def create_dict_item(sef, line, delim ='\t'):
        itemRatings_dict = OrderedDict
        
        for l in line:
            column = l.split(delim)
            user = column[0]
            item = column[1]
            rating = column[2]

            if item not in itemRatings_dict:
                itemRatings_dict[item] = () 
            if rating not in itemRatings_dict:
                itemRatings_dict[item][user] = rating
        
        return itemRatings_dict

    def rate(self, user, item, rating):
        if user not in self.ratings:
            self.ratings[user] = {}

        if item not in self.ratings[user]:
            self.ratings[user][item] = rating

    def rating(self, user, item):
        return self.ratings[user][item]

    def random_split(self, ratio):
        """ POR HACER """

    def nratings(self):
        nrate = 0

        for user in self.ratings.keys():
            for item in self.ratings[user]:
                nrate += 1
        return nrate
    
    def users(self):
        ret = []

        for user in self.ratings.keys():
            ret.append(user)

        return ret

    def items(self):
        ret = []

        for item in self.itemRatings.keys():
            ret.append(item)

        return ret
    
    def user_items(self, user):
        return self.ratings[user]

    def item_users(self, item):
        return self.itemRating[item]


class Ranking:
    class ScoredItem:
        """
        Clase utilizada para gestionar las comparaciones que se realizan dentro del heap
        """
        def __init__(self, element):
            self.element = element

        def __lt__(self, other):
            """
            En primer lugar se compara el score. En caso de que sean iguales (mismo score),
            se compara usando el itemid (se colocará más arriba el elemento con un itemid menor).
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

    def add(self, item, score):
        scored_item = self.ScoredItem((score, item))
        if len(self.heap) < self.topn:
            heapq.heappush(self.heap, scored_item)
            self.changed = 1
        elif scored_item > self.heap[0]:
            heapq.heappop(self.heap)
            heapq.heappush(self.heap, scored_item)
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
        for item, score in self:
            r = r + str(item) + ":" + str(score) + " "
        return r[0:-1] + ">"


class Recommender(ABC):
    def __init__(self, training):
        self.training = training

    def __repr__(self):
        return type(self).__name__

    @abstractmethod
    def score(self, user, item):
        """ Core scoring function of the recommendation algorithm """

    def recommend(self, topn):
        """ Completar: devolver un diccionario con un ranking para cada usuario """
        for user in self.training.users():
            ranking = Ranking(topn)

            # Solo recomendar items que aun no tenga # 
            for item in self.training.items():
                if item not in self.training.user_items(user):
                    ranking.add(item, self.score(user, item))

            self.recommendation[user] = ranking
        return self.recommendation



class RandomRecommender(Recommender):
    def score(self, user, item):
        return random.random()


class MajorityRecommender(Recommender):
    def __init__(self, ratings, threshold=0):
        super().__init__(ratings)
        self.threshold = threshold

    def score(self, user, item):
        return sum(rating >= self.threshold for user, rating in self.training.item_users(item).items())


class AverageRecommender(Recommender):
    def __init__(self, training, minimo=0):
        super().__init__(training)
        self.minimo = minimo

    def score(self, user, item):
        """ Al indicarse el minimo por el constructor, se checkea que el numero de rankings llegue a ese minimo.
        Por cada rating en user, se obtiene la suma del mismo y se divide entre el numero total de rankings, obteniendo asi la media """
        if len(self.training.item_users(item).items()) >= self.minimo:
            return sum(rating for user, rating in self.training.item_users(item).items())/len(self.training.item_users(item).items())

        # En caso de que no se llegue al minimo se devuelve 0 #
        return 0

class UserSimilarity(ABC):
    @abstractmethod
    def sim(self, user1, user2):
        """ Computation of user-user similarity metric """


class CosineUserSimilarity(UserSimilarity):
    def __init__(self, ratings):
        self.ratings = ratings

    def sim(self, user1, user2):
        # cos = SUM(items_u1 interseccion items_u2) / mod_u1 * mod_u2
        
        # SUM(items_u1 interseccion items_u2) #
        total_sum = 0
        for i in self.ratings.user_items(user1).keys():
            if i in self.ratings.user_items(user2).keys():
                total_sum += self.ratings.rating(user1, i) * self.ratings.rating(user2, i) 

        # Modulo user1 #
        m1 = 0
        for j in self.ratings.user_items(user1).keys():
            m1 += pow(self.ratings.rating(user1, j), 2)
        m1 = sqrt(m1)

        # Modulo user2 #
        m2 = 0
        for k in self.ratings.user_items(user2).keys():
            m2 += pow(self.ratings.rating(user2, k), 2)
        m2 = sqrt(m2)

        return total_sum / (m1 * m2)


class UserKNNRecommender(Recommender):
    def __init__(self, ratings, sim, k):
        super().__init__(ratings)
        self.sim = sim
        self.k = k
        self.dist = {}

        all_users = set(self.training.users())
        # Crear vecinos "offline" en constructor #
        for user in self.training.users():
            # Quitamos al propio usuario #
            all_users.discard(user)
            
            # Si el usuario no está en el vecindario, lo introducimos en el vecindario con el ranking que tenga #
            if user not in self.dist:
                self.dist[user] = Ranking(k)
                
            # Si cualquier otro usuario que pueda ser vecino no está, lo introducimos del mismo modo #
            for k_user in all_users:
                if k_user not in self.dist:
                    self.dist[k_user] = Ranking(k)

                    # Caluclamos la similitud de coseno entre usuarios y guardamos la distancia #
                    similitud = sim.sim(user, k_user)
                    if similitud != 0:
                        self.dist[user].add(k_user, similitud)
                        self.dist[k_user].add(user, similitud)
    
    def score(self, user, item):
        total_sum = 0
        for (k_user, distancia) in self.dist[user]:
            # Por cada vecino que tenga el usuario, checkear que el vecino haya valorado el item y hacer algoritmo knn #
            k_user_ratings = self.training.ratings[k_user]
            if item in k_user_ratings.keys():
                total_sum += distancia *  k_user_ratings[item]

        return total_sum


class NormUserKNNRecommender(Recommender):
    def __init__(self, ratings, sim, k, min):
        super().__init__(ratings, sim, k)
        self.min = min

    def score(self, user, item):
        num = 0
        den = 0
        num_ratings = 0

        """ NormUserKNN tiene en cuenta el numero de vecinos efectivos, por lo tanto el vecino 
        tiene que tener un ranking != 0, el numerador será la distancia del usuario a su vecino por
        su rating mientras que el denominador será la suma de las distancias de los usuarios """
        for (user2, dist) in self.distances[user]:
            user2_ratings = self.training.ratings[user2]
            if user2_ratings != 0:
                if item in user2.keys():
                    n_ratings += 1
                    num += dist * user2_ratings[item]
                    den += dist
        
        if  num_ratings < self.min or den < 1:
            return 0
        
        return num / den

class ItemKNNRecommender(Recommender):
    def __init__(self, ratings, sim, k):
        super.__init__(ratings)
        self.sim = sim
        self.k = k
        self.dist = {}

        all_items = set(self.training.items())
        # Crear vecinos "offline" en constructor #
        for item in self.training.items():
            # Quitamos al propio item #
            all_items.discard(item)

            # Si el item no está en el vecindario, lo introducimos en el vecindario con el ranking que tenga #
            if item not in self.dist:
                self.dist[item] = Ranking(k)

            # Si cualquier otro item que pueda ser vecino no está, lo introducimos del mismo modo #
            for k_item in all_items:
                if k_item not in self.dist:
                    self.dist[k_item] = Ranking(k)

            # Caluclamos la similitud de coseno entre usuarios y guardamos la distancia #
                    similitud = sim.sim(item, k_item)
                    if similitud != 0:
                        self.dist[item].add(k_item, similitud)
                        self.dist[k_item].add(item, similitud)

    def score(self, user, item):
        total_sum = 0
        for (k_item, distancia) in self.dist[item]:
            # Por cada vecino que tenga el item, checkear que el vecino haya valorado el item y hacer algoritmo knn #
            k_item_ratings = self.training.ratings[k_item]
            if item in k_item_ratings.keys():
                total_sum += distancia * self.training.ratings[user]

        return total_sum


class EvaluationMetric(ABC):
    def __init__(self, test, cutoff):
        self.test = test
        self.cutoff = cutoff

    def __repr__(self):
        return type(self).__name__ + ("@" + str(self.cutoff) if self.cutoff != math.inf else "")

    # Esta función se puede dejar abstracta declarándola @abstractmethod, 
    # pero también se puede meter algo de código aquí y el resto en las
    # subclases - a criterio del estudiante.
    def compute(self, recommendation):
        """ Completar """

class Precision(EvaluationMetric):
    def __init__(self, test, cutoff, threshold):
        super().__init__(test, cutoff)
        self.threshold = threshold

    """ Precision@threshold = (relevantes AND recomendados)/recomendados
        rating(relevantes) >= threshold
        Al final, tras hacer la precision para cada usuario, se divide por el total de usuarios"""
    def compute(self, recommendation):
        total_sum = 0
        for user in recommendation.keys():
            relevantes = 0
            recomendados = 0

            for r in recommendation[user]:
                if self.test.rating(user, r[0]) >= self.threshold:
                    relevantes += 1
                else:
                    pass

                recomendados += 1
                
                if recomendados == self.cutoff:
                    break

            num = relevantes/recomendados
            total_sum += num

        return total_sum/len(recommendation.keys())



class Recall(EvaluationMetric):
    def __init__(self, test, cutoff, threshold):
        super().__init__(test, cutoff)
        self.threshold = threshold

    """ Recall = (relevantes AND recomendados)/relevantes
        rating(relevantes) >= threshold
        Al final, tras hacer el recall para cada usuario, se divide por el total de usuarios"""
    def compute(self, recommendation):
        total_sum = 0
        for user in recommendation.keys():
            relevantes = 0
            recomendados = 0

            for r in recommendation[user]:
                if self.test.rating(user, r[0]) >= self.threshold:
                    relevantes += 1
                else:
                    pass
                
                recomendados += 1

                if recomendados == self.cutoff:
                    break

        # Para hacer recall, hay que coger el numero total de items relevantes (que superen el threshold) #
            for item in self.test.user_items(user):
                if self.test.rating(user, item) >= self.threshold:
                    total_items += 1
                
            num = relevantes/total_items
            total_sum += num

        return total_sum/len(recommendation.keys())
