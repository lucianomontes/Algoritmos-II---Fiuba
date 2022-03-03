#ifndef LISTA_H
#define LISTA_H

#include <stdbool.h>
#include <stddef.h>


/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct lista;

typedef struct lista lista_t;

struct lista_iter;

typedef struct lista_iter lista_iter_t;

/* ******************************************************************
 *                    PRIMITIVAS DE LA LISTA
 * *****************************************************************/

// crea una lista.
// Post: devuelve lista vacia.
lista_t *lista_crear(void);

// Devuelve verdadero si lista no tiene elementos, falso en caso contrario.
// Pre: lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Se inserta un elemento al inicio de la lista y devuelve false en caso de error.
// Pre: lista fue creada.
// Post: Se agrego un elemento al inicio de a lista, se encuentra al principio.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Se inserta un elemento al final de la lista y devuelve false en caso de error.
// Pre: lista fue creada.
// Post: Se agrego un elemento al final de a lista, se encuentra al ultimo.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Elimina el primer elemento de la lista y devuelve NULL si esta vacia.
// Pre: lista fue creada.
// Post: Devuelve el valor del primer elemento anterior, lista tiene un elemento menos
// si la lista no estaba vacia.
void *lista_borrar_primero(lista_t *lista);

// Devueve el valor del primer elemento de la lista, devuelve NULL si esta vacia
// Pre: lista fue creada.
// Post: Devuelve el valor del primer elemento si la lista no esta vacia.
void *lista_ver_primero(const lista_t *lista);

// Devueve el valor del ultimo elemento de la lista, devuelve NULL si esta vacia
// Pre: lista fue creada.
// Post: Devuelve el valor del ultimo elemento si la lista no esta vacia.
void *lista_ver_ultimo(const lista_t* lista);

// Devuelve el largo de la lista
// Pre: lista fue creada
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// para cada uno de los elementos de la lista llama a destruir_dato.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la lista, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));


/* *****************************************************************
 *                      PRIMITIVAS ITERADORES
 * *****************************************************************/   

// Crea un iterador a una lista.
// Post: Devuelve un iterador apuntando al primer elemento de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// Avanza al siguiente dato de la lista.
// Pre: iterador fue creado.
// Post: Devuelve true si se avanzo correctamente, false si es final de lista.
bool lista_iter_avanzar(lista_iter_t *iter);

// Devuelve el dato al que el iterador esta apuntando actualmente.
// Pre: iterador fue creado.
// Post: Devuelve el dato o NULL en caso de error.
void *lista_iter_ver_actual(const lista_iter_t *iter);

// Posiciona el iterador al final de la lista.
// Pre: iterador fue creado.
// Post: Devuelve true si el iterador pudo apuntar al ultimo elemento de la lista, false en caso de error.
bool lista_iter_al_final(const lista_iter_t *iter);

// Destruye el iterador.
// Pre: iterador fue creado.
// Post: destruye el iterador.
void lista_iter_destruir(lista_iter_t *iter);

// Inserta un nuevo elemento en donde esta posicionado el iterador.
// Pre: iterador fue creado.
// Post: inserta el elemento sin modificar el orden de los demas elementos de la lista y devuelve true, false caso contrario.
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// Borra un elemento de la lista en donde esta posicionado el iterador.
// Pre: iterador fue creado.
// Post: borra el elemento que apunta el iterador sin modificar el resto de la lista y devuelve true, false en caso de error.
void *lista_iter_borrar(lista_iter_t *iter);

// Recorrere la lista y opera segun la funcion que le pasemos.
// Pre: lista fue creada.
// Post: la funcion fue aplicada a la lista.
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);



/* *****************************************************************
 *                      PRUEBAS UNITARIAS
 * *****************************************************************/

// Realiza pruebas sobre la implementación del alumno.
void pruebas_lista_alumno(void);

#endif // LISTA_H

