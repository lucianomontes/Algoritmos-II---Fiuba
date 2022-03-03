#include "lista.h"
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
#define TAM_VENTEROS1 10
#define LARGO_CERO 0
#define VALOR_CERO 0
#define VALOR_UNO 1
#define VALOR_DOS 2
#define DUPLICAR 2
#define TOPE_TRES 3
#define TRES_CEROS 3

// Encapsular/enmascarar pila_destruir
void destruir_dato_pila (void* pila){

    pila_destruir(pila);
}

// Encapsular/enmascarar cola_destruir
void destruir_dato_cola (void* cola){

    cola_destruir(cola,NULL);
}

// Funciones barbara

bool duplicar(void* dato, void* extra){
    *(int*)dato *= DUPLICAR;

    return true;
}

bool f_valor_uno(void* dato, void* extra){
    *(int*)dato = VALOR_UNO;

    return true;
}

bool imprimir(void* dato, void* extra){
    printf(" %d", *(int*)dato );

    return true;
}

bool tres_primeros_cero(void* dato, void* extra){
    if(*(int*)extra>=TOPE_TRES) return false;

    *(int*)dato = VALOR_CERO;
    (*(int*)extra)++;

    return true;

}


/* ******************************************************************
 *                   PRUEBAS UNITARIAS ALUMNO
 * *****************************************************************/


// Pruebas crear y destruir lista
void pruebas_crear_destruir(){
    printf("\nINICIO PRUEBAS CREAR Y DESTRUIR\n");
    // declaro lista vacia
    lista_t* lista0 = lista_crear();

    //Verifico que se haya creado
    print_test("La lista0 se creo correctamente", lista0!=NULL);
    //Destruyo lista
    lista_destruir(lista0,NULL);
    print_test("La lista0 fue destruida", true);       
}


// Prueba enteros
void prueba_enteros(){   
    //Declaraciones
    lista_t* lista_enteros = lista_crear(); 
    int venteros[TAM_VENTEROS] = { 8, 2, 3};
    int elargo = LARGO_CERO;
    bool insertar = true;
    bool borrar = true;

    //Verificamos que se haya creado
    print_test("La lista_enteros se creo correctamente", lista_enteros!=NULL);

    //Insertamos los enteros en la primer posicion mientras verificamos que todo este correcto
    for(int i=0;i<TAM_VENTEROS;i++){
        (lista_insertar_primero(lista_enteros, &venteros[i]) ) ? elargo++ : (insertar=false) ;
    }
    print_test("Se inserto correctamente elementos en lista_enteros", insertar);
    print_test("Verifico largo de lista_enteros", elargo==TAM_VENTEROS);
    
    //Borramos los elementos y verificamos
    for(int j=2;j>=0;j--){
        (lista_borrar_primero(lista_enteros) == &venteros[j] ) ? elargo-- : (borrar=false) ;
    }
    print_test("Se borro correctamente elementos lista_enteros", borrar && elargo==LARGO_CERO);
    
    //Destruyo lista_enteros
    lista_destruir(lista_enteros,NULL);
    print_test("Se destruyo lista_enteros",true);
}

// Prueba chars
void prueba_chars(){

    // Declaraciones
    lista_t* lista_char = lista_crear();
    char vchar[TAM_VCHAR] = "JWH";
    int char_largo = LARGO_CERO;
    bool insertar = true;
    bool borrar = true;

    //Verificamos que se haya creado
    print_test("La lista_char se creo correctamente", lista_char!=NULL);

    //Insertamos los chars al ultimo mientras verificamos que todo este correcto
    for(int i=0;i<TAM_VCHAR;i++){
        (lista_insertar_ultimo(lista_char, &vchar[i]) ) ? char_largo++ : (insertar=false);   
    }
    print_test("Se inserto elementos correctamente lista_char", insertar);
    print_test("Verifico largo de lista_char", char_largo==TAM_VCHAR);

    //Borrarmos los elementos y verificamos
    for(int j=0;j<TAM_VCHAR;j++){
        (lista_borrar_primero(lista_char) == &vchar[j] ) ? char_largo-- : (borrar=false);
    }
    print_test("Se borro correctamente elementos lista_char", borrar && char_largo==LARGO_CERO);
    
    //Destruyo lista_char
    lista_destruir(lista_char,NULL);
    print_test("Se destruyo lista_char",true);
}

