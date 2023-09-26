set -o errexit

pip install -r requirements.txt

python3 manage.py makemigrations
python3 manage.py migrate

python3 manage.py createsuperuser

export DJANGO_SUPERUSER_PASSWORD=alumnodb
export DJANGO_SUPERUSER_USERNAME=alumnodb
export DJANGO_SUPERUSER_EMAIL=alumnodb@uam.es

# python3 populate_catalog.py
# python3 manage.py createsuperuser --noinput