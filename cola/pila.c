#include "pila.h"
#include <stdlib.h>

// Constantes pila.c
#define PILA_VACIA 0
#define CAPACIDAD_INICIAL 8
#define DIVIDIR 2
#define AUMENTAR 2

/* Definición del struct pila proporcionado por la cátedra.
 */
struct pila{
    void** datos;
    size_t cantidad;  // Cantidad de elementos almacenados.
    size_t capacidad;  // Capacidad del arreglo 'datos'.
};

/*********************************************************************
                        FUNCIONES AUXILIARES 
**********************************************************************/


// reserva memoria dinamica para la pila, el doble o la mitad de lo que tenia, si hay error devuelve false
bool redimencionar_pila(pila_t* pila, size_t capacidad_nueva){

    void** datos_nuevos = realloc(pila->datos, capacidad_nueva*sizeof(void*));

    if(datos_nuevos == NULL){
        return false;
    }
    pila->datos = datos_nuevos;
    pila->capacidad = capacidad_nueva;
    return true;
}


/* *****************************************************************
 *                    PRIMITIVAS DE LA PILA
 * *****************************************************************/

// ...

// Crea una pila.
// Post: devuelve una nueva pila vacía.
pila_t* pila_crear(void){

    pila_t* pila = malloc(sizeof(pila_t));

    if(pila == NULL){
        return 0;
    }
    pila->cantidad = PILA_VACIA;
    pila->capacidad = CAPACIDAD_INICIAL;
    pila->datos = malloc(pila->capacidad*sizeof(void*));

    if(pila->datos == NULL){
        free(pila);
        return 0;
    }
    return pila;
}

// Destruye la pila.
// Pre: la pila fue creada.
// Post: se eliminaron todos los elementos de la pila.
void pila_destruir(pila_t *pila){
    free(pila->datos);
    free(pila);
} 

// Devuelve verdadero si la pila no tiene elementos apilados, false en caso contrario.
// Pre: la pila fue creada.
bool pila_esta_vacia(const pila_t *pila){
    return pila->cantidad == PILA_VACIA;
}

// Agrega un nuevo elemento a la pila. Devuelve falso en caso de error.
// Pre: la pila fue creada.
// Post: se agregó un nuevo elemento a la pila, valor es el nuevo tope.
bool pila_apilar(pila_t *pila, void* valor){

    if(pila->cantidad == pila->capacidad){
        if( !redimencionar_pila(pila, pila->capacidad*AUMENTAR) ){
            return false;
        }
    }
    pila->cantidad++;
    pila->datos[pila->cantidad-1] = valor;
    return true;
}    

// Obtiene el valor del tope de la pila. Si la pila tiene elementos,
// se devuelve el valor del tope. Si está vacía devuelve NULL.
// Pre: la pila fue creada.
// Post: se devolvió el valor del tope de la pila, cuando la pila no está
// vacía, NULL en caso contrario.
void* pila_ver_tope(const pila_t *pila){

    if(pila->cantidad == PILA_VACIA){
        return NULL;
    }
   return pila->datos[pila->cantidad-1];
}    

// Saca el elemento tope de la pila. Si la pila tiene elementos, se quita el
// tope de la pila, y se devuelve ese valor. Si la pila está vacía, devuelve
// NULL.
// Pre: la pila fue creada.
// Post: si la pila no estaba vacía, se devuelve el valor del tope anterior
// y la pila contiene un elemento menos.
void* pila_desapilar(pila_t *pila){

    if(pila->cantidad == PILA_VACIA){
        return NULL;
    }
    pila->cantidad--;
    if(pila->cantidad == pila->capacidad/4 && pila->capacidad > CAPACIDAD_INICIAL){
        redimencionar_pila(pila, pila->capacidad/DIVIDIR);      
    }
    return pila->datos[pila->cantidad];
}


