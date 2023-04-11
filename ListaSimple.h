#pragma once
#include "Structures.h"
void Add(List *Lista,char Name[],char Path[]);
void AddPos(List *Lista,char Name[],char Path[],int Pos);
int Search(char Name[],List *Lista);
void PrintNode(Node *tmp);
void Print(List *Lista);
void DeleteByName(char Name[],List *Lista);
void DeleteByIndex(int index,List *tmp);
void CreateNode(char Name[],char Path[],Node *tmp);
void AdjustIndex(Node *tmp);
Node *SearchSong(List *Head,int index);
int Comparar(char str1[], char str2[]);
