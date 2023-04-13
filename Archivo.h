#pragma once
#include "Structures.h"

void Leer(List *Store,PlayList *MyPlaylist,char Direccion[]);
void AgregarCancion(List *Store,char Name[],char Path[],int pos);
void AgregarLista(PlayList *Lista,char Name[],char Description[]);
void EliminarCancion(List *Store,char Name[],int id);
void EliminarLista(PlayList *Lista,char Nombre[],int index);
void LimpiarCadena(char* cadena);