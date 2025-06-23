

default: 
	gcc -c -fPIC practice.c
	gcc -shared -o comit.so practice.o 
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so ./main

clean: 
	rm *.o *.so main build 

clean2:
	rm *.o *.core .*.swp .*.swo main build


recomp:
	gcc main.c -o main 

builda:
	gcc -c -fPIC buildfile.c
	gcc -shared -o built.so buildfile.o 

fake:
	gcc -c -fPIC fakelib.c
	gcc -shared -o libfake.so fakelib.o 

sneak:
	gcc -c -fPIC sneaky.c
	gcc -shared -o libsneaky.so sneaky.o 

redo:
	gcc -c -fPIC sneaky.c
	gcc -shared -o libsneaky.so sneaky.o 
	gcc -c -fPIC fakelib.c
	gcc -shared -o libfake.so fakelib.o
	gcc -c -fPIC practice.c
	gcc -shared -o comit.so practice.o
	gcc main.c -o main
	rm *.o
