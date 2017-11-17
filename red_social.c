#include <stdio.h>
#include <stdlib.h>

#include "struct.h"





int main(int argc, char* argv[])
{

	lista_usuarios *v = NULL;
	FILE *pf;

	/* aca debemos validar los argumentos de la funcion main*/

	if(cargar_usuarios(v,pf) != ST_OK)
	{
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
