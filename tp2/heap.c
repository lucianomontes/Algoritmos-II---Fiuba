/* *****************************************************************
 *      NOMBRE Y APELLIDO : LUCIANO NICOLAS MONTES PADRON: 102536
 *      NOMBRE Y APELLIDO : AGUSTIN LOPEZ NUÑEZ    PADRON: 101826
 * *****************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "heap.h"

/* *****************************************************************
 *                          CONSTANTES
 * *****************************************************************/

#define POS_CERO 0
#define TAM_INICIAL 24
#define AMPLIAR 2
#define REDUCIR 2
#define FACTOR_CARGA_MIN 0.25
#define CANTIDAD_UNO 1


/* *****************************************************************
 *                          ESTRUCTURAS
 * *****************************************************************/

struct heap{
    void **vector; //sujeto a cambios
	size_t cant;
	size_t tam;
	cmp_func_t cmp;
};

/* *****************************************************************
 *                       FUNCIONES AUXILIARES
 * *****************************************************************/

 void **copiar_arreglo(void **arreglo, size_t n){
    void **copia  = malloc(sizeof(void*) * n);
    if(!copia) return NULL;

    for(size_t i = 0; i < n; i++){
        copia[i] = arreglo[i];
    }

    return copia;
}

bool heap_redimensionar(heap_t *heap, size_t tam_nuevo){
    void** vector_nuevo = realloc(heap->vector, tam_nuevo * sizeof(void*));
    if(!vector_nuevo) return false;

    heap->vector = vector_nuevo;
    heap->tam = tam_nuevo;

    return true;
}

void swap(void *arreglo[], size_t pos1, size_t pos2){
    void* valor1 = arreglo[pos1];
    void* valor2 = arreglo[pos2];

    arreglo[pos1] = valor2;
    arreglo[pos2] = valor1;
}

void upheap(void *arreglo[], size_t pos, cmp_func_t cmp){
    size_t pos_padre = (pos-1)/2;

    if(pos <= 0) return;
    
    if(cmp(arreglo[pos_padre], arreglo[pos]) > 0){
        swap(arreglo, pos_padre, pos);
        upheap(arreglo, pos_padre, cmp);
    } 
}


void downheap(void *arreglo[], size_t tam, size_t pos, cmp_func_t cmp){

    if (pos >= tam) return;
	size_t max = pos; // PADRE
	size_t izq = 2 * pos + 1;
	size_t der = 2 * pos + 2;
	if (izq < tam && cmp(arreglo[max], arreglo[izq]) > 0) max = izq;
	if (der < tam && cmp(arreglo[max], arreglo[der]) > 0) max = der;
	if (max != pos){
		swap(arreglo, pos, max);
		downheap(arreglo, tam, max, cmp);
    }
}

void heapify(void *arreglo[], size_t n, cmp_func_t cmp){
    
    for(size_t i = (n/2)-1; i+1 > 0; i--){
        downheap(arreglo, n, i, cmp);
    }
}
/* *****************************************************************
 *                        PRIMITIVAS HEAP
 * *****************************************************************/


/* Crea un heap. Recibe como único parámetro la función de comparación a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir().
 */
heap_t *heap_crear(cmp_func_t cmp){
    heap_t *heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;

    void** vector = malloc(sizeof(void*)*TAM_INICIAL);
    if(!vector){
        free(heap);
        return NULL;
    } 

    heap->vector = vector;
    heap->cant = 0;
    heap->tam = TAM_INICIAL;
    heap->cmp = cmp;

    return heap;
}


/*
 * Constructor alternativo del heap. Además de la función de comparación,
 * recibe un arreglo de valores con que inicializar el heap. Complejidad
 * O(n).
 *
 * Excepto por la complejidad, es equivalente a crear un heap vacío y encolar
 * los valores de uno en uno
*/
heap_t *heap_crear_arr(void *arreglo[], size_t n, cmp_func_t cmp){
    heap_t *heap = malloc(sizeof(heap_t));
    if(!heap) return NULL;

    void **arreglo_copia = copiar_arreglo(arreglo, n);
    if(!arreglo_copia){
        free(heap);
        return NULL;
    }

    heapify(arreglo_copia, n, cmp);
    heap->vector = arreglo_copia;
    heap->cant = n;
    heap->tam = n;
    heap->cmp = cmp;

    return heap;
}


/* Elimina el heap, llamando a la función dada para cada elemento del mismo.
 * El puntero a la función puede ser NULL, en cuyo caso no se llamará.
 * Post: se llamó a la función indicada con cada elemento del heap. El heap
 * dejó de ser válido. */
void heap_destruir(heap_t *heap, void destruir_elemento(void *e)){

    if(destruir_elemento){    
        for(size_t i = 0; i < heap->cant; i++){
            destruir_elemento(heap->vector[i]);
        }    
    }
    free(heap->vector);
    free(heap);
}


/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
    
    return heap->cant;
}

/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){
    
    return !heap->cant;
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operación exitosa, o false en caso de error.
 * Pre: el heap fue creado.
 * Post: se agregó un nuevo elemento al heap.
 */
bool heap_encolar(heap_t *heap, void *elem){

    if(heap->cant == heap->tam){
        if(!heap_redimensionar(heap, heap->tam * AMPLIAR)) return false;
    }    

    heap->vector[heap->cant] = elem;
    heap->cant++;
    upheap(heap->vector, heap->cant-1, heap->cmp);
    
    return true;
}


/* Devuelve el elemento con máxima prioridad. Si el heap esta vacío, devuelve
 * NULL.
 * Pre: el heap fue creado.
 */
void *heap_ver_max(const heap_t *heap){
    
    if(heap_esta_vacio(heap)) return NULL;
     
    return heap->vector[0];
}


/* Elimina el elemento con máxima prioridad, y lo devuelve.
 * Si el heap esta vacío, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap.
 */
void *heap_desencolar(heap_t *heap){
    float factor_carga = (float)heap->cant / (float)heap->tam;

    if((factor_carga < FACTOR_CARGA_MIN) && (heap->tam / REDUCIR > TAM_INICIAL)){
        if(!heap_redimensionar(heap, heap->tam / REDUCIR)) return NULL;
    }

    if(heap_esta_vacio(heap)) return NULL;
    if(heap->cant != CANTIDAD_UNO) swap(heap->vector, POS_CERO, heap->cant-1);

    void* dato = heap->vector[heap->cant-1];
    heap->vector[heap->cant-1] = NULL;
    heap->cant--;

    downheap(heap->vector, heap->cant, POS_CERO, heap->cmp);

    return dato;
}


void heap_sort(void *elementos[], size_t cant, cmp_func_t cmp){
    heapify(elementos, cant, cmp);

    for(size_t i = 0; i < cant; i++){
        swap(elementos, POS_CERO, cant-1-i);
        if(i < cant-1)downheap(elementos, cant-1-i, POS_CERO, cmp);
    }
}
