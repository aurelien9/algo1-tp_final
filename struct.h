#ifndef STRUCT_H
#define STRUCT_H

#define MAX_LENGTH_MENSAJE 140
#define MAX_LENGTH_STAMP 10

typedef char* t_cadena;


typedef struct
{
	int num;
	char stamp[MAX_LENGTH_STAMP];
	int id;
	char mensaje[MAX_LENGTH_MENSAJE];
}mensaje;


typedef struct lista_s lista_s;

struct lista_s
{
	lista_s* sig;
	mensaje* datos;
};


typedef struct
{
	int real;
	int alloc;
	int* datos;
}vector_s;


typedef struct usuario
{
	t_cadena usuario;
	int id;
	t_cadena nombre;
	vector_s* amigos;
	lista_s* mensajes;
}usuario;


typedef struct userList userList;

struct userList
{
	userList* sig;
	usuario* datos;
};


#endif
