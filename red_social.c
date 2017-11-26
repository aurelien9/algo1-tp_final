#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tipos.h"
#include "funciones.h"




int main(int argc, char* argv[])
{

	userList *v = NULL;
	FILE *pf;
	FILE *pout = stdout;

	pf = fopen(argv[1], "r"); /*SOLO PARA PROBAR*/
	
	estado = validar_argumentos(argc, argv, pf);
	
	if(estado== ST_OK) /*corroborra los argumentos esten bien para continuar con el programa*/
	{
		if((estado=cargar_usuarios(&v,pf)) != ST_OK)
		{
			imprimir_estado(estado);
			return EXIT_FAILURE;
		}
	
		if((estado=imprimir_usuarios(v,pout)) != ST_OK)
		{
			imprimir_estado(estado);
			return EXIT_FAILURE;
		}

		if((estado=destruir_usuarios(&v)) != ST_OK)
		{
			imprimir_estado(estado);
			return EXIT_FAILURE;
		}
		fclose(pf);
	}
		imprimir_estado(estado);
	return EXIT_SUCCESS;
}
