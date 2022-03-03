#ifndef _BF_H
#define _BF_H

#include <stdbool.h>
#include <stdio.h>

// DECLARACION DE ESTRUCTURAS

struct celda;

typedef struct celda celda_t;


// DECLARACION DE FUNCIONES

celda_t* crear_celdas();

void destruir_celdas(celda_t* celda);

void interpretar(celda_t* celda, const unsigned char accion, FILE* bf, pila_t* pila_ciclos);


#endif // _BF_H