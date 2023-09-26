#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from app import app
from app import database as db
from flask import render_template, request, url_for
import os
import sys
import time

import pymongo

@app.route('/', methods=['POST','GET'])
@app.route('/index', methods=['POST','GET'])
def index():
    return render_template('index.html')


@app.route('/borraEstado', methods=['POST','GET'])
def borraEstado():
    if 'state' in request.form:
        state    = request.form["state"]
        bSQL    = request.form["txnSQL"]
        bCommit = "bCommit" in request.form
        bFallo  = "bFallo"  in request.form
        duerme  = request.form["duerme"]
        dbr = db.delState(state, bFallo, bSQL=='1', int(duerme), bCommit)
        return render_template('borraEstado.html', dbr=dbr)
    else:
        return render_template('borraEstado.html')

    
@app.route('/topUK', methods=['POST','GET'])
def topUK():
    movies=[[],[],[]]
    client = pymongo.MongoClient(host="localhost", port=27017)
    coll = db.getMongoCollection(client)
    
    movies[0] = coll.find({"year" : { "$gte" :  "1990", "$lte" : "1992"}, "genres": "Comedy"})
    movies[1] = coll.find({"$or":[{"year":"1995"}, {"year":"1997"}, {"year":"1998"}], "title": {"$regex" : ", The"}})
    movies[2] = coll.find({"$and":[{"actors": {"$regex" : "Lockett, Katie"}}, {"actors": {"$regex" : "McAree, Darren"}}]})
    
    return render_template('topUK.html', movies=movies)