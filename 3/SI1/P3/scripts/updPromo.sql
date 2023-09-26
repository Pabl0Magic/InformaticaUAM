ALTER TABLE customers
ADD promo NUMERIC not null default 0;
ALTER TABLE customers
ADD CONSTRAINT CK_Table_Column_Range CHECK (
   promo >= 0 AND promo <= 100
);


CREATE OR REPLACE FUNCTION update_promo() 
   returns TRIGGER
   language plpgsql
   as 
   $$
   BEGIN
      PERFORM pg_sleep(10);
      UPDATE public.orders
      SET totalamount = (totalamount/((100-OLD.promo)/100)) * ((100-NEW.promo)/100)
      WHERE customerid = NEW.customerid AND status is NULL;

      RETURN NEW; 
   END;
   $$;
   

CREATE or replace TRIGGER updPromo after update
   OF promo
   ON public.customers
   for each row
   EXECUTE procedure update_promo();
