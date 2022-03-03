#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "abb.h"
#include "pila.h"


/* *****************************************************************
 *                          CONSTANTES
 * *****************************************************************/

#define DER true
#define IZQ false

/* *****************************************************************
 *                          ESTRUCTURAS
 * *****************************************************************/

typedef struct nodo_abb{
    char *clave;
    struct nodo_abb *izq;
    struct nodo_abb *der;
    void *dato;
}nodo_abb_t;


struct abb{
    size_t cantidad;
    nodo_abb_t *raiz;
    abb_comparar_clave_t cmp;
    abb_destruir_dato_t destruir;
};


struct abb_iter{
    pila_t *pila;
    nodo_abb_t *actual;
};

/* *****************************************************************
 *                    FUNCIONES AUXILIARES
 * *****************************************************************/
char *copiar_clave(const char* clave){
    char *clave_cop = malloc((sizeof(char) * strlen(clave)) + 1);
    
    if(!clave_cop) return NULL;
    strcpy(clave_cop, clave);

    return clave_cop;
}


nodo_abb_t *nodo_abb_crear(void *dato, const char *clave){
    nodo_abb_t *nodo = malloc(sizeof(nodo_abb_t));
    char *clave_cop = copiar_clave(clave);

    if(!nodo || !clave_cop) return NULL;

    nodo->dato = dato;
    nodo->clave = clave_cop;
    nodo->izq = NULL;
    nodo->der = NULL;

    return nodo;
}


nodo_abb_t *buscar_nodo_abb(const abb_t *abb, nodo_abb_t *nodo, const char *clave){
    
    if(!nodo) return NULL;

    if(abb->cmp(nodo->clave, clave) == 0) return nodo;
    if((abb->cmp(nodo->clave, clave) > 0)) return buscar_nodo_abb(abb, nodo->izq, clave);
    return buscar_nodo_abb(abb, nodo->der, clave);
}    

void cambiar_hijo(abb_t *arbol, nodo_abb_t *padre, bool der, nodo_abb_t *nodo_a_insertar){
    
    if(!padre) arbol->raiz = nodo_a_insertar;
        else{ 
            if(der) padre->der = nodo_a_insertar;// Si nodo es der
            else padre->izq = nodo_a_insertar;// Si nodo es izq
        }
}


bool insertar_nodo(abb_t *arbol, nodo_abb_t *padre, nodo_abb_t *actual, bool der, nodo_abb_t *nodo_a_insertar){
    
    if(!actual){
        actual = nodo_a_insertar;
        cambiar_hijo(arbol, padre, der, actual);
        return true;
    }

    if(arbol->cmp(actual->clave, nodo_a_insertar->clave) > 0) return insertar_nodo(arbol, actual, actual->izq, IZQ, nodo_a_insertar);
    return insertar_nodo(arbol, actual, actual->der, DER, nodo_a_insertar);
}


void _abb_destruir(nodo_abb_t *nodo, abb_destruir_dato_t f_dest){
    
    if(nodo->izq) _abb_destruir(nodo->izq, f_dest);
    if(nodo->der) _abb_destruir(nodo->der, f_dest);

    if(f_dest) f_dest(nodo->dato);
    free(nodo->clave);
    free(nodo);
}


void* abb_destruir_nodo(abb_t* arbol, nodo_abb_t* nodo_abb){
    void* dato = nodo_abb->dato;

    free(nodo_abb->clave);
    free(nodo_abb);
    arbol->cantidad--;

    return dato; 
}


void *abb_borrar_sin_hijos(abb_t *arbol, nodo_abb_t *padre, nodo_abb_t *actual, bool der, nodo_abb_t *nodo_a_insertar){

        cambiar_hijo(arbol, padre, der, nodo_a_insertar);
        return abb_destruir_nodo(arbol, actual);   
}


void *abb_borrar_con_un_hijo(abb_t *arbol, nodo_abb_t *padre, nodo_abb_t *actual, bool der){
    nodo_abb_t *nodo;

    if(actual->der) nodo = actual->der;// Si actual tiene hijo der
    else nodo = actual->izq;// Si actual tiene hijo izq
    
    return abb_borrar_sin_hijos(arbol, padre, actual, der, nodo);
}


nodo_abb_t* buscar_padre_reemplazante(nodo_abb_t* reemplazo){

    nodo_abb_t* padre_reemplazo = NULL;

    while(reemplazo->der){
        padre_reemplazo = reemplazo;
        reemplazo = reemplazo->der;
    }
    return padre_reemplazo;
}


void *abb_borrar_con_hijos(abb_t *arbol, nodo_abb_t *padre, nodo_abb_t *actual, bool der){
    
    nodo_abb_t* reemplazo = actual->izq;
    nodo_abb_t* padre_reemplazante = buscar_padre_reemplazante(reemplazo);
    
    if(padre_reemplazante){
        reemplazo = padre_reemplazante->der;
        padre_reemplazante->der = reemplazo->izq;
        reemplazo->izq = actual->izq;
        reemplazo->der = actual->der;
    }
    else {
        reemplazo = actual->izq;
        reemplazo->der = actual->der;
    }
    if(!padre) arbol->raiz = reemplazo;
    else if(der) padre->der = reemplazo;
    else padre->izq = reemplazo;
    //abb_borrar(arbol, reemplazo->clave);

    return abb_destruir_nodo(arbol, actual);      
}


