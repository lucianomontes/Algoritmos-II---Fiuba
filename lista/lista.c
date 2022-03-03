#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

// Definicion de constantes

#define LARGO_CERO 0
#define LARGO_UNO 1


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

// Defino struct nodo
typedef struct nodo_lista{
    void* dato;
    struct nodo_lista* prox;
}nodo_lista_t;

// Defino struct lista
struct lista{
    nodo_lista_t* prim;
    nodo_lista_t* ult;
    size_t largo;
};

// Defino struct iterador

struct lista_iter{
    lista_t* lista;
    nodo_lista_t* actual;
    nodo_lista_t* anterior; 
};



/*********************************************************************
                        FUNCIONES AUXILIARES 
**********************************************************************/

// Crea un nodo y le da un valor
nodo_lista_t* crear_nodo(void* valor){

    nodo_lista_t* nodo = malloc(sizeof(nodo_lista_t));

    if(nodo == NULL){
        return NULL;
    }
    nodo->dato = valor;
    nodo->prox = NULL;

    return nodo;
}

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// crea una lista.
// Post: devuelve lista vacia.
lista_t *lista_crear(void){

    lista_t* lista = malloc(sizeof(lista_t));

    if(lista == NULL){
        return NULL;
    }
    lista->prim = NULL;
    lista->ult = NULL;
    lista->largo = LARGO_CERO;

    return lista;
}

// Devuelve verdadero si lista no tiene elementos, falso en caso contrario.
// Pre: lista fue creada.
bool lista_esta_vacia(const lista_t *lista){
    return lista->prim==NULL && lista->ult==NULL && lista->largo==LARGO_CERO;
}

// Se inserta un elemento al inicio de la lista y devuelve false en caso de error.
// Pre: lista fue creada.
// Post: Se agrego un elemento al inicio de a lista, se encuentra al principio.
bool lista_insertar_primero(lista_t *lista, void *dato){

    nodo_lista_t* nodo_lista = crear_nodo(dato);

    if(nodo_lista == NULL){
        return false;
    }
    if(lista_esta_vacia(lista) ){
        lista->ult = nodo_lista;
    }
    else{
        nodo_lista->prox = lista->prim;
    }
    lista->prim = nodo_lista;
    lista->largo++;
    return true;
}

// Se inserta un elemento al final de la lista y devuelve false en caso de error.
// Pre: lista fue creada.
// Post: Se agrego un elemento al final de a lista, se encuentra al ultimo.
bool lista_insertar_ultimo(lista_t *lista, void *dato){
    
    nodo_lista_t* nodo_lista = crear_nodo(dato);

    if(nodo_lista == NULL){
        return false;
    }

    if(lista_esta_vacia(lista) ){
        lista->prim= nodo_lista;
    }
    else{
        lista->ult->prox = nodo_lista;
    }
    lista->ult = nodo_lista;
    lista->largo++;
    return true;
}

// Elimina el primer elemento de la lista y devuelve NULL si esta vacia.
// Pre: lista fue creada.
// Post: Devuelve el valor del primer elemento anterior, lista tiene un elemento menos
// si la lista no estaba vacia.
void *lista_borrar_primero(lista_t *lista){

    if(lista_esta_vacia(lista) ){
        return NULL;
    }

    void* primer_dato = lista_ver_primero(lista);

    if(lista->prim == lista->ult){
        free(lista->prim);
        lista->prim = NULL;
        lista->ult = NULL;
        lista->largo = LARGO_CERO;
        return primer_dato;
    }
    nodo_lista_t* nodo_lista_aux = lista->prim->prox;    
    free(lista->prim);
    lista->prim = nodo_lista_aux;
    lista->largo--;
    return primer_dato;
}

// Devueve el valor del primer elemento de la lista, devuelve NULL si esta vacia
// Pre: lista fue creada.
// Post: Devuelve el valor del primer elemento si la lista no esta vacia.
void *lista_ver_primero(const lista_t *lista){
    if(lista_esta_vacia(lista) ){
        return NULL;
    }
    return lista->prim->dato;
}

// Devueve el valor del ultimo elemento de la lista, devuelve NULL si esta vacia
// Pre: lista fue creada.
// Post: Devuelve el valor del ultimo elemento si la lista no esta vacia.
void *lista_ver_ultimo(const lista_t* lista){
    if(lista_esta_vacia(lista) ){
        return NULL;
    }
    return lista->ult->dato;
}

