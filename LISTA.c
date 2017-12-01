#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tipos.h"
#include "funciones.h"
#include "LISTA.h"


/* Operationnes sobre las listas */

int LISTA_vacia(lista_t l)
{
	return l == NULL;
}

retval_t LISTA_crear_nodo(nodo_t **nodo, void *dato)
{
	if(nodo == NULL)
		return RV_ILLEGAL;
	if((*nodo = (nodo_t*)calloc(1,sizeof(nodo_t))) == NULL)
		return RV_ENOMEM;

	(*nodo)->sig = NULL;
	(*nodo)->dato = dato;

	return RV_SUCCESS;
}


retval_t LISTA_destruir_nodo(lista_t *pl, retval_t (*destructor)(void**))
{
	retval_t rv;

	if(pl == NULL)
		return RV_ILLEGAL;
	if(*pl == NULL)
		return RV_SUCCESS;
	if(destructor == NULL)
		return RV_ILLEGAL;

	if((rv = destructor(&((*pl)->dato))) != RV_SUCCESS)
		return rv;

	(*pl)->sig = NULL;
	(*pl)->dato = NULL;
	free(*pl);
	*pl = NULL;

	return RV_SUCCESS;
}

retval_t LISTA_destruir(lista_t *pl, retval_t (*destructor)(void**))
{
	nodo_t *sig;

	if(pl == NULL)
		return RV_ILLEGAL;

	if(LISTA_vacia(*pl))
		return RV_SUCCESS;

	sig = (*pl)->sig;

	if(LISTA_destruir_nodo(pl, destructor) != RV_SUCCESS)
		return RV_ERROR_DESTRUIR_LISTA;

	return LISTA_destruir(&sig, destructor);
}


retval_t LISTA_insertar_al_principio(lista_t *pl, void *dato)
{
	retval_t rv;
	nodo_t *nodo;

	if (pl == NULL)
		return RV_ILLEGAL;

	if((rv = LISTA_crear_nodo(&nodo,dato)) != RV_SUCCESS)
		return rv;

	nodo->sig = *pl;
	*pl = nodo;

	return RV_SUCCESS;
}

retval_t LISTA_insertar_al_final(lista_t *pl, void *dato)
{
	if(pl == NULL)
		return RV_ILLEGAL;

	if(LISTA_vacia(*pl))
		return LISTA_insertar_al_principio(pl, dato);

	return LISTA_insertar_al_final(&((*pl)->sig), dato);
}


retval_t LISTA_recorrer(lista_t pl, void (*imprimir)(lista_t, FILE*), FILE* pfout)
{
	lista_t sig = pl;

	if(imprimir == NULL)
		return RV_ILLEGAL;

	if(LISTA_vacia(pl))
		return RV_SUCCESS;

	imprimir(pl, pfout);

	sig = sig->sig;

	return LISTA_recorrer(sig, imprimir, pfout);
}



retval_t LISTA_destruir_mensaje(void **mensajeBis)
{
	mensaje_t **mensaje = (mensaje_t**)(mensajeBis);
	if(mensaje == NULL)
		return RV_ILLEGAL;

	free(*mensaje);
	*mensaje = NULL;

	return RV_SUCCESS;
}


retval_t LISTA_destruir_usuario(void **usuarioBis)
{
	retval_t rv;
	usuario_t **usuario = (usuario_t**)(usuarioBis);

	if(usuario == NULL || *usuario == NULL)
		return RV_ILLEGAL;

	free((*usuario)->usuario);

	(*usuario)->usuario = NULL;

	free((*usuario)->nombre);
	(*usuario)->nombre = NULL;

	free((*usuario)->amigos->datos);
	(*usuario)->amigos->datos = NULL;

	free((*usuario)->amigos);
	(*usuario)->amigos = NULL;

	if((rv = LISTA_destruir(&((*usuario)->mensajes), LISTA_destruir_mensaje)) != RV_SUCCESS)
	{
		return RV_ERROR_DESTRUIR_MENSAJES;
	}

	free(*usuario);
	*usuario = NULL;

	return RV_SUCCESS;
}



/* gestion de imprimir */

void LISTA_imprimir_mensaje(lista_t pl, FILE* pfout)
{
	mensaje_t* mensaje = (mensaje_t*)(pl->dato);

	fprintf(pfout, "mensaje = %i,", mensaje->num);
	fprintf(pfout, "%s,", mensaje->stamp);
	fprintf(pfout, "%i,", mensaje->id);
	fprintf(pfout, "%s\n", mensaje->mensaje);
}


