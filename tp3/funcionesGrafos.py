import heapq
from collections import deque
from random import randint
from random import choice

# ################################################################ #
#                            CONSTANTES                            #
# ################################################################ #

VISITADO = True
NO_VISITADO = False
CANTIDAD_RECORRIDOS = 50
LARGO_RECORRIDO = 20000

# ################################################################ #
#                     FUNCIONES AUXILIARES                         #
# ################################################################ #

def bfs(grafo, vertice_inicial):
    """Recorrido BFS, recorre todo el grafo en anchura"""
    visitados = set()
    distancia = {}
    padres = {}
    q = deque()
    q.append(vertice_inicial)
    padres[vertice_inicial] = None
    visitados.add(vertice_inicial)
    distancia[vertice_inicial] = 0

    while(len(q) > 0):
        v = q.popleft()
        for w in grafo.adyacentes(v):
            if w not in visitados:
                visitados.add(w)
                distancia[w] = distancia[v] + 1
                padres[w] = v
                q.append(w)

    return distancia, padres



def bfs_camino_minimo(grafo, origen, destino):
    """Encuentra el camino minimo utilizando bfs (al ser dirigido y no pesado)"""
    cola = deque()
    visitados = set()
    camino = []
    padre = {}
    if origen == destino: return []
    for vertice in grafo.claves():
        padre[vertice] = None

    cola.append(origen)

    while len(cola) > 0 :
    	actual = cola.popleft()
    	visitados.add(actual)
    	for w in grafo.adyacentes(actual):
    		if w not in visitados :
    			visitados.add(w)
    			padre[w] = actual
    			cola.append(w)
    	if actual == destino:
            camino.append(destino)
            clave = padre[destino]
            while clave != origen :
            	camino.append(clave)
            	clave = padre[clave]
            camino.append(clave)
    
    return camino


def cfc(grafo):
    """Algoritmo de Tarjan para encontrar componentes fuertemente conexas utilizando un recorrido dfs"""
    visitados = set()
    orden = {}
    pila1 = []
    pila2 = []
    cfcs = []
    en_cfs = set()
    for v in grafo.claves():
    	if v not in visitados:
    		orden[v] = 0
    		dfs_cfc(grafo, v, visitados, orden, pila1, pila2, cfcs, en_cfs)
    return cfcs

def dfs_cfc(grafo, v, visitados, orden, pila1, pila2, cfcs, en_cfs):
	visitados.add(v)
	pila1.append(v)
	pila2.append(v)
	for w in grafo.adyacentes(v):
		if w not in visitados:
			orden[w] = orden[v] + 1
			dfs_cfc(grafo, w, visitados, orden, pila1, pila2, cfcs, en_cfs)
		elif w not in en_cfs:
			while orden[pila1[-1]] > orden[w]:
				pila1.pop(-1)

	if pila1[-1] == v:
		pila1.pop(-1)
		z = None
		nueva_cfc = []
		while z != v:
			z = pila2.pop(-1)
			en_cfs.add(z)
			nueva_cfc.append(z)
		cfcs.append(nueva_cfc)


def pila_a_lista(pila):
    lista = []
    n = len(pila)
    
    for i in range (0, n):
        lista[i] = pila.pop()
    
    return lista

def dfs(grafo, vertice_inicial):
    visitados = {}
    pila = deque()

    for v in grafo.claves():
	    if v not in visitados:
		    _dfs(grafo, v, pila, visitados)
	
    return pila_a_lista(pila)

def _dfs(grafo, v, pila, visitados):
    visitados[v] = VISITADO
    
    for w in grafo.adyacentes(v):
	    if w not in visitados:
		    _dfs(grafo, w, pila, visitados)
	
    pila.append(v)


def random_walk(grafo, origen, largo):
    """Genera una lista de cierto largo con un recorrido random sobre el grafo"""
    vertice = origen
    recorrido = []

    for i in range(0, largo):
        recorrido.append(vertice)
        listaAdyacentes = grafo.adyacentes(vertice)
        if len(listaAdyacentes) == 0: break
        vertice = choice(listaAdyacentes)

    return recorrido


def calcular_centralidad(grafo, k):
    """Betweeness centrality aproximado utilizando random walks"""
    apariciones = {}

    for v in grafo.claves(): apariciones[v] = 0
    
    for i in range(0, CANTIDAD_RECORRIDOS):
        recorrido = random_walk(grafo, grafo.vertice_aleatorio(), LARGO_RECORRIDO)
        for j in range(0, len(recorrido)):
            apariciones[recorrido[j]] += 1
    
    """  
    contador = 0
    for vertice, cantidadApariciones in apariciones.items():
        if contador < k : 
            heapq.heappush(heap, (cantidadApariciones, vertice))
            contador += 1
        else:
            tope = heapq.heappop(heap)
            if tope[0] < cantidadApariciones: #tope[0] accede a la cantidad de apariciones del tope
                heapq.heappush(heap, (cantidadApariciones, vertice))
            else: heapq.heappush(heap, tope)
    importantes = [] """
    importantes = heapq.nlargest(k, apariciones, key = apariciones.get)
    
    """ while len(heap) > 0: 
        tupla = heapq.heappop(heap)
        importantes.append(tupla) # tupla[1] es el nombre del vertice
    """
    return importantes


def label_propagation(grafo, n):
    """Algoritmo de Label Propagation para detectar comunidades en un grafo"""
    label = {}
    comunidades = {}
    visitados = set()
    listaDeComunidades = []
    contador = 0

    for v in grafo.claves():
        label[v] = contador
        contador += 1

    while len(visitados) != len(grafo):
        v = grafo.vertice_aleatorio()
        if v not in visitados: visitados.add(v)
        for adyacente in grafo.adyacentes(v):
            if label[adyacente] < label[v]: label[adyacente] = label[v]
    
    for v in label: 
        if label[v] not in comunidades:
            vertices = []
            vertices.append(v)
            comunidades[label[v]] = vertices
        else: 
            lista = comunidades[label[v]]
            lista.append(v)
            comunidades[label[v]] = lista
    
    for comunidad in comunidades:
        if len(comunidades[comunidad]) >= n: listaDeComunidades.append(comunidades[comunidad])
    
    return listaDeComunidades #devuelve un lista de listas con vertices que pertenecen a una comunidad con n o mas vertices


