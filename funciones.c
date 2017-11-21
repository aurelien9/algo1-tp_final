#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tipos.h"
#include "funciones.h"



status_t cargar_usuarios(userList** v, FILE *pf)
{

	char renglon[MAX_LENGTH] = "";

	while(fgets(renglon, MAX_LENGTH, pf) != NULL)
	{
		if(renglon[0] == CROCHETE_1)
		{
			cargar_usuario(v, renglon, pf);
		}
	}

	return ST_OK;
}



status_t cargar_usuario(userList** v, char* renglon, FILE *pf)
{
	userList* actual = *v;
	userList* antes = *v;

	/* creacion del usuario*/
	if(actual == NULL) /*si es el primer usuario*/
	{
		actual = (userList*)malloc(sizeof(userList));
		*v = actual;
	}
	else /*si no es el primer usuario vamos hasta la fin de la lista*/
	{
		while(actual != NULL)
		{
			antes = actual;
			actual = actual->sig;
		}
		actual = (userList*)malloc(sizeof(userList));
		antes->sig = actual;
	}

	actual->sig = NULL;
	actual->datos = (usuario*)malloc(sizeof(usuario));

	/* completar el usuario*/
	actual->datos->usuario = convert_renglon_usuario(renglon);

	fgets(renglon, MAX_LENGTH, pf);

	actual->datos->id = convert_renglon_id(&renglon);

	fgets(renglon, MAX_LENGTH, pf);

	supp_header(&renglon);
	actual->datos->nombre = renglon;

	fgets(renglon, MAX_LENGTH, pf);
	printf("XXX\n");

	if (crear_vector_amigos(renglon, actual->datos) != ST_OK)
		return ST_ERROR_CREAR_VECTOR;
	printf("XXX\n");

	if (crear_lista_mensaje(actual->datos, pf) != ST_OK)
		return ST_ERROR_CREAR_LISTA;

	return ST_OK;
}



char* convert_renglon_usuario(char* renglon)
{
	char* renglon2;
	int i, j;

	renglon2 = (char*)malloc(sizeof(char)*(strlen(renglon) - 3));

	for(i = 1, j = 0; i < strlen(renglon) - 2; i++, j++)
	{
		renglon2[j] = renglon[i];
	}
	renglon2[j] = '\0';

	return renglon2;
}



int convert_renglon_id(char** renglon)
{
	int i;
	supp_header(renglon);
	i = atoi(*renglon);
	free(*renglon);

	return i;
}



