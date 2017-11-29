#ifndef FUNCIONES_H
#define FUNCIONES_H

retval_t cargar_usuarios(lista_t *pl, FILE* pfin);

retval_t cargar_usuario(lista_t *pl, char* renglon, FILE* pfin);

char* convert_renglon_usuario(char* renglon);

int convert_renglon_id(char* renglon);

retval_t crear_vector_amigos(char* renglon, vector_t **amigos);

int numero_amigos(char* renglon);

char* supp_header(char* renglon);

retval_t cargar_mensajes(lista_t *pl, FILE* pfin);

retval_t cargar_mensaje(lista_t *pl, FILE* pfin);

void leer_mensaje(char* renglon, FILE* pfin, size_t n, char delim);

retval_t validar_argumentos(int argc, char* argv[],FILE *file);

void imprimir_estado(retval_t rv);



#endif
