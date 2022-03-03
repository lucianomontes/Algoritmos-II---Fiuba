#include "tp0.h"

#define MENOR -1
#define MAYOR 1
#define IGUALES 0
#define LARGO_CERO -1

/* ******************************************************************
 *                     FUNCIONES A COMPLETAR
 * *****************************************************************/

/* swap() intercambia dos valores enteros.
 */
void swap (int* x, int* y) {
	int aux;
	aux = *x;
	*x = *y;
	*y = aux;
}

/* maximo() busca el mayor elemento del arreglo y devuelve su posicion.
 * Si el vector es de largo 0, devuelve -1.
 */
int maximo(int vector[], int n) {	
	if (n == 0){
		return LARGO_CERO;
	}	
	int posicion = 0; 	
	for(int i=1;i<n;i++){
		if(vector[i]>vector[posicion])
				posicion = i;
	}
	return posicion;
}

/* La funcion recibe dos elementos enteros, los compara y devuelve -1 si el primer elemento es MENOR,
 1 si el segundo es MAYOR y 0 si son IGUALES.
*/
int	comparar_elementos(int elemento1, int elemento2){

	if(elemento1<elemento2){
		return MENOR;
	}
	if(elemento2<elemento1){
		return MAYOR;
	}
	return IGUALES;		
}

/* La función comparar recibe dos vectores y sus respectivas longitudes
 * y devuelve -1 si el primer vector es menor que el segundo; 0 si son
 * iguales; y 1 si el segundo es menor.
 *
 * Un vector es menor a otro cuando al compararlos elemento a elemento,
 * el primer elemento en el que difieren no existe o es menor.
 */
int comparar(int vector1[], int n1, int vector2[], int n2) {
	int i=0;
	
	while( i<n1 && i<n2 ) {

		if(vector1[i]!=vector2[i]){
			return comparar_elementos(vector1[i] , vector2[i]);
		}
		i++;	
	}

	return comparar_elementos(n1 , n2);
}

/* selection_sort() ordena el arreglo recibido mediante el algoritmo de
 * selección.
 */

void seleccion(int vector[], int n) {

	int pos_maximo;

	for(int i=n;i>0;i--){
		pos_maximo = maximo(vector , i);
		if(i-1 != pos_maximo)
		swap( &vector[i-1], &vector[pos_maximo]);
	}
}


