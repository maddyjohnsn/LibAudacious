

default: 
	gcc -c -fPIC practice.c
	gcc -shared -o comit.so practice.o 
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so ./main

clean: 
	rm *.o *.so *.core  main build .*.swp .*.swo 

recomp:
	gcc main.c -o main 

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
