#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "lista.h"
#include "hash.h"
#include "heap.h"
#include "strutil.h"
#include <string.h>


lista_t **ordenar_usuarios(hash_t *hash_usuarios, size_t posibles_valores){
    
    lista_t **vector_listas = malloc(sizeof(lista_t*)*posibles_valores);
    if(!vector_listas) return NULL;

    for(size_t i=0;i<posibles_valores;i++){
        vector_listas[i] = lista_crear();
        if(!vector_listas[i]) return NULL;
    }

    hash_iter_t* hash_iter_usuarios = hash_iter_crear(hash_usuarios);
    if(!hash_iter_usuarios) return NULL;

    char* usuario;
    size_t cant_tags;
    hash_t *hash_usuario;

    while(!hash_iter_al_final(hash_iter_usuarios)){

        usuario = (char*)hash_iter_ver_actual(hash_iter_usuarios);
        hash_usuario = (hash_t*)hash_obtener(hash_usuarios, usuario);
        cant_tags = hash_cantidad(hash_usuario);
        lista_insertar_primero(vector_listas[cant_tags], usuario);

        hash_iter_avanzar(hash_iter_usuarios);
    }

    hash_iter_destruir(hash_iter_usuarios);

    return vector_listas;
}

heap_t* ordenar_lista(lista_t* lista){

    heap_t* heap_min = heap_crear((cmp_func_t)strcmp);
    if(!heap_min) return NULL;

    while(!lista_esta_vacia(lista)){
        heap_encolar(heap_min, lista_borrar_primero(lista));
    }

    return heap_min;
}

void imprimir_usuarios(lista_t** vector_listas, size_t tam){

    heap_t *heap;
    for(size_t i=1;i<=tam;i++){

        if(!lista_esta_vacia(vector_listas[i])){
            printf("%ld :", i);
            heap = ordenar_lista(vector_listas[i]);

            while(!heap_esta_vacio(heap)){
                printf(" %s", (char*)heap_desencolar(heap));
                (heap_esta_vacio(heap)) ? printf("\n") : printf(","); 
            }
        heap_destruir(heap, NULL);
        }
    }
}

void procesar_usuarios(FILE *archivo){

    hash_t *hash_usuarios = hash_crear(NULL);
    if(!hash_usuarios) return;

    char *linea;
    char **strv;
    size_t tam = 0;
    size_t max_tags = 0;

    while(!feof(archivo) && getline(&linea, &tam, archivo) != -1){
        linea[strlen(linea)-1] = '\0';
        strv = split(linea, ',');
        hash_t* hash_usuario;

        for(size_t z = 0; strv[z] != NULL; z++){
            if(z == 0){
                if(!hash_pertenece(hash_usuarios, strv[z])){
                    hash_t* hash_unicos = hash_crear(NULL);
                    hash_guardar(hash_usuarios, strv[z], hash_unicos);
                }
                hash_usuario = hash_obtener(hash_usuarios, strv[0]);
            }    
            else {
                hash_guardar(hash_usuario, strv[z], NULL);
                if( max_tags < hash_cantidad(hash_usuario) ) max_tags = hash_cantidad(hash_usuario);     
            }
        }
        free_strv(strv);
    }    

    lista_t** vector_listas = ordenar_usuarios(hash_usuarios, max_tags+1);
    if(!vector_listas) return;
    
    imprimir_usuarios(vector_listas, max_tags);

    hash_destruir(hash_usuarios);
}



int main(int argc, char *argv[]){
    
    /*GUIA PARA DESPUES, EN REALIDAD HAY UN PIPING Y KCSHO*/
   /*  if(argc != 2){
        fprintf(stderr, "Error: Cantidad erronea de parametros");
        return 0;
    } */

    FILE *archivo = fopen(argv[1], "r"); //Abre el archivo que se indico por stdin como segundo argumento
    if(!archivo){
        fprintf(stderr, "Error: archivo fuente inaccesible");
        return 0;
    }

    procesar_usuarios(archivo);
    fclose(archivo);

    return 0;
}