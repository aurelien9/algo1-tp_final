#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tipos.h"
#include "funciones.h"
#include "LISTA.h"



retval_t cargar_usuarios(tda_lista *tda)
{
	char renglon[MAX_LENGTH] = "";
	retval_t rv;

	if(tda == NULL || tda->pfin == NULL)
		return RV_ILLEGAL;

	while(fgets(renglon, MAX_LENGTH, tda->pfin) != NULL)
	{
		if(renglon[0] == CROCHETE_1)
		{
			if((rv = cargar_usuario(tda, renglon)) != RV_SUCCESS)
				return rv;
		}
	}
	return RV_SUCCESS;
}



retval_t cargar_usuario(tda_lista *tda, char* renglon)
{
	retval_t rv;
	usuario_t *dato;

	if(tda == NULL || renglon == NULL || tda->pfin == NULL)
		return RV_ILLEGAL;


	/* creamos el usuario ---------------------------------------*/
	dato = (usuario_t*)malloc(sizeof(usuario_t));

	dato->usuario = convert_renglon_usuario(renglon);

	fgets(renglon, MAX_LENGTH, tda->pfin);
	dato->id = convert_renglon_id(renglon);

	fgets(renglon, MAX_LENGTH, tda->pfin);
	dato->nombre = supp_header(renglon);

	fgets(renglon, MAX_LENGTH, tda->pfin);
	if ((rv = crear_vector_amigos(renglon, &(dato->amigos))) != RV_SUCCESS)
		return rv;

	dato->mensajes = (tda_lista*)malloc(sizeof(tda_lista));
	dato->mensajes->l = NULL;
	dato->mensajes->destructor = LISTA_destruir_mensaje;
	dato->mensajes->pfin = tda->pfin;
	dato->mensajes->pfout = tda->pfout;
	dato->mensajes->imprimir = LISTA_imprimir_mensaje;

	if ((rv = cargar_mensajes(dato->mensajes)) != RV_SUCCESS)
		return rv;

	/* insertar el dato al fin de la lista de usuario ----------*/
	if((rv = LISTA_insertar_al_final(&(tda->l), dato)) != RV_SUCCESS)
		return rv;

	return RV_SUCCESS;
}




char* convert_renglon_usuario(char* renglon)
{
	char* renglon2;
	int i, j;

	renglon2 = (char*)calloc((strlen(renglon) - 2),sizeof(char));

	for(i = 1, j = 0; i < strlen(renglon) - 2; i++, j++)
	{
		renglon2[j] = renglon[i];
	}
	renglon2[j] = '\0';

	return renglon2;
}



int convert_renglon_id(char* renglon)
{
	int i;
	char* renglon2;

	renglon2 = supp_header(renglon);
	i = atoi(renglon2);
	free(renglon2);

	return i;
}


retval_t crear_vector_amigos(char* renglon, vector_t **amigos)
{
	int i = 0, j = 0, a, b;
	char id[5];

	if (amigos == NULL || renglon == NULL)
		return RV_ILLEGAL;

	*amigos = (vector_t*)malloc(sizeof(vector_t));/* no funciona con malloc ^^*/

	(*amigos)->real = numero_amigos(renglon);
	(*amigos)->alloc = (*amigos)->real + 2; /* creamos un vector mas grande para los proximos amigos*/

	(*amigos)->datos = (int*)calloc((*amigos)->alloc,sizeof(int));

	while(renglon[i] != IGUAL)
		i++;
	i += 2;

	while(j < (*amigos)->real)
	{
		a = 0;

		for(b = 0; b < 5; b++) /*para reinit id[]*/
			id[b] = '\0';

		while(renglon[i] != COMA && renglon[i] != '\n' && renglon[i] != '\0')
		{
			id[a] = renglon[i];
			i++;
			a++;
		}
		i++;
		((*amigos)->datos)[j] = atoi(id);
		j++;
	}

	return RV_SUCCESS;
}


int numero_amigos(char* renglon)
{
	int i;
	int numero = 1;

	if (strlen(renglon) < 9) /*si no hay amigos*/
		return 0;

	for (i = 0; i < strlen(renglon); i++)
	{
		if(renglon[i] == COMA)
			numero++;
	}

	return numero;
}



char* supp_header(char* renglon)
{
	int i = 0, j = 0;
	char* renglon2;

	while(renglon[i] != IGUAL)
		i++;
	i += 2;


	renglon2 = (char*)calloc((strlen(renglon)- i),sizeof(char));

	while((renglon[i] != '\n') && (renglon[i] != '\0'))
	{
		renglon2[j] = renglon[i];
		j++;
		i++;
	}

	renglon2[j] = '\0';

	return renglon2;
}



retval_t cargar_mensajes(tda_lista *tda)
{
	retval_t rv;

	if(tda == NULL || tda->pfin == NULL)
		return RV_ILLEGAL;

	while(!feof(tda->pfin) && fgetc(tda->pfin) != '\n')
	{

		if((rv = cargar_mensaje(tda)) != RV_SUCCESS)
			return rv;
	}

	return RV_SUCCESS;
}


retval_t cargar_mensaje(tda_lista *tda)
{
	mensaje_t *mensaje;
	retval_t rv;
	char num[MAX_LENGTH_NUM];
	char id[MAX_LENGTH_ID];
	char stamp[MAX_LENGTH_STAMP];
	char mensaj[MAX_LENGTH_MENSAJE];

	if(tda == NULL || tda->pfin == NULL)
		return RV_ILLEGAL;

	mensaje = (mensaje_t*)malloc(sizeof(mensaje_t));

	fseek(tda->pfin,9,SEEK_CUR);
	leer_mensaje(num, tda->pfin, MAX_LENGTH_NUM, COMA);
	mensaje->num = atoi(num);

	leer_mensaje(stamp, tda->pfin, MAX_LENGTH_STAMP, COMA);
	strncpy(mensaje->stamp, stamp, MAX_LENGTH_STAMP);

	leer_mensaje(id, tda->pfin, MAX_LENGTH_ID, COMA);
	mensaje->id = atoi(id);

	leer_mensaje(mensaj, tda->pfin, MAX_LENGTH_MENSAJE, RETURN);
	strncpy(mensaje->mensaje, mensaj, MAX_LENGTH_MENSAJE);

	if((rv = LISTA_insertar_al_final(&(tda->l), mensaje)) != RV_SUCCESS)
		return rv;

	return RV_SUCCESS;
}


void leer_mensaje(char* renglon, FILE* pf, size_t n, char delim)
{
	char letra;
	int i = 0;

	for(i = 0; i < n; i++)
	{
		renglon[i] = '\0';
	}

	i = 0;

	while((letra = fgetc(pf)) != EOF && letra != delim)
	{
		renglon[i] = letra;
		i++;
	}
	renglon[i] = '\0';

}
