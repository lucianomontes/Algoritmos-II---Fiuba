#!/usr/bin/python3
import funcionesGrafos
import csv
from sys import argv
from grafo import Grafo
from collections import deque

# ################################################################ #
#                            CONSTANTES                            #
# ################################################################ #

MIN_SEGUIMIENTOS = 0
MAS_IMP = 1
PERSECUCION = 2
COMUNIDADES = 3
DIVULGAR = 4
DIVULGAR_CICLO = 5
CFC = 6

# ################################################################ #
#                     FUNCIONES PRINCIPALES                        #
# ################################################################ #

def min_seguimientos(grafo, origen, destino):
  """Imprime una lista con los delincuentes con los cuáles vamos del delincuente origen al delincuente destino de la forma más rápida. 
  En caso de no poder hacer el seguimiento imprime Seguimiento imposible."""
  lista = funcionesGrafos.bfs_camino_minimo(grafo, origen, destino)
  sep = ' -> '
  if len(lista) == 0:
    print("Seguimiento imposible")
  lista.reverse()
  for vertice in lista:
    if vertice == lista[len(lista)-1]: sep = '\n'
    print(vertice, end = sep)  


def mas_imp(grafo, cant):
  """Imprime una aproximación de los delincuentes más importantes utilizando betweeness centrality"""
  listaCentrales = funcionesGrafos.calcular_centralidad(grafo, cant)
  for delincuente in listaCentrales:
    sep = ', '
    if delincuente == listaCentrales[len(listaCentrales) - 1]: sep = '\n'
    print(delincuente, end = sep)


def comparar_delincuentes(delincuente1, delincuente2, importantes):
  if delincuente1 == None or importantes[delincuente1] > importantes[delincuente2]: return -1
  return 1


def calcular_camino_minimo(grafo, origen, importantes):
  padre = {}
  visitados = set()
  cola = deque()
  
  delincuente = None
  padre[origen] = None

  cola.append(origen)
  visitados.add(origen)
  while len(cola) > 0 :
    vertice = cola.popleft() 
    for w in grafo.adyacentes(vertice):
      if w not in visitados:
        visitados.add(w)
        padre[w] = vertice
        cola.append(w)
        if w in importantes:
          if comparar_delincuentes(delincuente, w, importantes) < 0: delincuente = w
    if delincuente != None : break     
        
  camino = []

  actual = delincuente
  while actual != None:
    camino.append(actual)
    actual = padre[actual]

  return camino


def persecucion(grafo, origenes, k):
    """Dado cada uno de los delincuentes pasados (agentes encubiertos), obtiene cuál es el camino más corto para llegar desde alguno de los delincuentes pasados por parámetro, 
    a alguno de los K delincuentes más importantes. En caso de tener caminos de igual largo, prioriza los que vayan a un delincuente más importante."""
    listaImportantes = funcionesGrafos.calcular_centralidad(grafo, k)
    importantes = {}

    ranking = 1
    while len(listaImportantes) > 0:
      delincuente =  listaImportantes.pop() 
      importantes[delincuente] = ranking #menor numero de ranking corresponde a un delincuente mas importante
      ranking += 1

    camino_minimo = calcular_camino_minimo(grafo, origenes[0], importantes)

    for i in range(1,len(origenes)):
      camino = calcular_camino_minimo(grafo, origenes[i],importantes)

      if len(camino) == 0: continue
      if len(camino) < len(camino_minimo): camino_minimo = camino
      if len(camino) == len(camino_minimo) and comparar_delincuentes(camino_minimo[0], camino[0], importantes) < 0: camino_minimo = camino

    camino_minimo.reverse()
    if camino_minimo != None: imprimir_ciclo(camino_minimo)


def comunidades(grafo, n):
  """Imprime un listado de las comunidades que tienen al menos n integrantes (detecta comunidades con Label Propagation)"""
  listasDeComunidades = funcionesGrafos.label_propagation(grafo, n)
  
  for i in range(0, len(listasDeComunidades)):
    print("Comunidad {}".format(i+1), end = ': ')
    for vertice in listasDeComunidades[i]:
      sep = ', '
      if vertice == listasDeComunidades[i][len(listasDeComunidades[i])-1]: sep = '\n'
      print(vertice, end = sep)


