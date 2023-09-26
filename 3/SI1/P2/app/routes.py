#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from crypt import methods
from random import Random, randint, random

from sqlalchemy import true
from app import app, database
from flask import render_template, request, url_for, redirect, session
import json
import os
import sys
import hashlib
import shutil
from datetime import date
from app import database as db

@app.route('/', methods=['GET', 'POST'])
@app.route('/index', methods=['GET', 'POST'])
def index():
    """print (url_for('static', filename='estilo.css'), file=sys.stderr)
    if request.method=="POST":
        filter = request.form.get("filter") 
        cat = request.form.get("Categoria")

        catalogue_data = open(os.path.join(app.root_path,'catalogue/catalogue.json'), encoding="utf-8").read()
        catalogue = json.loads(catalogue_data)
        catalogue_filtered = [x for x in catalogue['peliculas'] if filter.lower() in  x['titulo'].lower()]
        if(cat!="Categoria" and cat!="Sin definir"):    
            catalogue_filtered = [x for x in catalogue_filtered if cat == x['categoria']]

        return render_template('index.html', title = "Home", movies=catalogue_filtered)
    
    
    catalogue_data = open(os.path.join(app.root_path,'catalogue/catalogue.json'), encoding="utf-8").read()
    catalogue_filtered = json.loads(catalogue_data)
    return render_template('index.html', title = "Home", movies=catalogue_filtered['peliculas'])"""

    if request.method=="POST":
        filter = request.form.get("filter") 
        cat = request.form.get("Categoria")
        print("A",filter, "A",cat,"A")
        moviesFiltered = db.db_getMovies(filter, cat)
    elif request.method == "GET":
        moviesFiltered = db.db_getMovies()

    
    print(moviesFiltered)
    return render_template('index.html', title = "Home", movies=moviesFiltered)

@app.route('/login', methods=['GET', 'POST'])
def login():
    """
    # doc sobre request object en http://flask.pocoo.org/docs/1.0/api/#incoming-request-data
    if 'username' in request.form:
        # aqui se deberia validar con fichero .dat del usuario
        username = request.form.get("username")
        pwd = request.form.get("password")
        dir = os.path.join(os.getcwd(), "app", "si1users")
        if username in os.listdir(dir):
            dir = os.path.join(dir, username, "userdata", "userdata")
            userdata = open(dir, "r").read()
            password = hashlib.md5()
            password.update(pwd.encode("utf-8"))
            codedPassword = str(password.hexdigest())
            if codedPassword in userdata:
                session['usuario'] = request.form['username']
                session.modified=True
                
                dir = os.path.join(app.root_path, "si1users", session['usuario'], "userdata",'carrito.json')
                if os.path.exists(dir):
                    f = open(dir, "r")
                    catalogue_data = f.read()
                    os.remove(dir)
                    carro = json.loads(catalogue_data)
                else:
                    carro = {}
                session['carrito'] = carro

                # se puede usar request.referrer para volver a la pagina desde la que se hizo login
                return redirect(url_for('index'))
            else:
                return render_template("login.html", notif="Contraseña o usuario incorrecto.")
        else:
            # aqui se le puede pasar como argumento un mensaje de login invalido
            return render_template('login.html', notif = "Contraseña o usuario incorrecto")
    else:
        # se puede guardar la pagina desde la que se invoca 
        session['url_origen']=request.referrer
        session.modified=True        
        # print a error.log de Apache si se ejecuta bajo mod_wsgi
        print (request.referrer, file=sys.stderr)
        session['logged_in']=True
        return render_template('login.html', title = "Sign In")
    """
    if 'username' in request.form:
        ret = database.db_login(request.form['username'], request.form['password'])
        if ret == "OK":
            session['usuario'] = request.form['username']
            session.modified=True
            # se puede usar request.referrer para volver a la pagina desde la que se hizo login
            return redirect(url_for('index'))
        else:
            return render_template("login.html", notif="Contraseña o usuario incorrecto.")
    else:
        # se puede guardar la pagina desde la que se invoca 
        session['url_origen']=request.referrer
        session.modified=True        
        # print a error.log de Apache si se ejecuta bajo mod_wsgi
        print (request.referrer, file=sys.stderr)
        session['logged_in']=True
        return render_template('login.html', title = "Sign In")


