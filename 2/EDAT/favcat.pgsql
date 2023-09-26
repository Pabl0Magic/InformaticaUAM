-- Fav category
SELECT film_category.category_id
FROM rental, inventory, film, film_category
--
WHERE rental.customer_id = 2 -- NUMBER GOES HERE
--
AND inventory.inventory_id = rental.inventory_id
AND inventory.film_id = film.film_id
AND film_category.film_id = film.film_id
GROUP BY category_id
ORDER BY count(*) DESC LIMIT 1;

-- Recommended films
SELECT film.film_id, film.title, count(*) as num_rentals
FROM rental, inventory, film, film_category, category
WHERE inventory.inventory_id = rental.inventory_id
AND inventory.film_id = film.film_id
AND film_category.film_id = film.film_id
AND film_category.category_id = 15 -- NUMBER DE ARRIBA GOES HERE
AND category.category_id = film_category.category_id
AND film.film_id NOT IN (SELECT film.film_id  
FROM rental, inventory, film
WHERE rental.customer_id = 2
AND inventory.inventory_id = rental.inventory_id
AND inventory.film_id = film.film_id)
group by film.film_id
ORDER BY num_rentals DESC;