//Prueba insertar y borrar varios
void prueba_varios(){

    // Declaraciones
    lista_t* lista_varios = lista_crear();
    double dvarios = 4.20;
    int vec_varios [TAM_VARIOS]= { 2, 7, 1, 5};
    char cadenav[TAM_VARIOS] = "Hola";

    //Verificamos que se haya creado
    print_test("La lista_varios se creo correctamente", lista_varios!=NULL);

    //Insertamos al ultimo los elementos mientras verificamos que todo este correcto
    print_test("lista_varios se apilo correctamente", lista_insertar_ultimo(lista_varios,&dvarios) && lista_insertar_ultimo(lista_varios,&vec_varios) && lista_insertar_ultimo(lista_varios,&cadenav) );
    
    //Borramos los elementos y verificamos
    print_test("Se borraron los elementos lista_varios correctamente", lista_borrar_primero(lista_varios)==&dvarios && lista_borrar_primero(lista_varios)==&vec_varios && lista_borrar_primero(lista_varios)==&cadenav );

    //Destruimos lista_varios
    lista_destruir(lista_varios,NULL);
    print_test("Se destruyo lista_varios", true);
}

// Prueba insertar y borrar pila
void prueba_pila(){

    //Declaraciones
    lista_t* lista_con_pila = lista_crear();
    pila_t* pila0 = pila_crear();

    //Verificamos que se haya creado
    print_test("La lista_con_pila se creo correctamente", lista_con_pila!=NULL);

    //Insertamos la pila mientras verificamos que todo este correcto
    print_test("Se inserto pila en lista_con_pila correctamente", lista_insertar_primero(lista_con_pila, pila0) );

    //Destruimos lista_con_pila
    lista_destruir(lista_con_pila, destruir_dato_pila);
    print_test("Se destruyo lista_con_pila", true);
} 

// Prueba insertar y borrar cola
void prueba_cola(){

    //Declaraciones
    lista_t* lista_con_cola = lista_crear();
    cola_t* cola0 = cola_crear();

    //Verificamos que se haya creado
    print_test("La lista_con_cola se creo correctamente", lista_con_cola!=NULL);

    //Insertamos la cola mientras verificamos que todo este correcto
    print_test("Se inserto cola en lista_con_cola correctamente", lista_insertar_primero(lista_con_cola, cola0) );

    //Destruimos lista_con_cola
    lista_destruir(lista_con_cola, destruir_dato_cola);
    print_test("Se destruyo lista_con_cola", true);
} 

// Pruebas insertar y borrar elementos
void pruebas_insertar_borrar(){

    printf("\nINICIO PRUEBAS INSERTAR Y BORRAR ESTATICO\n");

    prueba_enteros();
    prueba_chars();
    prueba_varios(); 

    printf("\nINICIO PRUEBAS INSERTAR Y BORRAR DINAMICO\n");

    prueba_pila();
    prueba_cola();
}


// Pruebas volumen
void pruebas_volumen(){

    printf("\nINICIO PRUEBAS VOLUMEN\n");
    // Declaraciones
    lista_t* lista_vol = lista_crear();
    int elementos_vol[TAM_VOLUMEN];
    int largo_vol = LARGO_CERO;
    bool insertar = true;
    bool borrar = true;

    //Verificamos que se creo lista_vol
    print_test("Se creo correctamente lista_vol", lista_vol!=NULL);

    //Insertamos los enteros mientras verificamos que todo este correcto
    for(int i=0;i<TAM_VOLUMEN;i++){
        elementos_vol[i] = (rand() % TAM_VOLUMEN);
        (lista_insertar_ultimo(lista_vol, &elementos_vol[i]) ) ? largo_vol++ : (insertar=false);
    }
    print_test("Se inserto correctamente 10000 elementos", insertar);
    print_test("Prueba largo lista_vol igual 10000 elementos", largo_vol == TAM_VOLUMEN);

    // Borro elementos lista_vol y verifico que todo sea correcto
    for(int j=0;j<TAM_VOLUMEN;j++){
        (lista_borrar_primero(lista_vol) == &elementos_vol[j] ) ? largo_vol-- : (borrar=false);
    }
    print_test("Se borro correctamente elementos lista_vol", borrar && largo_vol==LARGO_CERO);

    // Destruyo lista_vol
    lista_destruir(lista_vol,NULL);
    print_test("Se destruyo lista_vol", true);
}


