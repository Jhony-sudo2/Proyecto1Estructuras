#make file para compilar el programa 
programa: Main.o List.o Cancion.o PlayList.o DoubleList.o Archivo.o
	gcc -o programa Main.o  DoubleList.o List.o PlayList.o Archivo.o Cancion.o -lao -lmpg123 -lm 

Main.o: Main.c ListaSimple.h Cancion.h PlayList.h DoubleList.h
	gcc -c Main.c 

List.o: List.c ListaSimple.h
	gcc -c List.c

Cancion.o: Cancion.c Cancion.h
	gcc -c Cancion.c 

PlayList.o: PlayList.c PlayList.h
	gcc -c PlayList.c

DoubleList.o: DoubleList.c DoubleList.h
	gcc -c DoubleList.c
Archivo.o: Archivo.c Archivo.h
	gcc -c Archivo.c 

clean:
	rm -f programa *.o