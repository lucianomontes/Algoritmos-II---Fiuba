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
    char *valor3 = "";

    /* Inserta 3 valores*/
    print_test("Prueba heap insertar valor1", heap_encolar(heap, valor1));
    print_test("Prueba heap insertar valor2", heap_encolar(heap, valor2));
    print_test("Prueba heap insertar valor3", heap_encolar(heap, valor3));

    /* Al borrar cada elemento comprueba que sean los correctos al igual que la cantidad restante*/
    print_test("Prueba heap ver maximo es valor 2", (char*)heap_ver_max(heap) == valor2);
    print_test("Prueba heap borrar es valor2", heap_desencolar(heap) == valor2);
    print_test("Prueba heap la cantidad de elementos es 2", heap_cantidad(heap) == 2);
    print_test("Prueba heap ver maximo es valor 1", (char*)heap_ver_max(heap) == valor1);
    print_test("Prueba heap borrar es valor1", heap_desencolar(heap) == valor1);
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap ver maximo es valor 3", (char*)heap_ver_max(heap) == valor3);
    print_test("Prueba heap borrar es valor3", heap_desencolar(heap) == valor3);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);
}

static void prueba_heap_valor_null(){
    printf("\n\nPRUEBAS HEAP VALOR NULL\n\n");

    heap_t* heap = heap_crear(intcmp_heap);

    int *valor = NULL;

    /* Inserta 1 valor y luego lo borra */
    print_test("Prueba heap insertar valor NULL", heap_encolar(heap, valor));
    print_test("Prueba heap la cantidad de elementos es 1", heap_cantidad(heap) == 1);
    print_test("Prueba heap borrar es valor NULL", heap_desencolar(heap) == valor);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);

    heap_destruir(heap, NULL);
}

static void prueba_heap_volumen(size_t largo){
    printf("\n\nPRUEBAS HEAP VOLUMEN\n\n");

    heap_t* heap = heap_crear(intcmp_heap);
    int *valores = malloc(sizeof(int) * largo);
    /* Inserta 'largo' parejas en el heap */ 
    bool ok = true;
    int maximo = 0;
    for (int i = 0; i < largo; i++) {
        valores[i] = (int)(rand() % largo);
        if(maximo < valores[i]) maximo = valores[i];
        ok = heap_encolar(heap, &valores[i]);
        if (!ok) break;
    }

    print_test("Prueba heap almacenar muchos elementos", ok);
    print_test("Prueba heap la cantidad de elementos es correcta", heap_cantidad(heap) == largo);
    print_test("Prueba heap maximo volumen", *(int*)heap_ver_max(heap) == maximo);

    /* Verifica que borre y devuelva los valores correctos */
    int valor_anterior = (*(int*)heap_desencolar(heap));
    int desencolados = 1;
    while(!heap_esta_vacio(heap)){
        ok = (*(int*)heap_desencolar(heap) <= valor_anterior);
        desencolados++;
        if (!ok) break;
    }

    print_test("Prueba heap borrar muchos elementos", desencolados == largo && ok);
    print_test("Prueba heap la cantidad de elementos es 0", heap_cantidad(heap) == 0);


    /* Destruye el heap y libera el vector usado*/
    heap_destruir(heap,NULL);
    free(valores); 
}

static void prueba_heapsort(){
    printf("\n\nPRUEBAS HEAPSORT\n\n");
    
    int largo = 10;
    void **valores = malloc(sizeof(void*)*largo);
    if(!valores) return;

    /* Asigno valores */
    for(size_t i=0;i<largo;i++){
        int* valor = malloc(sizeof(int*));
        *valor = rand() % largo;
        valores[i] = valor;
    }

    /* Prueba arreglo de 10 elementos */   
    print_test("Prueba crear arreglo 10 elementos desordenados", valores);

    /* Ordeno el arreglo mediante heap_sort */
    heap_sort(valores, largo, intcmp_heap);
    
    /* Verifico que este ordenado */
    bool ok = true;
    for(int i = 1; i < largo; i++){
        if( *(int*)valores[i] < *(int*)valores[i-1]) ok = false;
        if(!ok) break; 
    }
    print_test("Prueba arreglo ordenado mediante heapsort", ok);

    /* Libero memoria del arreglo */
    for(int i=0;i<largo;i++){
        free(valores[i]);
    }
    free(valores);
    print_test("Destruyo arreglo", true);
} 


void pruebas_heap_alumno(void){

    prueba_heap_vacio();
    prueba_heap_pocos_valores();
    prueba_heap_valor_null();
    prueba_heap_volumen(5000);
    prueba_heapsort();

}
