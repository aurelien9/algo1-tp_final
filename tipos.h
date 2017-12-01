#ifndef TIPOS_H
#define TIPOS_H

/* Texto de los distintos estados */
#define ERR_PREFIJO "Error"
#define TXT_SUCCESS "Todos los procesos funcionaron correctamente"
#define TXT_ILLEGAL "Uno de los punteros no se pudo verificar correctamente"
#define TXT_ENOMEM "No hay suficiente memoria para ejecutar el programa"
#define TXT_ERROR_CANT_ARGC "Falta algunos argumentos para ejecutar el programa"
#define TXT_ERROR_MIN_ARG "El programa para sar ejecutado necesita un minimo de 1 argumentos"
#define TXT_ERROR_OPEN_ARCHIVO "No se pudo abrir el archivo"
#define TXT_ERROR_DESTRUIR_LISTA "No se pudo eliminar la lista"
#define TXT_ERROR_IMPRIMIR "No se pueden mostrar los datos"
#define TXT_ERROR_ESTADO "El estado no pudo ser leido"
#define TXT_ERROR_ARG_ELIMINAR "El argumento del usuario no se puede leer. Debe ser de la forma i:id o u:usuario"
#define TXT_USER_NO_EXIST "El usuario que quiere eliminar no exista"
#define TXT_ERROR_ELIMINAR "Imposible de eliminar el usuario"
#define TXT_ERROR_FORMATO_ARG "Los argumentos de eliminar deben ser de la forma u:usuario o i:id"
#define MIN_ARG 1
#define CANT_ARG 0

#define MAX_LENGTH_ID 5
#define MAX_LENGTH 50
#define MAX_LENGTH_NUM 10
#define CROCHETE_1 '['
#define CROCHETE_2 ']'
#define IGUAL '='
#define COMA ','
#define GUION '-'
#define RETURN '\n'
#define DOS_PUNTO ':'
#define LETTRA_I 'i'
#define LETTRA_U 'u'

#define SHORT_ELIM "-e"
#define LONG_ELIM "--eliminar"
#define SHORT_OUT "-o"
#define LONG_OUT "--output"

#define OUT_SINGLE "single"
#define OUT_MULT "multi"

typedef enum {
	RV_SUCCESS,
	RV_ILLEGAL,
	RV_ENOMEM,
	RV_ERROR_IMPRIMIR,
	RV_ERROR_DESTRUIR_MENSAJES,
	RV_ERROR_CANT_ARGC,
	RV_ERROR_MIN_ARG,
	RV_ERROR_OPEN_ARCHIVO,
	RV_ERROR_DESTRUIR_LISTA,
	RV_ERROR_ARG_ELIMNAR,
	RV_USER_NO_EXIST,
	RV_FALSE,
	RV_ERROR_ELIMNAR,
	RV_ERROR_FORMATO_ARG
}retval_t;

typedef enum {
	SIMPLE,
	MULTI,
	NONE
}output_t;

#endif
