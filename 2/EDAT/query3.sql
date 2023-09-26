SELECT DISTINCT city.city_id,
                city.city
FROM   city,
       address,
       customer,
       rental,
       inventory,
       film_actor,
       actor
WHERE  city.city_id = address.city_id
       AND address.address_id = customer.address_id
       AND customer.customer_id = rental.customer_id
       AND rental.inventory_id = inventory.inventory_id
       AND inventory.film_id = film_actor.film_id
       AND film_actor.actor_id = actor.actor_id
       AND actor.first_name = 'Bob'
       AND actor.last_name = 'Fawcett'
ORDER  BY city.city ASC;