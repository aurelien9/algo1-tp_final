#ifndef STRUCT_H
#define STRUCT_H

#define MAX_LENGTH_MENSAJE 140
#define MAX_LENGTH_STAMP 11

typedef char* t_cadena;

typedef enum {
	RV_SUCCESS,
	RV_ILLEGAL,
	RV_ENOMEM,
	RV_ERROR_IMPRIMIR,
	RV_ERROR_DESTRUIR_MENSAJES,
	RV_ERROR_DESTRUIR_NODO
}retval_t;

typedef struct nodo_t
{
	struct nodo_t *sig;
	void *dato;
}nodo_t, *lista_t;


typedef struct tda_lista
{
	nodo_t *l;
	retval_t (*destructor)(void**);
	retval_t (*imprimir)(struct tda_lista*);
	FILE* pfin;
	FILE* pfout;
}tda_lista;


typedef struct
{
	int num;
	char stamp[MAX_LENGTH_STAMP];
	int id;
	char mensaje[MAX_LENGTH_MENSAJE];
}mensaje_t;


typedef struct
{
	int real;
	int alloc;
	int* datos;
}vector_t;


typedef struct usuario
{
	t_cadena usuario;
	int id;
	t_cadena nombre;
	vector_t* amigos;
	tda_lista* mensajes;
}usuario_t;




#endif
