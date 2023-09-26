CREATE OR REPLACE FUNCTION getTopActors(genre CHAR, OUT Actor VARCHAR, OUT Num INT, OUT Debut INT,
OUT Film VARCHAR, OUT Director VARCHAR)
RETURNS SETOF RECORD
AS 
$$

BEGIN
    RETURN query
    SELECT actorname, CAST(topactors.num AS INT), CAST(year AS INT), movietitle, directorname
    FROM (
        SELECT DISTINCT ON (imdb_actors.actorname) imdb_actors.actorname, actoridselect.num, imdb_movies.year, imdb_movies.movietitle, imdb_directors.directorname 
        FROM (
            imdb_actors JOIN imdb_actormovies ON imdb_actors.actorid = imdb_actormovies.actorid
            JOIN imdb_movies ON imdb_actormovies.movieid = imdb_movies.movieid
            JOIN imdb_moviegenres ON imdb_movies.movieid = imdb_moviegenres.movieid
            JOIN imdb_directormovies ON imdb_movies.movieid = imdb_directormovies.movieid
            JOIN imdb_directors ON imdb_directormovies.directorid = imdb_directors.directorid
            JOIN (
                SELECT actorid, threshold.num 
                FROM (
                    SELECT actorid, count(movieid) as num FROM imdb_moviegenres NATURAL JOIN imdb_actormovies
                    WHERE imdb_moviegenres.genre = $1
                    GROUP BY actorid
                ) AS threshold
                WHERE threshold.num > 4
                ORDER BY threshold.num DESC 
            ) AS actoridselect ON actoridselect.actorid = imdb_actors.actorid
        ) ORDER BY imdb_actors.actorname, num DESC 
    ) AS topactors
    ORDER BY topactors.num DESC;

END;

$$
LANGUAGE plpgsql;

select getTopActors('Drama');