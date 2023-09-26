UPDATE orderdetail
SET price = products.price/(1+(0.02*ROUND((DATE_PART('day', CURRENT_TIMESTAMP::timestamp - orders.orderdate::timestamp)/365)::numeric, 0)))
FROM products, orders
WHERE orderdetail.prod_id = products.prod_id AND orderdetail.orderid = orders.orderid;