// Prueba insertar elemento nulo
void prueba_insertar_nulo(){

    printf("\nINICIO PRUEBA INSERTAR ELEMENTO NULO\n");
    // Declaraciones
    lista_t* lista_nulo = lista_crear();
    void* pelemento_nulo = NULL;
    
    // Verificamos que se haya creado
    print_test("Se creo lista_nulo correctamente", lista_nulo!=NULL);

    // Encolamos elementos NULL en lista_nulo
    print_test("Se inserto el elemento nulo", lista_insertar_primero(lista_nulo, pelemento_nulo) );

    // lista_nulo no esta vacia
    print_test("Comprobamos lista_nulo no este vacia", !lista_esta_vacia(lista_nulo) );

    // Destruyo lista_nulo
    lista_destruir(lista_nulo,NULL);
    print_test("Se destruyo lista_nulo", true);
}


// Prueba bordes
void prueba_bordes(){
    printf("\nINICIO PRUEBAS BORDES\n");
    lista_t* lista_borde = lista_crear();
    int elemento_borde = VALOR_DOS;
    bool insertar = true;
    bool borrar = true;

    // Verifico que se haya creado lista_borde
    print_test("Se creo correctamente lista_borde", lista_borde!=NULL);

    // Verifico lista_borde esta vacia
    print_test("Verifico lista_borde esta vacia", lista_esta_vacia(lista_borde));

    // Verifico lista_ver_primero y borrar sean invalidas
    print_test("Verifico lista_ver_primero y borrar sean invalidas", lista_borrar_primero(lista_borde)==NULL && lista_ver_primero(lista_borde)==NULL);

    // Inserto y borro y vuelvo a chequear
    if(!lista_insertar_primero(lista_borde,&elemento_borde) || !lista_insertar_primero(lista_borde,&elemento_borde) ){
        insertar = false;
    }
    if(lista_borrar_primero(lista_borde)!= &elemento_borde || lista_borrar_primero(lista_borde)!= &elemento_borde ){
        borrar = false;
    }
    print_test("Insertar y borrar lista_borde correctamente", insertar && borrar);
    print_test("Verifico nuevamente list_ver_primero y borrar sean invalidas", lista_borrar_primero(lista_borde)==NULL && lista_ver_primero(lista_borde)==NULL);

    // Destruyo lista_borde
    lista_destruir(lista_borde,NULL);
    print_test("Destruyo lista_borde", true);
}