def divulgar(grafo, delincuente, n):
    """Imprime una lista con todos los delincuentes a los cuales les termina llegando un rumor que comienza en el delincuente pasado por parámetro, y a lo sumo realiza n saltos"""
    distancia, padres= funcionesGrafos.bfs(grafo, delincuente)
    resultado = []

    for vertice in distancia.keys():
        if distancia[vertice] <= n: 
            resultado.append(vertice)

    for elemento in resultado:
      sep = ', '
      if elemento == resultado[len(resultado)-1]: sep = '\n'
      if elemento != delincuente: print(elemento, end = sep)

    
def imprimir_ciclo(lista):
    if len(lista) == 1:
        print("No se encontro recorrido.")
    else:
        sep = ' -> '
        contador = 0
        for vertice in lista:
            contador += 1
            if contador == len(lista): sep = '\n'
            print(vertice, end = sep)   
  

def bt_divulgar_ciclo(grafo, delincuente, n, listaParcial, visitados):
    if len(listaParcial)-1 == n and listaParcial[-1] == delincuente: return True
    if len(listaParcial) > n : return False

    v = listaParcial[-1]        
    for w in grafo.adyacentes(v):
        if w == delincuente and len(listaParcial) != n : continue
        if w in visitados : continue   
        listaParcial.append(w)
        visitados.add(w)
        if bt_divulgar_ciclo(grafo, delincuente, n, listaParcial, visitados) == True : return True  
        listaParcial.pop(-1)
        visitados.remove(w)
    return False


def divulgar_ciclo(grafo, delincuente, n):
    """Permite encontrar un camino simple que empiece y termine en el delincuente pasado por parámetro, de largo n. 
    En caso de no encontrarse un ciclo de ese largo y dicho comienzo, imprime No se encontro recorrido."""
    listaParcial = []
    visitados = set()
    listaParcial.append(delincuente)

    bt_divulgar_ciclo(grafo, delincuente, n, listaParcial, visitados)
    imprimir_ciclo(listaParcial)


def cfc(grafo):
  """Imprime un listado con todas las componentes fuertemente conexas del grafo"""
  listaDeComponentes = funcionesGrafos.cfc(grafo)
  
  for i in range(0, len(listaDeComponentes)):
    print("CFC {}: ".format(i+1), end = '')
    for elemento in listaDeComponentes[i]:
      sep = ', '
      if elemento == listaDeComponentes[i][len(listaDeComponentes[i])-1]: sep = '\n'
      print(elemento, end = sep)

# ################################################################ #
#                     MANEJO DEL INPUT                             #
# ################################################################ #

def cargar_grafo(archivo):
  """Lee el archivo pasado por parametro(.tsv) y cargar el grafo""" 
  grafo = Grafo()

  with open(archivo, "r") as mensajes:
      lector = csv.reader(mensajes, delimiter="\t")
      for linea in lector:
        grafo.agregar_vertice(linea[0])
        #if(linea[0] == linea[1]): continue
        grafo.agregar_vertice(linea[1])
        grafo.agregar_arista(linea[0], linea[1])

  return grafo

def validar_entrada(argv):
	if len(argv) != 2:
		raise ValueError("La cantidad de parametros es incorrecta.")
	return argv[1]


def main():
  """Lee los comandos y ejecuta la funcion indicada"""
  mensajes = validar_entrada(argv)
  grafo = cargar_grafo(mensajes)  
  comandos = {"min_seguimientos": 0, "mas_imp": 1, "persecucion": 2, 
  "comunidades": 3, "divulgar": 4, "divulgar_ciclo": 5, "cfc": 6}
  linea = input()
  ingreso = linea.split(" ")

  try:
  	if comandos[ingreso[0]] == MIN_SEGUIMIENTOS:
  		min_seguimientos(grafo, ingreso[1], ingreso[2]) 
  	elif comandos[ingreso[0]] == MAS_IMP:
  		mas_imp(grafo, int(ingreso[1]))  
  	elif comandos[ingreso[0]] == PERSECUCION:
  		persecucion(grafo, ingreso[1].split(","), int(ingreso[2])) 
  	elif comandos[ingreso[0]] == COMUNIDADES:
  		comunidades(grafo, int(ingreso[1]))  
  	elif comandos[ingreso[0]] == DIVULGAR:
  		divulgar(grafo, ingreso[1], int(ingreso[2]))
  	elif comandos[ingreso[0]] == DIVULGAR_CICLO:
  		divulgar_ciclo(grafo, ingreso[1], int(ingreso[2])) 
  	elif comandos[ingreso[0]] == CFC:
  		cfc(grafo)  
  except ValueError:
  	print("Comando erroneo")

  return


main()