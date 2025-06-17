

default: 
	gcc -c -fPIC practice.c
	gcc -shared -o comit.so practice.o 
	LD_PRELOAD=./libprelo.so LD_AUDIT=./built.so:./comit.so ./main

clean: 
	rm *.o *.so main build .*.swp .*.swo 
recomp:
	gcc buildfile.c -o build 

builda:
	gcc -c -fPIC buildfile.c
	gcc -shared -o built.so buildfile.o 


