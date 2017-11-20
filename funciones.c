#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"

#define MAX_LENGTH 50
#define CROCHETE_1 '['
#define CROCHETE_2 ']'
#define IGUAL '='
#define COMA ','

status_t cargar_usuarios(lista_usuarios *v, FILE *pf)
{

	char renglon[MAX_LENGTH] = "";

	while(fgets(renglon, MAX_LENGTH, pf) != NULL)
	{
		if(renglon[1] == CROCHETE_1)
		{
			cargar_usuario(v, renglon, pf);
		}
	}

	return ST_OK;
}



status_t cargar_usuario(lista_usuarios** v, char* renglon, FILE *pf)
{
	lista_usuarios* actual = *v;
	lista_usuario* antes = *v;
	int id;


	/* creacion del usuario*/
	if(actual == NULL) /*si es el primer usuario*/
	{
		actual = (lista_usuarios*)malloc(sizeof(lista_usuarios));
		*v = actual;
	}
	else /*si no es el primer usuario vamos hasta la fin de la lista*/
	{
		while(actual != NULL)
		{
			antes = actual;
			actual = actual->sig;
		}
		actual = (lista_usuarios*)malloc(sizeof(lista_usuarios));
		antes->sig = actual;
	}

	actual.sig = NULL;
	actual.datos = (usuario*)malloc(sizeof(usuario));

	/* completar el usuario*/
	actual->datos->usuario = convert_renglon_usuario(renglon);

	fgets(renglon, MAX_LENGTH, pf);

	actual->datos->id = convert_renglon_id(renglon);

	fgets(renglon, MAX_LENGTH, pf);

	actual->datos->nombre = convert_renglon_nombre();

	fgets(renglon, MAX_LENGTH, pf);

	actual->datos->amigos = crear_vector_amigos(renglon);

	if (crear_lista_mensaje(actual->datos, pf) != ST_OK)
		return ST_ERROR_CREAR_LISTA;

	return ST_OK;
}



char* convert_renglon_usuario(char* renglon)
{
	char renglon2[MAX_LENGTH] = "";
	int i, j;
	char* renglon3;

	for(i = 0, j = 0; i < strlen(renglon) + 1; i++) status_t destruir_lista_mensaje(usuario* user)
		{

			free(user->mensajes);

			return ST_OK;
		}
		{
			if((renglon[i] != CROCHETE_1) || (renglon[i] != CROCHETE_2))
			{
				renglon2[j] = renglon[i];
				j++;
			}
		}

		strncpy(renglon3, renglon2, MAX_LENGTH);

	return renglon3;
}



int convert_renglon_id(char* renglon)
{
	return atoi(supp_header(renglon));
}



char* convert_renglon_nombre(char* renglon)
{
	int id, i;
	char* renglon2;

	while(renglon[i] != IGUAL)
		i++;
	i++ /*for the space after the = */

	strncpy(renglon2, renglon, MAX_LENGTH);

	return renglon2;
}



vector_s* crear_vector_amigos(renglon)
{
	vector_s *amigos;
	int i, j = 0, a;
	char id[5];

	amigos->real = numero_amigos(renglon);
	amigos->alloc = real + 2; /* creamos un vector mas grande para los proximos amigos*/

	amigos->datos = (int*)malloc((amigos->alloc)*sizeof(int));

	while(renglon[i] != IGUAL)
		i++;
	i += 2;

	while(j <= amigos.real)
	{
		a = 0;
		while(renglon[i] != COMA || renglon[i] != '\0')
		{
			id[a] = renglon[i];
			i++;
		}
		(amigos->datos)[j] = atoi(id);
		j++;
	}

	return amigos;
}


int numero_amigos(char* renglon)
{
	int i;
	int numero = 0;

	for (i = 0; i < strlen(renglon); i++)
	{
		if(renglon[i] == COMA)
			numero++;
	}

	if(numero > 0)
		numero++;

	return numero;
}



