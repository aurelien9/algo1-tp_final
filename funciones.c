#include <stdio.h>
#include <stdlib.h>

#include "struct.h"

#define MAX_LENGTH 140

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
	strncpy(actual->datos->usuario, renglon);

	fgets(renglon, MAX_LENGTH, pf);

	actual->datos->id = convert_renglon_id(renglon); /*a hacer*/

	fgets(renglon, MAX_LENGTH, pf);

	actual->datos->nombre = convert_renglon_nombre(); /*a hacer*/

	fgets(renglon, MAX_LENGTH, pf);

	actual->datos->amigos = crear_vector_amigos(renglon); /*a hacer*/

	crear_lista_mensaje(actual->datos); /*a hacer*/

}
