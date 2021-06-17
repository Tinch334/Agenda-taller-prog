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
typedef void (*FuncionVisitante) (int dato);

typedef int (*FuncionComparacion) (int dato1, int dato2);


typedef struct _SNodo {
  int dato;
  struct _SNodo *sig;
} SNodo;

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
 * Agrega un elemento al final de la lista.
 */
SList slist_agregar_final(SList lista, int dato);

/**
 * Agrega un elemento al inicio de la lista.
 */
SList slist_agregar_inicio(SList lista, int dato);

/**
 * Recorrido de la lista, utilizando la funcion pasada.
 */
void slist_recorrer(SList lista, FuncionVisitante visit);

/**
 * Devuelve la longitud de la lista.
 */
int slist_longitud(SList lista);

/**
 * Concatena la primera lista con la segunda lista, almacenando el resultado en la primera.
 */
SList slist_concatenar(SList lista1, SList lista2);

/**
 * Inserta un elemento en la posicion dada. Devuelve 0 si el elemento se inserto de manera correcta y 1 si ocurrio un error. Tomar en cuenta que posicion empieza a contar desde 0.
 */
int slist_insertar(SList *lista, int posicion, int dato);

/*
 * Borra de la lista un elemento en la posicion dada. Devuelve 0 si el elemento se borro de manera correcta y 1 si ocurrio un error. Tomar en cuenta que la posicion empieza a contar desde 0.
 */
int slist_eliminar(SList *lista, int posicion);

/*
 * Determina si un elemento esta en la lista. Devuelve 0 si no esta y 1 si esta.
 */
int slist_contiene(SList lista, int dato);

/*
 * Si un elemento esta en la lista devuelve su indice, empezando desde 0. Si no esta devuelve -1.
 */
int slist_indice(SList lista, int dato);

/*
 * Devuelve una SList con los elementos comunes a ambas listas, si no hay elementos comunes devuelve NULL.
 */
SList slist_intersecar(SList lista1, SList lista2);

/*
 * Devuelve una SList con los elementos comunes a ambas listas, si no hay elementos comunes devuelve NULL. Para determinar que elementos son iguales/comunes usa la funcion pasada, que toma los dos datos y devuelve 1 si son iguales y 0 si no. Finalmente "ambos", si es 1 ambos valores deben ser almacenados, es decir el de la lista1 y el de la lista2, es util cuando el concepto de igualdad no implica igualdad tradicional.
 */
SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparacion comp, int ambos);

/*
 * Devuleve el reverso de la lista dada.
 */
SList slist_reverso(SList lista);

/*
 * Devuelve una lista con los elementos de las listas pasadas intercalados. Por ejemplo dadas [1, 2, 3, 4] y [5, 6] devuelve [1, 5, 2, 6, 3, 4].
 */
SList slist_intercalar(SList lista1, SList lista2);
#endif /* __SLIST_H__ */