void LISTA_imprimir_usuario_simple(lista_t pl, FILE* pfout)
{
	int i, j;
	usuario_t* usuario = (usuario_t*)(pl->dato);

	fprintf(pfout, "[%s]\n", usuario->usuario);
	fprintf(pfout, "id = %i\n", usuario->id);
	fprintf(pfout, "nombre = %s\n", usuario->nombre);


	fprintf(pfout, "amigos = ");
	for(i = 0, j = usuario->amigos->real - 1; i < j; i++)
		fprintf(pfout, "%i,", usuario->amigos->datos[i]);
	fprintf(pfout, "%i\n", usuario->amigos->datos[i]);

	LISTA_recorrer(usuario->mensajes, LISTA_imprimir_mensaje, pfout);

	if(pl->sig != NULL && pfout == stdout)
		printf("\n");
}

void LISTA_imprimir_usuario_multi(lista_t pl, FILE* pfout)
{
	usuario_t* usuario = (usuario_t*)(pl->dato);
	char *archivo;

	archivo = (char*)malloc(MAX_LENGTH_ID + 1 + strlen(usuario->usuario));

	sprintf(archivo, "%i", usuario->id);
	archivo = strcat(archivo, "-");
	archivo = strcat(archivo, usuario->usuario);

	pfout = fopen(archivo, "w");

	fprintf(stdout, "Se crea un nueva archivo : %s\n", archivo);

	LISTA_imprimir_usuario_simple(pl, pfout);

	fclose(pfout);
	free(archivo);
}

/* Gestion de eliminar */
retval_t LISTA_gestion_eliminar(lista_t *pl, char* v)
{
	int id, i;
	retval_t rv;
	lista_t nodo_a_eliminar = NULL;

	if(pl == NULL)
		return RV_ILLEGAL;
	if(v[0] == 'i')
	{
		for (i = 0; i < strlen(v) - 2; i++)

			v[i] = v[i + 2];
		v[i] = '\0';
		id = atoi(v);

		if((rv = LISTA_buscar(*pl, &id, LISTA_cmp_id, &nodo_a_eliminar)) != RV_SUCCESS)
			return rv;
		if((rv = LISTA_eliminar(pl, &nodo_a_eliminar)) != RV_SUCCESS)
			return rv;
	}

	else if(v[0] == 'u')
	{
		for (i = 0; i < strlen(v) - 2; i++)
			v[i] = v[i + 2];
		v[i] = '\0';

		if((rv = LISTA_buscar(*pl, v, LISTA_cmp_usuario, &nodo_a_eliminar)) != RV_SUCCESS)
			return rv;
		if((rv = LISTA_eliminar(pl, &nodo_a_eliminar)) != RV_SUCCESS)
			return rv;
	}

	else
		return RV_ERROR_ARG_ELIMNAR;


	return RV_SUCCESS;
}


retval_t LISTA_eliminar(lista_t *pl, lista_t *peliminar)
{

	if(*pl == *peliminar)
	{
		(*pl) = (*peliminar)->sig;
		if(LISTA_destruir_nodo(peliminar, LISTA_destruir_usuario) != RV_SUCCESS)
			return RV_ERROR_ARG_ELIMNAR;
		return RV_SUCCESS;
	}

	if((*pl)->sig == *peliminar)
	{
		(*pl)->sig = (*peliminar)->sig;
		if(LISTA_destruir_nodo(peliminar, LISTA_destruir_usuario) != RV_SUCCESS)
			return RV_ERROR_ARG_ELIMNAR;
		return RV_SUCCESS;
	}

	return LISTA_eliminar(&((*pl)->sig),peliminar);
}

retval_t LISTA_buscar(lista_t pl, void *t, retval_t (*cmp)(usuario_t*,void*), lista_t *result)
{
	if(cmp == NULL || t == NULL)
		return RV_ILLEGAL;

	if(pl == NULL)
		return RV_USER_NO_EXIST;

	if((*cmp)(pl->dato, t) == RV_SUCCESS)
	{
		*result = pl;
		return RV_SUCCESS;
	}

	return LISTA_buscar(pl->sig, t, cmp, result);
}


retval_t LISTA_cmp_id(usuario_t* usuario, void *t)
{
	if(usuario == NULL || t == NULL)
		return RV_ILLEGAL;

	if(usuario->id == *((int*)(t)))
		return RV_SUCCESS;
	else
		return RV_FALSE;
}

retval_t LISTA_cmp_usuario(usuario_t* usuario, void *t)
{
	if(usuario == NULL || t == NULL)
		return RV_ILLEGAL;

	if(!strcmp(usuario->usuario, (char*)(t)))
		return RV_SUCCESS;
	else
		return RV_FALSE;
}
