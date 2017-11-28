#ifndef LISTA_H
#define LISTA_H

int LISTA_vacia(lista_t l);

retval_t LISTA_crear(tda_lista *tda);

retval_t LISTA_crear_nodo(nodo_t **nodo, void *dato);

retval_t LISTA_destruir_nodo(tda_lista *tda);

retval_t LISTA_destruir(tda_lista *tda);

retval_t LISTA_insertar_al_principio(lista_t *pl, void *dato);

retval_t LISTA_insertar_al_final(lista_t *pl, void *dato);

retval_t LISTA_recorrer(tda_lista *tda);

retval_t LISTA_destruir_mensaje(void **mensajeBis);

retval_t LISTA_destruir_usuario(void **usuarioBis);

retval_t LISTA_imprimir_mensaje(tda_lista *tda);

retval_t LISTA_imprimir_usuario(tda_lista *tda);


#endif
