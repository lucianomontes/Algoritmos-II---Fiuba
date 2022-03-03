#ifndef COUNT_MIN_SKETCH_H
#define COUNT_MIN_SKETCH_H

#include <stdbool.h>
#include <stddef.h>

/* *****************************************************************
 *          PADRON : 102536 NOMBRE : MONTES, LUCIANO NICOLAS
 *          PADRON : 101826 NOMBRE: LOPEZ NUÑEZ, AGUSTIN
 * *****************************************************************/

/* ******************************************************************
 *                DEFINICION DE LOS TIPOS DE DATOS
 * *****************************************************************/

struct cms;

typedef struct cms cms_t;

/* Crea el cms
 */
cms_t *cms_crear();

/* Guarda un elemento en el cms, si la clave ya se encuentra en la
 * estructura, la reemplaza. De no poder guardarlo devuelve false.
 * Pre: La estructura cms fue inicializada
 * Post: Se almacenó el par (clave, dato)
 */
bool cms_guardar(cms_t *cms, const char *clave);


size_t cms_obtener(const cms_t *cms, const char *clave);

/* Destruye la estructura liberando la memoria pedida y llamando a la función
 * destruir para cada par (clave, dato).
 * Pre: La estructura cms fue inicializada
 * Post: La estructura cms fue destruida
 */
void cms_destruir(cms_t *cms);

#endif // COUNT_MIN_SKETCH_H
