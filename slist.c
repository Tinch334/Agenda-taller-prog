#include "slist.h"
#include <stdlib.h>
#include <string.h>

/*
 * NOTA: Para usar funciones con punteros dobles(**) hay que usar el * para desreferenciar adentro de un parentesis. De lo contrario el operador "->" toma precedencia y la expresion no funciona. Recordar ademas que "SList" ya es un puntero(Ver su declaracion "slist.h"). Ejemplo:
 *
 *  void slist_mostrar(SList *lista) {
 *      printf("\nElem: %d\n", (*lista)->dato);
 *  }
 */

SList slist_crear() {
  return NULL;
}

void borrar_struct(Contacto structABorrar) {
    free(structABorrar.nombre);
    free(structABorrar.direccion);
    free(structABorrar.telefono);
    free(structABorrar.mail);
    free(structABorrar.aliasTelegram);
    free(structABorrar.usuarioInstagram);
}

//Esta función destruye todos los nodos de la lista haciendo que 
//liberemos la memoria del nodo usando free y, pasando al siguiente
//hasta llegar a NULL
void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;

  while (lista != NULL) {
    nodoAEliminar = lista;
    //Destruye todas las strings de la struct y su espacio asociado en memoria.
    borrar_struct(nodoAEliminar->contacto);

    lista = lista->sig;

    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, Contacto dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  //no sería conveniente tener una función que clone un contacto y retorne dicho contado?
  //"strdup" es una funcion de "string.h" que copia la string provista devolviendo un puntero a la misma, evitando tener que asignar memoria manualmente.
  nuevoNodo->contacto.nombre = strdup(dato.nombre);
  nuevoNodo->contacto.direccion = strdup(dato.direccion);
  nuevoNodo->contacto.telefono = strdup(dato.telefono);
  nuevoNodo->contacto.mail = strdup(dato.mail);
  nuevoNodo->contacto.aliasTelegram = strdup(dato.aliasTelegram);
  nuevoNodo->contacto.usuarioInstagram = strdup(dato.usuarioInstagram);

  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->contacto);
}

int slist_longitud(SList lista) {
    int longitud = 1;

    if (lista == NULL)
        return 0;

    for (SList nodo = lista;nodo->sig != NULL; nodo = nodo->sig, longitud++);

    return longitud;
}

//Borrar el primer o ultimo elemento no funciona con una lista de un solo elemento.
int slist_eliminar(SList *lista, int posicion) {
     //Tomo en cuenta que se pueden borrar elementos al principio y al final de la lista.
    if (posicion > slist_longitud(*lista))
        return 1;
    else if (posicion == 0) {
        //Guardo el primer nodo. Reasigno al segundo nodo como primer elemento de la lista y borro el primero.
        SList nodo = *lista;
        *lista = (*lista)->sig;

        borrar_struct(nodo->contacto);
        free(nodo);
        //no era mejor poner un return acá?
    }
    //por qué hago el caso último separado de los otros casos? borrar el último es lo mismo que borrar cualquier nodo intermedio.
    //su siguiente es NULL.
    else if (posicion == slist_longitud(*lista)) {
        SList nodo = *lista;

        //Va al penultimo elemento de la lista.
        for (int i = 0; i < slist_longitud(*lista) - 2; i++, nodo = nodo->sig);

        //Usando el penultimo nodo elimina el ultimo y hace que el proximo elemento sea "NULL".
        borrar_struct(nodo->contacto);
        free(nodo->sig);
        nodo->sig = NULL;
    }
    else {
        //Para borrar un elemento en medio de la lista "sig" del nodo anterior a su posicion debe pasar a apuntar al proximo nodo.
        SList anterior = *lista;

        for (int i = 0; i < posicion - 1; i++, anterior = anterior->sig);

        //Borro el nodo deseado y asigno el "sig" del anterior al posterior.
        SList posterior = anterior->sig->sig;
        borrar_struct(anterior->sig->contacto);
        free(anterior->sig);
        anterior->sig = posterior;
    }

    return 0;
}

//Recorro la lista buscando donde está el nombre a eliminar y luego llamo a una función que se desplaza hasta esa posición. 
//No se podía hacer todo junto?
int slist_indice(SList lista, char *nombre) {
    SList nodo = lista;
    int ret = -1;

    for (int i = 0; nodo != NULL && strcmp(nodo->contacto.nombre, nombre) == 0; nodo = nodo->sig, i++)
        if (strcmp(nodo->contacto.nombre, nombre) == 0)
            ret = i;

    return ret;
}
