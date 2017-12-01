#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tipos.h"
#include "funciones.h"
#include "LISTA.h"



retval_t cargar_usuarios(lista_t *pl, FILE* pfin)
{
	char renglon[MAX_LENGTH] = "";
	retval_t rv;

	if(pl == NULL || pfin == NULL)
		return RV_ILLEGAL;

	while(fgets(renglon, MAX_LENGTH, pfin) != NULL)
	{
		if(renglon[0] == CROCHETE_1)
		{
			if((rv = cargar_usuario(pl, renglon, pfin)) != RV_SUCCESS)
				return rv;
		}
	}
	return RV_SUCCESS;
}



retval_t cargar_usuario(lista_t *pl, char* renglon, FILE* pfin)
{
	retval_t rv;
	usuario_t *dato;

	if(pl == NULL || renglon == NULL || pfin == NULL)
		return RV_ILLEGAL;


	/* creamos el usuario ---------------------------------------*/
	dato = (usuario_t*)malloc(sizeof(usuario_t));

	dato->usuario = convert_renglon_usuario(renglon);

	fgets(renglon, MAX_LENGTH, pfin);
	dato->id = convert_renglon_id(renglon);

	fgets(renglon, MAX_LENGTH, pfin);
	dato->nombre = supp_header(renglon);

	fgets(renglon, MAX_LENGTH, pfin);
	if ((rv = crear_vector_amigos(renglon, &(dato->amigos))) != RV_SUCCESS)
		return rv;

	dato->mensajes = NULL;

	if ((rv = cargar_mensajes(&(dato->mensajes), pfin)) != RV_SUCCESS)
		return rv;

	/* insertar el dato al fin de la lista de usuario ----------*/
	if((rv = LISTA_insertar_al_final(pl, dato)) != RV_SUCCESS)
		return rv;

	return RV_SUCCESS;
}




char* convert_renglon_usuario(char* renglon)
{
	char* renglon2;
	int i, j;

	renglon2 = (char*)calloc((strlen(renglon) - 2),sizeof(char));

	for(i = 1, j = 0; i < strlen(renglon) - 2; i++, j++)
	{
		renglon2[j] = renglon[i];
	}
	renglon2[j] = '\0';

	return renglon2;
}



int convert_renglon_id(char* renglon)
{
	int i;
	char* renglon2;

	renglon2 = supp_header(renglon);
	i = atoi(renglon2);
	free(renglon2);

	return i;
}


