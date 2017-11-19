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
		if(renglon[1] == '[')
		{
			cargar_usuario(v, renglon, pf);
		}
	}

	return ST_OK;
}



status_t cargar_usuario(lista_usuarios v, char* renglon, FILE *pf)
{
	lista_usuarios *actual = v;
	int id;

	while(actual != NULL)
		actual = actual->sig;

	/* creacion del usuario*/
	actual = (lista_usuarios*)malloc(sizeof(lista_usuarios));

	actual.sig = NULL;
	actual.datos = (usuario*)malloc(sizeof(usuario));

	/* completar el usuario*/
	actual->datos->usuario = convert_renglon_usuario(renglon);

	fgets(renglon, MAX_LENGTH, pf);

	actual->datos->id = convert_renglon_id(renglon);

	fgets(renglon, MAX_LENGTH, pf);

	actual->datos->nombre = convert_renglon_nombre();

	fgets(renglon, MAX_LENGTH, pf);

	actual->datos->amigos = crear_vector_amigos(renglon); /*a hacer*/

	crear_lista_mensaje(actual->datos); /*a hacer*/
}



char* convert_renglon_usuario(char* renglon)
{
	char renglon2[MAX_LENGTH] = "";
	int i, j;
	char* renglon3;

	for(i = 0, j = 0; i < strlen(renglon) + 1; i++)
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
	return atoi(renglon);
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

	amigos->real = numero_amigos(renglon);
	amigos->alloc = real + 2; /* creamos un vector mas grande para los proximos amigos*/

	amigos6->datos = (int*)malloc(alloc*sizeof(int));

	for(i = 0; i <= real; i++)
		(amigos->datos)[i] = get_id_amigo(renglon, i + 1);

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


int get_id_amigo(char* renglon, int i)
{
	int j;

	if(i == 1)

}
