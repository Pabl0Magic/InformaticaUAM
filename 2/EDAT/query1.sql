SELECT Count(*),
       Extract (year FROM rental_date) AS rental_year
FROM   rental
GROUP  BY rental_year; 
    


