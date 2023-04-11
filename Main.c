#include <stdlib.h>
#include <stdio.h>
#include "Cancion.h"
#include "ListaSimple.h"
#include "string.h"
#include "PlayList.h"
#include "DoubleList.h"
#include "Archivo.h"
#include <ctype.h>
#include <pthread.h>
void Menu();
void OperacionesCanciones(int Selection);
void OperacionesPlaylist(int Selection);
void Reproduccion(int Selection);
int Validar();
int SeleccionarPlayList();
void Reproducir();
void *cambio(void *arg);
List Store;
PlayList MyPlayList;
DoubleList RNormal;
DoubleNode *Actual;
int main(){
    Menu();
    return 0;
}

void Menu(){
    int Selection;
    int Selection2;
    while (Selection != 5)
    {
        printf("-------REPRODUCTOR :V -------------\n");
        printf(" 1.Operaciones de Canciones\n 2.Playlist\n 3.Reproduccion\n 4.Carga Masiva \n 5.Salir\n");
        Selection = Validar();
        switch (Selection)
        {
            case 1:
                printf("1 Insertas\n2 Eliminar\n3 Buscar \n4.Listar Canciones\n");
                scanf("%i",&Selection2);
                OperacionesCanciones(Selection2);
            break;
            
            case 2:
                printf("1.Crear\n2.Eliminar\n3.Actualizar \n4.Listar \n5.Agregar Canciones\n6.Eliminar Canciones\n");
                scanf("%i",&Selection2);
                OperacionesPlaylist(Selection2);
            break;
            
            case 3:
                if (MyPlayList.Root == NULL)
                {
                    printf("NO HAY PLAYLIST CREADAS\n");
                }else{        
                    printf("1.Normal\n2.Repetri\n");
                    Selection2 = Validar();
                    Reproduccion(Selection2);
                }
            break;
            case 4:
                char path[] = "";
                printf("Ingrese la direccion del archivo\n");
                scanf("%s",path);
                Leer(&Store,&MyPlayList,path);
                break;
            case 5:
                printf("ADIOS\n");
                break;
            default:
                printf("Elija una Opcion Correcta\n");
                break;
            }

    }

}

void OperacionesCanciones(int Selection){
    switch (Selection)
    {
    case 1:
        getchar();
        char Name[20];
        char Path[30];
        printf("INGRESE EL NOMBRE DE LA CANCION: ");
        fgets(Name,20,stdin);
        printf("INGRESE LA DIRECCION DE LA CANCION: ");
        fgets(Path,30,stdin);
        Name[strcspn(Name, "\n")] = '\0';
        Path[strcspn(Path, "\n")] = '\0';
        Add(&Store,Name,Path);
        break;
    case 2:
        int Selection;
        printf("1.Eliminar por nombre\n2.Eliminar por Id\n");
        scanf("%i",&Selection);
        if (Selection == 1)
        {
            getchar();
            char Name[20];
            printf("Ingrese el nombre de la cancion a eliminar\n");
            fgets(Name,20,stdin);
            Name[strcspn(Name, "\n")] = '\0';
            DeleteByName(Name,&Store);
        }else if(Selection == 2)
        {
            getchar();
            int Id;
            printf("Ingrese el id de la cancion a eliminar\n");
            scanf("%i",&Id);
            DeleteByIndex(Id,&Store);
        }else{
            printf("OPCION INCORRECTA\n");
        }
        
        break;
    case 3:
        getchar();
        printf("Ingrese el nombre de la cancion\n");
        fgets(Name,20,stdin);
        Name[strcspn(Name, "\n")] = '\0';
        Search(Name,&Store);
        break;
    case 4:
        Print(&Store);
        break;
    
    default:
        break;
    }
}

