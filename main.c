/*
    HECHO POR JUAN IGNACIO BERTONI Y MARTÍN GOÑI
    CURSO: 5TO INFO
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "slist.h"

//FUNCIONES AUXILIARES


void borrarPantalla() {
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}   

void ingresarString(char **punteroACadena) {
    char temp[256];

    scanf("%[^\n]%*c", temp);

    (*punteroACadena) = malloc(sizeof(char) * (strlen(temp) + 1));
    strcpy((*punteroACadena), temp);
    
    //free(punteroACadena); //no sabria donde liberar esto (la funcion no retorna nada, asi que no puedo liberar la referencia en el main)
}


static void imprimirContacto(Contacto contacto) {
    printf("\n%-10s \t %-5s \t %-7s \t %-27s \t %-15s \t %-10s \t \n","Nombre","Direccion","Telefono","Mail","Telegram","Instagram");    
    printf("%-10s \t %-5s \t %-7s \t %-27s \t %-15s \t %-10s \t \n",contacto.nombre,contacto.direccion,contacto.telefono,contacto.mail,contacto.aliasTelegram,contacto.usuarioInstagram);
}


void conseguirContacto(Contacto *contactoACrear)
{
    printf("Nombre: ");
    ingresarString(&(contactoACrear->nombre));
    printf("\nDireccion: ");
    ingresarString(&(contactoACrear->direccion));
    printf("\nTelefono: ");
    ingresarString(&(contactoACrear->telefono));
    printf("\nMail: ");
    ingresarString(&(contactoACrear->mail));
    printf("\nAlias telegram: ");
    ingresarString(&(contactoACrear->aliasTelegram));
    printf("\nInstagram: ");
    ingresarString(&(contactoACrear->usuarioInstagram));
}


int confirmacion(int opcion)
{
    int conf=0;

    printf("Esta seguro que quiere eliminar %s? (1=Si, 0=No)  ", opcion ? "el contacto" : "toda la agenda");
    scanf("%d%*c", &conf);
    printf("\n");

    while(conf > 1 || conf < 0){
        printf("\nIngrese una opcion valida: ");
        scanf("%d", &conf);
    } 

    return conf;
}


//FUNCIONES DEL TP

int menu() {
    int opcion;

    borrarPantalla();

    printf("Agenda personal - Ver:1.1");
    printf("\n1- Ingresar nuevo contacto");
    printf("\n2- Mostrar todos los contactos");
    printf("\n3- Buscar un contacto por nombre");
    printf("\n4- Buscar un contacto por telefono");
    printf("\n5- Eliminar un contacto por nombre");
    printf("\n6- Eliminar todos los contactos");
    printf("\n7- Cargar la agenda desde un archivo");
    printf("\n8- Guardar la agenda en un archivo");
    printf("\n9- Salir");

    printf("\n\nOpcion elegida: ");
    scanf("%d%*c", &opcion);

    return opcion;
}


/*1*/
void nuevoContacto(SList *agenda)    
{
    borrarPantalla();

    Contacto contactoNuevo;
    conseguirContacto(&contactoNuevo);
    *agenda = slist_agregar_final(*agenda,contactoNuevo);
}


/*2*/
void muestraContacto(SList agenda)
{
    borrarPantalla();

    if (agenda != NULL) {
        printf("A g e n d a\n");

        slist_recorrer(agenda, imprimirContacto);
    }
    else
        printf("La lista de contactos esta vacia, no hay contactos para mostrar\n\n");
    

    printf("\nPresione enter para volver al menu");
    getchar();
}


/*3*/
SList buscaContactosNombre(SList listaContactos) {
    SList nodo = listaContactos;
    char *nombreBuscar, aux[255];
    int encuentra = 0;
    SList contactoEncontrado = slist_crear();

    borrarPantalla();

    printf("Ingrese el nombre a buscar: ");
    ingresarString(&nombreBuscar);

    /*Pasaje de nombreBuscar y nombre a minuscula para evitar problemas con capitalizacion.*/
    for (int i = 0; i < strlen(nombreBuscar); i++)
        nombreBuscar[i] = tolower(nombreBuscar[i]);
    
    for(;nodo != NULL; nodo = nodo->sig) {
        /*Usamos un buffer auxiliar para no modificar el nombre de la struct original*/
        strcpy(aux, nodo->contacto.nombre);

        for (int i = 0; i < strlen(aux); i++)
            aux[i] = tolower(aux[i]);

        if (strstr(aux, nombreBuscar) != NULL) {
            Contacto nuevo = {nodo->contacto.nombre,nodo->contacto.direccion,nodo->contacto.telefono,nodo->contacto.mail,nodo->contacto.aliasTelegram,nodo->contacto.usuarioInstagram};
            contactoEncontrado = slist_agregar_final(contactoEncontrado,nuevo);
            encuentra=1;
        }
    
}
    if (!encuentra)
        printf("\nNo se han encontrado contactos con ese nombre\n");

    free(nombreBuscar);
    return contactoEncontrado;
}


