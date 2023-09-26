#!/usr/bin/python
'''
    practica3.py
    Programa principal que realiza el análisis de tráfico sobre una traza PCAP.
    Autor: Javier Ramos <javier.ramos@uam.es>
    2020 EPS-UAM
'''


import sys
import argparse
from argparse import RawTextHelpFormatter
import time
import logging
import shlex
import subprocess
import pandas as pd
from io import StringIO
import os
import warnings
warnings.filterwarnings("ignore")
import matplotlib.pyplot as plt
import matplotlib.ticker as mtick

'''
    Función: calcularECDF
    Entrada: 
        -datos: lista con los datos sobre los que calcular la ECDF
    Salida: :
        -datos: lista con los valores x (datos de entrada)
        -y: lista con los valores de probabilidad acumulada para cada dato de entrada
    Descripción:  Esta función recibe una lista de datos y calcula la función empírica de distribución 
    acumulada sobre los mismos. Los datos se devuelven listos para ser pintados.
'''
def calcularECDF(datos):
    datos.sort()
    n = len (datos)
    y = [(i-1)/n for i in range(1,n+1)]

    return datos,y



'''
    Función: ejecutarComandoObtenerSalida
    Entrada: 
        -comando: cadena de caracteres con el comando a ejecutar
    Salida: 
        -codigo_retorno: código numérico que indica el retorno del comando ejecutado.
        Si este valor es 0, entonces el comando ha ejecutado correctamente.
        -salida_retorno: cadena de caracteres con el retorno del comando. Este retorno
        es el mismo que obtendríamos por stdout al ejecutar un comando de terminal.

    Descripción: Esta función recibe una cadena con un comando a ejecutar, lo ejecuta y retorna
    tanto el código de resultado de la ejecución como la salida que el comando produzca por stdout
'''
def ejecutarComandoObtenerSalida(comando):
    proceso = subprocess.Popen(shlex.split(comando), stdout=subprocess.PIPE)
    salida_retorno = ''
    while True:
        
        salida_parcial = proceso.stdout.readline()
        if salida_parcial.decode() == '' and proceso.poll() is not None:
            break
        if salida_parcial:
            salida_retorno += salida_parcial.decode()
    codigo_retorno = proceso.poll()
    return codigo_retorno,salida_retorno


'''
    Función: pintarECDF
    Entrada:
        -datos: lista con los datos que se usarán para calcular y pintar la ECDF
        -nombre_fichero: cadena de caracteres con el nombre del fichero donde se guardará la imagen
        (por ejemplo figura.png)
        -titulo: cadena de caracteres con el título a pintar en la gráfica
        -titulo_x: cadena de caracteres con la etiqueta a usar para el eje X de la gráfica
        -titulo_y: cadena de caracteres con la etiqueta a usar para el eje Y de la gráfica
    Salida: 
        -Nada

    Descripción: Esta función pinta una gráfica ECDF para unos datos de entrada y la guarda en una imagen
'''
def pintarECDF(datos,nombre_fichero,titulo,titulo_x,titulo_y):
    
    x, y = calcularECDF(datos)
    x.append(x[-1])
    y.append(1) 
    fig1, ax1 = plt.subplots()
    plt.step(x, y, '-')
    _ = plt.xticks(rotation=45)
    plt.title(titulo)
    fig1.set_size_inches(12, 10)
    plt.tight_layout()
    plt.locator_params(nbins=20)
    ax1.set_xlabel(titulo_x)
    ax1.set_ylabel(titulo_y)
    plt.savefig(nombre_fichero, bbox_inches='tight')


