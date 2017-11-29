#ifndef TIPOS_H
#define TIPOS_H

/* Texto de los distintos estados */
#define ERR_PREFIJO "Error"
#define TXT_SUCCESS "Todos los procesos funcionaron correctamente"
#define TXT_ILLEGAL "Uno de los punteros no se pudo verificar correctamente"
#define TXT_ENOMEM "No hay suficiente memoria para ejecutar el programa"
#define TXT_ERROR_CANT_ARGC "El programa se ejecuto sin ningun argumento"
#define TXT_ERROR_OPEN_ARCHIVO "No se pudo abrir el archivo"
#define TXT_ERROR_DESTRUIR_LISTA "No se pudo eliminar la lista"
#define TXT_ERROR_IMPRIMIR "No se pueden mostrar los datos"
#define TXT_ERROR_ESTADO "El estado no pudo ser leido"

#define MAX_LENGTH_ID 5
#define MAX_LENGTH 50
#define MAX_LENGTH_NUM 10
#define CROCHETE_1 '['
#define CROCHETE_2 ']'
#define IGUAL '='
#define COMA ','
#define RETURN '\n'

 
typedef enum {
	RV_SUCCESS,
	RV_ILLEGAL,
	RV_ENOMEM,
	RV_ERROR_IMPRIMIR,
	RV_ERROR_DESTRUIR_MENSAJES,
	RV_ERROR_CANT_ARGC,
	RV_ERROR_OPEN_ARCHIVO,
	RV_ERROR_DESTRUIR_LISTA
}retval_t;

typedef enum {
	SIMPLE,
	MULTI,
	NONE
}output_t;

#endif
