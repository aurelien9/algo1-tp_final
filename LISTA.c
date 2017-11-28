#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "struct.h"
#include "tipos.h"
#include "funciones.h"
#include "LISTA.h"


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


retval_t LISTA_destruir_nodo(tda_lista *tda)
{
	retval_t rv;

	if(tda == NULL)
		return RV_ILLEGAL;
	if(tda->l == NULL)
		return RV_SUCCESS;
	if(tda->destructor == NULL)
		return RV_ILLEGAL;

	if((rv = tda->destructor(&(tda->l->dato))) != RV_SUCCESS)
		return rv;

	tda->l->sig = NULL;

	free(tda->l);
	tda->l = NULL;

	return RV_SUCCESS;
}

retval_t LISTA_destruir(tda_lista *tda)
{
	tda_lista *sig = tda;

	if(tda == NULL)
		return RV_ILLEGAL;

	if(LISTA_vacia(tda->l))
		return RV_SUCCESS;

	sig->l = tda->l->sig;

	LISTA_destruir_nodo(tda);

	return LISTA_destruir(sig);
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


retval_t LISTA_recorrer(tda_lista *tda)
{
	tda_lista *sig = tda;

	if(tda == NULL || tda->imprimir == NULL)
		return RV_ILLEGAL;

	if(tda->l == NULL)
		return RV_SUCCESS;

	tda->imprimir(tda);
	sig->l = sig->l->sig;
	return LISTA_recorrer(sig);
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

	if((rv = LISTA_destruir((*usuario)->mensajes)) != RV_SUCCESS)
	{
		return RV_ERROR_DESTRUIR_MENSAJES;
	}
	free((*usuario)->mensajes);
	(*usuario)->mensajes = NULL;

	free(*usuario);
	*usuario = NULL;

	return RV_SUCCESS;
}


retval_t LISTA_imprimir_mensaje(tda_lista *tda)
{
	mensaje_t *mensaje;

	if(tda == NULL)
		return RV_ILLEGAL;

	mensaje = (mensaje_t*)(tda->l->dato);
	fprintf(tda->pfout, "mensaje = %i,", mensaje->num);
	fprintf(tda->pfout, "%s,", mensaje->stamp);
	fprintf(tda->pfout, "%i,", mensaje->id);
	fprintf(tda->pfout, "%s\n", mensaje->mensaje);
	return RV_SUCCESS;
}


retval_t LISTA_imprimir_usuario(tda_lista *tda)
{
	int i, j;
	usuario_t *usuario;

	if(tda == NULL)
		return RV_ILLEGAL;

	usuario = (usuario_t*)(tda->l->dato);

	fprintf(tda->pfout, "[%s]\n", usuario->usuario);
	fprintf(tda->pfout, "id = %i\n", usuario->id);
	fprintf(tda->pfout, "nombre = %s\n", usuario->nombre);


	fprintf(tda->pfout, "amigos = ");
	for(i = 0, j = usuario->amigos->real - 1; i < j; i++)
		fprintf(tda->pfout, "%i,", usuario->amigos->datos[i]);
	fprintf(tda->pfout, "%i\n", usuario->amigos->datos[i]);

	if(LISTA_recorrer(usuario->mensajes) != RV_SUCCESS)
		return RV_ERROR_IMPRIMIR;

	if(tda->l->sig != NULL)
		printf("\n");

	return RV_SUCCESS;
}
