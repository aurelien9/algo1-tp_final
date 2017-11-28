#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tipos.h"
#include "struct.h"
#include "funciones.h"
#include "LISTA.h"




int main(int argc, char* argv[])
{

	FILE *pf;
	FILE *pout = stdout;
	tda_lista tda;

	pf = fopen(argv[1], "r"); /*SOLO PARA PROBAR*/
	/* aca debemos validar los argumentos de la funcion main*/

	tda.l = NULL;
	tda.destructor = LISTA_destruir_usuario;
	tda.pfin = pf;
	tda.pfout = pout;
	tda.imprimir = LISTA_imprimir_usuario;


	if(cargar_usuarios(&tda) != RV_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	if(LISTA_recorrer(&tda) != RV_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	if(LISTA_destruir(&tda) != RV_SUCCESS)
	{
		return EXIT_FAILURE;
	}

	fclose(pf);

	return EXIT_SUCCESS;
}
