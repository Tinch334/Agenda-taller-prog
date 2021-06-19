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
  Contacto contacto;
  struct _SNodo *sig;
} SNodo;

typedef void (*FuncionVisitante) (Contacto contacto);

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
 * Agrega un elemento al final de la lista. Se le pasan los argumentos de manera individual para evitar tener que crear una struct.
 */
SList slist_agregar_final(SList lista, Contacto dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

/*
 * Borra de la lista un elemento en la posicion dada. Devuelve 0 si el elemento se borro de manera correcta y 1 si ocurrio un error. Tomar en cuenta que la posicion empieza a contar desde 0.
 */
int slist_eliminar(SList *lista, int posicion);

/*
 * Si un elemento esta en la lista devuelve su indice, empezando desde 0. Si no esta devuelve -1. Se le pasa solo el nombre del elemento, no toda la struct.
 */
int slist_indice(SList lista, char *nombre);
#endif /* __SLIST_H__ */
