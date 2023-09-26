# -*- coding: utf-8 -*-

import os
import sys, traceback
from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, text
from sqlalchemy.sql import select

# configurar el motor de sqlalchemy
db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1", echo=False)
db_meta = MetaData(bind=db_engine)

# cargar una tabla
db_table_movies = Table('imdb_movies', db_meta, autoload=True, autoload_with=db_engine)

def db_exception(db_conn):
    if db_conn is not None:
            db_conn.close()
    print("Exception in DB access:")
    print("-"*60)
    traceback.print_exc(file=sys.stderr)
    print("-"*60)

    return 'Something is broken'

"""def db_listOfMovies1949():
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        # Seleccionar las peliculas del anno 1949
        #db_movies_1949 = select([db_table_movies]).where(text("year = '1949'"))
        #db_result = db_conn.execute(db_movies_1949)
        db_result = db_conn.execute("Select * from imdb_movies where year = '1949'")
        
        db_conn.close()
        
        return  list(db_result)
    except:
        if db_conn is not None:
            db_conn.close()
        print("Exception in DB access:")
        print("-"*60)
        traceback.print_exc(file=sys.stderr)
        print("-"*60)

        return 'Something is broken'"""

def db_register(user, password, email, tarjeta, direccion):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()

        # cargar una tabla
        db_table_customers = Table('customers', db_meta, autoload=True, autoload_with=db_engine)

        # Comprobar que no existe ese usuario
        cust_exists = select([db_table_customers]).where(text("username = '%s'"%user))
        db_result = db_conn.execute(cust_exists)

        #Utilizar el ultimo customer_id
        cust_id = db_conn.execute("SELECT max(customerid) AS num FROM customers")
        cust_id_list = cust_id.fetchall()
        

        if len(list(db_result)) == 0:
             db_insert_result = db_conn.execute(db_table_customers.insert(), customerid = (cust_id_list[0].num) + 1, username = user, password = password, email = email, creditcard = tarjeta, address = direccion)
        else:
            db_conn.close()
            return "User already registered"

        db_conn.close()
        return db_insert_result

    except:
        return db_exception(db_conn)

def db_login(user, password):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()

        # cargar una tabla
        db_table_customers = Table('customers', db_meta, autoload=True, autoload_with=db_engine)

        # Comprobar que existe el usuario
        find_user = select([db_table_customers]).where(text("username = '%s'"%user))
        db_result = db_conn.execute(find_user)

        if len(list(db_result)) == 0:
            db_conn.close()
            return "User not registered"

        get_password = db_conn.execute("SELECT password FROM customers WHERE username = '"+ user + "'")
        get_password_list = get_password.fetchall()       

        if get_password_list[0].password == password:
            db_conn.close()
            return "OK"
        else:
            db_conn.close()
            return "Password Incorrect"
    
    except:
        return db_exception(db_conn)

    


def db_getMovies(nameFilter="", catFilter=None, id=None):
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()
        
        catBool = catFilter and catFilter != "Sin definir" and catFilter != "Categoria"
        nameBool = nameFilter and nameFilter != ""

        stmnt = "Select * from imdb_movies"
        if nameBool or catBool or id:
            stmnt = stmnt + " where"
            if id:
                stmnt = stmnt + " movieid = "+str(id)
            if nameBool:
                stmnt = stmnt + " movietitle like '%%"+nameFilter+"%%'"
            if nameBool and catBool:
                stmnt = stmnt + " and"
            if catBool:
                stmnt = stmnt + " movieid in (select movieid from imdb_moviegenres where genre = '"+catFilter+"')"
        stmnt = stmnt + " order by movietitle limit 5"
        
        print(stmnt)
        db_result = db_conn.execute(stmnt)
        db_conn.close()
        return  list(db_result)
    except:
        db_exception(db_conn)

def db_getUser(username=None):
    if username:
        try:
            # conexion a la base de datos
            db_conn = None
            db_conn = db_engine.connect()
            
            stmnt = "Select * from customers where username = '"+username+"'"

            db_result = db_conn.execute(stmnt)
            db_conn.close()
            return  list(db_result)[0]
        except:
            db_exception(db_conn)

def db_rateMovie(userid, movieid, rating):
    if userid and movieid and rating:
        try:
            # conexion a la base de datos
            db_conn = None
            db_conn = db_engine.connect()
            
            stmnt = "Select * from ratings where customerid = "+str(userid)+" and movieid = "+str(movieid)
            db_result = db_conn.execute(stmnt)
            if len(list(db_result)) > 0:
                stmnt = "update ratings set rating = "+str(rating)+" where movieid = "+str(movieid)+" and customerid = "+str(userid)
                db_result = db_conn.execute(stmnt)
            else:
                stmnt = "insert into ratings values ("+str(userid)+", "+str(movieid)+", "+str(rating)+")"
                db_result = db_conn.execute(stmnt)

            db_conn.close()
            return  list(db_result)
        except:
            db_exception(db_conn)