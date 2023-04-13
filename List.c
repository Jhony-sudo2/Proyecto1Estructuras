#include <stdlib.h>
#include <stdio.h>
#include "ListaSimple.h"
#include <string.h>


void Add(List *Head,char Name[],char Path[]){
    int Index = 1;
    Node *tmp;
    tmp = malloc(sizeof(Node));
    CreateNode(Name,Path,tmp);
    if(Head->Raiz == NULL){
        tmp->Index = Index;
        Head->Raiz = tmp;
    }else{
        Node *p = Head->Raiz;
        Index++;
        while (p->Next != NULL)
        {
            p = p->Next;
            Index++;
        }
        tmp->Index = Index;
        p->Next = tmp;
        
    }
}
void AddPos(List *Lista,char Name[],char Path[],int Pos){
    
}
int Search(char Name[],List *Head){
    Node *P = Head->Raiz;
    int Continue = 0;
    while (P != NULL & Continue != 1)
    {
        if(strcmp(Name,P->Name) == 0){
            PrintNode(P);
            Continue = 1;
        }else{
            P = P->Next;
        }

    }
    return Continue;
    
}

void Print(List *Head){
    Node *P = Head->Raiz;
    if (P == NULL)
    {
        printf("No hay ninguna cancion en la sotre\n");
    }
    
    while (P != NULL)
    {
        PrintNode(P);
        P = P->Next;
    }
    
}

Node *SearchSong(List *Head,int index){
    Node *p = Head->Raiz;
    while (p!= NULL)
    {
        if (p->Index == index)
        {
            return p;
        }else {
            p = p->Next;
        }
        
    }
    
}

void PrintNode(Node *tmp){
    printf("ID:%i  Nombre:%s Path:%s\n",tmp->Index,tmp->Name,tmp->Path);  
}


void CreateNode(char Name[],char Path[],Node *tmp){
    char Direccion[] = "./Canciones/";
    tmp->Next = NULL;
    size_t size = strlen(Name);
    size_t size_path = strlen(Path);
    size_t size_Direccion = strlen(Direccion);
    int k = 0;
    for (int i = 0; i < size_Direccion; i++)
    {
        tmp->Path[i] = Direccion[i];
        k++;
    }

    for (int i = 0; i < size; i++)
    {
        tmp->Name[i] = Name[i];
    }
    if (Path[0] == '.')k = 0;
    for (int i = 0; i < size_path; i++)
    {
        tmp->Path[k] = Path[i];
        k++;
    }
    
    
}

void DeleteByIndex(int index,List *Head){
    if (Head->Raiz == NULL)
    {
        printf("NO HAY CANCIONES CREADAS\n");
    }else
        {
        if (Head->Raiz->Index == index)
        {
            Head->Raiz = Head->Raiz->Next;
            AdjustIndex(Head->Raiz);
        }else
        {
            Node *p = Head->Raiz;
            int Continue = 0;
            while (p!= NULL & Continue != 1 & p->Next != NULL)
            {
                Node *tmp = p->Next;
                if (tmp->Index == index)
                {    
                    p->Next = tmp->Next;
                    AdjustIndex(tmp->Next);
                    free(tmp);
                    Continue = 1;
                }else p = p->Next;  
            }   
        }  
    }
}

void DeleteByName(char Name[],List* Head){
    if (Head->Raiz == NULL)
    {
        printf("LA STORE ESTA VACIA\n");
    }else{
        
        if (Comparar(Name,Head->Raiz->Name) == 0)
        {   
            Head->Raiz = Head->Raiz->Next;
            AdjustIndex(Head->Raiz);
            Print(Head);

        }else{
            Node *P = Head->Raiz;
            int Continue = 0;
            while (P != NULL & Continue != 1 & P->Next != NULL)
            {
                Node *tmp = P->Next;
                if (Comparar(Name,tmp->Name) == 0)
                {    
                    P->Next = tmp->Next;
                    AdjustIndex(tmp->Next);
                    free(tmp);
                    Continue = 1;
                }else P = P->Next;
                
            }
        }
    }
}

void AdjustIndex(Node *tmp){
    Node *p = tmp;
    while (p!= NULL)
    {
        p->Index = p->Index -1;
        p = p->Next;
    }
}

int Comparar(char str1[], char str2[]) {
    int i = 0, j = 0;
    while (str1[i] != '\0' && str2[j] != '\0') {
        while (str1[i] == ' ') {
            i++;
        }
        while (str2[j] == ' ') {
            j++;
        }
        if (str1[i] != str2[j]) {
            return str1[i] - str2[j];
        }

        i++;
        j++;
    }
    if (str1[i] != '\0' && str1[i] != ' ') {
        return str1[i] - str2[j];
    }
    if (str2[j] != '\0' && str2[j] != ' ') {
        return str1[i] - str2[j];
    }

    return 0;
}