DROP INDEX IF EXISTS customersindex;
DROP INDEX IF EXISTS ordersindex;
CREATE INDEX customersindex ON customers(country);
CREATE INDEX ordersindex ON orders(extract(year from orderdate));

explain analyse SELECT (COUNT(DISTINCT(status)) + COUNT(DISTINCT CASE WHEN status IS NULL THEN 1 END)) as result
from orders, customers 
where country = 'Iran' and 
    EXTRACT(YEAR FROM orderdate) = '2021' and
    orders.customerid = customers.customerid