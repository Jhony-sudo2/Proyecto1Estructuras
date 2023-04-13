#pragma once
#include "Structures.h"
Node_List *AddPlayList(char Name[],char Description[],PlayList* Lista);
void AddPlayListWithSongs(PlayList* Lista,char Name[],char Description[],List* Songs);
Node_List *getPlayList(int index,PlayList *Lista);
void AddSong(int index,List *Store,Node_List *tmp);
void CreateList(char Name[],char Description[],Node_List *tmp);
void DeleteSong(int Index,PlayList *Lista);
void DeletePlayList(int Index,PlayList *Head);
void DeletePlayListByName(char Name[],PlayList *Head);
void PrintPlayList(PlayList* Lista);
void PrintList(Node_List* tmp);
void Update(int index,PlayList *Lista);
void AdjustIndexList(Node_List *tmp);
int Comparar(char str1[], char str2[]);
void AddSongArchivo(List *Store,int index,Node_List *PlayList);
