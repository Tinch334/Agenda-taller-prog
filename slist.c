#include "slist.h"
#include <stdlib.h>

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

//Esta función destruye todos los nodos de la lista haciendo que 
//liberemos la memoria del nodo usando free y, pasando al siguiente
//hasta llegar a NULL
void slist_destruir(SList lista) {
  SNodo *nodoAEliminar;
  while (lista != NULL) {
    nodoAEliminar = lista;
    lista = lista->sig;
    free(nodoAEliminar);
  }
}

int slist_vacia(SList lista) {
  return lista == NULL;
}

SList slist_agregar_final(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = NULL;

  if (lista == NULL)
    return nuevoNodo;

  SList nodo = lista;
  for (;nodo->sig != NULL;nodo = nodo->sig);
  /* ahora 'nodo' apunta al ultimo elemento en la lista */

  nodo->sig = nuevoNodo;
  return lista;
}

SList slist_agregar_inicio(SList lista, int dato) {
  SNodo *nuevoNodo = malloc(sizeof(SNodo));
  nuevoNodo->dato = dato;
  nuevoNodo->sig = lista;
  return nuevoNodo;
}

void slist_recorrer(SList lista, FuncionVisitante visit) {
  for (SNodo *nodo = lista; nodo != NULL; nodo = nodo->sig)
    visit(nodo->dato);
}

int slist_longitud(SList lista) {
    int longitud = 1;

    if (lista == NULL)
        return 0;

    for (SList nodo = lista;nodo->sig != NULL; nodo = nodo->sig, longitud++);

    return longitud;
}

SList slist_concatenar(SList lista1, SList lista2) {
    //Si la primera lista esta vacia devolver la segunda y vieversa.
    if (lista1 == NULL)
        return lista2;
    
    if (lista2 == NULL)
        return lista1;

    SList nodo = lista1;
    for (;nodo->sig != NULL; nodo = nodo->sig);

    nodo->sig = lista2;

    //Tecnicamente no es necesario poner un return al final, esto se debe a que si se necesita hacer un return, particularmente si la primera lista esta vacia, el segundo return se hace para ahorrar procesamiento, si la lista esta vacia no es necesario usar el for. Retomando, si ninguna lista esta vacia el primer elemento de la primera lista no cambio, por lo que no seria necesario. El problema con esto es que cuando una funcion que se supone debe devolver una valor no lo hace puede haber problemas en C ya que normalmente se devuelve basura.
    return lista1;
}

int slist_insertar(SList *lista, int posicion, int dato) {
    if (posicion > slist_longitud(*lista))
        return 1;

    //Tomo en cuenta que se pueden insertar elementos al principio y al final de la lista.
    if (posicion > slist_longitud(*lista))
        return 1;
    else if (posicion == 0)
        *lista = slist_agregar_inicio(*lista, dato);
    else if (posicion == slist_longitud(*lista))
        *lista = slist_agregar_final(*lista, dato);
    else {
        //Para insertar un elemento en medio de la lista "sig" del nodo anterior a su posicion debe pasar a apuntar al nuevo dato y su "sig" debe apuntar al elemento que desplazo.
        SList nodo = *lista;
        SList nuevoNodo = malloc(sizeof(SNodo));
        nuevoNodo->dato = dato;

        for (int i = 0; i < posicion - 1; i++, nodo = nodo->sig)

        //Primero hacemos que "sig" del nodo nuevo apunte a el nodo que desplazo. Despues hacemos que el "sig" del nodo que esta antes del nuevo apunte al nuevo.
        nuevoNodo->sig = nodo->sig;
        nodo->sig = nuevoNodo;
    }

    return 0;
}

//Borrar el primer o ultimo elemento no funciona con una lista de un solo elemento.
int slist_eliminar(SList *lista, int posicion) {
    if (posicion > slist_longitud(*lista))
        return 1;

     //Tomo en cuenta que se pueden borrar elementos al principio y al final de la lista.
    if (posicion > slist_longitud(*lista))
        return 1;
    else if (posicion == 0) {
        //Guardo el primer nodo. Reasigno al segundo nodo como primer elemento de la lista y borro el primero.
        SList nodo = *lista;
        *lista = (*lista)->sig;

        free(nodo);
    }
    else if (posicion == slist_longitud(*lista)) {
        SList nodo = *lista;

        //Va al penultimo elemento de la lista.
        for (int i = 0; i < slist_longitud(*lista) - 2; i++, nodo = nodo->sig);

        //Usando el penultimo nodo elimina el ultimo y hace que el proximo elemento sea "NULL".
        free(nodo->sig);
        nodo->sig = NULL;
    }
    else {
        //Para borrar un elemento en medio de la lista "sig" del nodo anterior a su posicion debe pasar a apuntar al proximo nodo.
        SList anterior = *lista;

        for (int i = 0; i < posicion - 1; i++, anterior = anterior->sig);

        //Borro el nodo deseado y asigno el "sig" del anterior al posterior.
        SList posterior = anterior->sig->sig;
        free(anterior->sig);
        anterior->sig = posterior;
    }

    return 0;

}