status_t crear_vector_amigos(char* renglon, usuario* user)
{
	int i = 0, j = 0, a;
	char id[5];

	if (!user)
		return ST_ERROR_PUNTERO_NULO;

	user->amigos = (vector_s*)malloc(sizeof(vector_s));
	printf("CCC\n");

	user->amigos->real = numero_amigos(renglon);
	user->amigos->alloc = user->amigos->real + 2; /* creamos un vector mas grande para los proximos amigos*/

	user->amigos->datos = (int*)malloc((user->amigos->alloc)*sizeof(int));
	printf("CCC\n");

	while(renglon[i] != IGUAL)
		i++;
	i += 2;

	while(j < user->amigos->real)
	{
		a = 0;
		while(renglon[i] != COMA && renglon[i] != '\0')
		{
			id[a] = renglon[i];
			i++;
			a++;
		}
		i++;
		(user->amigos->datos)[j] = atoi(id);
		j++;
	}

	return ST_OK;
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



status_t crear_lista_mensaje(usuario* user, FILE* pf)
{
	char* renglon;
	char** arreglo = NULL;
	size_t l;
	lista_s *actual = user->mensajes;
	lista_s *antes = user->mensajes;

	while(fgets(renglon, MAX_LENGTH_MENSAJE_LARGO, pf) && *renglon != '\n')
	{
		if(user->mensajes == NULL)
		{
			actual = (lista_s*)malloc(sizeof(lista_s));
			actual->sig = NULL;
			user->mensajes = actual;
		}
		else
		{
			while(actual != NULL)
			{
				antes = actual;
				actual = actual->sig;
			}

			actual = (lista_s*)malloc(sizeof(lista_s));
			actual->sig = NULL;
			antes->sig = actual;
		}

		actual->datos = (mensaje*)malloc(sizeof(mensaje));

		supp_header(&renglon);
		if (split(&arreglo, renglon, ',', &l) != ST_OK)
			return ST_ERROR_CREAR_LISTA;

		free(renglon);

		actual->datos->num = atoi(arreglo[0]);
		strncpy(actual->datos->stamp, arreglo[1], MAX_LENGTH_STAMP);
		actual->datos->id = atoi(arreglo[2]);
		strncpy(actual->datos->mensaje, arreglo[3], MAX_LENGTH_MENSAJE);

		if (destruir_arreglo_cadenas(&arreglo, l) != ST_OK)
			return ST_ERROR_CREAR_LISTA;
	}

	return ST_OK;
}


void supp_header(char** renglon)
{
	int i = 0, j = 0;
	char* renglon2;

	while((*renglon)[i] != IGUAL)
		i++;
	i += 2;

	renglon2 = (char*)malloc(sizeof(char)*(strlen(*renglon)-i));

	for (; i < strlen(*renglon); i++)
	{
		renglon2[j] = (*renglon)[i];
		j++;
	}

	if(renglon2[j-1] == '\n')
		renglon2[j-1] = '\0';
	else
		renglon2[j] = '\0';

	*renglon = renglon2;
}


char* strdup(const char* sc)
{
	size_t l;
	char *s;

	if(sc == NULL)
		return NULL;

	l = strlen(sc) + 1; /*se le suma uno para hacer lugar al '\0'*/

	s = (char*)malloc(sizeof(char)*(l));

	if(s != NULL)
		memcpy(s,sc,l);
	return s;
}



status_t split(char*** arreglo, char* cadena, char delimitador, size_t* l)
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

status_t destruir_usuarios(userList** v)
{
	userList* actual = *v;
	userList* next;

	if(!(*v))
		return ST_ERROR_PUNTERO_NULO;

	while(actual->sig != NULL)
	{
		next = actual->sig;
		destruir_usuario(&(actual->datos));
		free(actual);
		actual = next;
	}

	*v = NULL;

	return ST_OK;
}


status_t destruir_usuario(usuario** user)
{
	if (!user)
		return ST_ERROR_PUNTERO_NULO;

	free((*user)->usuario);
	free((*user)->nombre);

	if(destruir_vector_amigos(*user) != ST_OK)
		return ST_ERROR_DESTRUIR_VECTOR;

	if (destruir_lista_mensaje(*user) != ST_OK)
		return ST_ERROR_DESTRUIR_LISTA;

	free(*user);
	*user = NULL;

	return ST_OK;
}


status_t destruir_vector_amigos(usuario* user)
{
	if(!(user->amigos->datos))
		return ST_ERROR_PUNTERO_NULO;

	free(user->amigos->datos);

	free(user->amigos);

	user->amigos = NULL;
	return ST_OK;
}


status_t destruir_lista_mensaje(usuario* user)
{
	lista_s* actual = user->mensajes;
	lista_s* next;

	if(!(user->mensajes))
		return ST_ERROR_PUNTERO_NULO;

	while(actual->sig != NULL)
	{
		next = actual->sig;
		free(actual->datos);
		free(actual);
		actual = next;
	}

	free(actual);

	user->mensajes = NULL;

	return ST_OK;
}



status_t imprimir_usuarios(userList* v, FILE* pf)
{
	userList* actual = v;

	if(!v)
		return ST_ERROR_PUNTERO_NULO;

	while(actual != NULL)
	{
		if(imprimir_usuario(actual->datos, pf) != ST_OK)
		{
			return ST_ERROR_IMPRIMIR_DATOS;
		}
		actual = actual->sig;
		fprintf(pf, "\n");
	}
	return ST_OK;
}


status_t imprimir_usuario(usuario* user, FILE* pf)
{
	lista_s* actual = user->mensajes;
	int i;

	fprintf(pf, "[%s]\n", user->usuario);
	fprintf(pf, "id = %i\n", user->id);
	fprintf(pf, "nombre = %s\n", user->nombre);

	fprintf(pf, "amigos = ");
	for(i = 0; i < user->amigos->real - 1; i++)
		fprintf(pf, "%i,", user->amigos->datos[i]);
	fprintf(pf, "%i\n", user->amigos->datos[i]);

	while(actual != NULL)
	{
		fprintf(pf, "mensaje = %i,%s,%i,%s\n", actual->datos->num, actual->datos->stamp, actual->datos->id, actual->datos->mensaje);
		actual = actual->sig;
	}

	return ST_OK;
}