'''
    Función: pintarSerieTemporal
    Entrada:
        -x: lista de tiempos en formato epoch y granularidad segundos
        -y: lista con los valores a graficar
        -nombre_fichero: cadena de caracteres con el nombre del fichero donde se guardará la imagen
        (por ejemplo figura.png)
        -titulo: cadena de caracteres con el título a pintar en la gráfica
        -titulo_x: cadena de caracteres con la etiqueta a usar para el eje X de la gráfica
        -titulo_y: cadena de caracteres con la etiqueta a usar para el eje Y de la gráfica
    Salida: 
        -Nada

    Descripción: Esta función pinta una serie temporal dados unos datos x e y de entrada y la guarda en una imagen
'''
def pintarSerieTemporal(x,y,nombre_fichero,titulo,titulo_x,titulo_y):
   
    fig1, ax1 = plt.subplots()
    plt.plot(x, y, '-')
    _ = plt.xticks(rotation=45)
    plt.title(titulo)
    fig1.set_size_inches(12, 10)
    plt.gcf().autofmt_xdate()
    plt.gca().xaxis.set_major_locator(mtick.FixedLocator(x))
    plt.gca().xaxis.set_major_formatter(mtick.FuncFormatter(lambda pos,_: time.strftime("%d-%m-%Y %H:%M:%S",time.localtime(pos))))
    plt.tight_layout()
    plt.locator_params(nbins=20)
    ax1.set_xlabel(titulo_x)
    ax1.set_ylabel(titulo_y)
    plt.savefig(nombre_fichero, bbox_inches='tight')


