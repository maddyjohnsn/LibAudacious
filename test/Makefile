

default: 
	gcc -c -fPIC ../src/practice.c
	gcc -shared -o comit.so practice.o 
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so ./main

mem:
	gcc -c -ggdb -g -fPIC ../src/practice.c
	gcc -shared -g -o comit.so practice.o
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so valgrind --track-origins=yes ./main

clean: 
	rm *.o *.so  main 

superclean:
	rm vgcore.* *.o *.so *.core main .*.swp .*.swo

no:
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so valgrind --track-origins=yes ./main

clean2:
	rm *.o *.core .*.swp .*.swo main build


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
	gcc -c -fPIC ../src/practice.c
	gcc -shared -o comit.so practice.o
	gcc main.c -o main
	rm *.o
