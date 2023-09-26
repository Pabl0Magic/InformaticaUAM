DROP INDEX IF EXISTS ordersindex;
CREATE INDEX ordersindex ON orders(status);

analyze orders;

explain select count(*)
from orders
where status is null;

explain select count(*)
from orders
where status ='Shipped';

explain select count(*)
from orders
where status ='Paid';

explain select count(*)
from orders
where status ='Processed';