/*4*/
SList buscaContactosTelefono(SList listaContactos) {
    SList nodo = listaContactos;
    char *telefonoBuscar; 
    int encuentra = 0;
    SList contactoEncontrado = slist_crear();

    borrarPantalla();

    printf("Ingrese telefono a buscar: ");
    ingresarString(&telefonoBuscar);

    for(;nodo != NULL; nodo = nodo->sig) {
        if (strstr(nodo->contacto.telefono, telefonoBuscar) != NULL) {
            Contacto nuevo = {nodo->contacto.nombre,nodo->contacto.direccion,nodo->contacto.telefono,nodo->contacto.mail,nodo->contacto.aliasTelegram,nodo->contacto.usuarioInstagram};
            contactoEncontrado = slist_agregar_final(contactoEncontrado,nuevo);
            encuentra=1;
        }
    }       
    if (!encuentra)
        printf("\nNo se han encontrado contactos con ese telefono\n");

    free(telefonoBuscar);
    return contactoEncontrado;
}


/*5*/
void eliminarContactoNombre(SList *agenda)
{
    int indice; 
    char* nombreDeContactoABorrar;

    borrarPantalla();

    printf("Ingresar contacto a borrar (nombre completo):  ");
    ingresarString(&nombreDeContactoABorrar);

    for(int i=0; i<strlen(nombreDeContactoABorrar);i++)
        nombreDeContactoABorrar[i] = tolower(nombreDeContactoABorrar[i]);

    indice = slist_indice(*agenda, nombreDeContactoABorrar);
    
    if (indice == (-1))
        printf("\nNo se ha encontrado el contacto especificado\n");
    else {
        printf("\n");

        if (confirmacion(1)) 
            slist_eliminar(&(*agenda), indice);
        else
            printf("Se ha cancelado la accion\n");
    }

    printf("\nPresione enter para volver al menu");
    getchar();

    free(nombreDeContactoABorrar);
}


/*6*/
void eliminarTodosContactos(SList *agenda)
{
    borrarPantalla();

    if(confirmacion(0)) {
        slist_destruir(*agenda);
        /*Como el programa se va a seguir usando luego de vaciar la lista, evitar que siga apuntando a la memoria liberada.*/
        *agenda = NULL;
    }
    else
        printf("Se ha cancelado la accion\n");

    printf("\nPresione enter para volver al menu");
    getchar();
}


/*7*/
void cargarAgenda(SList *agenda)
{
    //Antes de poder añadir elementos a la lista la vaciamos para cargar la agenda desde cero.
    slist_destruir(*agenda);
    *agenda = NULL;

    char* nombreArchivo;
    Contacto contactoLeido;

    borrarPantalla();

    printf("Ingrese el nombre del archivo del cual cargar la agenda: ");
    ingresarString(&nombreArchivo);

    //Usamos los buffers para solo alocar la memoria necesaria en la agenda.
    char bufNombre[255], bufTelefono[255], bufMail[255], bufDireccion[255], bufTelegram[255], bufInstagram[255];

    /*Abrimos el archivo con permisos de lectura para trabajar con el*/
    FILE* arch = fopen(nombreArchivo, "r");

    if (arch != NULL) {
        /*
        En el archivo, los contactos estan almacenados uno por linea, con todos los campos juntos separados por comas. Forma de un archivo:
        Roberto,100025,robertthemail@roberto.com,Francia 354,robertotelegram,robertoig
        Marcos,558756,marcosmail@marcos.com,Alem 4720,marcosTelegram,marcosig
        Guadalupe,55997755,guadalupemail@gudalupe.com,Echeverria 12,guadalupeTelgram,guadalupeig
        */
        while (fscanf(arch, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]%*c", bufNombre, bufTelefono, bufMail, bufDireccion, bufTelegram, bufInstagram) != EOF) {
            contactoLeido.nombre = strdup(bufNombre);
            contactoLeido.telefono = strdup(bufTelefono);
            contactoLeido.mail = strdup(bufMail);
            contactoLeido.direccion = strdup(bufDireccion);
            contactoLeido.aliasTelegram = strdup(bufTelegram);
            contactoLeido.usuarioInstagram = strdup(bufInstagram);

            *agenda = slist_agregar_final(*agenda, contactoLeido);
        }

        if (fclose(arch) == 0)
            printf("\nEl archivo se cargo con exito\n");
        else
            printf("\nOcurrio un problema con el archivo especificado, por favor intenta de nuevo\n");
    }
    else        
        printf("\nOcurrio un problema con el archivo especificado, por favor intenta de nuevo\n");

    printf("\nPresione enter para volver al menu");
    getchar();

    free(nombreArchivo);
}

