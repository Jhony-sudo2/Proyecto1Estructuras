#pragma once

typedef struct Node
{
    char Name[20];
    char Path[30];
    struct Node *Next;
    int Index;
}Node;

typedef struct DoubleNode
{
    char Path[30];
    char Name[20];
    struct DoubleNode *Next;
    struct DoubleNode *Prev;
}DoubleNode;

typedef struct PlayArgs
{
    char path[30];
    int i;
}PlayArgs;


typedef struct List
{
    Node *Raiz;
}List;

typedef struct Node_List
{
    List Songs;
    struct Node_List *Next;
    int Index;
    char Description[50];
    char Name[20];
}Node_List;

typedef struct PlayList
{
    Node_List *Root;
}PlayList;




typedef struct DoubleList
{
    DoubleNode *Root;
}DoubleList;

typedef struct CircularDoublyLinkedList{

}CircularList;

