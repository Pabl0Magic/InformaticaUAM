SELECT film.film_id, inventory_id
FROM film, inventory
WHERE film.film_id = 9 OR inventory.film_id = 9

SELECT customer_id
FROM customer
WHERE customer_id = 2

SELECT staff_id
FROM staff
WHERE staff_id = 2

SELECT store_id
FROM store
WHERE store_id = 2

INSERT INTO rental VALUES
(default, now(), 9, 3, NULL, 1, now())

INSERT INTO payment VALUES
(default, 2, 2, 145, 5.99, now())

SELECT MAX(rental_id) from rental