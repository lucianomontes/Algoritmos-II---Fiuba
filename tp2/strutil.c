#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
/*
 * Devuelve una nueva cadena con los primeros �n� caracteres de la cadena
 * �str�. La liberaci�n de la memoria din�mica devuelta queda a cargo de
 * quien llame a esta funci�n.
 *
 * Devuelve NULL si no se pudo reservar suficiente memoria.
 */
char *substr(const char *str, size_t n){

	if(!str) return NULL;
	size_t longitud = strlen(str);
	
	if(longitud > n){
		longitud = n;
	}

	char *substring = malloc(sizeof(char)*(longitud+1));

	if(!substring) return NULL;

	strncpy(substring,str,longitud);

	substring[longitud] = '\0';

	return substring;
}

/*
 * Devuelve en un arreglo dinámico terminado en NULL todos los subsegmentos de
 * ‘str’ separados por el carácter ‘sep’. Tanto el arreglo devuelto como las
 * cadenas que contiene se ubicarán en nuevos espacios de memoria dinámica.
 *
 * La liberación de la memoria dinámica devuelta queda a cargo de quien llame a
 * esta función. La función devuelve NULL en caso de error.
 */
char **split(const char *str, char sep){
	
	if(!str) return NULL;
	
	size_t contador = 0;
	size_t corte_ant = 0;
	size_t longitud = strlen(str);
	
	for(size_t i=0;i<=longitud;i++){
		if(str[i] == sep || str[i]== '\0') contador++;
	}
	
	char **subcadenas = malloc(sizeof(char*)*(contador+1));
	if(!subcadenas) return NULL; 
	
	size_t k=0;

	for(size_t i=0;i<=longitud;i++){
		if( str[i] == sep || str[i]== '\0'){
			subcadenas[k] = substr(str + corte_ant, i-corte_ant);
			corte_ant = i+1;
			k++;
		} 
	}
	subcadenas[k] = NULL;
		
	return subcadenas;
}

/*
 * Devuelve la cadena resultante de unir todas las cadenas del arreglo
 * terminado en NULL ‘str’ con ‘sep’ entre cadenas. La cadena devuelta se
 * ubicará en un nuevo espacio de memoria dinámica.
 *
 * La liberación de la memoria dinámica devuelta queda a cargo de quien llame a
 * esta función. La función devuelve NULL en caso de error.
 */
char *join(char **strv, char sep){

	size_t largo=0;
	size_t i=0;

	while(strv[i]){
		largo+= (strlen(strv[i])+1);
		i++;
	}
	size_t ultimo = i;

	if(largo == 0 || largo == 1){
		char *str = malloc(sizeof(char));
		if(!str) return NULL;
		str[0] = '\0';
		return str;
	}
	
	char *str = malloc(sizeof(char)*(largo));
	if(!str) return NULL;
	str[0]= '\0';
	size_t pos = 0;
	
	for(size_t j=0;j<i;j++){
		strcpy(str + pos, strv[j]);
		pos+= strlen(strv[j]);
		if(j!= ultimo-1 && sep!= '\0'){ 
			str[pos] = sep;
			pos++;
		}	
	}
	str[largo-1]= '\0';

	return str;
}

/*
 * Libera un arreglo dinámico de cadenas, y todas las cadenas que contiene.
 */
void free_strv(char *strv[]){

	size_t i=0;

	while(strv[i]){
		free(strv[i]);
		i++;
	}
	free(strv);
}
