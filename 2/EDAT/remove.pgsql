DELETE FROM payment
USING (SELECT rental.rental_id FROM rental, inventory
WHERE inventory.film_id = 1 
AND rental.inventory_id = inventory.inventory_id
) as t2 WHERE payment.rental_id = t2.rental_id;

DELETE FROM rental
USING (SELECT inventory_id
FROM inventory
WHERE inventory.film_id = 1
) as t2 WHERE rental.inventory_id = t2.inventory_id;

DELETE FROM inventory WHERE film_id = 1;
DELETE FROM film_actor WHERE film_id = 1;
DELETE FROM film_category WHERE film_id = 1;
DELETE FROM film WHERE film_id = 1;
