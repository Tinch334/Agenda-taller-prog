#include <stdio.h>
#include <stdlib.h>
#include "slist.h"

static void imprimir_entero(Contacto dato) {
    printf("%s ", dato.nombre);
}

int main(int argc, char *argv[]) {
    SList lista = slist_crear();
    SList segundaLista = slist_crear();

    lista = slist_agregar_inicio(lista, "Pepe", "Cordoba 558", "105896", "unmail@gmail.com", "pepito123", "pepitoig");
    lista = slist_agregar_inicio(lista, "Juana", "Mendoza 1278", "98564", "mailJUanA@yahoo.com", "juanatelegram", "juanaig");
    /*lista = slist_agregar_inicio(lista, 1);
    lista = slist_agregar_final(lista, 4);*/

    segundaLista = slist_agregar_inicio(segundaLista, "Roberto", "Francia 354", "00025", "robertthemail@robert.com", "robertotelegram", "robertoig");
    segundaLista = slist_agregar_inicio(segundaLista, "Marcos", "Alem 4720", "558756", "marcosmail@marcos.com", "marcosTelegram", "marcosig");
    segundaLista = slist_agregar_inicio(segundaLista, "Guadalupe", "Echeverria 12", "999663355", "guadalupemail@gudalupe.com", "guadalupeTelgram", "guadalupeig");

    printf("Primera lista: ");
    slist_recorrer(lista, imprimir_entero);
    printf("\nLongitud de la primera lista: %d\n", slist_longitud(lista));

    printf("Segunda lista: ");
    slist_recorrer(segundaLista, imprimir_entero);
    printf("\nLongitud de la segunda lista: %d\n", slist_longitud(segundaLista));


    slist_destruir(lista);
    slist_destruir(segundaLista);

    return 0;
}