// Pruebas lista iter inicio y final
void pruebas_iter_inicio_final(){

    lista_t* lista_iter0 = lista_crear();
    lista_iter_t* iter0 = lista_iter_crear(lista_iter0);
    int elemento0 = VALOR_CERO;
    int elemento2 = VALOR_DOS;

    // Verifico que se haya creado lista_iter0 y iter0
    print_test("Verifico que se haya creado lista_iter0 y iter0", lista_iter0!=NULL && iter0!=NULL);

    // Inserto un elemento al inicio de la lista_iter0
    print_test("Se inserto correctamente un elemento al inicio de la lista_iter0", lista_iter_insertar(iter0, &elemento0) && lista_ver_primero(lista_iter0)==&elemento0 );

    // Inserto un elemento al final de la lista_iter0
    print_test("Se inserto correctamente un elemento al final de la lista_iter0", lista_iter_avanzar(iter0) && lista_iter_insertar(iter0, &elemento2) && lista_ver_ultimo(lista_iter0)==&elemento2 );

    // Borro ultimo elemento de la lista_iter0 y verifico
    while(lista_iter_ver_actual(iter0) != lista_ver_ultimo(lista_iter0)){
        lista_iter_avanzar(iter0);
    }
    print_test("Se elimino correctamente el ultimo elemento de la lista_iter0", lista_iter_borrar(iter0)==&elemento2 );
    print_test("Verifico que se actualice ultimo elemento lista_iter0", lista_ver_ultimo(lista_iter0) == &elemento0);

    // Borro iter0
    lista_iter_destruir(iter0);
    print_test("Destruyo iter0", true);

    // Creo iter1, borro primer elemento de a lista_iter0 y verifico
    lista_iter_t* iter1 = lista_iter_crear(lista_iter0);
    print_test("Se creo correctamente iter1", iter1!=NULL);
    print_test("Se elimino correctamente el primer elemento de la lista_iter0", lista_iter_ver_actual(iter1)==lista_ver_primero(lista_iter0) && lista_iter_borrar(iter1)==&elemento0 );
    print_test("Verifico que se actualice primer elemento lista_iter0", lista_ver_primero(lista_iter0) == NULL);

    // Destruyo iter1 y lista_iter0
    lista_iter_destruir(iter1);
    lista_destruir(lista_iter0, NULL);
    print_test("Destruyo iter1", true);
    print_test("Destruyo lista_iter0", true);
}

// Pruebas iter medio
void pruebas_iter_medio(){

    lista_t* lista_medio = lista_crear();
    lista_iter_t* iter_medio0 = lista_iter_crear(lista_medio);
    int elemento0 = VALOR_CERO;
    int elemento2 = VALOR_DOS;

    // iter_medio0 se creo correctamente
    print_test("Se creo iter_medio0 correctamente", iter_medio0!=NULL);

    // Inserto dos valores
    print_test("Inserto dos elementos de valor dos en la lista", lista_iter_insertar(iter_medio0, &elemento2) && lista_iter_insertar(iter_medio0, &elemento2) );

    // Destruyo iter_medio0
    lista_iter_destruir(iter_medio0);
    print_test("Destruyo iter_medio0", true);
    
    // Creo iter_medio1, avanazo e inserto al medio y verifico
    lista_iter_t* iter_medio1 = lista_iter_crear(lista_medio);
    print_test("Se creo iter_medio1 correctamente", iter_medio1!=NULL);
    print_test("Avanzo iter_medio1 e inserto al medio", lista_iter_avanzar(iter_medio1) && lista_iter_insertar(iter_medio1, &elemento0) );
    print_test("Verifico que se haya insertado al medio", lista_iter_ver_actual(iter_medio1)==&elemento0 && lista_ver_primero(lista_medio)==&elemento2 && lista_ver_ultimo(lista_medio)==&elemento2 );

    // Elimino el elemento medio y verifico
    print_test("Elimino elemento medio", lista_iter_borrar(iter_medio1)==&elemento0 );
    print_test("Verifico que ya no este el elemento" , lista_iter_ver_actual(iter_medio1)==&elemento2 && lista_ver_primero(lista_medio)==&elemento2 && lista_ver_ultimo(lista_medio)==&elemento2  );

    // Destruyo iter_medio1 y lista_medio
    lista_iter_destruir(iter_medio1);
    lista_destruir(lista_medio, NULL);
    print_test("Destruyo iter_medio1", true);
    print_test("Destruyo lista_medio", true);
}


