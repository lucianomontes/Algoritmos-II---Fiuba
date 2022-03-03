#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "lista.h"
#include "hash.h"
#include "heap.h"
#include "strutil.h"
#include <string.h>

// CONSTANTES
#define MAX_CARACTERES 15
#define POSIBLES_CARACTERES 37 // SI NO HAY CHAR (1) + NUMEROS 0 A 9 (10) + LETRAS MINUSCULAS (26)

// FUNCIONES
void destruir_vector_listas(lista_t** vector_listas){
    size_t i = 0;
    for(i = 0; vector_listas[i]; i++){
        lista_destruir(vector_listas[i], NULL);
    }
    free(vector_listas[i]);
    free(vector_listas);
}

// tam corresponde a los posibles valores que puede tomar el vector_lista a la hora de hacer counting sort
lista_t** vector_listas_crear(size_t tam){
    lista_t** vector_listas = malloc(sizeof(lista_t*)*(tam+1));
    if(!vector_listas) return NULL;

    for(size_t i = 0;i < tam; i++){
        vector_listas[i] = lista_crear();
        if(!vector_listas[i]){
            destruir_vector_listas(vector_listas);
            return NULL;
        }
    }
    vector_listas[tam] = NULL;

    return vector_listas;
}

size_t calcular_posicion(char* cadena, size_t pos_char){
    if(strlen(cadena)-1 < pos_char) return 0;

    if(cadena[pos_char] < 58) return cadena[pos_char]-47;

    return cadena[pos_char]-86;
}

void char_counting_sort(lista_t** vector_lista, lista_t* lista, size_t valores, size_t pos_char){

    char* usuario;
    size_t pos;
    // LISTA A VECTOR_LISTA ORDENADO POR POS_CHAR (MENOS SIGNIFICATIVO A MAS)
    while(!lista_esta_vacia(lista)){
        usuario = lista_borrar_primero(lista);
        pos = calcular_posicion(usuario, pos_char);
        lista_insertar_ultimo(vector_lista[pos], usuario);
    }
    // VUELVO A LLENAR LA LISTA PERO ORDENADO CON LA POS_CHAR QUE ESTAMOS TOMANDO
    for(size_t i = 0; vector_lista[i];i++){
        while(!lista_esta_vacia(vector_lista[i])){
            usuario = lista_borrar_primero(vector_lista[i]);
            lista_insertar_ultimo(lista, usuario);
        }
    }
}

void radix_sort(lista_t* lista, size_t valores){
    lista_t** vector_lista  = vector_listas_crear(valores);
    if(!vector_lista) return;

    // APLICO COUNTING SORT SIMPLIFICADO CON CADA POS_CHAR (DE MENOS A MAS SIGNIFICATIVO)
    for(size_t i = 1;i <= MAX_CARACTERES;i++){
        char_counting_sort(vector_lista, lista, valores, MAX_CARACTERES-i);
    }
    destruir_vector_listas(vector_lista);
}


lista_t **ordenar_usuarios(hash_t *hash_usuarios, size_t posibles_valores){    
    lista_t **vector_listas = vector_listas_crear(posibles_valores);
    if(!vector_listas) return NULL;

    hash_iter_t* hash_iter_usuarios = hash_iter_crear(hash_usuarios);
    if(!hash_iter_usuarios) return NULL;

    char* usuario;
    size_t cant_tags;
    hash_t *hash_unicos;

    while(!hash_iter_al_final(hash_iter_usuarios)){

        usuario = (char*)hash_iter_ver_actual(hash_iter_usuarios);
        hash_unicos = (hash_t*)hash_obtener(hash_usuarios, usuario);
        cant_tags = hash_cantidad(hash_unicos);
        lista_insertar_primero(vector_listas[cant_tags-1], usuario);
        hash_destruir(hash_unicos);
        hash_iter_avanzar(hash_iter_usuarios);
    }

    hash_iter_destruir(hash_iter_usuarios);

    return vector_listas;
}

void imprimir_usuarios(lista_t** vector_listas){
    size_t i = 0;
    for(i = 0; vector_listas[i] ; i++){
        if(!lista_esta_vacia(vector_listas[i])){
            printf("%ld:", i+1);
            radix_sort(vector_listas[i], POSIBLES_CARACTERES);

            while(!lista_esta_vacia(vector_listas[i])){
                printf(" %s", (char*)lista_borrar_primero(vector_listas[i]));
                (lista_esta_vacia(vector_listas[i])) ? printf("\n") : printf(","); 
            }
        }
    }
    destruir_vector_listas(vector_listas);
}

void procesar_usuarios(FILE *archivo){

    hash_t *hash_usuarios = hash_crear(NULL);
    if(!hash_usuarios) return;

    char *linea = NULL;
    char **strv;
    size_t tam = 0;
    size_t max_tags = 0;
    hash_t* hash_tags_usuario;

    while(!feof(archivo)){
        if(getline(&linea, &tam, archivo) == EOF) break;
        linea[strlen(linea)-1] = '\0';
        strv = split(linea, ',');

        if(!hash_pertenece(hash_usuarios, strv[0])){
            hash_t* hash_unicos = hash_crear(NULL);
            hash_guardar(hash_usuarios, strv[0], hash_unicos);
        }
        hash_tags_usuario = (hash_t*)hash_obtener(hash_usuarios, strv[0]);
        
        for(size_t z = 1; strv[z]; z++){
            hash_guardar(hash_tags_usuario, strv[z], NULL);
            if( max_tags < hash_cantidad(hash_tags_usuario) ) max_tags = hash_cantidad(hash_tags_usuario);              
        }
        free_strv(strv);
    }   
    free(linea);

    lista_t** vector_listas = ordenar_usuarios(hash_usuarios, max_tags);
    if(!vector_listas) return;
    
    imprimir_usuarios(vector_listas);

    hash_destruir(hash_usuarios);
}

int main(int argc, char *argv[]){
    FILE *archivo = fopen(argv[1], "r");
    if(!archivo){
        fprintf(stderr, "Error: archivo fuente inaccesible");
        return 0;
    }

    procesar_usuarios(archivo);
    fclose(archivo);

    return 0;
}