#include "heap.h"
#include "testing.h"    
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 


/*PARA EVITAR FLAGS*/
int strcmp_heap(const void *a, const void *b) {
    return strcmp(a, b);
}

int intcmp_heap(const void *a, const void *b) {
    const int *x = a;
    const int *y = b;

    if (*x < *y)
        return -1;
    return *x > *y;
}
/*PARA EVITAR FLAGS*/

static void prueba_crear_heap_vacio()
{
    heap_t* heap = heap_crear(strcmp_heap);

    print_test("Prueba heap crear heap vacio", heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap ver max es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba heap desencolar es false", !heap_desencolar(heap));

    heap_destruir(heap, NULL);
}

static void prueba_heap_volumen(size_t largo)
{
    heap_t* heap = heap_crear(intcmp_heap);
    int *valores = malloc(sizeof(int) * largo);
    /* Inserta 'largo' parejas en el heap */ 
    bool ok = true;
    for (int i = 0; i < largo; i++) {
        valores[i] = i;
        ok = heap_encolar(heap, &valores[i]);
        if (!ok) break;
    }

    print_test("Prueba heap almacenar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);
    print_test("Prueba heap maximo volumen", *(int*)heap_ver_max(heap) == valores[largo]);

    /* Verifica que borre y devuelva los valores correctos */
    for (int i = 0; i < largo; i++) {
        ok = ((int*)heap_desencolar(heap) == &valores[largo-1]);
        if (!ok) break;
    }

    print_test("Prueba heap borrar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    /* Destruye el heap*/
    heap_destruir(heap,NULL);
 
}


void pruebas_heap_alumno(void){

    prueba_crear_heap_vacio();
    prueba_heap_volumen(5000);

}
