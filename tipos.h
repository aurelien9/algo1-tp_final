#ifndef TIPOS_H
#define TIPOS_H

typedef enum {
  ST_OK, 
  ST_ERROR_PUNTERO_NULO, 
  ST_ERROR_NOMEM, 
  ST_ERROR_CANT_ARGC, 
  ST_ERROR_OPEN_ARCHIVO, 
  ST_ERROR_DESTRUIR_ARREGLO, 
  ST_ERROR_CREAR_LISTA, 
  ST_ERROR_DESTRUIR_VECTOR, 
  ST_ERROR_DESTRUIR_LISTA, 
  ST_ERROR_CREAR_VECTOR, 
  ST_ERROR_IMPRIMIR_DATOS} status_t;

//Texto de los distintos estados
#define ERR_PREFIJO "Error"
#define TXT_OK "Todos los procesos funcionaron correctamente"
#define TXT_ERROR_PUNTERO_NULO "Uno de los punteros no se pudo verificar correctamente"
#define TXT_ERROR_NOMEM "No hay suficiente memoria para ejecutar el programa"
#define TXT_ERROR_CANT_ARGC "El programa se ejecuto sin ningun argumento"
#define TXT_ERROR_OPEN_ARCHIVO "No se pudo abrir el archivo"
#define TXT_ERROR_DESTRUIR_ARREGLO "No se pudo destruir el arreglo"
#define TXT_ERROR_CREAR_LISTA "No se puo crear la lista"
#define TXT_ERROR_DESTRUIR_VECTOR "El vector no pude ser eliminado"
#define TXT_ERROR_DESTRUIR_LISTA "No se pudo eliminar la lista"
#define TXT_ERROR_CREAR_VECTOR "No se pudo crear el vector"
#define TXT_ERROR_IMPRIMIR_DATOS "No se pueden mostrar los datos"
#define TXT_ERROR_ESTADO "El estado no pudo ser leido"

#define MAX_LENGTH 50
#define MAX_LENGTH_MENSAJE_LARGO 166
#define CROCHETE_1 '['
#define CROCHETE_2 ']'
#define IGUAL '='
#define COMA ','

#endif
