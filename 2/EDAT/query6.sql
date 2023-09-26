CREATE view bestcatcusid
AS
  (SELECT customer.customer_id AS cusid,
          film_category.category_id,
          Count(*)             AS total
   FROM   customer,
          (SELECT customer_id,
                  inventory_id
           FROM   rental,
                  (SELECT customer_id AS cusidinner
                   FROM   rental
                   GROUP  BY customer_id
                   HAVING Count(*) IN (SELECT Count(*)
                                       FROM   rental
                                       GROUP  BY rental.customer_id
                                       ORDER  BY Count(*) DESC
                                       LIMIT  1)) AS bestcustomers
           WHERE  cusidinner = customer_id) AS rn,
          inventory,
          film_category
   WHERE  customer.customer_id = rn.customer_id
          AND inventory.inventory_id = rn.inventory_id
          AND inventory.film_id = film_category.film_id
   GROUP  BY customer.customer_id,
             film_category.category_id);

SELECT BestCat.cusid AS customer_id,
       category.name
FROM   category,
       (SELECT cusid,
               category_id,
               total
        FROM   bestcatcusid,
               (SELECT cusid        AS cusidMax,
                       Max(total) AS max
                FROM   bestcatcusid
                GROUP  BY cusid) AS maxTable
        WHERE  cusid = maxTable.cusidmax
               AND total = max) AS BestCat
WHERE  category.category_id = BestCat.category_id 

DROP view IF EXISTS bestcatcusid;