#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "DoubleList.h"

void AddD(Node *tmp,DoubleList *Lista,int Type){
    DoubleNode *New = malloc(sizeof(DoubleNode));
    Create(tmp->Path,New,tmp->Name);
    if (Lista->Root == NULL)
    {
        Lista->Root = New;
    }else
    {
        DoubleNode *p = Lista->Root;
        while (p->Next!=NULL)
        {
            p = p->Next;
        }
        p->Next = New;
        New->Prev = p;
        if (Type == 1)
        {
            New->Next = Lista->Root;
            Lista->Root->Prev = New;
        } 
    }
}


void CreatList(Node_List *PlayL,DoubleList *Lista,int Type){
    Node *p = PlayL->Songs.Raiz;
    while (p!=NULL)
    {
        AddD(p,Lista,Type);
        p = p->Next;
    }
    
}


void Create(char Path[],DoubleNode *tmp,char Name[]){
    size_t size_path = strlen(Path);
    size_t size_name = strlen(Name);
    for (int i = 0; i < size_path; i++)
    {
        tmp->Path[i] = Path[i];
    }
    for (int i = 0; i < size_path; i++)
    {
        tmp->Name[i] = Name[i];
    }
    
}

void PrintSiguiente(DoubleNode *tmp){
    DoubleNode *p = tmp->Next;
    while (p != NULL)
    {
        printf("Nombre:%s\n",p->Name);
        p = p->Next;
    }
    
}