void *_abb_borrar(abb_t *arbol, nodo_abb_t *padre, nodo_abb_t *actual, bool der, const char *clave){
   
    if(!actual) return NULL;

    if(arbol->cmp(actual->clave, clave) > 0) return _abb_borrar(arbol, actual, actual->izq, IZQ, clave); 
    if(arbol->cmp(actual->clave, clave) < 0) return _abb_borrar(arbol, actual, actual->der, DER, clave);  
    // Si no tiene hijos.
    if(!actual->der && !actual->izq) return abb_borrar_sin_hijos(arbol, padre, actual, der, NULL);
    // Si tiene solo un hijo.
    else if(!actual->der || !actual->izq) return abb_borrar_con_un_hijo(arbol, padre, actual, der);
    // Si tiene dos hijos.
    return abb_borrar_con_hijos(arbol, padre, actual, der); 
}


void iter_avanzar_todo_izq(nodo_abb_t *nodo, abb_iter_t* iter){

    while(nodo->izq){
        pila_apilar(iter->pila, nodo);
        nodo = nodo->izq;
    }
}    
/* *****************************************************************
 *                    PRIMITIVAS DEL ABB
 * *****************************************************************/

abb_t* abb_crear(abb_comparar_clave_t cmp, abb_destruir_dato_t destruir_dato){
    abb_t *abb = malloc(sizeof(abb_t));

    if(!abb) return NULL;

    abb->raiz = NULL;
    abb->cantidad = 0;
    abb->cmp = cmp;
    abb->destruir = destruir_dato;

    return abb;
}


bool abb_guardar(abb_t *arbol, const char *clave, void *dato){
    nodo_abb_t *nodo;
    
    if(arbol->raiz){
        nodo = buscar_nodo_abb(arbol, arbol->raiz, clave);
        if(nodo){
            if(arbol->destruir) arbol->destruir(nodo->dato);
            nodo->dato = dato;
            return true;
        }
    }

    nodo = nodo_abb_crear(dato, clave);
    if(!nodo) return false;

    if(!insertar_nodo(arbol, arbol->raiz, arbol->raiz, DER, nodo)){//a discresion se manda que es derecho
        free(nodo);
        return false;
    } 
    arbol->cantidad++;

    return true;
}


void *abb_borrar(abb_t* arbol, const char* clave){

    if(!arbol->raiz) return NULL;
    
    return _abb_borrar(arbol, NULL, arbol->raiz, DER, clave); //a criterio se manda que es derecho
}


void *abb_obtener(const abb_t *arbol, const char *clave){
    nodo_abb_t *nodo = buscar_nodo_abb(arbol, arbol->raiz, clave);
    
    if(!nodo) return NULL;
    return nodo->dato;
}


bool abb_pertenece(const abb_t *arbol, const char *clave){

    return (buscar_nodo_abb(arbol, arbol->raiz, clave) != NULL);
}


size_t abb_cantidad(abb_t *arbol){
    
    return arbol->cantidad;
}


void abb_destruir(abb_t *arbol){
    
    if(arbol->raiz) _abb_destruir(arbol->raiz, arbol->destruir);
    free(arbol);
}

/* *****************************************************************
 *                    ITERADOR INTERNO
 * *****************************************************************/

bool _abb_in_order(nodo_abb_t *nodo, bool visitar(const char *, void *, void *), void *extra){
    
    if(nodo->izq && !_abb_in_order(nodo->izq, visitar, extra)) return false;    
    if(!visitar(nodo->clave, nodo->dato, extra)) return false;
    if(nodo->der && !_abb_in_order(nodo->der, visitar, extra)) return false;

    return true;    
}


void abb_in_order(abb_t *arbol, bool visitar(const char *, void *, void *), void *extra){

    if(visitar && arbol->cantidad > 0) _abb_in_order(arbol->raiz, visitar, extra);
    return;
}
/* *****************************************************************
 *                    PRIMITIVAS DEL ITERADOR
 * *****************************************************************/
abb_iter_t *abb_iter_in_crear(const abb_t *arbol){
    abb_iter_t *iter = malloc(sizeof(abb_iter_t));
    nodo_abb_t *nodo = arbol->raiz;
    iter->pila = pila_crear();
   
    if(nodo){
        //iter_avanzar_todo_izq(nodo, iter);
        while(nodo->izq){
            pila_apilar(iter->pila, nodo);
            nodo = nodo->izq;
        }
    }
    iter->actual = nodo;

    return iter;
}


bool abb_iter_in_avanzar(abb_iter_t *iter){

    if(!iter->actual) return false;
    if(iter->actual->der){
        iter->actual = iter->actual->der;
        //iter_avanzar_todo_izq(iter->actual, iter);
        while(iter->actual->izq){
            pila_apilar(iter->pila, iter->actual);
            iter->actual = iter->actual->izq;
        }
    }
    else iter->actual = pila_desapilar(iter->pila);

    return true;
}


const char *abb_iter_in_ver_actual(const abb_iter_t *iter){
    
    if(!iter->actual) return NULL;
    return iter->actual->clave;
}


bool abb_iter_in_al_final(const abb_iter_t *iter){
    
    return (pila_esta_vacia(iter->pila) && !iter->actual);
}


void abb_iter_in_destruir(abb_iter_t* iter){
    
    pila_destruir(iter->pila);
    free(iter);
}