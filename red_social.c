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
	/* aca debemos validar los argumentos de la funcion main*/

	if(cargar_usuarios(&v,pf) != ST_OK)
	{
		return EXIT_FAILURE;
	}

	if(imprimir_usuarios(v,pout) != ST_OK)
	{
		return EXIT_FAILURE;
	}

	if(destruir_usuarios(&v) != ST_OK)
	{
		return EXIT_FAILURE;
	}

	fclose(pf);

	return EXIT_SUCCESS;
}
