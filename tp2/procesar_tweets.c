#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "hash.h"
#include "count_min_sketch.h"
#include "heap.h"
#include "strutil.h"

typedef struct tupla{
    const char *hashtag;
    size_t cantidad;
}tupla_t;


int cmp_min(const void *a, const void *b) {
    const tupla_t *x = (tupla_t*)a;
    const tupla_t *y = (tupla_t*)b;

    if ((x->cantidad < y->cantidad) || ((x->cantidad == y->cantidad) && (strcmp(x->hashtag, y->hashtag) > 0))){
        return -1;
    }
    return 1;
}


hash_t* obtener_tags(FILE* archivo, cms_t* cms, size_t cant_lineas){
    hash_t* hash = hash_crear(NULL);
    char *linea;
    char **strv;
    size_t tam = 0;

    if(!hash) return NULL;

    for(size_t i = 0; i < cant_lineas; i++){
            if(getline(&linea, &tam, archivo) == EOF) break;
            linea[strlen(linea)-1] = '\0';
            strv = split(linea, ',');
            for(size_t z = 1; strv[z]; z++){
                hash_guardar(hash, strv[z], NULL); 
                cms_guardar(cms, strv[z]);   
            }
            free_strv(strv);
    }

    return hash;
}


void llenar_heap(hash_t* hash, cms_t* cms, heap_t* heap, size_t cant_tags){
    hash_iter_t *hash_iter = hash_iter_crear(hash);
    if(!hash_iter) return;

    for(size_t i = 0; i < cant_tags && !hash_iter_al_final(hash_iter); i++){
        tupla_t* tupla = malloc(sizeof(tupla_t));
        tupla->hashtag = hash_iter_ver_actual(hash_iter);
        tupla->cantidad = cms_obtener(cms, tupla->hashtag);
        heap_encolar(heap, tupla);
        hash_iter_avanzar(hash_iter);
    }
    /*Va reemplazando (en el heap) los hashtags de mayor frecuencia*/
    while(!hash_iter_al_final(hash_iter)){
        tupla_t* tupla = malloc(sizeof(tupla_t));
        tupla->hashtag = hash_iter_ver_actual(hash_iter);
        tupla->cantidad = cms_obtener(cms, tupla->hashtag);
        tupla_t* tope = (tupla_t*)heap_ver_max(heap);
        if(tupla->cantidad > tope->cantidad){
            heap_desencolar(heap);
            heap_encolar(heap, tupla);
        }
        else free(tupla);
        hash_iter_avanzar(hash_iter);
    }
}


void imprimir_tweets(heap_t* heap, size_t* separador){
    size_t i = 0, cantidad = heap_cantidad(heap);
    tupla_t** vector_tuplas = malloc(sizeof(tupla_t*) * cantidad);
    if(!vector_tuplas) return;

    while(!heap_esta_vacio(heap)){
        vector_tuplas[cantidad-i-1] = heap_desencolar(heap);
        i++; 
    }
    *separador += 1;
    printf("--- %zu\n", *separador);
    for(size_t j = 0; j < cantidad; j++){
        printf("%zu %s\n", vector_tuplas[j]->cantidad, vector_tuplas[j]->hashtag);
    }
}


void procesar_tweets(FILE *archivo, size_t cant_lineas, size_t cant_tags){
    size_t separador = 0;
    cms_t* cms = cms_crear();
    heap_t* heap = heap_crear(cmp_min);

    while(!feof(archivo)){

        hash_t* hash = obtener_tags(archivo, cms, cant_lineas);
        if(hash_cantidad(hash)){
            llenar_heap(hash, cms, heap, cant_tags);
            imprimir_tweets(heap, &separador);
        }
        hash_destruir(hash);
    }


}


int main(int argc, char *argv[]){
    FILE *archivo = stdin; //Abre el archivo que se indico por stdin como segundo argumento
    if(!archivo){
        fprintf(stderr, "Error: archivo fuente inaccesible");
        return 0;
    }

    procesar_tweets(archivo, atoi(argv[1]), atoi(argv[2]));
    fclose(archivo);

    return 0;
}