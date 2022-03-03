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

static void prueba_heap_vacio(){
    printf("\n\nPRUEBAS HEAP VACIO\n\n");

    heap_t* heap = heap_crear(strcmp_heap);

    print_test("Prueba heap crear heap vacio", heap_esta_vacio(heap));
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);
    print_test("Prueba heap ver max es NULL, no existe", !heap_ver_max(heap));
    print_test("Prueba heap desencolar es false", !heap_desencolar(heap));

    heap_destruir(heap, NULL);
}

static void prueba_heap_pocos_valores(){
    printf("\n\nPRUEBAS HEAP POCOS VALORES\n\n");

    heap_t* heap = heap_crear(strcmp_heap);

    char *valor1 = "matrix";
    char *valor2 = "nabucodonosor";
    char *valor3 = "neo";

    /* Inserta 3 valores*/
    print_test("Prueba heap encolar valor1", heap_encolar(heap, valor1));
    print_test("Prueba heap encolar valor2", heap_encolar(heap, valor2));
    print_test("Prueba heap encolar valor3", heap_encolar(heap, valor3));

    /* Al desencolar cada elemento comprueba que sean los correctos al igual que la cantidad restante*/
    print_test("Prueba heap ver maximo es valor 3", (char*)heap_ver_max(heap) == valor3);
    print_test("Prueba heap desencolar es valor3", heap_desencolar(heap) == valor3);
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver maximo es valor 2", (char*)heap_ver_max(heap) == valor2);
    print_test("Prueba heap desencolar es valor2", heap_desencolar(heap) == valor2);
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver maximo es valor 1", (char*)heap_ver_max(heap) == valor1);
    print_test("Prueba heap desencolar es valor1", heap_desencolar(heap) == valor1);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);
}

static void prueba_heap_valor_null(){
    printf("\n\nPRUEBAS HEAP VALOR NULL\n\n");

    heap_t* heap = heap_crear(intcmp_heap);

    int *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba heap encolar valor NULL", heap_encolar(heap, valor));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap desencolar el valor NULL", heap_desencolar(heap) == valor);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);
}

static void prueba_heap_volumen(size_t largo){
    printf("\n\nPRUEBAS HEAP VOLUMEN\n\n");

    heap_t* heap = heap_crear(intcmp_heap);
    int *valores = malloc(sizeof(int) * largo);
    /* Inserta 'largo' parejas en el heap */ 
    bool ok = true;
    for (int i = 0; i < largo; i++) {
        valores[i] = (int) largo-i;
        ok = heap_encolar(heap, &valores[i]);
        if (!ok) break;
    }

    print_test("Prueba heap encolar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);
    print_test("Prueba heap maximo volumen", *(int*)heap_ver_max(heap) == valores[0]);

    /* Verifica que borre y devuelva los valores correctos */
    for (int i = 0; i < largo; i++) {
        ok = (*(int*)heap_desencolar(heap) == valores[i]);
        if (!ok) break;
    }

    print_test("Prueba heap desencolar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    /* Destruye el heap*/
    free(valores);
    heap_destruir(heap,NULL);
 
}

void pruebas_heap_alumno(void){

    prueba_heap_vacio();
    prueba_heap_pocos_valores();
    prueba_heap_valor_null();
    prueba_heap_volumen(5000);

}
