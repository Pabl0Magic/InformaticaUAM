# Version 1.2
# Modificacion
# 1) Las consultas 1 y 2 se han intercambiado para que sigan el mismo orden 
#    que en el enunciado de la práctica
# 2) se ha añadido la opción allqueries la cual ejecuta todas las consultas
# Por lo general no se requiere modificar el fichero

export PGDATABASE:=dvdrental
export PGUSER :=alumnodb
export PGPASSWORD :=alumnodb
export PGCLIENTENCODING:=LATIN9
export PGHOST:=localhost

DBNAME =$(PGDATABASE)
PSQL = psql
CREATEDB = createdb
DROPDB = dropdb --if-exists
PG_DUMP = pg_dump
PG_RESTORE = pg_restore

all: dropdb createdb restore
createdb:
	@echo Creando BBDD
	@$(CREATEDB)
dropdb:
	@echo Eliminando BBDD
	@$(DROPDB) $(DBNAME)
	rm -f *.log
dump:
	@echo creando dumpfile
	@$(PG_DUMP) > $(DBNAME).sql
restore:
	@echo restore data base
	@cat $(DBNAME).sql | $(PSQL)  
shell:
	@echo create psql shell
	@$(PSQL)  
newdatabase:
	@echo creando newdatabase
	@make all PGDATABASE=newdatabase

allqueries: query1 query2 query3 query4 query5 query6
	@cat query?.log > all_queries.log

query1:
	@echo query-1: "Films rented each year" | tee query1.log
	@cat query1.sql | $(PSQL) | tee -a query1.log
query2:
	@echo query-2: "Client who has rented more films" | tee query2.log
	@cat query2.sql | $(PSQL) | tee -a query2.log
query3:
	@echo query-3: "Cities where a film in which Bob Fawcett appears" | tee query3.log
	@cat query3.sql | $(PSQL) | tee -a query3.log
query4:
	@echo query-4: "4. Language in which most of the films have been filmed" | tee query4.log
	@cat query4.sql | $(PSQL) | tee -a query4.log
query5:
	@echo query-5: "5. Language of the films in which a greater number of rentals has been done" | tee query5.log
	@cat query5.sql | $(PSQL) | tee -a query5.log
query6:
	@echo query-6: "Favorite category of the customer who has rented more movies" | tee query6.log
	@cat query6.sql | $(PSQL) | tee -a query6.log