void OperacionesPlaylist(int Selection){
     switch (Selection)
    {
    case 1:
        getchar();
        char Name[20];
        char Description[50];
        printf("Ingrese el nombre de la playlist\n");
        fgets(Name,20,stdin);
        printf("Ingrese una descripcion de su playlist\n");
        fgets(Description,50,stdin);
        Name[strcspn(Name, "\n")] = '\0';
        Description[strcspn(Description,"\n")] = '\0';
        printf("Ingresar canciones a la playlist\nY:SI\nN:NO\n");
        char S;
        S = getchar();
        if (S == 'y')
        {
            AddPlayListWithSongs(&MyPlayList,Name,Description,&Store);    
        }else if(S == 'n') AddPlayList(Name,Description,&MyPlayList);
        else printf("INGRESE UNA OPCION CORRECTA\n");
        
        break;
    case 2:
        printf("Ingrese el id de la playlist a Eliminar\n");
        scanf("%i",&Selection);
        DeletePlayList(Selection,&MyPlayList);
        break;
    case 3:
        int index;
        index = SeleccionarPlayList();
        Update(index,&MyPlayList);
        break;
    case 4:
        printf("1 Listar PlayLists\n2 Listar Canciones de una Playlist\n");
        int Selection = Validar();
        getchar();
        if(Selection == 1){
            PrintPlayList(&MyPlayList);
        }else if(Selection == 2){
            printf("Ingrese el id de la playlist para listar las canciones\n");
            scanf("%i",&Selection);
            Print(&getPlayList(Selection,&MyPlayList )->Songs);   
        }else{
            printf("Opcion Incorrecta\n");
        }
        break;
    case 5:
        index = SeleccionarPlayList();
        AddSong(index,&Store,getPlayList(index,&MyPlayList));
        break;
    case 6:
        index = SeleccionarPlayList();
        DeleteSong(index,&MyPlayList);
        break;
    
    default:
        break;
    }
}

void Reproduccion(int Selection){
    switch (Selection)
    {
    case 1:
        /* REPRODUCCION NORMAL LISTA DOBLEMENTE ENLAZADA */
        int index = SeleccionarPlayList();
        CreatList(getPlayList(index,&MyPlayList),&RNormal,0);
        Actual = RNormal.Root;
        Reproducir();
        RNormal.Root = NULL;
        Actual = NULL;
        break;
    case 2:
        /*REPETIR LISTA CIRCULAR */
        index = SeleccionarPlayList();
        CreatList(getPlayList(index,&MyPlayList),&RNormal,1);
        Actual = RNormal.Root;
        Reproducir();
        RNormal.Root = NULL;
        Actual = NULL;
        break;
    case 5:
        /*LISTA DE REPRODUCCION*/
    case 6:
        /*AGREGAR CANCION A LA LISTA DE REPRODUCCION USAR PILA -> FILO*/
        break;
    
    default:
        break;
    }
}

void Reproducir(){
    pthread_t hilo1;
    pthread_t hilo2;
    int id1 = 1;
    int id2 =2;
    PlayArgs args1 = {"",id1};
    strcpy(args1.path,Actual->Path);
    //hilo de reproduccion
    pthread_create(&hilo1,NULL,Play,(void *)&args1);
    int Selection;
    printf("1. SIGUIENTE\n");
    printf("2. ANTERIOR\n");
    printf("3. Salir de la reproduccion\n");
    scanf("%i",&Selection);
        if (Selection == 1)
        {
            Actual  = Actual->Next;
            pthread_cancel(hilo1);
            
            
        }else if(Selection == 2){
            Actual  = Actual->Prev;
            pthread_cancel(hilo1);

        }else{
            printf("SALIENDO DE LA REPRODUCCION\n");
            pthread_cancel(hilo1);
        }
        
    
    pthread_join(hilo1, NULL);
    if (Selection != 3)
    {
        Reproducir();
    }
    
    
}

void *cambio(void *arg){
    int Selection;
    printf("1. SIGUIENTE\n");
    printf("2. ANTERIOR\n");
    printf("3. Salir de la reproduccion\n");
    scanf("%i",&Selection);
    while (Selection  != 3)
    {
        
        Selection =Validar();
        if (Selection == 1)
        {
            Actual  = Actual->Next;
            Reproducir();
            
        }else if(Selection == 2){
            Actual  = Actual->Prev;
            Reproducir();

        }else{
            printf("SALIENDO DE LA REPRODUCCION\n");

        }
        
    }
    return NULL;
}

int SeleccionarPlayList(){
    int result = -1;
    if (MyPlayList.Root == NULL)
    {
        printf("No hay playlist creadas\n");
    }else
    {
        while (result == -1)
        {
            PrintPlayList(&MyPlayList);
            printf("Ingrese el id de la playlist que desea modificar\n");
            result  = Validar();
            if (result == -1)
            {
                printf("-----Ingrese una opcion correcta------\n");
            }
            
        }
    }
    
    
    return result;
    
}

int Validar(){
    char input[50];
    int is_number = -1;
    scanf("%s",input);
    for (int i = 0; input[i] != '\0'; i++) {
        if (!isdigit(input[i])) {
            is_number = 0;
            break;
        }
    }

    if (is_number) {
        int number = atoi(input);
        is_number = number;
    } 

    return is_number;
}

