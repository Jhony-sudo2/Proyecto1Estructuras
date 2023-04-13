#include <stdio.h>
#include <stdlib.h>
#include "Pila.h"
#include "ListaSimple.h"
void push(Node *Cancion,List *Pila){
    Node *New = malloc(sizeof(Node));
    CreateNode(Cancion->Name,Cancion->Path,New);
    New->Next = Pila->Raiz;
    Pila->Raiz = New;
}

void *pop(List *Pila){
    if(Pila->Raiz != NULL){
        Node *tmp = Pila->Raiz;
        Pila->Raiz = Pila->Raiz->Next;
        free(tmp);
    }
}

bool Vacia(List *Pila){
    return Pila->Raiz == NULL;
}

Node *top(List *Pila){
    if (Pila->Raiz == NULL) return NULL;
    else return Pila->Raiz;
    
}

int Lenght(List *Pila){
    int size = 0;
    if (Pila->Raiz == NULL) return size;
    
    Node *tmp = Pila->Raiz;
    while (tmp != NULL)
    {
        size ++;
        tmp = tmp->Next;
    }
    return size;
    
}

void AgregarCancionPila(List *Pila,List *Store){
    int id_song;
    printf("CANCIONES DISPONIBLES\n");
    Print(Store);
    printf("Selecciones el id de la cancion que desee agregar\n");
    scanf("%i",&id_song);
    Node *tmp = SearchSong(Store,id_song);
    if (tmp == NULL)
    {
        printf("LA POSICION ES INCORRECTA\n");
    }
    else
    {
        push(tmp,Pila);
    }
}

void PintarPila(List *Pila){
    if (Vacia(Pila))
    {
        printf("No se han agregado canciones adicionales\n");
    }else
    {
        Node *p = Pila->Raiz;
        while (p != NULL)
        {
            printf("Nombre Cancion:%s\n",p->Name);
            p = p->Next;
        }
        
    }
}