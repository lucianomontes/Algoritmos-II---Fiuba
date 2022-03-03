#include "pila.h"
#include "testing.h"
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

// Declaracion constantes
#define PILA_VACIA 0
#define CAPACIDAD_INICIAL 8
#define TAM_VENTEROS 3
#define TAM_VCHAR 3
#define TAM_VARIOS 4
#define TAM_VOLUMEN 10000
#define POS_DIEZ_MIL 9999
#define VALOR_DOS 2


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/

// Pruebas crear y destruir pila
void pruebas_crear_destruir(){
    printf("\nINICIO PRUEBAS CREAR Y DESTRUIR\n");
    // declaro pila vacia
    pila_t* pila0 = pila_crear();

    //Verifico que se haya creado
    print_test("La pila0 se creo correctamente", pila0!=NULL);
    //Destruyo pila
    pila_destruir(pila0);
    print_test("La pila0 fue destruida", true);       
}


// Prueba apilar elemento y devuelve false en caso que algo este mal
bool prueba_apilar_elemento(pila_t* pila, void* valor){

    if(!pila_apilar(pila, valor) || !pila || pila_ver_tope(pila)!=valor ){
      return false;  
    }   
    return true;
}

// Prueba desapilar elemento
bool prueba_desapilar_elemento(pila_t* pila, void* valor){

    if(pila_desapilar(pila) != valor || !pila ){
        return false;
    }
    return true;
}

// Prueba apilamiento enteros
void prueba_enteros(){
    
    //Declaraciones
    pila_t* pila_enteros = pila_crear(); 
    int venteros[TAM_VENTEROS] = { 8, 2, 3};
    int ecantidad = PILA_VACIA;
    bool apilar = true;
    bool desapilar = true;

    //Verificamos que se haya creado
    print_test("La pila_enteros se creo correctamente", pila_enteros!=NULL);

    //Apilamos los enteros mientras verificamos que todo este correcto
    for(int i=0;i<TAM_VENTEROS;i++){
        (prueba_apilar_elemento(pila_enteros, &venteros[i]) ) ? ecantidad++ : (apilar=false) ;
    }
    print_test("Se apilo correctamente pila_enteros", apilar);
    print_test("Verifico cantidad elementos pila_enteros", ecantidad==TAM_VENTEROS);
    
    //Desapilamos y verificamos
    for(int j=2;j>=0;j--){
        (prueba_desapilar_elemento(pila_enteros, &venteros[j]) ) ? ecantidad-- : (desapilar=false) ;
    }
    print_test("Se desapilo correctamente pila_enteros", desapilar && ecantidad==PILA_VACIA);
    
    //Destruyo pila_enteros
    pila_destruir(pila_enteros);
    print_test("Se destruyo pila_enteros",true);
}

// Prueba apilamiento chars
void prueba_chars(){

    // Declaraciones
    pila_t* pila_char = pila_crear();
    char vchar[TAM_VCHAR] = "JWH";
    int char_cantidad = PILA_VACIA;
    bool apilar = true;
    bool desapilar = true;

    //Verificamos que se haya creado
    print_test("La pila_char se creo correctamente", pila_char!=NULL);

    //Apilamos los chars mientras verificamos que todo este correcto
    for(int i=0;i<TAM_VCHAR;i++){
        (prueba_apilar_elemento(pila_char, &vchar[i]) ) ? char_cantidad++ : (apilar=false);   
    }
    print_test("Se apilo correctamente pila_char", apilar);
    print_test("Verifico cantidad elemenentos pila_char", char_cantidad==TAM_VCHAR);

    //Desapilamos y verificamos
    for(int j=2;j>=0;j--){
        (prueba_desapilar_elemento(pila_char, &vchar[j]) ) ? char_cantidad-- : (desapilar=false);
    }
    print_test("Se desapilo correctamente pila_char", desapilar && char_cantidad==PILA_VACIA);
    
    //Destruyo pila_char
    pila_destruir(pila_char);
    print_test("Se destruyo pila_char",true);
}

// Prueba apilamiento varios
void prueba_varios(){

    // Declaraciones
    pila_t* pila_varios = pila_crear();
    double dvarios = 4.20;
    int vec_varios [TAM_VARIOS]= { 2, 7, 1, 5};
    char cadenav[TAM_VARIOS] = "Hola";

    //Verificamos que se haya creado
    print_test("La pila_varios se creo correctamente", pila_varios!=NULL);

    //Apilamos los chars mientras verificamos que todo este correcto
    print_test("Pila_varios se apilo correctamente", prueba_apilar_elemento(pila_varios,&dvarios) && prueba_apilar_elemento(pila_varios,&vec_varios) && prueba_apilar_elemento(pila_varios,&cadenav) );
    //Desapilamos y verificamos
    print_test("Se desapilo pila_varios correctamente", prueba_desapilar_elemento(pila_varios,&cadenav) && prueba_desapilar_elemento(pila_varios,&vec_varios) && prueba_desapilar_elemento(pila_varios,&dvarios) );

    //Destruimos pila_varios
    pila_destruir(pila_varios);
    print_test("Se destruyo pila_varios", true);
}
    
