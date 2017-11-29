#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"
#include "struct.h"
#include "funciones.h"
#include "LISTA.h"




int main(int argc, char* argv[])
{

	FILE *pfin;
	FILE *pfout = stdout;
	lista_t pl = NULL;
	unsigned char eliminar = 0;
	retval_t rv;


	pfin = fopen(argv[1], "r"); /*SOLO PARA PROBAR*/
	/* aca debemos validar los argumentos de la funcion main*/


	if((rv = cargar_usuarios(&pl, pfin)) != RV_SUCCESS)
	{
		imprimir_estado(rv);
		return EXIT_FAILURE;
	}

	if(eliminar)
	{
		if ((rv = LISTA_eliminar(&pl)) != RV_SUCCESS)
		{
			imprimir_estado(rv);
			return EXIT_FAILURE;
		}
	}

	if((rv = LISTA_recorrer(pl, LISTA_imprimir_usuario, pfout)) != RV_SUCCESS)
	{
		imprimir_estado(rv);
		return EXIT_FAILURE;
	}

	if((rv = LISTA_destruir(&pl, LISTA_destruir_usuario)) != RV_SUCCESS)
	{
		imprimir_estado(rv);
		return EXIT_FAILURE;
	}

	fclose(pfin);

	return EXIT_SUCCESS;
}
