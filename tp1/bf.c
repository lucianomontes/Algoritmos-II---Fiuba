#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "pila.h"
#include "bf.h"


// DEFINICION CONSTANTES

#define TAM_CELDAS 30000
#define CELDA_INICIAL 0
#define VALOR_INICIAL 0
#define VALOR_CERO 0
#define VALOR_UNO 1
#define POS_SEGUNDO_PARAMETRO 1
#define DOS_PARAMETROS 2
#define UN_PARAMETRO 1
#define POS_CERO 0


// DEFINICION ESTRUCTURAS

struct celda{
    unsigned char* valores;
    int actual;
    size_t cantidad; // PARA POSIBLE REDIMENCION DE CELDAS..
};


// FUNCIONES AUXILIARES

void caso_apertura(celda_t* celda, const unsigned char accion, FILE* bf, pila_t* pila_ciclos){

    if(celda->valores[celda->actual] == VALOR_CERO){
        int contador = VALOR_UNO;
        unsigned char accion;
        while(contador!=VALOR_CERO){
            accion = (unsigned char)fgetc(bf);
            if(accion == '[') contador++;
            else if(accion == ']') contador--;
        }
    }
    else{
        long int *posicion = malloc(sizeof(long int));
        if(!posicion) return;
        *(posicion) = ftell(bf)-1;
        pila_apilar(pila_ciclos, posicion);
    }
}

void caso_cierre(celda_t* celda, const unsigned char accion, FILE* bf, pila_t* pila_ciclos){

    long int *posicion = (long int*)pila_desapilar(pila_ciclos);
    if(celda->valores[celda->actual] != VALOR_CERO){
        fseek(bf, *posicion, SEEK_SET);
    }   
    free(posicion);    
}


// FUNCIONES 

celda_t* crear_celdas(){

    celda_t* celda = malloc(sizeof(celda_t));
    if(!celda) return NULL;

    unsigned char* valores = malloc(sizeof(unsigned char)*TAM_CELDAS);
    if(!valores) return NULL;

    for(size_t i=0;i<TAM_CELDAS;i++){
        valores[i] = VALOR_INICIAL;
    }

    celda->cantidad = TAM_CELDAS;
    celda->valores = valores;
    celda->actual = CELDA_INICIAL;

    return celda;
}

void destruir_celdas(celda_t* celda){

    if(!celda) return;

    free(celda->valores);
    free(celda);
}


void interpretar(celda_t* celda, const unsigned char accion, FILE* bf, pila_t* pila_ciclos){

    switch(accion){

    case '+':
        celda->valores[celda->actual]++; 
        break;
    
    case '-':
        celda->valores[celda->actual]--; 
        break;

    case '>':
        if(celda->actual < celda->cantidad-1) celda->actual++; // POSIBLE FUTURA REDIMENCION,,
        break;

    case '<':
        if(celda->actual > POS_CERO) celda->actual--;    
        break;

    case '.':
        printf("%c", celda->valores[celda->actual]);
        break;

    case ',': ;
        char valor;
        scanf("%c", &valor);
        celda->valores[celda->actual] = (unsigned char)valor;
        break;

    case '[': 
        caso_apertura(celda, accion, bf, pila_ciclos);
        break;

    case ']': 
        caso_cierre(celda, accion, bf, pila_ciclos);
        break;

    default:
        break;
    }
}


// MAIN BRAINFUCK

int main(int argc, char** argv){

    FILE* bf;
    if(argc == DOS_PARAMETROS){
        bf = fopen(argv[POS_SEGUNDO_PARAMETRO], "r");
        if(!bf){
            printf("Error: archivo fuente inaccesible.\n");
            return 0; 
        }       
    }
    else if(argc == UN_PARAMETRO) bf = stdin;
    else{
        printf("Error: Cantidad erronea de parametros.\n");
        return 0;
    }

    celda_t* celda = crear_celdas();
    if(!celda) return 0;

    pila_t* pila_ciclos = pila_crear();
    if(!pila_ciclos) return 0;

    while(!feof(bf)){    
        interpretar( celda, (unsigned char)fgetc(bf), bf, pila_ciclos);
    } 

    pila_destruir(pila_ciclos);
    destruir_celdas(celda);
    fclose(bf);

    return 0;
}
