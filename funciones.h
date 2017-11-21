#ifndef FUNCIONES__H
#define FUNCIONES__H

status_t cargar_usuarios(userList** v, FILE *pf);

status_t cargar_usuario(userList** v, char* renglon, FILE *pf);

char* convert_renglon_usuario(char* renglon);

int convert_renglon_id(char* renglon);

status_t crear_vector_amigos(char* renglon, usuario* user);

int numero_amigos(char* renglon);

status_t crear_lista_mensaje(usuario* user, FILE* pf);

char* supp_header(char* renglon);

char* strdup(const char* sc);

status_t split(char*** arreglo, char* cadena, char delimitador, size_t* l);

status_t destruir_arreglo_cadenas(char ***campos, size_t size);

status_t destruir_usuarios(userList** v);

status_t destruir_usuario(usuario** user);

status_t destruir_vector_amigos(usuario* user);

status_t destruir_lista_mensaje(usuario* user);

status_t imprimir_usuarios(userList* v, FILE* pf);

status_t imprimir_usuario(usuario* user, FILE* pf);

#endif
