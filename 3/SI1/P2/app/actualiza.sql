create or replace function setCustomersBalance(IN initialBalance bigint)
returns void
language plpgsql
as $$
BEGIN
    update public.customers set
    balance = floor(random() * initialBalance);
end;
$$;

ALTER TABLE public.customers
    ADD balance double precision;

select setCustomersBalance(100);


CREATE TABLE public.ratings (
    customerid integer not null,
    movieid integer not null,
    rating integer
);

ALTER TABLE ONLY public.ratings
    drop CONSTRAINT if exists ratings_customerid_fkey,
    ADD CONSTRAINT ratings_customerid_fkey FOREIGN KEY (customerid) 
    REFERENCES public.customers(customerid)
    ON UPDATE NO ACTION ON DELETE CASCADE,
    drop CONSTRAINT if exists ratings_movieid_fkey,
    ADD CONSTRAINT ratings_movieid_fkey FOREIGN KEY (movieid) 
    REFERENCES public.imdb_movies(movieid)
    ON UPDATE NO ACTION ON DELETE CASCADE,
    drop CONSTRAINT if exists ratings_pkey,
    ADD CONSTRAINT ratings_pkey primary key (customerid, movieid);


ALTER TABLE public.imdb_movies
    add ratingmean float default 0,
    add ratingcount integer default 0;


ALTER TABLE public.customers
    ALTER COLUMN password TYPE varchar(90);


ALTER TABLE public.imdb_moviecountries
    drop constraint if exists imdb_moviecountries_pkey,
    add CONSTRAINT imdb_moviecountries_pkey primary key (movieid, country);


ALTER TABLE public.imdb_moviegenres
    drop constraint if exists imdb_moviegenres_pkey,
    add constraint imdb_moviegenres_pkey primary key (movieid, genre);


ALTER TABLE public.imdb_movielanguages
    drop constraint if exists imdb_movielanguages_pkey,
    add constraint imdb_movielanguages_pkey primary key (movieid, language);


ALTER TABLE public.orderdetail
    drop constraint if exists orderdetail_orderid_fkey,
    add constraint orderdetail_orderid_fkey FOREIGN key (orderid)
    REFERENCES public.orders (orderid)
    ON UPDATE NO ACTION ON DELETE CASCADE,
    drop constraint if exists orderdetail_prodid_fkey,
    add constraint orderdetail_prodid_fkey FOREIGN key (prod_id)
    REFERENCES public.products (prod_id)
    ON UPDATE NO ACTION ON DELETE CASCADE;


ALTER TABLE public.imdb_actormovies
    drop constraint if exists actormovies_pkey,
    add constraint actormovies_pkey primary key (actorid, movieid, character),
    drop constraint if exists actormovies_actorid_fkey,
    add constraint actormovies_actorid_fkey FOREIGN key (actorid)
    REFERENCES public.imdb_actors (actorid)
    ON UPDATE NO ACTION ON DELETE CASCADE,
    drop constraint if exists actormovies_movieid_fkey,
    add constraint actormovies_movieid_fkey FOREIGN key (movieid)
    REFERENCES public.imdb_movies (movieid)
    ON UPDATE NO ACTION ON DELETE CASCADE;


ALTER TABLE public.inventory
    drop constraint if exists inventory_prodid_fkey,
    add constraint inventory_prodid_fkey FOREIGN key (prod_id)
    REFERENCES public.products (prod_id)
    ON UPDATE NO ACTION ON DELETE CASCADE;

CREATE OR REPLACE FUNCTION update_orders() 
    returns TRIGGER
    language plpgsql
    as 
    $$
    BEGIN
        if TG_OP = 'INSERT' then 
            update orders
                set netamount = netamount + (NEW.quantity * NEW.price),
                totalamount = totalamount + (NEW.quantity * NEW.price * (1 + (tax / 100)))
                where orderid = NEW.orderid;
            return NEW;

        elsif TG_OP = 'UPDATE' then
            update orders
                set netamount = netamount + ((NEW.quantity - OLD.quantity) * NEW.price),
                totalamount = totalamount + ((NEW.quantity - OLD.quantity) * NEW.price * (1 + (tax / 100)))
                where orderid = NEW.orderid;
            return NEW;

        elsif TG_OP = 'DELETE' then 
            update orders
                set netamount = netamount - (OLD.quantity * OLD.price),
                totalamount = totalamount - (OLD.quantity * OLD.price * (1 + (tax / 100)))
                where orderid = OLD.orderid;
            return OLD;
        end if;
    END;
    $$;

CREATE or replace TRIGGER updOrders after insert or update or delete
    ON public.orderdetail
    for each row
    EXECUTE procedure update_orders ();


CREATE OR REPLACE FUNCTION update_rating() 
    returns TRIGGER
    language plpgsql
    as 
    $$
    BEGIN
        if TG_OP = 'INSERT' then 
            UPDATE public.imdb_movies
                SET 
                    ratingmean = ((ratingmean*ratingcount) + NEW.rating) / (ratingcount + 1),
                    ratingcount = ratingcount + 1
                    where movieid = NEW.movieid;
            return NEW;

        elsif TG_OP = 'UPDATE' then
            UPDATE public.imdb_movies
                SET ratingmean = ((ratingmean*ratingcount) - OLD.rating + NEW.rating) / (ratingcount)
                where movieid = NEW.movieid;
            return NEW;

        elsif TG_OP = 'DELETE' then
            UPDATE public.imdb_movies
                SET ratingmean = ((ratingmean*ratingcount) - OLD.rating) / (ratingcount - 1),
                ratingcount = ratingcount - 1
                where movieid = NEW.movieid;
            return OLD;
        end if;
    
    END;
    $$;

CREATE or replace TRIGGER updRatings after insert or update or delete
    ON public.ratings
    for each row
    EXECUTE procedure update_rating ();

CREATE OR REPLACE FUNCTION update_inventory() 
    returns TRIGGER
    language plpgsql
    as 
    $$
    BEGIN
    if NEW.status = 'Paid' and OLD.status != 'Paid' then
        UPDATE public.inventory
        SET 
            sales = sales + aux.quantity,
            stock = stock - aux.quantity
        FROM (
            SELECT prod_id, quantity
            FROM orderdetail
            WHERE orderid = NEW.orderid
        ) AS aux
        WHERE aux.prod_id = inventory.prod_id;

        UPDATE public.customers
        SET 
            balance = balance - NEW.totalamount
        WHERE customerid = NEW.customerid;
    end if;
    return NEW;
    END;
    $$;

CREATE or replace TRIGGER updInventoryAndCustomer after update
    ON public.orders
    for each row
    EXECUTE procedure update_inventory ();