retval_t crear_vector_amigos(char* renglon, vector_t **amigos)
{
	int i = 0, j = 0, a, b;
	char id[5];

	if (amigos == NULL || renglon == NULL)
		return RV_ILLEGAL;

	*amigos = (vector_t*)malloc(sizeof(vector_t));/* no funciona con malloc ^^*/

	(*amigos)->real = numero_amigos(renglon);
	(*amigos)->alloc = (*amigos)->real + 2; /* creamos un vector mas grande para los proximos amigos*/

	(*amigos)->datos = (int*)calloc((*amigos)->alloc,sizeof(int));

	while(renglon[i] != IGUAL)
		i++;
	i += 2;

	while(j < (*amigos)->real)
	{
		a = 0;

		for(b = 0; b < 5; b++) /*para reinit id[]*/
			id[b] = '\0';

		while(renglon[i] != COMA && renglon[i] != '\n' && renglon[i] != '\0')
		{
			id[a] = renglon[i];
			i++;
			a++;
		}
		i++;
		((*amigos)->datos)[j] = atoi(id);
		j++;
	}

	return RV_SUCCESS;
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



char* supp_header(char* renglon)
{
	int i = 0, j = 0;
	char* renglon2;

	while(renglon[i] != IGUAL)
		i++;
	i += 2;


	renglon2 = (char*)calloc((strlen(renglon)- i),sizeof(char));

	while((renglon[i] != '\n') && (renglon[i] != '\0'))
	{
		renglon2[j] = renglon[i];
		j++;
		i++;
	}

	renglon2[j] = '\0';

	return renglon2;
}



retval_t cargar_mensajes(lista_t *pl, FILE* pfin)
{
	retval_t rv;

	if(pl == NULL || pfin == NULL)
		return RV_ILLEGAL;

	while(!feof(pfin) && fgetc(pfin) != '\n' && !feof(pfin))
	{

		if((rv = cargar_mensaje(pl, pfin)) != RV_SUCCESS)
			return rv;
	}

	return RV_SUCCESS;
}


retval_t cargar_mensaje(lista_t *pl, FILE* pfin)
{
	mensaje_t *mensaje;
	retval_t rv;
	char num[MAX_LENGTH_NUM];
	char id[MAX_LENGTH_ID];
	char stamp[MAX_LENGTH_STAMP];
	char mensaj[MAX_LENGTH_MENSAJE];

	if(pl == NULL || pfin == NULL)
		return RV_ILLEGAL;

	mensaje = (mensaje_t*)malloc(sizeof(mensaje_t));

	fseek(pfin,9,SEEK_CUR);
	leer_mensaje(num, pfin, MAX_LENGTH_NUM, COMA);
	mensaje->num = atoi(num);

	leer_mensaje(stamp, pfin, MAX_LENGTH_STAMP, COMA);
	strncpy(mensaje->stamp, stamp, MAX_LENGTH_STAMP);

	leer_mensaje(id, pfin, MAX_LENGTH_ID, COMA);
	mensaje->id = atoi(id);

	leer_mensaje(mensaj, pfin, MAX_LENGTH_MENSAJE, RETURN);
	strncpy(mensaje->mensaje, mensaj, MAX_LENGTH_MENSAJE);

	if((rv = LISTA_insertar_al_final(pl, mensaje)) != RV_SUCCESS)
		return rv;

	return RV_SUCCESS;
}


void leer_mensaje(char* renglon, FILE* pfin, size_t n, char delim)
{
	char letra;
	int i = 0;

	for(i = 0; i < n; i++)
	{
		renglon[i] = '\0';
	}

	i = 0;

	while((letra = fgetc(pfin)) != EOF && letra != delim)
	{
		renglon[i] = letra;
		i++;
	}
	renglon[i] = '\0';
}



/*///////////////////////////////FUNCIONES DE PROTECCION/////////////////////////////////*/
retval_t validar_argumentos(int argc,char* argv[], output_t* output, char** eliminar, FILE** ppf, int* peliminar)
{
	int i;

	if(!(argv) || !(output) || !(eliminar) || !(ppf))
	{
		return RV_ILLEGAL;
	}
	if(argc<MIN_ARG)
	{
	 return RV_ERROR_MIN_ARG;	
	}
	if((*ppf = fopen(argv[5], "r")) == NULL ) /* Hardcodeo, tengo que pensar una forma de pensarlo para mas de un archivo*/
	{
		return RV_ERROR_OPEN_ARCHIVO;
	}
	for(i=0 ; i<argc ; i++)
	{
		if( !(strcmp(argv[i],SHORT_ELIM)) || !(strcmp(argv[i],LONG_ELIM)))
		{
			*peliminar = 1;
			if((*eliminar = (char*)malloc(sizeof(char)/*strlen(argv[i+1])*/)) == NULL)
			{
				return RV_ENOMEM;
			}
			strcpy(*eliminar, argv[i+1]);
		}
		if( !(strcmp(argv[i],SHORT_OUT)) || !(strcmp(argv[i],SHORT_OUT)))
		{
			if( !(strcmp(argv[i+1], OUT_SINGLE)))
			{
				*output = SIMPLE;
			}
			else if( !(strcmp(argv[i+1], OUT_MULT)))
			{
				*output = MULTI;
			}
			else
			{
				*output = NONE;
			}
		}
		
	}
	return RV_SUCCESS;
}


void imprimir_estado(retval_t rv)
{
	switch(rv)
	{
	case RV_SUCCESS:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_SUCCESS);
		break;
	}
	case RV_ILLEGAL:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_ILLEGAL);
		break;
	}
	case RV_ENOMEM:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_ENOMEM);
		break;
	}
	case RV_ERROR_CANT_ARGC:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_ERROR_CANT_ARGC);
		break;
	}
	case RV_ERROR_OPEN_ARCHIVO:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_ERROR_OPEN_ARCHIVO);
		break;
	}
	case RV_ERROR_DESTRUIR_LISTA:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_ERROR_DESTRUIR_LISTA);
		break;
	}
	case RV_ERROR_IMPRIMIR:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_ERROR_IMPRIMIR);
		break;
	}
	case RV_ERROR_ARG_ELIMNAR:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_ERROR_ARG_ELIMINAR);
		break;
	}
	case RV_USER_NO_EXIST:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_USER_NO_EXIST);
		break;
	}
	case RV_ERROR_ELIMNAR:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_ERROR_ELIMINAR);
		break;
	}
	default:
	{
		fprintf(stderr, "%s: %s\n", ERR_PREFIJO, TXT_ERROR_ESTADO);
	}
	}
}
