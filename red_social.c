#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"
#include "struct.h"
#include "funciones.h"
#include "LISTA.h"




int main(int argc, char* argv[])
{
	char** arreglo_pfin; /*arreglo que contienne todos las nombres de los archivos de configuracion */
	FILE* pfout = stdout;
	lista_t pl = NULL;
	unsigned char bool_eliminar = 0;
	retval_t rv;
	char* eliminar;
	output_t output = NONE;
	size_t cant_file;


	if((rv = validar_argumentos(argc, argv, &arreglo_pfin, &cant_file, &output, &eliminar, &bool_eliminar)) != RV_SUCCESS)
	{
		imprimir_estado(rv);
		return EXIT_FAILURE;
	}


	if((rv = cargar_usuarios(&pl, arreglo_pfin, cant_file)) != RV_SUCCESS)
	{
		imprimir_estado(rv);
		return EXIT_FAILURE;
	}


	if(bool_eliminar)
	{
		if ((rv = LISTA_gestion_eliminar(&pl, eliminar)) != RV_SUCCESS)
		{
			imprimir_estado(rv);
		}
		free(eliminar);
	}

	switch(output)
	{
	case SIMPLE:
	{
		if((rv = LISTA_recorrer(pl, LISTA_imprimir_usuario_simple, pfout)) != RV_SUCCESS)
		{
			imprimir_estado(rv);
		}
		break;
	}

	case MULTI:
	{
		if((rv = LISTA_recorrer(pl, LISTA_imprimir_usuario_multi, pfout)) != RV_SUCCESS)
		{
			imprimir_estado(rv);
		}
		break;
	}
	default:
	{
		rv = RV_ERROR_OUT;
		imprimir_estado(rv);
	}
	}
	if((rv = LISTA_destruir(&pl, LISTA_destruir_usuario)) != RV_SUCCESS)
	{
		imprimir_estado(rv);
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
