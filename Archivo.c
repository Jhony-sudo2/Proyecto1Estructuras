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
                sscanf(linea, " <%*[^>] >%[^<] </%*[^>] >", nombre);
                sscanf(linea, "<Nombre> %[^<] </Nombre>", nombre);
            }else if (strstr(linea, "<canciones>") != NULL) {
                Canciones = 1;
            }
            else if (strstr(linea, "<path>") != NULL) {

                sscanf(linea, " <%*[^>] >%[^<] </%*[^>] >",path);
                sscanf(linea, "<path>%[^<]</path>", path);
            }
            else if (strstr(linea, "<pos>") != NULL) {

                sscanf(linea, " <%*[^>] >%d </%*[^>] >", &pos);
                sscanf(linea, "<pos>%d</pos>", &pos);
                
            }else if (strstr(linea, "<id>") != NULL) {

                sscanf(linea, " <%*[^>] >%d </%*[^>] >", &id);
                sscanf(linea, "<id>%d</id>", &id);
                
            }else if (strstr(linea, "<Descripcion>") != NULL){

                sscanf(linea, " <%*[^>] >%[^<] </%*[^>] >", description);
                sscanf(linea, "<Descripcion>%[^<]</Descripcion>", description);
            }else if (strstr(linea, "</cancion>") != NULL) {
                if (Tipo ==1)
                {    
                    AgregarCancion(Store,nombre,path,pos);
                    
                }else{
                    printf("ELIMINANDO cancion:\n");
                    printf("NOMBRE:%s\n",nombre);
                    EliminarCancion(Store,nombre,id);
                }
                
            }else if (strstr(linea, "</Lista>") != NULL)
            {
                if (Tipo == 1)
                {
                    AddPlayList(nombre,description,MyPlaylist);
                }else{
                    printf("ELIMINANDO LISTA\n");
                    EliminarLista(MyPlaylist,nombre,id);
                }
                
            }else if (strstr(linea,"</canciones>"))
            {
                Canciones = 0;
                if (Tipo == 1)
                {
                    printf("CREANDO PLAYLIS CON CANCIONES\n");
                }else{
                    printf("ELIMINANDO CANCIONES DE PLAYLIST\n");
                }
                
            }
            
            
            
            
        }

        fclose(archivo);
        printf("TERMINANDO DE LEER EL ARCHIVO\n");
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

void AgregarLista(PlayList *Lista,char Name[],char Description[]){

}

void EliminarCancion(List *Store,char Name[],int id){
    Name[strcspn(Name, "\n")] = '\0';
    if (id == 0)
    {
        DeleteByName(Name,Store);
    }else{
        DeleteByIndex(id,Store);
    }
    
}

void EliminarLista(PlayList *Lista,char Nombre[],int index){
    if (index == 0)
    {
        printf("ELIMINANDO LISTA POR NOMBRE\n");
        printf("ELIMINANDO LA LISTA:%s\n",Nombre);
        DeletePlayListByName(Nombre,Lista);
    }else{
        printf("ELIMINANDO LISTA POR ID\n");
        DeletePlayList(index,Lista);    
    }
    
}

