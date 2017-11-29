#ifndef STRUCT_H
#define STRUCT_H

#define MAX_LENGTH_MENSAJE 140
#define MAX_LENGTH_STAMP 11

typedef char* t_cadena;



typedef struct nodo_t
{
	struct nodo_t *sig;
	void *dato;
}nodo_t, *lista_t;


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
	lista_t mensajes;
}usuario_t;




#endif
