#pragma once
#include "Structures.h"
#include <stdbool.h>
void push(Node *Cancion,List *Pila);
void *pop(List *Pila);
bool Vacia(List *Pila);
int Lenght(List *Pila);
void AgregarCancionPila(List *Pila,List *Store);
void PintarPila(List *Pila);