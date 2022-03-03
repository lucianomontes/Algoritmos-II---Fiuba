#include<stdio.h>    


/* swap() intercambia dos valores enteros.
 */
void swap (int* x, int* y);

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[], int n);

/* La funcion recibe dos elementos enteros, los compara y devuelve -1 si el primer elemento es MENOR, 1 si el segundo es MAYOR y 0 si son IGUALES.
*/
int comparar_elementos(int elemento1, int elemento2);

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2);

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */
void seleccion(int vector[], int n);
