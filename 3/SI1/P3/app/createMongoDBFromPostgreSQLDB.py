import pymongo
import os
import json
import sys, traceback
import collections
from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, text
from sqlalchemy.sql import select


client = pymongo.MongoClient(host="localhost", port=27017)
client.drop_database('si1')
db = client["si1"]
newcol = db["topUK"]
#newcol.insert_one({"id": 1})


db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1P3", echo=False)
db_meta = MetaData(bind=db_engine)

def db_exception(db_conn):
    if db_conn is not None:
            db_conn.close()
    print("Exception in DB access:")
    print("-"*60)
    traceback.print_exc(file=sys.stderr)
    print("-"*60)

    return 'Something is broken'

try:
    db_conn = None
    db_conn = db_engine.connect()

    db_movies = db_conn.execute("SELECT movieid FROM imdb_movies NATURAL JOIN imdb_moviecountries WHERE country = 'UK' ORDER BY year DESC LIMIT 400")

    movies = list(db_movies)
    id_movie = 0

    for movie in movies:
        movie_dict = {}

        db_title = db_conn.execute("SELECT movietitle FROM imdb_movies WHERE movieid = "+str(movie[0]))
        db_title_list = list(db_title)
        
        db_genre = db_conn.execute("SELECT genre FROM imdb_moviegenres WHERE movieid = "+str(movie[0]))
        db_genre_list = list(db_genre)
        list_genre = []
        for elem in db_genre_list:
            list_genre.append(elem[0])

        db_year = db_conn.execute("SELECT year FROM imdb_movies WHERE movieid = "+str(movie[0]))
        db_year_list = list(db_year)

        db_ratingcount = db_conn.execute("SELECT ratingcount FROM imdb_movies WHERE movieid = "+str(movie[0]))
        db_ratingcount_list = list(db_ratingcount)

        db_ratingmean = db_conn.execute("SELECT ratingmean FROM imdb_movies WHERE movieid = "+str(movie[0]))
        db_ratingmean_list = list(db_ratingmean)

        db_director = db_conn.execute("SELECT directorname FROM imdb_directors NATURAL JOIN imdb_directormovies WHERE movieid = "+str(movie[0]))
        db_director_list = list(db_director)
        list_director = []
        for elem in db_director_list:
            list_director.append(elem[0])

        db_actor = db_conn.execute("SELECT actorname FROM imdb_actors NATURAL JOIN imdb_actormovies WHERE movieid = "+str(movie[0]))
        db_actor_list = list(db_actor)
        list_actor = []
        for elem in db_actor_list:
            list_actor.append(elem[0])

        newcol.insert_one({"title": db_title_list[0][0], 
                            "genres": list_genre, 
                            "year": db_year_list[0][0], 
                            "number_of_votes": db_ratingcount_list[0][0],
                            "average_rating": db_ratingmean_list[0][0],
                            "directors": list_director,
                            "actors": list_actor})
except:
    db_exception(db_conn)

    """SELECT movietitle, year, ratingmean FROM imdb_movies,
    (SELECT COUNT(imdb_moviegenres.genre) as i FROM imdb_moviegenres, imdb_movies WHERE
        imdb_movies.movieid = 147) as X, 
     (SELECT COUNT(genre) as g FROM imdb_moviegenres) as Y
     WHERE CAST(X.i as decimal)/Y.g >= 0.5 ORDER BY year DESC LIMIT 10"""


    """select * from(select movietitle, count(*) as num_genres from imdb_movies natural join imdb_moviegenres group by movietitle) as x where x.num_genres = 3"""