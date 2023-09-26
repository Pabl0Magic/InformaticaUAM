CREATE OR REPLACE FUNCTION gettopsales(year1 INT, year2 INT,
OUT Year INT, OUT Film VARCHAR, OUT sales bigint) 
RETURNS SETOF RECORD 
AS 
$$

BEGIN
    RETURN query
    SELECT topsales.orderyear, topsales.movietitle, topsales.salesquantity FROM 
    (
        SELECT DISTINCT ON (orderyear) CAST (
            EXTRACT (
                year FROM orderdate
                ) AS INT
    ) AS orderyear, imdb_movies.movietitle, SUM(orderdetail.quantity) AS salesquantity
    FROM orders, orderdetail, imdb_movies, products
    WHERE orders.orderid = orderdetail.orderid AND products.prod_id = orderdetail.prod_id AND imdb_movies.movieid = products.movieid
    GROUP BY orderyear, imdb_movies.movietitle
    ORDER BY orderyear, salesquantity DESC
    ) AS topsales
    WHERE topsales.orderyear BETWEEN $1 AND $2
    ORDER BY topsales.salesquantity DESC;
END;

$$
LANGUAGE plpgsql;

select gettopsales(2016, 2023);