n_user = 0
@app.route('/register', methods=['GET', 'POST'])
def register():
    """
    if request.method == "GET":
        return render_template('register.html')
    
    elif request.method == "POST":
        parent=os.path.join(os.getcwd(), "app", "si1users")
        while not os.path.exists(parent):
            os.mkdir(parent)

        dir = str(request.form.get("username"))
        path = os.path.join(parent, dir)
        if(os.path.exists(path)):
            return render_template("register.html", notif="Usuario existente.")
        os.mkdir(path)
        
        data = "userdata"
        dataPath = os.path.join(path, data)
        os.mkdir(dataPath)
        f = open("userdata", "w")
        user = str(request.form.get("username"))
        password = str(request.form.get("pass"))
        codedPassword = hashlib.md5()
        codedPassword.update(password.encode("utf-8"))
        pwd = str(codedPassword.hexdigest())

        email = str(request.form.get("email"))
        tarjeta = str(request.form.get("tarjeta"))
        randomNum = randint(0,50)
        saldo = float(randomNum)
        f.write("Username: "+user+"\nPassword: "+pwd+"\nEmail: "+email+"\nCredit card: "+tarjeta+"\nSaldo: "+ str(saldo))

        shutil.move(os.getcwd()+"/userdata", path+"/userdata")

        # se puede guardar la pagina desde la que se invoca 
        session['url_origen']=request.referrer
        session.modified=True        
        # print a error.log de Apache si se ejecuta bajo mod_wsgi
        print (request.referrer, file=sys.stderr)
        return redirect('/login')
    """
    if request.method == "GET":
        return render_template('register.html')
    
    elif request.method == "POST":
        if 'username' in request.form:
            ret = database.db_register(request.form['username'], request.form['pass'], request.form['email'], request.form['tarjeta'], request.form['direccion'])

            if ret == "Something is broken" or ret == "User already registered":
                return render_template('register.html', notif = ret)
            
            return redirect('/login')
        else:
            # se puede guardar la pagina desde la que se invoca 
            session['url_origen']=request.referrer
            session.modified=True        
            # print a error.log de Apache si se ejecuta bajo mod_wsgi
            print (request.referrer, file=sys.stderr)
            return render_template('register.html')


@app.route('/logout', methods=['GET', 'POST'])
def logout():
    session.pop('usuario', None)
    session['logged_in']=False
    return redirect(url_for('index'))

