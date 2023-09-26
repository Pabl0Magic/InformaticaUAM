# -*- coding: utf-8 -*-

import os
import sys, traceback, time

from sqlalchemy import create_engine
from pymongo import MongoClient

# configurar el motor de sqlalchemy
db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1P3", echo=False, execution_options={"autocommit":False})

# Crea la conexión con MongoDB
mongo_client = MongoClient()

def getMongoCollection(mongoDB_client):
    mongo_db = mongoDB_client.si1
    return mongo_db.topUK

def mongoDBCloseConnect(mongoDB_client):
    mongoDB_client.close();

def dbConnect():
    return db_engine.connect()

def dbCloseConnect(db_conn):
    db_conn.close()
  
def delState(state, bFallo, bSQL, duerme, bCommit):
    db_conn = dbConnect()

    
    # Array de trazas a mostrar en la página
    dbr=[]

    # TODO: Ejecutar consultas de borrado
    # - ordenar consultas según se desee provocar un error (bFallo True) o no
    # - ejecutar commit intermedio si bCommit es True
    # - usar sentencias SQL ('BEGIN', 'COMMIT', ...) si bSQL es True
    # - suspender la ejecución 'duerme' segundos en el punto adecuado para forzar deadlock
    # - ir guardando trazas mediante dbr.append()
    """ Orden correcto de borrado: orderdetail->orders->customers"""
    try:
        # TODO: ejecutar consultas
        if bFallo is True:
            dbr.append("Transaccion en orden incorrecto (orderdetail->customers->orders)  => fallo")

            beginresult = db_conn.execute("BEGIN;")
            dbr.append("Start transaction")

            #ORDERDETAIL
            resultordedetail = db_conn.execute("DELETE FROM orderdetail WHERE orderid in (SELECT orderid FROM orders WHERE status LIKE '" +str(state)+"');").rowcount
            dbr.append("Se han borrado "+str(resultordedetail)+" filas en la tabla orderdetail")
            dbr.append("Comprobar que no hay resultados")
            countordetresult = db_conn.execute("SELECT COUNT(*) FROM orderdetail WHERE orderid in (SELECT orderid FROM orders WHERE status LIKE '" +str(state)+"');").fetchone()
            dbr.append("No hay filas para "+str(countordetresult[0]))


            if bCommit is True:
                dbr.append("Commit intermedio")
                db_conn.execute("COMMIT;")
                db_conn.execute("BEGIN;")
                dbr.append("Continue transaction")

            #CUSTOMERS
            resultcustomers = db_conn.execute("DELETE FROM customers WHERE customerid in (SELECT customerid FROM orders WHERE status LIKE '"+str(state)+"');").rowcount
            dbr.append("Se han borrado "+str(resultcustomers)+" filas en la tabla customers")
            dbr.append("Comprobar que no hay resultados")
            countcustresult = db_conn.execute("SELECT COUNT(*) FROM customers WHERE customerid in (SELECT customerid FROM orders WHERE status LIKE '"+str(state)+"');").fetchone()
            dbr.append("No hay filas para "+str(countcustresult[0]))

            #ORDERS
            resultorders = db_conn.execute("DELETE FROM orders WHERE status LIKE '"+str(state)+"';").rowcount
            dbr.append("Se han borrado "+str(resultorders)+" filas en la tabla orders")
            dbr.append("Comprobar que no hay resultados")
            countordresult = db_conn.execute("SELECT COUNT(*) FROM orders WHERE status LIKE '"+str(state)+"';").fetchone()
            dbr.append("No hay filas para "+str(countordresult[0]))

            

        else:
            dbr.append("Transaccion en orden correcto (orderdetail->orders->customers)")

            beginresult = db_conn.execute("BEGIN;")
            dbr.append("Start transaction")

            #ORDERDETAIL
            resultordedetail = db_conn.execute("DELETE FROM orderdetail WHERE orderid in (SELECT orderid FROM orders WHERE status ='" +str(state)+"');").rowcount
            
            dbr.append("Comprobar que no hay resultados")
            countordetresult = db_conn.execute("SELECT COUNT(*) FROM orderdetail WHERE orderid in (SELECT orderid FROM orders WHERE status ='" +str(state)+"');").fetchone()
            dbr.append("No hay filas para "+str(countordetresult[0]))
            
            #ORDERS
            resultorders = db_conn.execute("DELETE FROM orders WHERE status ='"+str(state)+"';").rowcount
            dbr.append("Se han borrado "+str(resultorders)+" filas en la tabla orders")
            dbr.append("Comprobar que no hay resultados")
            countordresult = db_conn.execute("SELECT COUNT(*) FROM orders WHERE status ='"+str(state)+"';").fetchone()
            dbr.append("No hay filas para "+str(countordresult[0]))

            time.sleep(float(duerme))
            #CUSTOMERS
            resultcustomers = db_conn.execute("DELETE FROM customers WHERE customerid in (SELECT customerid FROM orders WHERE status ='"+str(state)+"');").rowcount
            dbr.append("Se han borrado "+str(resultcustomers)+" filas en la tabla customers")
            dbr.append("Comprobar que no hay resultados")
            countcustresult = db_conn.execute("SELECT COUNT(*) FROM customers WHERE customerid in (SELECT customerid FROM orders WHERE status ='"+str(state)+"');").fetchone()
            dbr.append("No hay filas para "+str(countcustresult[0]))
            
            
    except Exception as e:
        # TODO: deshacer en caso de error
        dbr.append("Ha ocurrido un error => Rollback")
        
        rollbackresult = db_conn.execute("ROLLBACK;")
        dbr.append("Comprobar que rollback funciona")
        countrollbackdetresult = db_conn.execute("SELECT COUNT(*) FROM orderdetail WHERE orderid in (SELECT orderid FROM orders WHERE status LIKE '" +str(state)+"');").fetchone()
        dbr.append("Vuelve a haber resultados en orderdetail para "+str(countrollbackdetresult[0]))

        countrollbackcustresult = db_conn.execute("SELECT COUNT(*) FROM customers WHERE customerid in (SELECT customerid FROM orders WHERE status LIKE '"+str(state)+"');").fetchone()
        dbr.append("Vuelve a haber resultados en customers para "+str(countrollbackcustresult[0]))

        countrollbackordresult = db_conn.execute("SELECT COUNT(*) FROM orders WHERE status LIKE '"+str(state)+"';").fetchone()
        dbr.append("Vuelve a haber resultados en orders para "+str(countrollbackordresult[0]))

    else:
        result = db_conn.execute("COMMIT;")
        dbCloseConnect(db_conn)
        
    return dbr