// Pruebas apilar elementos
void pruebas_apilar_desapilar(){

    printf("\nINICIO PRUEBAS APILAMIENTO\n");

    prueba_enteros();
    prueba_chars();
    prueba_varios();
}    

// Pruebas volumen y controlar invariantes
void pruebas_volumen(){

    printf("\nINICIO PRUEBAS VOLUMEN\n");
    // Declaraciones
    pila_t* pila_vol = pila_crear();
    int elementos_vol[TAM_VOLUMEN];
    int cantidad_vol = PILA_VACIA;
    bool apilar = true;
    bool desapilar = true;

    //Verificamos que se creo pila_vol
    print_test("Se creo correctamente pila_vol", pila_vol!=NULL);

    //Apilamos los enteros mientras verificamos que todo este correcto
    for(int i=0;i<TAM_VOLUMEN;i++){
        elementos_vol[i] = (rand() % TAM_VOLUMEN);
        (prueba_apilar_elemento(pila_vol, &elementos_vol[i]) ) ? cantidad_vol++ : (apilar=false);
    }
    print_test("Se apilo correctamente 10000 elementos", apilar);
    print_test("Prueba cantidad pila_vol igual 10000 elementos", cantidad_vol == TAM_VOLUMEN);

    // Desapilo pila_vol y verifico que todo sea correcto
    for(int j=POS_DIEZ_MIL;j>=0;j--){
        (prueba_desapilar_elemento(pila_vol, &elementos_vol[j]) ) ? cantidad_vol-- : (desapilar=false);
    }
    print_test("Se desapilo correctamente pila_vol", desapilar && cantidad_vol==PILA_VACIA);

    // Destruyo pila_vol
    pila_destruir(pila_vol);
}


// Prueba apilar elemento nulo
void prueba_apilar_nulo(){

    printf("\nINICIO PRUEBA APILAR ELEMENTO NULO\n");
    // Declaraciones
    pila_t* pila_nulo = pila_crear();
    void* pelemento_nulo = NULL;
    
    // Verificamos que se haya creado
    print_test("Se creo pila_nulo correctamente", pila_nulo!=NULL);

    // Apilamos elementos null en pula_nulo
    print_test("Se apilo el elemento nulo", prueba_apilar_elemento(pila_nulo, pelemento_nulo) );

    // Destruyo pila_nulo
    pila_destruir(pila_nulo);
    
}


// Prueba bordes
void prueba_bordes(){
    printf("\nINICIO PRUEBAS BORDES\n");
    pila_t* pila_borde = pila_crear();
    int elemento_borde = VALOR_DOS;
    bool apilar_desapilar = true;

    // Verifico que se haya creado pila_borde
    print_test("Se creo correctamente pila_borde", pila_borde!=NULL);

    // Verifico pila_borde esta vacia
    print_test("Verifico pila_borde esta vacia", pila_esta_vacia(pila_borde));

    // Verifico ver_tope y desapilar sean invalidas
    print_test("Verifico pila_ver_tope y pila_desapilar sean invalidas", pila_desapilar(pila_borde)==NULL && pila_ver_tope(pila_borde)==NULL);

    // Apilo y desapilo y vuelvo a chequear
    if(!prueba_apilar_elemento(pila_borde,&elemento_borde) || !prueba_apilar_elemento(pila_borde,&elemento_borde) ){
        apilar_desapilar = false;
    }
    if(!prueba_desapilar_elemento(pila_borde,&elemento_borde) || !prueba_desapilar_elemento(pila_borde,&elemento_borde) ){
        apilar_desapilar = false;
    }
    print_test("Apilar y desapilar pila_borde correctamente", apilar_desapilar);
    print_test("Verifico nuevamente pila_ver_tope y pila_desapilar sean invalidas", pila_desapilar(pila_borde)==NULL && pila_ver_tope(pila_borde)==NULL);

    // Destruyo pila borde
    pila_destruir(pila_borde);
    print_test("Destruyo pila_borde", true);
}


void pruebas_pila_alumno() {

    pruebas_crear_destruir();
    pruebas_apilar_desapilar();
    pruebas_volumen();
    prueba_apilar_nulo();
    prueba_bordes();
}
