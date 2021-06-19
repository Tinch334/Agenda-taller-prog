/*
    HECHO POR JUAN IGNACIO BERTONI Y MARTÍN GOÑI
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "slist.h"

//FUNCIONES AUXILIARES

static void imprimir_entero(Contacto dato) {
    printf("%s ", dato.nombre);
}


void borrarPantalla() {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}


void ingresarString(char **string) {
    char temp[256];

    scanf("%[^\n]%*c", temp);

    (*string) = malloc(sizeof(char) * (strlen(temp) + 1));
    strcpy((*string), temp);
}


void imprimirContacto(Contacto contacto) {
    printf("\nNombre: %s - Direccion: %s - Telefono: %s", contacto.nombre, contacto.direccion, contacto.telefono);
    printf("\nMail: %s - Telegram: %s - Instagram: %s\n\n", contacto.mail, contacto.aliasTelegram, contacto.usuarioInstagram);
}

//FUNCIONES DEL TP

int menu() {
    int opcion;

    borrarPantalla();

    printf("Agenda personal - Juan Ingacio Bertoni - Martin Goni");
    printf("\n1- Ingresar nuevo contacto");
    printf("\n2- Mostrar todos los contactos");
    printf("\n3- Buscar un contacto por nombre");
    printf("\n4- Buscar un contacto por telefono");
    printf("\n5- Eliminar un contacto por nombre");
    printf("\n6- Eliminar todos los contactos");
    printf("\n7- Salir");

    printf("\n\nOpcion elegida: ");
    scanf("%d%*c", &opcion);

    return opcion;
}


void buscaContactosNombre(SList listaContactos) {
    SList nodo = listaContactos;
    char *nombreBuscar, aux[255];

    borrarPantalla();

    printf("Ingrese el nombre a buscar: ");
    ingresarString(&nombreBuscar);

    for(;nodo != NULL; nodo = nodo->sig) {
        strcpy(aux, nodo->contacto.nombre);
        aux[strlen(nombreBuscar)] = '\0';

        //Se transforma el nombre dado y el nombre de cada uno de los elementos a minuscula para que se pueda revisar la igualdad.
        for (int i = 0; i < strlen(nombreBuscar); i++) {
            aux[i] = tolower(aux[i]);
            //Alcanza con hacer esto una sola vez, pero para evitar poner otro for lo hago en el mismo for.
            nombreBuscar[i] = tolower(nombreBuscar[i]);
        }

        if (strcmp(nombreBuscar, aux) == 0)
            imprimirContacto(nodo->contacto);
    }

    printf("Presione enter para volver al menu");
    getchar();
}


void buscaContactosTelefono(SList listaContactos) {
    SList nodo = listaContactos;
    char *telefonoBuscar, aux[255];

    borrarPantalla();

    printf("Ingrese el nombre a telefono: ");
    ingresarString(&telefonoBuscar);

    for(;nodo != NULL; nodo = nodo->sig) {
        strcpy(aux, nodo->contacto.telefono);
        aux[strlen(telefonoBuscar)] = '\0';

        if (strcmp(telefonoBuscar, aux) == 0)
            imprimirContacto(nodo->contacto);
    }

    printf("Presione enter para volver al menu");
    getchar();
}


int main(int argc, char *argv[]) {
    SList listaContactos = slist_crear();
    Contacto structRoberto = {"Roberto", "Francia 354", "00025", "robertthemail@robert.com", "robertotelegram", "robertoig"};
    Contacto structMarcos = {"Marcos", "Alem 4720", "558756", "marcosmail@marcos.com", "marcosTelegram", "marcosig"};
    Contacto structGuadalupe = {"Guadalupe", "Echeverria 12", "5599773355", "guadalupemail@gudalupe.com", "guadalupeTelgram", "guadalupeig"};
    listaContactos = slist_agregar_inicio(listaContactos, structRoberto);
    listaContactos = slist_agregar_inicio(listaContactos, structMarcos);
    listaContactos = slist_agregar_inicio(listaContactos, structGuadalupe);

    int opcion;

    while ((opcion = menu()) != 7) {
        switch(opcion){
            case 1:
                break;
            case 2:
                break;
            case 3:
                buscaContactosNombre(listaContactos);
                break;
            case 4:
                buscaContactosTelefono(listaContactos);
                break;
            case 5:
                break;
            case 6:
                break;
        }
    }

    slist_destruir(listaContactos);

    return 0;
}