'''
    Función: pintarTarta
    Entrada:
        -etiquetas: lista con cadenas de caracteres que contienen las etiquetas a usar en el gráfico de tarta
        -valores: lista con los valores a graficar
        -nombre_fichero: cadena de caracteres con el nombre del fichero donde se guardará la imagen
        (por ejemplo figura.png)
        -titulo: cadena de caracteres con el título a pintar en la gráfica
        
    Salida: 
        -Nada

    Descripción: Esta función pinta un gráfico de tarta dadas unas etiquetas y valores de entrada y lo guarda en una imagen
'''
def pintarTarta(etiquetas,valores,nombre_fichero,titulo):
  
    explode = tuple([0.05]*(len(etiquetas)))
 
    fig1, ax1 = plt.subplots()
    plt.pie(valores, autopct='%1.1f%%', startangle=90, pctdistance=0.85)
    plt.legend(etiquetas, loc="best")
    plt.title(titulo)
    centre_circle = plt.Circle((0,0),0.70,fc='white')
    fig1 = plt.gcf()
    fig1.gca().add_artist(centre_circle)
    fig1.set_size_inches(12, 10)
    ax1.axis('equal')  
    plt.tight_layout()
    plt.savefig(nombre_fichero, bbox_inches='tight')

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Programa principal que realiza el análisis de tráfico sobre una traza PCAP',
    formatter_class=RawTextHelpFormatter)
    parser.add_argument('--trace', dest='tracefile', default=False,help='Fichero de traza a usar',required=True)
    parser.add_argument('--mac', dest='mac', default=False,help='MAC usada para filtrar',required=True)
    parser.add_argument('--ip_flujo_tcp', dest='ip_flujo_tcp', default=False,help='IP para filtrar por el flujo TCP',required=True)
    parser.add_argument('--port_flujo_udp', dest='port_flujo_udp', default=False,help='Puerto para filtrar por el flujo UDP',required=True)
    parser.add_argument('--debug', dest='debug', default=False, action='store_true',help='Activar Debug messages')
    args = parser.parse_args()

    if args.debug:
        logging.basicConfig(level = logging.DEBUG, format = '[%(asctime)s %(levelname)s]\t%(message)s')
    else:
        logging.basicConfig(level = logging.INFO, format = '[%(asctime)s %(levelname)s]\t%(message)s')

    #Creamos un directorio a donde volcaremos los resultado e imágenes

    if not os.path.isdir('resultados'):
        os.mkdir('resultados')
  
    #Ejemplo de ejecución de comando tshark y parseo de salida. Se parte toda la salida en líneas usando el separador \n
    logging.info('Ejecutando tshark para obtener el número de paquetes')
    codigo,salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.number'.format(args.tracefile))
    nlineas = 0
    for linea in salida.split('\n'):
        if linea != '':
            print(linea)
            nlineas +=1

    print('{} paquetes en la traza {}'.format(nlineas,args.tracefile))
    

    #Analisis de protocolos
    #TODO: Añadir código para obtener el porcentaje de tráfico IPv4 y NO-IPv4
    logging.info('Ejecutando tshark para obtener el trafico IPv4')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.number eth.type == 0x0800'.format(args.tracefile))
    nlineasIP = 0
    for linea in salida.split('\n'):
        if linea != '':
            #print(linea)
            nlineasIP+=1
    porcentajeIP = (nlineasIP/nlineas)*100
    print(porcentajeIP)
    logging.info('Ejecutando tshark para obtener el trafico NO IPv4')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.number !(eth.type == 0x0800)'.format(args.tracefile))
    nlineasNOIP = 0
    for linea in salida.split('\n'):
        if linea != '':
            #print(linea)
            nlineasNOIP+=1
    porcentajeNOIP = (nlineasNOIP/nlineas)*100
    print(porcentajeNOIP)
    #TODO: Añadir código para obtener el porcentaje de tráfico TCP,UDP y OTROS sobre el tráfico IP
    logging.info('Ejecutando tshark para obtener el trafico TCP')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.number tcp.port and eth.type == 0x0800'.format(args.tracefile))
    nlineasTCP = 0
    for linea in salida.split('\n'):
        if linea != '':
            #print(linea)
            nlineasTCP+=1
    porcentajeTCP = (nlineasTCP/nlineasIP)*100
    print(porcentajeTCP)
    logging.info('Ejecutando tshark para obtener el trafico UDP')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.number udp.port and eth.type == 0x0800'.format(args.tracefile))
    nlineasUDP = 0
    for linea in salida.split('\n'):
        if linea != '':
            #print(linea)
            nlineasUDP+=1
    porcentajeUDP = (nlineasUDP/nlineasIP)*100
    print(porcentajeUDP)
    logging.info('Ejecutando tshark para obtener el trafico que no es ni TCP ni UDP')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.number !(udp.port or tcp.port) and eth.type == 0x0800'.format(args.tracefile))
    nlineasOTROS = 0
    for linea in salida.split('\n'):
        if linea != '':
            #print(linea)
            nlineasOTROS+=1
    porcentajeOTROS = (nlineasOTROS/nlineasIP)*100    
    print(porcentajeOTROS)
   
    #Obtención de top direcciones IP
    #TODO: Añadir código para obtener los datos y generar la gráfica de top IP origen por bytes
    logging.info('Ejecutando tshark para obtener el trafico top IP origen por bytes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e ip.src -e frame.len'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    dictionary = {}
    sumaBytes = 0

    for item in aux:
        #Teoricamente el tamaño minimo de IP son 9 caracteres pero hay una ip que sale cortada
        #concretamente la 82.234.227.1 (que seria la 82.234.227.196).
        #No sabemos por qué sucede, asi que hemos optado por aumentar el rango de longitud 
        #para que no nos de index out of range
        if len(item) > 13:
            item = item.split('\t')
            sumaBytes += int(item[1])
            if item[0] in dictionary.keys():
                dictionary[item[0]] += int(item[1])
            else:
                dictionary[item[0]] = int(item[1])
        else:
            aux.remove(item)

    listaEtiquetas = []
    listaValores = []
    for i in range(5):
        key = max(dictionary, key=dictionary.get)
        listaEtiquetas.append(key)
        listaValores.append(dictionary[key])
        dictionary.pop(key)
    pintarTarta(listaEtiquetas, listaValores, "IP_origen_bytes.png", "Top IP origen por bytes")

    #TODO: Añadir código para obtener los datos y generar la gráfica de top IP destino por bytes
    logging.info('Ejecutando tshark para obtener el trafico top IP destino por bytes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e ip.dst -e frame.len'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    dictionary = {}
    sumaBytes = 0

    for item in aux:
        #Teoricamente el tamaño minimo de IP son 9 caracteres.
        #Al contrario de lo que sucede con ip.src, aqui no hay ningun tipo de problema.
        if len(item) > 9:
            item = item.split('\t')
            sumaBytes += int(item[1])
            if item[0] in dictionary.keys():
                dictionary[item[0]] += int(item[1])
            else:
                dictionary[item[0]] = int(item[1])
        else:
            aux.remove(item)

    listaEtiquetas = []
    listaValores = []
    for i in range(5):
        key = max(dictionary, key=dictionary.get)
        listaEtiquetas.append(key)
        listaValores.append(dictionary[key])
        dictionary.pop(key)

    pintarTarta(listaEtiquetas, listaValores, "IP_destino_bytes.png", "Top IP destino por bytes")
    
    #TODO: Añadir código para obtener los datos y generar la gráfica de top IP origen por paquetes
    logging.info('Ejecutando tshark para obtener el trafico top IP origen por paquetes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e ip.src'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    f = open("resultados_IP_origen_paquetes.dat", "w")
    for item in aux:
        if item != '':
            f.write("%s\n"%item)
    codigo, salida = ejecutarComandoObtenerSalida('uniq -c resultados_IP_origen_paquetes.dat')
    f.close()
    aux = salida.split('\n')
    aux.sort(reverse=True)
    listaEtiquetas = []
    listaValores = []
    for i in aux[:5]:
        while i[0] == ' ':
            i = i[1:]
        new = i.split(' ')
        listaValores.append(new[0])
        listaEtiquetas.append(new[1])
    pintarTarta(listaEtiquetas, listaValores, "IP_origen_paquetes.png", "Top IP origen por paquetes")
    #TODO: Añadir código para obtener los datos y generar la gráfica de top IP destino por paquetes
    logging.info('Ejecutando tshark para obtener el trafico top IP destino por paquetes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e ip.dst'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    f = open("resultados_IP_destino_paquetes.dat", "w")
    for item in aux:
        if item != '':
            f.write("%s\n"%item)
    codigo, salida = ejecutarComandoObtenerSalida('uniq -c resultados_IP_destino_paquetes.dat')
    f.close()
    aux = salida.split('\n')
    aux.sort(reverse=True)
    listaEtiquetas = []
    listaValores = []
    for i in aux[:5]:
        while i[0] == ' ':
            i = i[1:]
        new = i.split(' ')
        listaValores.append(new[0])
        listaEtiquetas.append(new[1])

    pintarTarta(listaEtiquetas, listaValores, "IP_destino_paquetes.png", "Top IP destino por paquetes")
    
    
    #Obtención de top puertos TCP
    #TODO: Añadir código para obtener los datos y generar la gráfica de top puerto origen TCP por bytes
    logging.info('Ejecutando tshark para obtener el trafico top TCP origen por bytes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e tcp.srcport -e frame.len'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    dictionary = {}
    sumaBytes = 0

    for item in aux:
        item = item.split('\t')
        if item[0] != '':
            sumaBytes += int(item[1])
            if item[0] in dictionary.keys():
                dictionary[item[0]] += int(item[1])
            else:
                dictionary[item[0]] = int(item[1])

    listaEtiquetas = []
    listaValores = []
    for i in range(5):
        key = max(dictionary, key=dictionary.get)
        listaEtiquetas.append(key)
        listaValores.append(dictionary[key])
        dictionary.pop(key)

    pintarTarta(listaEtiquetas, listaValores, "TCP_origen_bytes.png", "Top TCP origen por bytes")
    #TODO: Añadir código para obtener los datos y generar la gráfica de top puerto destino TCP por bytes
    logging.info('Ejecutando tshark para obtener el trafico top TCP destino por bytes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e tcp.dstport -e frame.len'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    dictionary = {}
    sumaBytes = 0

    for item in aux:
        #Aparentemente, el mismo error sucede que en ip.src,
        #porque hay un paquete que no nos está dando la frame.len
        #Lo resolvemos poniendo la condicion de que el nº de caracteres sea >2
        if len(item) > 2:
            item = item.split('\t')
            sumaBytes += int(item[1])
            if item[0] in dictionary.keys():
                dictionary[item[0]] += int(item[1])
            else:
                dictionary[item[0]] = int(item[1])
        else:
            aux.remove(item)

    listaEtiquetas = []
    listaValores = []
    for i in range(5):
        key = max(dictionary, key=dictionary.get)
        listaEtiquetas.append(key)
        listaValores.append(dictionary[key])
        dictionary.pop(key)

    pintarTarta(listaEtiquetas, listaValores, "TCP_destino_bytes.png", "Top TCP destino por bytes")

    #TODO: Añadir código para obtener los datos y generar la gráfica de top puerto origen TCP por paquetes
    logging.info('Ejecutando tshark para obtener el trafico top TCP origen por paquetes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e tcp.srcport'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    f = open("resultados_TCP_origen_paquetes.dat", "w")
    for item in aux:
        if item != '':
            f.write("%s\n"%item)
    codigo, salida = ejecutarComandoObtenerSalida('uniq -c resultados_TCP_origen_paquetes.dat')
    f.close()
    aux = salida.split('\n')
    aux.sort(reverse=True)
    listaEtiquetas = []
    listaValores = []
    for i in aux[:5]:
        while i[0] == ' ':
            i = i[1:]
        new = i.split(' ')
        listaValores.append(new[0])
        listaEtiquetas.append(new[1])
    pintarTarta(listaEtiquetas, listaValores, "TCP_origen_paquetes.png", "Top TCP origen por paquetes")
 
    #TODO: Añadir código para obtener los datos y generar la gráfica de top puerto destino  TCP por paquetes
    logging.info('Ejecutando tshark para obtener el trafico top TCP destino por paquetes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e tcp.dstport'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    f = open("resultados_TCP_destino_paquetes.dat", "w")
    for item in aux:
        if item != '':
            f.write("%s\n"%item)
    codigo, salida = ejecutarComandoObtenerSalida('uniq -c resultados_TCP_destino_paquetes.dat')
    f.close()
    aux = salida.split('\n')
    aux.sort(reverse=True)
    listaEtiquetas = []
    listaValores = []
    for i in aux[:5]:
        while i[0] == ' ':
            i = i[1:]
        new = i.split(' ')
        listaValores.append(new[0])
        listaEtiquetas.append(new[1])
    pintarTarta(listaEtiquetas, listaValores, "TCP_destino_paquetes.png", "Top TCP destino por paquetes")

    #Obtención de top puertos UDP
    #TODO: Añadir código para obtener los datos y generar la gráfica de top puerto origen UDP por bytes
    logging.info('Ejecutando tshark para obtener el trafico top UDP origen por bytes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e udp.srcport -e frame.len'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    dictionary = {}
    sumaBytes = 0

    for item in aux:
        #Al parecer, hay paquetes que vienen con un espacio en blanco
        #asi que ponemos una condicion para que no los meta en el diccionario
            item = item.split('\t')
            if item[0] != '':
                sumaBytes += int(item[1])
                if item[0] in dictionary.keys():
                    dictionary[item[0]] += int(item[1])
                else:
                    dictionary[item[0]] = int(item[1])
        
    listaEtiquetas = []
    listaValores = []
    for i in range(5):
        key = max(dictionary, key=dictionary.get)
        listaEtiquetas.append(key)
        listaValores.append(dictionary[key])
        dictionary.pop(key)

    pintarTarta(listaEtiquetas, listaValores, "UDP_origen_bytes.png", "Top UDP origen por bytes")

 
    #TODO: Añadir código para obtener los datos y generar la gráfica de top puerto destino UDP por bytes
    logging.info('Ejecutando tshark para obtener el trafico top UDP destino por bytes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e udp.dstport -e frame.len'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    dictionary = {}
    sumaBytes = 0

    for item in aux:
        item = item.split('\t')
        if item[0] != '':
            sumaBytes += int(item[1])
            if item[0] in dictionary.keys():
               dictionary[item[0]] += int(item[1])
            else:
                dictionary[item[0]] = int(item[1])


    listaEtiquetas = []
    listaValores = []
    for i in range(5):
        key = max(dictionary, key=dictionary.get)
        listaEtiquetas.append(key)
        listaValores.append(dictionary[key])
        dictionary.pop(key)

    pintarTarta(listaEtiquetas, listaValores, "UDP_destino_bytes.png", "Top UDP destino por bytes")
  
    #TODO: Añadir código para obtener los datos y generar la gráfica de top puerto origen UDP por paquetes
    logging.info('Ejecutando tshark para obtener el trafico top UDP origen por paquetes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e udp.srcport'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    f = open("resultados_UDP_origen_paquetes.dat", "w")
    for item in aux:
        if item != '':
            f.write("%s\n"%item)
    codigo, salida = ejecutarComandoObtenerSalida('uniq -c resultados_UDP_origen_paquetes.dat')
    f.close()
    aux = salida.split('\n')
    aux.sort(reverse=True)
    listaEtiquetas = []
    listaValores = []
    for i in aux[:5]:
        while i[0] == ' ':
            i = i[1:]
        new = i.split(' ')
        listaValores.append(new[0])
        listaEtiquetas.append(new[1])
    pintarTarta(listaEtiquetas, listaValores, "UDP_origen_paquetes.png", "Top UDP origen por paquetes")
    
    #TODO: Añadir código para obtener los datos y generar la gráfica de top puerto destino UDP por paquetes
    logging.info('Ejecutando tshark para obtener el trafico top UDP destino por paquetes')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e udp.dstport'.format(args.tracefile))
    aux = salida.split('\n')
    aux.sort()
    f = open("resultados_UDP_destino_paquetes.dat", "w")
    for item in aux:
        if item != '':
            f.write("%s\n"%item)
    codigo, salida = ejecutarComandoObtenerSalida('uniq -c resultados_UDP_destino_paquetes.dat')
    f.close()
    aux = salida.split('\n')
    aux.sort(reverse=True)
    listaEtiquetas = []
    listaValores = []
    for i in aux[:5]:
        while i[0] == ' ':
            i = i[1:]
        new = i.split(' ')
        listaValores.append(new[0])
        listaEtiquetas.append(new[1])
    pintarTarta(listaEtiquetas, listaValores, "UDP_destino_paquetes.png", "Top UDP destino por paquetes")

    #Obtención de series temporales de ancho de banda
    #TODO: Añadir código para obtener los datos y generar la gráfica de la serie temporal de ancho de banda con MAC como origen

    #TODO: Añadir código para obtener los datos y generar la gráfica de la serie temporal de ancho de banda con MAC como destino
   
    #Obtención de las ECDF de tamaño de los paquetes
    #TODO: Añadir código para obtener los datos y generar la gráfica de la ECDF de los tamaños de los paquetes a nivel 2
    logging.info('Ejecutando tshark para obtener los datos para generar la grafica ECDF de los tamaños de paquetes con MAC origen a nivel 2')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.len eth.src == {}'.format(args.tracefile, args.mac))
    aux = salida.split('\n')
    listaOrigen = []
    listaDestino = []

    for i in aux:
        if len(i) > 1:
            i = i[1:]
            listaOrigen.append(int(i))

    if len(listaOrigen) == 0:
        logging.info("LA LISTA ORIGEN ESTA VACIA\n Se puede deber a que no se manda nada")
    else:
        pintarECDF(listaOrigen, "Tamaños_paquetes_origen_lvl2.png", "Tamaños_paquetes_origen_lvl2", "Bytes", "probabilidad")

    logging.info('Ejecutando tshark para obtener los datos para generar la grafica ECDF de los tamaños de paquetes con MAC destino a nivel 2')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.len eth.dst == {}'.format(args.tracefile, args.mac))
    aux = salida.split('\n')
    for i in aux:
        if len(i) > 1:
            i = i[1:]
            listaDestino.append(int(i))

    if len(listaDestino) == 0:
        logging.info("LA LISTA DESTINO ESTA VACIA\n Se puede deber a que no se recibe nada")
    else:
        pintarECDF(listaDestino, "Tamaños_paquetes_destino_lvl2.png", "Tamaños_paquetes_destino_lvl2", "Bytes", "probabilidad")
    
    #Obtención de las ECDF de tamaño de los tiempos entre llegadas
    #TODO: Añadir código para obtener los datos y generar la gráfica de la ECDF de los tiempos entre llegadas para el flujo TCP
    logging.info('Ejecutando tshark para obtener los datos para generar la grafica ECDF de los tiempos entre llegadas para el flujo TCP')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.time_delta tcp.port'.format(args.tracefile))
    aux = salida.split('\n')
    listaTCP = []

    for i in aux:
        i = i.split('\t')
        if i[0] != '' and i[0] != '\t':
            listaTCP.append(float(i[0]))

    if len(listaTCP) == 0:
        logging.info("LA LISTA TCP ESTA VACIA")
    else:
        pintarECDF(listaTCP, "Tiempo_entre_llegadas_TCP.png", "Tiempo_entre_llegadas_TCP", "Tiempo", "Probabilidad")
    #TODO: Añadir código para obtener los datos y generar la gráfica de la ECDF de los tiempos entre llegadas para el flujo UDP
    logging.info('Ejecutando tshark para obtener los datos para generar la grafica ECDF de los tiempos entre llegadas para el flujo UDP')
    codigo, salida = ejecutarComandoObtenerSalida('tshark -r {} -T fields -e frame.time_delta udp.port'.format(args.tracefile))
    aux = salida.split('\n')
    listaUDP = []

    for i in aux:
        i = i.split('\t')
        if i[0] != '' and i[0] != '\t':
            listaUDP.append(float(i[0]))

    if len(listaUDP) == 0:
        logging.info("LA LISTA UDP ESTA VACIA")
    else:
        pintarECDF(listaUDP, "Tiempo_entre_llegadas_UDP.png", "Tiempo_entre_llegadas_UDP", "Tiempo", "Probabilidad")