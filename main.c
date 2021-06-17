#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(int dato) {
    printf("%d ", dato);
}

int main(int argc, char *argv[]) {
    SList lista = slist_crear();
    SList lista2 = slist_crear();
    SList inversa = slist_crear();
    SList intercalada = slist_crear();

    lista = slist_agregar_inicio(lista, 3);
    lista = slist_agregar_inicio(lista, 2);
    lista = slist_agregar_inicio(lista, 1);
    lista = slist_agregar_final(lista, 4);

    lista2 = slist_agregar_final(lista2, 5);
    lista2 = slist_agregar_final(lista2, 6);
    lista2 = slist_agregar_final(lista2, 7);
    lista2 = slist_agregar_final(lista2, 8);
    lista2 = slist_agregar_final(lista2, 9);


    printf("\nLista: ");
    slist_recorrer(lista, imprimir_entero);

    printf("\n\nLista invertida: ");
    inversa = slist_reverso(lista);
    slist_recorrer(inversa, imprimir_entero);

    printf("\n\nLista intecalada con la segunda lista: ");
    intercalada = slist_intercalar(lista, lista2);
    slist_recorrer(intercalada, imprimir_entero);
    printf("\n");

    slist_destruir(lista);

    return 0;
}
