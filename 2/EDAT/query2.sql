SELECT customer.customer_id,
       customer.first_name,
       customer.last_name,
       Count(*)
FROM   customer,
       rental
WHERE  customer.customer_id = rental.customer_id
GROUP  BY customer.customer_id
HAVING Count(*) IN (SELECT Count(*)
                    FROM   rental
                    GROUP  BY customer_id
                    ORDER  BY Count(*) DESC
                    LIMIT  1); 