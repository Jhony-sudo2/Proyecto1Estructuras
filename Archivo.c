#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Archivo.h"
#include "Structures.h"
#include <ctype.h>
#include "ListaSimple.h"
#include "PlayList.h"
void Leer(List *Store,PlayList *MyPlaylist,char Direccion[]){
    
    FILE *archivo;
    char linea[200];
    char tag[100];
    char nombre[20];
    char path[30];
    char description[50];
    int pos = 0;
    int id = 0;
    int Tipo;
    int Canciones = 0;
    Node_List *ListaActual;
    archivo = fopen(Direccion, "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
    }else{
        while (fgets(linea, 200, archivo)) {
            if (strstr(linea, "<Insertar>") != NULL)
            {
                Tipo = 1;
            }else if (strstr(linea, "<Eliminar>") != NULL)
            {
                Tipo = 2;
            }else if (strstr(linea, "<Nombre>") != NULL) {
                sscanf(linea, " <%*[^>]>%[^<]</%*[^>]>", nombre);
                sscanf(linea, "<Nombre>%[^<]</Nombre>", nombre);
            }else if (strstr(linea, "<Canciones>") != NULL) {
                Canciones = 1;
                ListaActual = AddPlayList(nombre,description,MyPlaylist);
                
            }
            else if (strstr(linea, "<path>") != NULL) {

                sscanf(linea, " <%*[^>] >%[^<] </%*[^>] >",path);
                sscanf(linea, "<path>%[^<]</path>", path);
            }
            else if (strstr(linea, "<pos>") != NULL) {

                sscanf(linea, " <%*[^>] >%d </%*[^>] >", &pos);
                sscanf(linea, "<pos>%d</pos>", &pos);
                if(Canciones == 1)AddSongArchivo(Store,pos,ListaActual);
            }else if (strstr(linea, "<id>") != NULL) {

                sscanf(linea, " <%*[^>] >%d </%*[^>] >", &id);
                sscanf(linea, "<id>%d</id>", &id);
                
            }else if (strstr(linea, "<Descripcion>") != NULL){

                sscanf(linea, " <%*[^>] >%[^<] </%*[^>] >", description);
                sscanf(linea, "<Descripcion>%[^<]</Descripcion>", description);
            }else if (strstr(linea, "</cancion>") != NULL) {
                if (Tipo ==1)
                {    
                    printf("AGREGANDO CANCION\n");
                    LimpiarCadena(path);
                    AgregarCancion(Store,nombre,path,pos);
                    
                }else{
                    EliminarCancion(Store,nombre,id);
                }
                
            }else if (strstr(linea, "</Lista>") != NULL)
            {

                if (Tipo == 1)
                {
                    if (Canciones == 0)
                    {
                        AddPlayList(nombre,description,MyPlaylist);
                    }
                    ListaActual = NULL;
                    Canciones = 0;
                }else{
                    EliminarLista(MyPlaylist,nombre,id);
                }
                Canciones = 0;
                
            }
            
            
            
            
        }
            fflush(archivo);    
        }
}


void AgregarCancion(List *Store,char Name[],char Path[],int pos){
    Name[strcspn(Name, "\n")] = '\0';
    if (pos == 0)
    {
        Add(Store,Name,Path);
    }else{
        AddPos(Store,Name,Path,pos);
    }
    
}

void EliminarCancion(List *Store,char Name[],int id){
    if (id == 0)
    {
        printf("ELIMINANDO CANCION POR NOMBRE:%s\n",Name);
        DeleteByName(Name,Store);
    }else{
        DeleteByIndex(id,Store);
    }
    
}

void EliminarLista(PlayList *Lista,char Nombre[],int index){
    if (index == 0)
    {
        printf("INICIANDO A ELIMINAR LA LISTA\n");
        DeletePlayListByName(Nombre,Lista);
        printf("TERMINANDO DE ELIMINAR LA LISTA\n");
    }else{
        DeletePlayList(index,Lista);    
    }
    
}

void LimpiarCadena(char* cadena) {
    int i = 0, j = 0;
    while (cadena[i]) {
        if (!isspace(cadena[i])) {
            cadena[j++] = cadena[i];
        }
        i++;
    }
    cadena[j] = '\0';
}

