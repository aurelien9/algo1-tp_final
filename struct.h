#ifndef STRUCT_H
#define STRUCT_H

#define MAX_LENGTH_MENSAJE 140

typedef char* t_cadena;


typedef struct
{
	int num;
	char stamp[10];
	char mensaje[MAX_LENGTH_MENSAJE];
	int id;
}mensaje;


typedef struct lista_s lista_s;

struct lista_s
{
	lista_s *sig;
	mensaje *datos;
};


typedef struct
{
	int real;
	int alloc;
	int *datos;
}vector_s;


typedef struct usuario
{
	int id;
	t_cadena nombre;
	t_cadena usuario;
	vector_s* amigos;
	lista_s* mensajes;
}usuario;


typedef struct userList userList;

struct userList
{
	userList *sig;
	usuario *datos;
};


#endif
