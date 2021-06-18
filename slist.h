//Esto pregunta si está definida la librería, en caso de no
//estarlo la define
#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>

//Esto está definiendo un nuevo tipo de dato, así como con typedef
//y struct ponemos un alias a una estructura como hemos visto en clase.
//Ahora, lo que estamos haciendo es llamar con el identificador 
//FuncionVisitante a cualquier función que tome un entero y tenga tipo
//de retorno void 
typedef struct {
    char *nombre, *direccion, *telefono, *mail, *aliasTelegram, *usuarioInstagram;
} Contacto;

typedef struct _SNodo {
  Contacto dato;
  struct _SNodo *sig;
} SNodo;

typedef void (*FuncionVisitante) (Contacto dato);

typedef int (*FuncionComparacion) (Contacto dato1, Contacto dato2);


//Cuando usamos SList estamos representando un SNodo*
//es decir, usar SList sería lo mismo que usar: struct _SNodo *
typedef SNodo *SList;

/**
 * Devuelve una lista vacía.
 */
SList slist_crear();

/**
 * Destruccion de la lista.
 */
void slist_destruir(SList lista);

/**
 * Determina si la lista es vacía.
 */
int slist_vacia(SList lista);

/**
 * Agrega un elemento al final de la lista. Se le pasan los argumentos de manera individual para evitar tener que crear una struct.
 */
SList slist_agregar_final(SList lista, char *nombre, char *direccion, char *telefono, char *mail, char *aliasTelegram, char *usuarioInstagram);

/**
 * Agrega un elemento al inicio de la lista. Se le pasan los argumentos de manera individual para evitar tener que crear una struct.
 */
SList slist_agregar_inicio(SList lista, char *nombre, char *direccion, char *telefono, char *mail, char *aliasTelegram, char *usuarioInstagram);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

/**
 * Devuelve la longitud de la lista.
 */
int slist_longitud(SList lista);

/*
 * Borra de la lista un elemento en la posicion dada. Devuelve 0 si el elemento se borro de manera correcta y 1 si ocurrio un error. Tomar en cuenta que la posicion empieza a contar desde 0.
 */
int slist_eliminar(SList *lista, int posicion);

/*
 * Determina si un elemento esta en la lista. Devuelve 0 si no esta y 1 si esta. Se le pasa solo el nombre del elemento, no toda la struct.
 */
int slist_contiene(SList lista, char *nombre);

/*
 * Si un elemento esta en la lista devuelve su indice, empezando desde 0. Si no esta devuelve -1. Se le pasa solo el nombre del elemento, no toda la struct.
 */
int slist_indice(SList lista, char *nombre);
#endif /* __SLIST_H__ */