// Pruebas iter interno
void pruebas_iter_interno(){

    lista_t* lista_interno = lista_crear();
    int venteros1[TAM_VENTEROS1] = {1,2,3,4,5,6,7,8,9,10};
    int venteros_doble[TAM_VENTEROS1] = {2,4,6,8,10,12,14,16,18,20};
    int venteros_valor_uno[TAM_VENTEROS1] = {1,1,1,1,1,1,1,1,1,1};
    int venteros_tres_cero[TAM_VENTEROS1] = {0,0,0,1,1,1,1,1,1,1};
    bool doble = true;
    bool insertar = true;
    bool valor_uno = true;
    // Lleno lista
    for(int i=0; i<TAM_VENTEROS1;i++){
       if(!lista_insertar_ultimo(lista_interno, &venteros1[i]) ) insertar=false;
    }
    print_test("Se lleno lista_interno correctamente", insertar);
    lista_iterar(lista_interno, imprimir, NULL);

    // Funcion duplicar todos los elementos de la lista
    lista_iterar(lista_interno, duplicar, NULL);
    
    // Creo iterador para chequear
    lista_iter_t* iter_doble = lista_iter_crear(lista_interno);
    print_test("\n\nSe creo correctamente iter_doble", iter_doble!=NULL);

    // Verifico que se hayan duplicado correctamente
    for(int i=0;i<TAM_VENTEROS1;i++){
       ( *(int*)lista_iter_ver_actual(iter_doble)==venteros_doble[i] ) ? (lista_iter_avanzar(iter_doble)) : (doble=false);
    }
    print_test("Se duplico correctamente lista_interno", doble);
    lista_iterar(lista_interno, imprimir, NULL);

    // Destruyo iter_doble
    lista_iter_destruir(iter_doble);
    print_test("\nSe destruyo iter_doble", true);


    // Funcion todos los elementos valor uno
    lista_iterar(lista_interno, f_valor_uno, NULL);

    // Creo iterador_uno para chequear
    lista_iter_t* iter_uno = lista_iter_crear(lista_interno);
    print_test("\nSe creo correctamente iter_uno", iter_uno!=NULL);

    // Verifico que todos valgan uno
    for(int j=0;j<TAM_VENTEROS1;j++){
        ( *(int*)lista_iter_ver_actual(iter_uno) == venteros_valor_uno[j]) ? lista_iter_avanzar(iter_uno) : (valor_uno=false);
    }
    print_test("Todos los elementos de lista_interno valen uno", valor_uno);
    lista_iterar(lista_interno, imprimir, NULL);

    // Destruyo iter_uno
    lista_iter_destruir(iter_uno);
    print_test("\nSe destruyo iter_uno", true);


    // Funcion tres primeros elementos valen cero
    int contador = 0;
    bool tres_cero = true;
    lista_iterar(lista_interno, tres_primeros_cero, &contador);

    // Creo iterador_cero para chequear
    lista_iter_t* iter_cero = lista_iter_crear(lista_interno);
    print_test("\nSe creo correctamente iter_cero", iter_cero!=NULL);

    // Verifico que los tres primeros elementos valgan cero
    for(int k=0;k<TAM_VENTEROS1;k++){
        ( *(int*)lista_iter_ver_actual(iter_cero) == venteros_tres_cero[k]) ? lista_iter_avanzar(iter_cero) : (tres_cero=false);
    }
    print_test("Los tres primeros elementos de lista_interno valen cero", tres_cero && contador==TRES_CEROS);
    lista_iterar(lista_interno, imprimir, NULL);

    // Destruyo iter_cero
    lista_iter_destruir(iter_cero);
    print_test("\nSe destruyo iter_cero", true);

    // Destruyo lista_interno
    lista_destruir(lista_interno,NULL);
    print_test("Se destruyo correctamente lista_interno", true);

}


// Pruebas lista iter
void pruebas_lista_iter(){

    printf("\nINICIO PRUEBAS ITERADOR EXTERNO\n");

    pruebas_iter_inicio_final();
    pruebas_iter_medio();

    printf("\nINICIO PRUEBAS ITERADOR INTERNO\n");

    pruebas_iter_interno();
}


void pruebas_lista_alumno(){

    print_test("Prueba lista", true);

    pruebas_crear_destruir();
    pruebas_insertar_borrar();
    pruebas_volumen();  
    prueba_insertar_nulo();
    prueba_bordes();
    pruebas_lista_iter();
}