@app.route('/details', methods=['GET', 'POST'])
def details():
    film=None
    """catalogue_data = open(os.path.join(app.root_path,'catalogue', 'catalogue.json'), encoding="utf-8").read()
    catalogue = json.loads(catalogue_data)
    if request.method == 'GET':
        if(len(request.args)==0):
            return render_template("index.html", notif="Error cargando detalles.")
        film_id = request.args['id_pelicula']
        for x in catalogue['peliculas']:
            if int(film_id) ==  int(x['id']):
                film = x
                break
        

    if request.method == 'POST':
        film_id = request.args['id_pelicula']
        for x in catalogue['peliculas']:
            if int(film_id) == int(x['id']):
                old_val = int(x['valMedia'])
                nVal = int(x['nVal'])
                film = x
                nVal += 1
                val = int(request.form.get("valoracion"))
                val_media = ((old_val*(nVal-1)) + val)/nVal
                x["nVal"] = nVal
                x["valMedia"] = val_media
                cat_dir = os.path.join(app.root_path, 'catalogue', 'catalogue.json')
                with open(cat_dir, "w") as f:
                    json.dump(catalogue, f, indent=4, sort_keys=True)
                return render_template('details.html', film=film)
        
        return render_template("index.html", notif="Pelicula no encontrada")
        
    if film is None:
        return render_template("index.html", notif="Pelicula no encontrada")
    return render_template('details.html', film=film)"""

    if request.method == 'GET':
        if(len(request.args)==0):
            return render_template("index.html", notif="Error cargando detalles.")
        film_id = request.args['id_pelicula']
        film = db.db_getMovies(id=film_id)[0]
        if not film:
            return render_template("index.html", notif="Pelicula no encontrada") 

        film_dict = {"id":film[0],
                    "titulo": film[1], 
                    "director":"",
                    "categoria":[],
                    "año": film[4],
                    "actores":[],
                    "valMedia":film[6],
                    "nVal":film[7],
                    "precio":""}
        return render_template("details.html", film=film_dict)
    
    elif request.method=='POST':
        if session["logged_in"]:
            user = db.db_getUser(session['usuario'])
            userid = user[0]
            movieid = request.args['id_pelicula']
            val = int(request.form.get("valoracion"))
            db.db_rateMovie(userid, movieid, val)
            film = db.db_getMovies(id=movieid)[0]
            film_dict = {"id":film[0],
                    "titulo": film[1], 
                    "director":"",
                    "categoria":[],
                    "año": film[4],
                    "actores":[],
                    "valMedia":film[6],
                    "nVal":film[7],
                    "precio":""}
            return render_template("details.html", film=film_dict)
        else:
            return render_template("index.html", notif="Necesitas estar logeado para valorar una pelicula.")

    
@app.route('/buscar', methods=['GET'])
def buscar():
    return render_template('buscar.html', title = "Buscar")

@app.route('/comprar', methods=['POST'])
def comprar():
    if session["logged_in"]:
        catalogue_data = open(os.path.join(app.root_path,'catalogue/catalogue.json'), encoding="utf-8").read()
        catalogue = json.loads(catalogue_data)
        film = None
        film_id = request.args['id_pelicula']
        cantidad = int(request.form.get("cantidad"))

        for x in catalogue['peliculas']:
            if int(film_id) == int(x['id']):
                film = x
                break
        if film==None:
            return render_template("index.html", notif="Error comprando película.")

        dir = os.path.join(app.root_path, "si1users", session['usuario'], "userdata", "userdata")
        f = open(dir, "r")
        userdata = f.readlines()
        saldo = userdata[4].split(": ")[1]
        if float(saldo) >= float(film['precio'])*float(cantidad):           
            if "carrito" not in session:
                session["carrito"]={str(film_id): cantidad}
            elif str(film_id) not in session["carrito"]:
                session["carrito"][str(film_id)] = cantidad
            else:              
                val = int(session["carrito"][str(film_id)])
                val += int(cantidad)
                session["carrito"][str(film_id)] = val            
            return render_template("index.html", notif="Elementos añadidos al carrito.")
        else:
            return render_template("index.html", notif="Saldo insuficiente.")
                 
    else:
        return render_template("index.html", notif="Compras disponibles para usuarios logueados.")

def getPago(catalogue):
    pago = 0
    for item in session['carrito']:
        pago += catalogue[item['id']]['precio'] * item['cantidad']

    return float("{0:.2f".format(pago))

def checkItemCarrito(articulos, val1, val2):
    for index, value in enumerate(articulos):
        if value[val1] ==val2:
            return index
    return -1


def get_film_from_ids(ids:dict):
    ret=[]
    catalogue_data = open(os.path.join(app.root_path,'catalogue/catalogue.json'), encoding="utf-8").read()
    catalogue = json.loads(catalogue_data)
    
    for film in catalogue['peliculas']:
        if str(film['id']) in ids:
            ret.append(film)
    return ret


