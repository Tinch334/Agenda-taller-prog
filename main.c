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

//llamar string a una variable que es un puntero a una cadena no sé si es recomendable.
void ingresarString(char **string) {
    char temp[256];

    scanf("%[^\n]%*c", temp);

    (*string) = malloc(sizeof(char) * (strlen(temp) + 1));
    strcpy((*string), temp);
    //No hay un free de este string en el programa.
}


static void imprimirContacto(Contacto contacto) {
    printf("\n%-10s \t %-s \t %-7s \t %-25s \t %-15s \t %-10s \t \n","Nombre","Direccion","Telefono","Mail","Telegram","Instagram");    
    printf("%-10s \t %-s \t %-7s \t %-25s \t %-15s \t %-10s \t \n",contacto.nombre,contacto.direccion,contacto.telefono,contacto.mail,contacto.aliasTelegram,contacto.usuarioInstagram);
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

    printf("Esta seguro que quiere eliminar %s(1=Si, 0=No)? ", (opcion) ? "el contacto" : "toda la agenda");
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

    printf("Agenda personal - Ver:1.0");
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
    *agenda = slist_agregar_final(*agenda, contactoNuevo);
}


/*2*/
void muestraContacto(SList agenda)
{
    SList nodo = agenda;
    int index=0;

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
//La idea era que los buscar retornen una lista. No que impriman en pantalla.
void buscaContactosNombre(SList listaContactos) {
    SList nodo = listaContactos;
    char *nombreBuscar, aux[255];
    int encontro = 0;

    borrarPantalla();

    printf("Ingrese el nombre a buscar: ");
    ingresarString(&nombreBuscar);

    //Pasamos ambas strings(El nombre a buscar y el nombre) a minuscula para evitar problemas con capitalizacion.
    for (int i = 0; i < strlen(nombreBuscar); i++){
        nombreBuscar[i] = tolower(nombreBuscar[i]);
    }

    for(;nodo != NULL; nodo = nodo->sig) {
    	//Para no hacer esto todo el tiempo, no es mejor guardar todo en minúscula?
        //Para no modificar el nombre en la struct usamos un buffer auxiliar al pasar el nombre del contacto a minuscula.
        strcpy(aux, nodo->contacto.nombre);

        for (int i = 0; i < strlen(aux); i++){
            aux[i] = tolower(aux[i]);
        }

        if (strstr(aux, nombreBuscar) != NULL) {
            imprimirContacto(nodo->contacto);
            encontro = 1;
        }
    }

    if (encontro == 0)
        printf("\nNo se han encontrado contactos con ese nombre\n");

    printf("\nPresione enter para volver al menu");
    getchar();

    free(nombreBuscar);
}


/*4*/
//La idea era que los buscar retornen una lista. No que impriman en pantalla.
void buscaContactosTelefono(SList listaContactos) {
    SList nodo = listaContactos;
    char *telefonoBuscar, aux[255];
    int encontro = 0;

    borrarPantalla();

    printf("Ingrese el nombre a telefono: ");
    ingresarString(&telefonoBuscar);

    for(;nodo != NULL; nodo = nodo->sig) {
        if (strstr(nodo->contacto.telefono, telefonoBuscar) != NULL) {
            imprimirContacto(nodo->contacto);
            encontro = 1;
        }
    }

    if (encontro == 0)
        printf("\nNo se han encontrado contactos con ese telefono\n");

    printf("\nPresione enter para volver al menu");
    getchar();

    free(telefonoBuscar);
}


/*5*/
void eliminarContactoNombre(SList *agenda)
{
    int indice, encontro = 0;
    char* nombreDeContactoABorrar;
    SList nodo = *agenda;

    borrarPantalla();

    printf("Ingresar contacto a borrar: ");
    ingresarString(&nombreDeContactoABorrar);

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

    if(confirmacion(0) == 1) {
        slist_destruir(*agenda);
        //Como el programa se va a seguir usando luego de vaciar la lista, evitar que siga apuntando a la memoria liberada.
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

    //Añadimos a estas personas para que se puedan probar las funciones.
    Contacto structRoberto = {"Roberto", "Francia 354", "100025", "robertthemail@roberto.com", "robertotelegram", "robertoig"};
    Contacto structMarcos = {"Marcos", "Alem 4720", "558756", "marcosmail@marcos.com", "marcosTelegram", "marcosig"};
    Contacto structGuadalupe = {"Guadalupe", "Echeverria 12", "55997755", "guadalupemail@gudalupe.com", "guadalupeTelgram", "guadalupeig"};
    listaContactos = slist_agregar_final(listaContactos, structRoberto);
    listaContactos = slist_agregar_final(listaContactos, structMarcos);
    listaContactos = slist_agregar_final(listaContactos, structGuadalupe);

    while ((opcion = menu()) != 9) {
        switch(opcion){
            case 1:
                nuevoContacto(&listaContactos);
                break;
            case 2:
                muestraContacto(listaContactos);
                break;
            case 3:
                buscaContactosNombre(listaContactos);
                break;
            case 4:
                buscaContactosTelefono(listaContactos);
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

    return 0;
}
