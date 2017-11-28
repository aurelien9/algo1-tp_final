#ifndef FUNCIONES_H
#define FUNCIONES_H

retval_t cargar_usuarios(tda_lista *tda);

retval_t cargar_usuario(tda_lista *tda, char* renglon);

retval_t cargar_mensajes(tda_lista *tda);

void leer_mensaje(char* renglon, FILE* pf, size_t n, char delim);

retval_t cargar_mensaje(tda_lista *tda);

char* convert_renglon_usuario(char* renglon);

int convert_renglon_id(char* renglon);

retval_t crear_vector_amigos(char* renglon, vector_t **amigos);

int numero_amigos(char* renglon);

char* supp_header(char* renglon);



#endif
