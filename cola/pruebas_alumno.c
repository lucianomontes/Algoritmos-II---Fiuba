#include "cola.h"
#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// Declaraciones constantes

#define TAM_VENTEROS 3
#define TAM_VCHAR 3
#define TAM_VARIOS 4
#define TAM_VOLUMEN 10000
#define COLA_VACIA 0
#define VALOR_DOS 2

// Encapsular/enmascarar pila_destruir
void destruir_dato_pila (void* pila){

    pila_destruir(pila);
}

/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

// Pruebas crear y destruir cola
void pruebas_crear_destruir(){
    printf("\nINICIO PRUEBAS CREAR Y DESTRUIR\n");
    // declaro cola vacia
    cola_t* cola0 = cola_crear();

    //Verifico que se haya creado
    print_test("La cola0 se creo correctamente", cola0!=NULL);
    //Destruyo cola
    cola_destruir(cola0,NULL);
    print_test("La cola0 fue destruida", true);       
}


// Prueba enteros
void prueba_enteros(){   
    //Declaraciones
    cola_t* cola_enteros = cola_crear(); 
    int venteros[TAM_VENTEROS] = { 8, 2, 3};
    int ecantidad = COLA_VACIA;
    bool encolar = true;
    bool desencolar = true;

    //Verificamos que se haya creado
    print_test("La cola_enteros se creo correctamente", cola_enteros!=NULL);

    //Encolamos los enteros mientras verificamos que todo este correcto
    for(int i=0;i<TAM_VENTEROS;i++){
        (cola_encolar(cola_enteros, &venteros[i]) ) ? ecantidad++ : (encolar=false) ;
    }
    print_test("Se encolo correctamente cola_enteros", encolar);
    print_test("Verifico cantidad elementos cola_enteros", ecantidad==TAM_VENTEROS);
    
    //Desencolamos y verificamos
    for(int j=0;j<TAM_VENTEROS;j++){
        (cola_desencolar(cola_enteros) == &venteros[j] ) ? ecantidad-- : (desencolar=false) ;
    }
    print_test("Se desencolo correctamente cola_enteros", desencolar && ecantidad==COLA_VACIA);
    
    //Destruyo cola_enteros
    cola_destruir(cola_enteros,NULL);
    print_test("Se destruyo cola_enteros",true);
}

// Prueba chars
void prueba_chars(){

    // Declaraciones
    cola_t* cola_char = cola_crear();
    char vchar[TAM_VCHAR] = "JWH";
    int char_cantidad = COLA_VACIA;
    bool encolar = true;
    bool desencolar = true;

    //Verificamos que se haya creado
    print_test("La cola_char se creo correctamente", cola_char!=NULL);

    //Encolamos los chars mientras verificamos que todo este correcto
    for(int i=0;i<TAM_VCHAR;i++){
        (cola_encolar(cola_char, &vchar[i]) ) ? char_cantidad++ : (encolar=false);   
    }
    print_test("Se apilo correctamente cola_char", encolar);
    print_test("Verifico cantidad elemenentos cola_char", char_cantidad==TAM_VCHAR);

    //Desencolamos y verificamos
    for(int j=0;j<TAM_VCHAR;j++){
        (cola_desencolar(cola_char) == &vchar[j] ) ? char_cantidad-- : (desencolar=false);
    }
    print_test("Se desapilo correctamente cola_char", desencolar && char_cantidad==COLA_VACIA);
    
    //Destruyo cola_char
    cola_destruir(cola_char,NULL);
    print_test("Se destruyo cola_char",true);
}

// Prueba encolamiento varios
void prueba_varios(){

    // Declaraciones
    cola_t* cola_varios = cola_crear();
    double dvarios = 4.20;
    int vec_varios [TAM_VARIOS]= { 2, 7, 1, 5};
    char cadenav[TAM_VARIOS] = "Hola";

    //Verificamos que se haya creado
    print_test("La cola_varios se creo correctamente", cola_varios!=NULL);

    //Encolamos los chars mientras verificamos que todo este correcto
    print_test("cola_varios se apilo correctamente", cola_encolar(cola_varios,&dvarios) && cola_encolar(cola_varios,&vec_varios) && cola_encolar(cola_varios,&cadenav) );
    
    //Desencolamos y verificamos
    print_test("Se desapilo cola_varios correctamente", cola_desencolar(cola_varios)==&dvarios && cola_desencolar(cola_varios)==&vec_varios && cola_desencolar(cola_varios)==&cadenav );

    //Destruimos cola_varios
    cola_destruir(cola_varios,NULL);
    print_test("Se destruyo cola_varios", true);
}


