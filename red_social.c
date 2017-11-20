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

	pf = fopen(argv[1], "r");
	/* aca debemos validar los argumentos de la funcion main*/

	if(cargar_usuarios(&v,pf) != ST_OK)
	{
		return EXIT_FAILURE;
	}

	if(destruir_usuarios(&v) != ST_OK)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
