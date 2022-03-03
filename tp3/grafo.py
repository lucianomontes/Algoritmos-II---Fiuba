from collections import deque
import random 

class Vertice(object):
    def __init__(self, clave):
        self.adyacentes = {}
        self.clave = clave


class Grafo(object):
    def __init__(self):
        self.vertices = {}
    
    def __len__(self):
        return len(self.vertices)
    
    def claves(self):
        return self.vertices.keys()
    
    def agregar_vertice(self, clave):
        if(self.vertice_pertence(clave)):
            return False
        
        v = Vertice(clave)
        self.vertices[clave] = v
        
        return True
    
    def agregar_arista(self, origen, destino):
        if not(self.vertice_pertence(origen) or self.vertice_pertence(destino)): 
            return False
        
        vertice_origen = self.vertices[origen]
        vertice_destino = self.vertices[destino]
        vertice_origen.adyacentes[destino] = vertice_destino

        return True
    
    def adyacentes(self, clave):
        return list(self.vertices[clave].adyacentes.keys())
    
    def cantidad_adyacentes(self, clave):
        return len(self.vertices[clave].adyacentes)

    def vertice_pertence(self, clave):
        return clave in self.vertices

    def vertice_obtener(self, clave):
        return self.vertices[clave].get()
    
    def vertice_aleatorio(self):
        """ rand = random.randint(0, len(self.vertices)-1)
        contador = 0
        for vertice in self.vertices.keys():
            if contador == rand: return vertice
            contador += 1 """
        return random.choice(list(self.vertices.keys()))
            



