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

retval_t LISTA_eliminar(lista_t *pl);

#endif