// Devuelve el largo de la lista
// Pre: lista fue creada
size_t lista_largo(const lista_t *lista){
    return lista->largo;
}

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *)){

    nodo_lista_t* nodo_lista_aux;
    while(lista->prim != NULL){
        if(destruir_dato != NULL){
            destruir_dato(lista->prim->dato);
        }
        nodo_lista_aux = lista->prim->prox;
        free(lista->prim);
        lista->prim = nodo_lista_aux;
    }
    free(lista);
}


/* *****************************************************************
 *                      PRIMITIVAS ITERADORES
 * *****************************************************************/   

// Crea un iterador a una lista.
// Post: Devuelve un iterador apuntando al primer elemento de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista){

    lista_iter_t* lista_iter = malloc(sizeof(lista_iter_t));
    
    if(lista_iter == NULL) return NULL;

    lista_iter->lista = lista;
    lista_iter->actual = lista->prim;

    return lista_iter;
}

// Avanza al siguiente dato de la lista.
// Pre: iterador fue creado.
// Post: Devuelve true si se avanzo correctamente, false si es final de lista.
bool lista_iter_avanzar(lista_iter_t *iter){

    if(iter->actual == NULL) return false;

    iter->anterior = iter->actual;
    iter->actual = iter->actual->prox;

    return true;
}

// Devuelve el dato al que el iterador esta apuntando actualmente.
// Pre: iterador fue creado.
// Post: Devuelve el dato o NULL en caso de error.
void *lista_iter_ver_actual(const lista_iter_t *iter){
    if(iter->actual == NULL) return NULL;

    return iter->actual->dato;
}

// Posiciona el iterador al final de la lista.
// Pre: iterador fue creado.
// Post: Devuelve true si el iterador pudo apuntar al ultimo elemento de la lista, false en caso de error.
bool lista_iter_al_final(const lista_iter_t *iter){
    return iter->actual == NULL;
}

// Destruye el iterador.
// Pre: iterador fue creado.
// Post: destruye el iterador.
void lista_iter_destruir(lista_iter_t *iter){
    free(iter);
}

// Inserta un nuevo elemento en donde esta posicionado el iterador.
// Pre: iterador fue creado.
// Post: inserta el elemento sin modificar el orden de los demas elementos de la lista, modifica el largo de la misma y devuelve true, false caso contrario.
bool lista_iter_insertar(lista_iter_t *iter, void *dato){

    nodo_lista_t* nuevo_nodo = crear_nodo(dato);

    if(nuevo_nodo == NULL) return false;
    
    if(iter->actual == iter->lista->prim){
        iter->lista->prim = nuevo_nodo;
    }
    if(lista_iter_al_final(iter)){
        iter->lista->ult = nuevo_nodo;
    } 
    nuevo_nodo->prox = iter->actual;
    if(nuevo_nodo != iter->lista->prim) iter->anterior->prox = nuevo_nodo;
    iter->actual = nuevo_nodo;
    iter->lista->largo++;

    return true;
}

// Borra un elemento de la lista en donde esta posicionado el iterador y devuelve el dato borrado.
// Pre: iterador fue creado.
// Post: borra el elemento que apunta el iterador sin modificar el resto de la lista, actualiza su largo y devuelve el dato borrado, NULL en caso de error.
void *lista_iter_borrar(lista_iter_t *iter){

    if(lista_iter_al_final(iter)) return NULL;
    
    nodo_lista_t* nodo_aux = iter->actual->prox;
    void* dato = lista_iter_ver_actual(iter);
    if(iter->lista->prim != iter->actual) iter->anterior->prox = iter->actual->prox;

    if(iter->lista->largo == LARGO_UNO){
        iter->lista->prim = NULL;
        iter->lista->ult = NULL;
    }
    else if(iter->actual == iter->lista->ult){
        iter->lista->ult = iter->anterior;
    }
    else if(iter->actual == iter->lista->prim){
        iter->lista->prim = iter->actual->prox;
    }
    free(iter->actual);
    iter->actual = nodo_aux;
    iter->lista->largo--;

    return dato;
}

// Recorrere la lista y opera segun la funcion que le pasemos.
// Pre: lista fue creada.
// Post: la funcion fue aplicada a la lista.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra){

    lista_iter_t* iter = lista_iter_crear(lista);

    if(iter==NULL) return;

    while( !lista_iter_al_final(iter) && visitar( lista_iter_ver_actual(iter), extra) ){
            lista_iter_avanzar(iter);
    }
    
    lista_iter_destruir(iter);
}