/*8*/
void guardarAgenda(SList agenda)
{
    SList nodo = agenda;
    char* nombreArchivo;

    borrarPantalla();

    printf("Ingrese el nombre del archivo para guardar la agenda: ");
    ingresarString(&nombreArchivo);

    /*primero se abre el archivo con permisos de escritura
    para trabajar con el*/
    FILE* arch = fopen(nombreArchivo, "w");

    if (arch != NULL) {
        for(;nodo != NULL; nodo = nodo->sig)
            //Guardamos un contacto por linea con sus datos separados por espacios.
            fprintf(arch, "%s,%s,%s,%s,%s,%s\n", nodo->contacto.nombre, nodo->contacto.telefono, nodo->contacto.mail, nodo->contacto.direccion, nodo->contacto.aliasTelegram, nodo->contacto.usuarioInstagram);

        if (fclose(arch) == 0)
            printf("\nEl archivo se guardo con exito\n");
        else
            printf("\nOcurrio un problema al guardar el archivo especificado, por favor intenta de nuevo\n");
    }
    else        
        printf("\nOcurrio un problema con el archivo especificado, por favor intenta de nuevo\n");

    printf("\nPresione enter para volver al menu");
    getchar();

    free(nombreArchivo);
}


int main(int argc, char *argv[]) {
    SList listaContactos = slist_crear();
    int opcion;

    /*contactos de testeo*/
    Contacto contactoRoberto = {"Roberto", "Francia 354", "100025", "robertthemail@roberto.com", "robertotelegram", "robertoig"};
    Contacto contactoMarcos = {"Marcos", "Alem 4720", "558756", "marcosmail@marcos.com", "marcosTelegram", "marcosig"};
    Contacto contactoGuadalupe = {"Guadalupe", "Echeverria 12", "55997755", "guadalupemail@gudalupe.com", "guadalupeTelgram", "guadalupeig"};
    listaContactos = slist_agregar_final(listaContactos, contactoRoberto);
    listaContactos = slist_agregar_final(listaContactos, contactoMarcos);
    listaContactos = slist_agregar_final(listaContactos, contactoGuadalupe);
    SList contactosEncontradosTelefono = slist_crear();
    SList contactosEncontradosNombre = slist_crear();

    while ((opcion = menu()) != 9) {
        switch(opcion){
            case 1:
                nuevoContacto(&listaContactos);
                break;
            case 2:
                muestraContacto(listaContactos);
                break;
            case 3:
                contactosEncontradosNombre = buscaContactosNombre(listaContactos);
                if (contactosEncontradosNombre != NULL) {
                    printf("\nSe encontraron los siguientes contactos:\n");
                    slist_recorrer(contactosEncontradosNombre,imprimirContacto);
                }
                printf("\nPresione enter para volver al menu");
                getchar();
                break;
            case 4:
                contactosEncontradosTelefono = buscaContactosTelefono(listaContactos);
                if (contactosEncontradosTelefono != NULL) {
                    printf("\nSe encontraron los siguientes contactos:\n");
                    slist_recorrer(contactosEncontradosTelefono,imprimirContacto);
                }
                printf("\nPresione enter para volver al menu");
                getchar();
                break;
            case 5:
                eliminarContactoNombre(&listaContactos);
                break;
            case 6:
                eliminarTodosContactos(&listaContactos);
                break;
            case 7:
            cargarAgenda(&listaContactos);
                break;
            case 8:
                guardarAgenda(listaContactos);
                break;
        }
    }

    slist_destruir(listaContactos);
    free(contactosEncontradosTelefono);
    free(contactosEncontradosNombre);

    printf("Saliendo de la agenda...");
    return 0;
}