status_t crear_lista_mensaje(usuario* user, FILE* pf)
{
	char renglon[MAX_LENGTH_MENSAJE + 26];
	char** arreglo = NULL;
	size_t l;
	lista_s *actual = user->mensajes;
	lista_s *antes = user->mensajes;

	while(fgets(renglon, MAX_LENGTH_MENSAJE + 26, pf) != '\0')
	{
		if(user->mensajes == NULL)
		{
			user->mensajes = (lista_s*)malloc(lista_s);
			user->mensajes->sig = NULL;

			if (split(&arreglo, renglon, ',', &l) != ST_OK)
				return ST_ERROR_CREAR_LISTA;


			user->mensajes->datos->num = atoi(arreglo[1]);
			user->mensajes->datos->stamp = convertir_date(arreglo[2]);
			user->mensajes->datos->id = atoi(arreglo[3]);
			user->mensajes->datos->mensaje = arreglo[4];


			if ((st = destruir_arreglo_cadenas(&arreglo, l)) != ST_OK)
				return ST_ERROR_CREAR_LISTA;
		}
		else
		{
			while(actual != NULL)
			{
				antes = actual;
				actual = actual->sig;
			}

			actual = (lista_s*)malloc(lista_s);
			actual->sig = NULL;
			antes->sig = actual;

			if (split(&arreglo, supp_header(renglon), ',', &l) != ST_OK)
				return ST_ERROR_CREAR_LISTA;


			actual->datos->num = atoi(arreglo[1]);
			strcpy(actual->datos->stamp, arreglo[2]);
			actual->datos->id = atoi(arreglo[3]);
			strcpy(actual->datos->mensaje, arreglo[4]);


			if ((st = destruir_arreglo_cadenas(&arreglo, l)) != ST_OK)
				return ST_ERROR_CREAR_LISTA;
		}

	}

	return ST_OK;
}


char* supp_header(char* renglon)
{
	int i = 0, j = 0;
	char renglon2[MAX_LENGTH_MENSAJE + 26];

	while(renglon[i] != IGUAL)
		i++;
	i += 2;

	for (; i <= strlen(renglon) + 1; i++)
	{
		renglon2[j] = renglon[i];
		j++;
	}

	return renglon2;
}


status_t split(char*** arreglo, const char* cadena, char delimitador, size_t* l)
{
	char** campos = *arreglo;
	size_t n, i;
	char *aux, *q, *linea, delim[2];

	if(!cadena || !l)
	{
		return ST_ERROR_PUNTERO_NULO;
	}

	for(i = 0, n = 1; cadena[i]; i++)
	{
		if(cadena[i] == delimitador)
			n++;
	}

	if((campos = (char**)malloc(sizeof(char*)*n)) == NULL)
	{
		*l = 0;
		return ST_ERROR_NOMEM;
	}

	if((linea = strdup(cadena)) == NULL)
	{
		free(campos);
		campos = NULL;
		*l = 0;
		return ST_ERROR_NOMEM;
	}

	delim[0] = delimitador;
	delim[1] = '\0';

	for(i = 0, q = linea; (aux = strtok(q, delim)) != NULL; i++, q = NULL)
	{
		if((campos[i] = strdup(aux)) == NULL)
		{
			if((destruir_arreglo_cadenas(&campos, i)) != ST_OK)
			{
				return ST_ERROR_DESTRUIR_ARREGLO;
			}
			campos = NULL;
			*l = 0;
		}
	}
	free(linea);
	*l = i;

	*arreglo = campos;
	return ST_OK;
}



status_t destruir_arreglo_cadenas(char ***campos, size_t size)
{
	size_t i;

	for(i = 0; i < size; i++)
	{
		free((*campos)[i]);
		(*campos)[i] = NULL;
	}

	free(*campos);
	*campos = NULL;

	return ST_OK;
}

status_t destruir_usuarios(lista_usuarios** v)
{
	lista_usuarios* actual = *v, next;

	if(!(**v))
		return ST_ERROR_PUNTERO_NULO;

	while(actual->sig != NULL)
	{
		next = actual->sig;
		free(actual);
		actual = next;
	}

	free(actual);

	*v = NULL;

	return ST_OK;
}


status_t destruir_usuario(usuario* user)
{
	if (!user)
		return ST_ERROR_PUNTERO_NULO;

	if(destruir_vector_amigos(user) != ST_OK)
		return ST_ERROR_DESTRUIR_VECTOR;

	if (destruir_lista_mensaje(user) != ST_OK)
		return ST_ERROR_DESTRUIR_LISTA;

	free(*user);

	return ST_OK;
}


status_t destruir_vector_amigos(usuario* user)
{
	if(!(user->amigos->datos))
		return ST_ERROR_PUNTERO_NULO;

	free(user->amigos->datos);

	return ST_OK;
}


status_t destruir_lista_mensaje(usuario* user)
{
	lista_s* actual = user->mensajes, next;

	if(!(user->mensajes))
		return ST_ERROR_WRITE;

	while(actual->sig != NULL)
	{
		next = actual->sig;
		free(actual);
		actual = next;
	}

	free(actual);

	user->mensajes = NULL;

	return ST_OK;
}
