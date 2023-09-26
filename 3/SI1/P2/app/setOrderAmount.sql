CREATE OR REPLACE procedure setOrderAmount()
LANGUAGE plpgsql
AS $$ 
BEGIN
    UPDATE orders AS ord SET 
    netamount = aux.total_price, 
    totalamount = round(aux.total_price*(1+(tax/100)), 2)
    FROM (
        SELECT orderid, SUM(price) AS total_price 
        FROM orderdetail 
        GROUP BY orderid) as aux
    WHERE ord.orderid = aux.orderid ;
END;
$$;

call setOrderAmount();