@app.route('/carrito', methods=['GET', 'POST'])
def carrito():
    if not session['logged_in']:
        return render_template("index.html", notif="Inicia sesion para ver tu carrito")

    if "carrito" not in session:
        cart_ids=[]
    else:
        cart_ids=session["carrito"]

    catalogue_data = open(os.path.join(app.root_path,'catalogue/catalogue.json'), encoding="utf-8").read()
    catalogue = json.loads(catalogue_data)
    
    data={}
    coste = 0.0
    for x in catalogue['peliculas']:
        if str(x['id']) in cart_ids: 
            data[str(x['id'])] = {'data': x, 'cant': cart_ids[str(x['id'])]}
            coste += float(x['precio'])*float(cart_ids[str(x['id'])])
            
    dir = os.path.join(os.getcwd(), "app", "si1users")
    if request.method == 'POST':
        if len(session['carrito'].keys()) < 1:
            return render_template("index.html", notif="Añade items al carrito antes.")
        if "elcarro" in request.form:
            if request.form['elcarro'] == 'comprar':           
                return finalizar_compra(request=request, coste=coste, films=data)
        elif "removeall" in request.form:    
            if request.form['removeall'] == 'removeall':
                session.pop("carrito", None)
                return render_template("index.html", notif="Carrito vaciado con exito.")

        else:
            return render_template("index.html", notif="Error Acceciendo al carrito.")
    elif request.method=='GET':
        return render_template('carrito.html', films=data, costetotal=coste)
            
def finalizar_compra(request, coste, films):
    dir = os.path.join(app.root_path, "si1users", session['usuario'], "userdata", "userdata")
    f = open(dir, "r")
    userdata = f.readlines()
    saldo = userdata[4].split(": ")[1]

    if coste>float((saldo)):
        return render_template("carrito.html", notif="No tienes suficiente saldo.")
    nuevosaldo = float(saldo) - coste
    userdata[4] = "Saldo: {}".format(str(nuevosaldo))
    f.close()
    f = open(dir, "w")
    f.writelines(userdata)
    f.close()

    today = date.today()
    strToday = today.strftime("%d/%m/%Y")
    dir_history = os.path.join(app.root_path, "si1users", session['usuario'], "userdata", 'compras.json')
    if not os.path.exists(dir_history):
        history={"compras": [], "saldo": nuevosaldo}
    else:
        history=json.loads(open(dir_history, "r").read())

    history["compras"].append({"precio": coste, "fecha":strToday, "articulos": session['carrito']})                
    with open(dir_history, "w") as f:
        json.dump(history, f, indent=4, sort_keys=True)

    session.pop("carrito",None)

    return render_template("index.html", notif="Compra realizada con exito")







"""if session['usuario']:
                userPath = os.path.join(dir, '%s'%session['usuario'])
                userData = open(os.path.join(userPath, 'userdata'), "r")
                data = userData.readlines()
                saldo = float(data[4])
                userData.close()
                
                pago = getPago(catalogue['peliculas'])
                if pago > saldo:
                    mes = "No hay suficiente saldo"
                else:
                    userData = open(os.path.join(userPath, 'userdata'), "w")
                    for line in data[:-1]:
                        userData.write(line)
                    saldo -= pago
                    userData.write("%.2f"%saldo + "\n")
                    userData.close()
                    
                    historyData = open(os.path.join(userPath, 'compras.json'), encoding='utf-8').read()
                    history = json.loads(historyData)
                    today = date.today()
                    strToday = today.strftime("%d/%m/%Y")
                    jsonData = {"precio": pago, "fecha":strToday, "articulos":session['carrito']}
                    if len(history) < 1:
                        history[0] = jsonData
                    else:
                        lastKey = int(sorted(list(history.keys()))[-1])+1
                        history[str(lastKey)] = jsonData

                    with open(os.path.join(userPath, 'compras.json'), "w") as write:
                        json.dump(history, write, indent=4, sort_keys=True)
                    mes = "¡Hecho! Te quedan %.2f"%saldo
            else:
                mes = "Inicia sesion para comprar"""