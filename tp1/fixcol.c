#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

// CONSTANTES

#define VALOR_CERO 0
#define VALOR_UNO 1
#define TRES_PARAMETROS 3
#define POS_SEGUNDO_PARAMETRO 1
#define POS_TERCER_PARAMETRO 2


// MAIN FIXCOL

int main(int argc, char** argv){

    if(argc!=TRES_PARAMETROS){
        fprintf(stderr, "Error: Cantidad erronea de parametros");
        return 0;
    } 

    FILE *archivo = fopen (argv[POS_SEGUNDO_PARAMETRO], "r");
    if(!archivo){
        fprintf(stderr, "Error: archivo fuente inaccesible");
    }

    size_t i = VALOR_CERO;
    size_t columnas;
    int caracter;

    columnas = atoi(argv[POS_TERCER_PARAMETRO]);

    if(columnas==VALOR_CERO) return 0;

    while( (caracter = fgetc(archivo)) != -1){

        if(caracter == '\n'){
            i=VALOR_CERO;
        }
        else if(i == columnas){   
            printf("\n");  
            i=VALOR_UNO;
        }
        else{
            i++;
        } 
        printf("%c", caracter);
    }

    fclose(archivo);
}