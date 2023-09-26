SELECT language.name
FROM   language
GROUP  BY language.name,
          language.language_id
HAVING language.language_id IN (SELECT film.language_id
                                FROM   film
                                GROUP  BY film.language_id,
                                          film.film_id
                                HAVING film.film_id IN (SELECT inventory.film_id
                                                        FROM   inventory,
                                       (SELECT rental.inventory_id,
                                               Count(*)
                                        FROM   rental
                                        GROUP  BY rental.inventory_id
                                        HAVING Count(*) IN (SELECT Count(*)
                                                            FROM   rental
                                               GROUP  BY inventory_id
                                               ORDER  BY Count(*) DESC
                                               LIMIT  1)) AS max_rented
                                                        WHERE
                                       max_rented.inventory_id
                                       =
                                       inventory.inventory_id));
                                       -- The last line was modified
                                       -- to make it more readable