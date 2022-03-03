#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include "count_min_sketch.h"

/* *****************************************************************
 *                            CONSTANTES
 * *****************************************************************/
#define TAM_VECTOR 457
#define CANT_VECTORES 3

/* *****************************************************************
 *                            ESTRUCTURAS
 * *****************************************************************/

struct cms{
    size_t **vec_contadores;
    size_t tam;
};

/* *****************************************************************
 *                       FUNCIONES DE HASH
 * *****************************************************************/
size_t fhash1(const char *clave, size_t tam) {
	size_t hash = 0;
	size_t i = 0;
	
    while (clave[i] != '\0') {
		hash = (hash << 2) ^ (hash >> 14) ^ (size_t) clave[i];
		i++;
	}

    return hash % tam;
}

size_t fhash2(const char *clave, size_t tam) {
    size_t hash = 5381;
    int c;
    
    while ((c = *clave++)){
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash % tam;
}

size_t fhash3(const char *clave, size_t tam){ 
	size_t hash; 
	
    for (hash = 0; *clave != '\0'; clave++){
		hash = *clave + 31 * hash;
	}

	return hash % tam;
}


/* *****************************************************************
 *                          PRIMITIVAS CMS
 * *****************************************************************/
cms_t *cms_crear(){
    cms_t *cms = malloc(sizeof(cms_t));
    size_t **vector_de_contadores = malloc(sizeof(size_t*) * CANT_VECTORES);
    size_t *contador1 = calloc(TAM_VECTOR, sizeof(size_t));
    size_t *contador2 = calloc(TAM_VECTOR, sizeof(size_t));
    size_t *contador3 = calloc(TAM_VECTOR, sizeof(size_t));

    if(!cms || !vector_de_contadores || !contador1 || !contador2 || !contador3){
        free(cms);
        free(vector_de_contadores);
        free(contador1);
        free(contador2);
        free(contador3);
        return NULL;
    }

    vector_de_contadores[0] = contador1;
    vector_de_contadores[1] = contador2;
    vector_de_contadores[2] = contador3;
    cms->vec_contadores = vector_de_contadores;
    cms->tam = TAM_VECTOR;

    return cms;
}


bool cms_guardar(cms_t *cms, const char *clave){
    if(!clave) return false;
    size_t pos1 = fhash1(clave, cms->tam);
    size_t pos2 = fhash2(clave, cms->tam);
    size_t pos3 = fhash3(clave, cms->tam);
    
    cms->vec_contadores[0][pos1]++;
    cms->vec_contadores[1][pos2]++;
    cms->vec_contadores[2][pos3]++;
    
    return true;
}


size_t cms_obtener(const cms_t *cms, const char *clave){
    size_t pos1 = fhash1(clave, cms->tam);
    size_t pos2 = fhash2(clave, cms->tam);
    size_t pos3 = fhash3(clave, cms->tam);
    size_t minimo;
    
    if(cms->vec_contadores[0][pos1] <= cms->vec_contadores[1][pos2] && cms->vec_contadores[0][pos1] <= cms->vec_contadores[2][pos3]){
        minimo = cms->vec_contadores[0][pos1];
    }
    else if(cms->vec_contadores[1][pos2] <= cms->vec_contadores[0][pos1] && cms->vec_contadores[1][pos2] <= cms->vec_contadores[2][pos3]){
        minimo = cms->vec_contadores[1][pos2];
    }
    else minimo = cms->vec_contadores[2][pos3];
    
    return minimo;
}


void cms_destruir(cms_t *cms){
    
    for(size_t i = 0; i < CANT_VECTORES; i++){
        free(cms->vec_contadores[i]);
    }
    free(cms->vec_contadores);
    free(cms);
}
