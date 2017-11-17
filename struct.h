#ifndef STRUCT_H
#define STRUCT_H

#define MAX_LENGTH_MENSAJE 140

typedef struct
{
  unsigned int year;
  unsigned int month;
  unsigned int day;
}

typedef struct
{
  int num;
  t_date stamp;
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


typedef struct usuario {
  int id ;
  t_cadena nombre;
  t_cadena usuario;
  vector_s amigos;
  lista_s mensajes;
}usuario;


typedef struct lista_usuarios;

struct lista_usuarios
{
  lista_usuarios *sig;
  usuario *datos;
};


#endif
