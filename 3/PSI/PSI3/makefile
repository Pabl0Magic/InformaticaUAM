export DJANGOPORT := 8000
export DEBUG := True
# you must update the value of HEROKUHOST
export HEROKUHOST := git:remote protected-bastion-43256
PSQL = psql
CMD = python3 manage.py

HEROKU = heroku run export SQLITE=1 &
# Add applications to APP variable as they are
# added to settings.py file
APP = models 
#export DATABASE_URL = postgres://qgdzyaxe:xxxxxxxxxxxxxxxxxxxxxxxxxxxxxx@lucky.db.elephantsql.com/qgdzyaxe

## delete and create a new empty database
#clear_db:
#	@echo Clear Database
#	dropdb --if-exists $(PGDATABASE)
#	createdb

# create alumnodb super user
create_super_user:
	$(CMD) shell -c "from django.contrib.auth import get_user_model; User = get_user_model(); User.objects.create_superuser('alumnodb', 'admin@myproject.com', 'alumnodb')"

populate:
	@echo populate database
	python3 ./manage.py populate

runserver:
	$(CMD) runserver $(DJANGOPORT)

update_models:
	$(CMD) makemigrations $(APP)
	$(CMD) migrate

reset_db:
	sudo dropdb -U alumnodb -h localhost psi
	sudo createdb -U alumnodb -h localhost psi

#reset_db: clear_db update_models create_super_user

shell:
	@echo manage.py  shell
	@$(CMD) shell

dbshell:
	@echo manage.py dbshell
	@$(CMD) dbshell

addparticipants:
	@echo populate database
	python3 ./manage.py addparticipants



static:
	@echo manage.py collectstatic
	python3 ./manage.py collectstatic

fully_update_db:
	@echo del migrations and make migrations and migrate
	rm -rf */migrations
	python3 ./manage.py makemigrations $(APP) 
	python3 ./manage.py migrate

test_authentication:
	$(CMD) test models.tests.test_authentication --keepdb

test_model:
	$(CMD) test models.tests.test_models --keepdb

test_services:
	$(CMD) test create.tests.test_services --keepdb