// Prueba encolamento pila
void prueba_pila(){

    //Declaraciones
    cola_t* cola_con_pila = cola_crear();
    pila_t* pila0 = pila_crear();

    //Verificamos que se haya creado
    print_test("La cola_con_pila se creo correctamente", cola_con_pila!=NULL);

    //Encolamos la pila mientras verificamos que todo este correcto
    print_test("cola_con_pila se encolo correctamente", cola_encolar(cola_con_pila, pila0) );

    //Destruimos cola_con pila
    cola_destruir(cola_con_pila, destruir_dato_pila);
    print_test("Se destruyo cola_con_pila", true);
} 


// Pruebas encolar y desencolar elementos
void pruebas_encolar_desencolar(){

    printf("\nINICIO PRUEBAS ENCOLAR Y DESENCOLAR ESTATICO\n");

    prueba_enteros();
    prueba_chars();
    prueba_varios(); 

    printf("\nINICIO PRUEBAS ENCOLAR Y DESENCOLAR DINAMICO\n");

    prueba_pila();
}


// Pruebas volume
void pruebas_volumen(){

    printf("\nINICIO PRUEBAS VOLUMEN\n");
    // Declaraciones
    cola_t* cola_vol = cola_crear();
    int elementos_vol[TAM_VOLUMEN];
    int cantidad_vol = COLA_VACIA;
    bool encolar = true;
    bool desencolar = true;

    //Verificamos que se creo cola_vol
    print_test("Se creo correctamente cola_vol", cola_vol!=NULL);

    //Encolamos los enteros mientras verificamos que todo este correcto
    for(int i=0;i<TAM_VOLUMEN;i++){
        elementos_vol[i] = (rand() % TAM_VOLUMEN);
        (cola_encolar(cola_vol, &elementos_vol[i]) ) ? cantidad_vol++ : (encolar=false);
    }
    print_test("Se encolo correctamente 10000 elementos", encolar);
    print_test("Prueba cantidad cola_vol igual 10000 elementos", cantidad_vol == TAM_VOLUMEN);

    // Desencolo cola_vol y verifico que todo sea correcto
    for(int j=0;j<TAM_VOLUMEN;j++){
        (cola_desencolar(cola_vol) == &elementos_vol[j] ) ? cantidad_vol-- : (desencolar=false);
    }
    print_test("Se desencolo correctamente cola_vol", desencolar && cantidad_vol==COLA_VACIA);

    // Destruyo cola_vol
    cola_destruir(cola_vol,NULL);
    print_test("Se destruyo cola_vol", true);
}


// Prueba encolar elemento nulo
void prueba_encolar_nulo(){

    printf("\nINICIO PRUEBA ENCOLAR ELEMENTO NULO\n");
    // Declaraciones
    cola_t* cola_nulo = cola_crear();
    void* pelemento_nulo = NULL;
    
    // Verificamos que se haya creado
    print_test("Se creo cola_nulo correctamente", cola_nulo!=NULL);

    // Encolamos elementos null en pula_nulo
    print_test("Se encolo el elemento nulo", cola_encolar(cola_nulo, pelemento_nulo) );

    // Destruyo cola_nulo
    cola_destruir(cola_nulo,NULL);
    print_test("Se destruyo cola_nulo", true);
}


// Prueba bordes
void prueba_bordes(){
    printf("\nINICIO PRUEBAS BORDES\n");
    cola_t* cola_borde = cola_crear();
    int elemento_borde = VALOR_DOS;
    bool encolar = true;
    bool desencolar = true;

    // Verifico que se haya creado cola_borde
    print_test("Se creo correctamente cola_borde", cola_borde!=NULL);

    // Verifico cola_borde esta vacia
    print_test("Verifico cola_borde esta vacia", cola_esta_vacia(cola_borde));

    // Verifico cola_ver_primero y desencolar sean invalidas
    print_test("Verifico cola_ver_primero y desencolar sean invalidas", cola_desencolar(cola_borde)==NULL && cola_ver_primero(cola_borde)==NULL);

    // Encolo y desencolo y vuelvo a chequear
    if(!cola_encolar(cola_borde,&elemento_borde) || !cola_encolar(cola_borde,&elemento_borde) ){
        encolar = false;
    }
    if(cola_desencolar(cola_borde)!= &elemento_borde || cola_desencolar(cola_borde)!= &elemento_borde ){
        desencolar = false;
    }
    print_test("Encolar y desencolar cola_borde correctamente", encolar && desencolar);
    print_test("Verifico nuevamente cola_ver_primero y cola_desencolar sean invalidas", cola_desencolar(cola_borde)==NULL && cola_ver_primero(cola_borde)==NULL);

    // Destruyo cola borde
    cola_destruir(cola_borde,NULL);
    print_test("Destruyo cola_borde", true);
}


void pruebas_cola_alumno(void){
    
    pruebas_crear_destruir();
    pruebas_encolar_desencolar();
    pruebas_volumen();  
    prueba_encolar_nulo();
    prueba_bordes();
}