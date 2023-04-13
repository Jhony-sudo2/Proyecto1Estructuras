#include <stdio.h>
#include <stdlib.h>
#include "PlayList.h"
#include "ListaSimple.h"
#include <string.h>

Node_List *AddPlayList(char Name[],char Description[],PlayList* Lista){
    int Index = 1;
    Node_List* tmp;
    tmp = malloc(sizeof(Node_List));
    CreateList(Name,Description,tmp);
    if(Lista->Root == NULL){
        tmp->Index = Index;
        Lista->Root = tmp;
    }else{
        Index++;
        Node_List* p = Lista->Root;
        while (p->Next != NULL)
        {
            p = p->Next;
            Index++;
        }
        tmp->Index = Index;
        p->Next = tmp;
    }
    return tmp;
}

void AddPlayListWithSongs(PlayList* Lista,char Name[],char Description[],List* Store){
    int index_song;
    Node_List *tmp = AddPlayList(Name,Description,Lista);
    printf("CANCIONES DISPONIBLES\n");
    printf("PULSE 0 PARA SALIR\n");
    Print(Store);
    while (index_song != 0)
    {
        printf("Ingrese el Id de la cancion que deseee agregar a la playlist\n");
        scanf("%i",&index_song);
        Node *Stmp = SearchSong(Store,index_song);
        if (Stmp != NULL)
        {   
            Add(&tmp->Songs,Stmp->Name,Stmp->Path);
            
        }else if(index_song != 0){
            printf("LA POSICION NO EXISTE\n");
        }else{
            printf("POSICION NO VALIDA\n");
        }
        
    }
}

void AddSongArchivo(List *Store,int index,Node_List *PlayList){
    
    Node *tmp = SearchSong(Store,index);
    if (tmp != NULL)
    {
        Add(&PlayList->Songs,tmp->Name,tmp->Path);
    }else{
        printf("No existe cancion en la posicion:%i\n",index);
    }
    
}

void AddSong(int index,List *Store,Node_List *tmp){
    if (tmp == NULL)
    {
    }else{
    
    int index_song;
    printf("CANCIONES DISPONIBLES\n");
    printf("PULSE 0 PARA SALIR\n");
    Print(Store);
    while (index_song != 0)
    {
        printf("Ingrese el Id de la cancion que deseee agregar a la playlist\n");
        scanf("%i",&index_song);
        Node *Stmp = SearchSong(Store,index_song);
        if (Stmp != NULL)
        {   
            printf("PATH:%s\n",Stmp->Path);       
            Add(&tmp->Songs,Stmp->Name,Stmp->Path);

        }else{
            printf("LA POSICION NO EXISTE\n");
        }
        
    }
    }
}

Node_List *getPlayList(int index,PlayList *Lista){
    Node_List *p = Lista->Root;
    while (p!=NULL)
    {
        if (p->Index == index)
        {
            return p;
        }else{
            p = p->Next;
        }
    }
    return NULL;
}


void PrintPlayList(PlayList* Lista){
    Node_List* p = Lista->Root;
    if (p == NULL)
    {
        printf("No has creado ninguna playlist\n");
    }
    
    while (p!= NULL)
    {
        PrintList(p);
        p = p->Next;
    }
    
}

void PrintList(Node_List* tmp){
    printf("ID:%i NOMBRE:%s Descripcion:%s\n",tmp->Index,tmp->Name,tmp->Description);
}
void DeletePlayList(int index,PlayList *Head){
    if (Head->Root == NULL)
    {
        printf("NO HAY PLAYLIST CREADAS\n");
    }else{
        
        if (Head->Root->Index == index)
        {
            Head->Root = Head->Root->Next;
            AdjustIndexList(Head->Root);
        }else
        {
            Node_List *p = Head->Root;
            int Continue = 0;
            while (p!= NULL & Continue != 1 & p->Next != NULL)
            {
                Node_List *tmp = p->Next;
                if (tmp->Index == index)
                {    
                    p->Next = tmp->Next;
                    AdjustIndexList(tmp->Next);
                    free(tmp);
                    Continue = 1;
                }else p = p->Next;  
            }
        }
    }

}

void DeletePlayListByName(char Name[],PlayList *Head){
    Node_List *p = Head->Root;
    int Continuar = 0;
    while (p != NULL & Continuar == 0)
    {
        printf("NOMBRE ACTUAL:%s\n",p->Name);
        printf("BUSCANDO:%s\n",Name);
        if (Comparar(Name,p->Name) == 0)
        {
            printf("ENCONTRE LA LISTA\n");
            DeletePlayList(p->Index,Head);
            Continuar = 1;
        }else
        {
            p = p->Next;
        }
        
        
    }
    
    
}

void DeleteSong(int Index,PlayList *Lista){
    int index_song;
    Node_List *p = getPlayList(Index,Lista);
    printf("Cancion que contiene la playlist\n");
    Print(&p->Songs);
    printf("Ingrese el id de la cancion que desea eliminar\n");
    scanf("%i",&index_song);
    DeleteByIndex(index_song,&p->Songs);
}

void Update(int index,PlayList *Lista){
    getchar();
    char Nombre[20];
    char Description[50];
    Node_List *p = getPlayList(index,Lista);
    printf("Ingrese el nuevo nombre de la playlist\n");
    fgets(Nombre,20,stdin);
    printf("Ingrese la nueva descripcion de la playlist\n");
    fgets(Description,50,stdin);
    Nombre[strcspn(Nombre, "\n")] = '\0';
    Description[strcspn(Description,"\n")] = '\0';
    CreateList(Nombre,Description,p);
}

void CreateList(char Name[],char Description[],Node_List* tmp){
    //tmp->Next = NULL;
    size_t size = strlen(Name);
    size_t size_path = strlen(Description);
    for (int i = 0; i < size; i++)
    {
        tmp->Name[i] = Name[i];
    }

    for (int i = 0; i < size_path; i++)
    {
        tmp->Description[i] = Description[i];
    }
}
void AdjustIndexList(Node_List *tmp){
    Node_List *p = tmp;
    while (p!= NULL)
    {
        p->Index = p->Index -1;
        p = p->Next;
    }
}