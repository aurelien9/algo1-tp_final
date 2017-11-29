#ifndef LISTA_H
#define LISTA_H

int LISTA_vacia(lista_t l);

retval_t LISTA_crear_nodo(nodo_t **nodo, void *dato);

retval_t LISTA_destruir_nodo(lista_t *pl, retval_t (*destructor)(void**));

retval_t LISTA_destruir(lista_t *pl, retval_t (*destructor)(void**));

retval_t LISTA_insertar_al_principio(lista_t *pl, void *dato);

retval_t LISTA_insertar_al_final(lista_t *pl, void *dato);

retval_t LISTA_recorrer(lista_t  pl, void (*imprimir)(lista_t, FILE*), FILE* pfout);

retval_t LISTA_destruir_mensaje(void **mensajeBis);

retval_t LISTA_destruir_usuario(void **usuarioBis);

void LISTA_imprimir_mensaje(lista_t pl, FILE* pfout);

void LISTA_imprimir_usuario_simple(lista_t pl, FILE* pfout);

void LISTA_imprimir_usuario_multi(lista_t pl, FILE* pfout);

retval_t LISTA_gestion_eliminar(lista_t *pl, char* v);

retval_t LISTA_eliminar(lista_t *pl, lista_t *peliminar);

retval_t LISTA_buscar(lista_t pl, void *t, retval_t (*cmp)(usuario_t*,void*), lista_t *result);

retval_t LISTA_cmp_id(usuario_t* usuario, void *t);

retval_t LISTA_cmp_usuario(usuario_t* usuario, void *t);

#endif