int slist_contiene(SList lista, int dato) {
    SList nodo = lista;

    if (lista == NULL)
        return 0;

    for (;nodo != NULL; nodo = nodo->sig)
        if (nodo->dato == dato)
            return 1;

    return 0;
}

int slist_indice(SList lista, int dato) {
    SList nodo = lista;

    if (lista == NULL)
        return -1;

    for (int i = 0; nodo != NULL; nodo = nodo->sig, i++)
        if (nodo->dato == dato)
            return i;

    return -1;
}

SList slist_intersecar(SList lista1, SList lista2) {
    //Si alguna de las listas esta vacia no puede haber interseccion.
    if (lista1 == NULL || lista2 == NULL)
        return NULL;

    SList interseccion = slist_crear();
    SList nodo1 = lista1;
    SList nodo2 = NULL;

    for (;nodo1 != NULL; nodo1 = nodo1->sig) {
        SList nodo2 = lista2;

        for (;nodo2 != NULL; nodo2 = nodo2->sig)
            //Si hay un elemento igual en las listas y no esta ya en la lista interseccion ponerlo.
            if (nodo1->dato == nodo2->dato && slist_contiene(interseccion, nodo1->dato) == 0)
                interseccion = slist_agregar_final(interseccion, nodo1->dato);
    }

    return interseccion;
}

//Con esta funcion al funcion "slist_intersecar" podria ser reemplzada con una llamada a esta que tenga como funcion igual una que revise la igualdad de los elementos.
SList slist_intersecar_custom(SList lista1, SList lista2, FuncionComparacion comp, int ambos) {
    //Si alguna de las listas esta vacia no puede haber interseccion.
    if (lista1 == NULL || lista2 == NULL)
        return NULL;

    SList interseccion = slist_crear();
    SList nodo1 = lista1;
    SList nodo2 = NULL;

    for (;nodo1 != NULL; nodo1 = nodo1->sig) {
        SList nodo2 = lista2;

        for (;nodo2 != NULL; nodo2 = nodo2->sig)
            //Si hay un elemento igual en las listas y no esta ya en la lista interseccion ponerlo.
            if (comp(nodo1->dato, nodo2->dato) == 1 && slist_contiene(interseccion, nodo1->dato) == 0) {
                interseccion = slist_agregar_final(interseccion, nodo1->dato);

                if (ambos == 1)
                    interseccion = slist_agregar_final(interseccion, nodo2->dato);
            }
    }

    return interseccion;
}

SList slist_reverso(SList lista) {
    SList inversa = slist_crear();
    SList nodo = NULL;

    if (lista == NULL)
        return NULL;
    else if (slist_longitud(lista) == 1)
        return lista;

    //Para obtener la lista invesa este "algoritmo" empieza desde el final de la lista y va hacia el principio, copiando los elementos. El primer for se ocupa del numero de elemento que esta siendo copiado y el segundo de llevar a "nodo" a ese elemento.
    for (int i = slist_longitud(lista) - 1; i >= 0; i--) {
        nodo = lista;

        for (int j = 0; j < i; j++, nodo = nodo->sig);
        inversa = slist_agregar_final(inversa, nodo->dato);
    }

    return inversa;
}

SList slist_intercalar(SList lista1, SList lista2) {
    SList intercalada = slist_crear();
    SList nodo1 = lista1;
    SList nodo2 = lista2;

    if (lista1 == NULL && lista2 == NULL)
        return NULL;
    else if (lista1 == NULL)
        return lista2;
    else if (lista2 == NULL)
        return lista1;

    do {
        intercalada = slist_agregar_final(intercalada, nodo1->dato);
        intercalada = slist_agregar_final(intercalada, nodo2->dato);

        nodo1 = nodo1->sig;
        nodo2 = nodo2->sig;

    } while (nodo1 != NULL && nodo2 != NULL);

    //Si alguna de las listas no se termino de intercalar(Es mas larga) terminar de ponerla al final.
    if (nodo1 != NULL) {
        for(;nodo1 != NULL; nodo1 = nodo1->sig)
            intercalada = slist_agregar_final(intercalada, nodo1->dato);
    }
    else if (nodo2 != NULL) {
        for(;nodo2 != NULL; nodo2 = nodo2->sig)
            intercalada = slist_agregar_final(intercalada, nodo2->dato);
    }

    return intercalada;
}
