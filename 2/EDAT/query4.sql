SELECT language.name,
       Count(*)
FROM   film,
       language
WHERE  language.language_id = film.language_id
GROUP  BY language.name
HAVING Count(*) IN (SELECT Count(*)
                    FROM   film
                    GROUP  BY film.language_id
                    ORDER  BY Count(*) DESC
                    LIMIT  1); 