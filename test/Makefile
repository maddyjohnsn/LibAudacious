
DBUG=-D BLOCKONE -D WRAPONE -D LIBONE
#every flag BLOCKONE BLOCKTWO BLOCKMAX BLOCKOVER WRAPONE WRAPTWO WRAPMAX WRAPOVER
# 
wflags: recomp
	gcc $(DBUG)  -shared -fPIC ../src/practice.c -o comit.so -ldl
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so ./main   

defr: recomp 
	gcc -c -fPIC ../src/practice.c -D NOTHING
	gcc -shared -o comit.so practice.o -ldl -D WRAPONE
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so ./main

recomp:
	gcc main.c -o main -ldl


test:
	
	for i in 1 2 3 4 5; do \
	gcc main.c -DMY_MACRO=1 -o main -ldl ; \
	gcc -c -DMY_MACRO=$$i -fPIC ../src/practice.c ; \
	gcc -shared -o comit.so practice.o -ldl ; \
	LD_AUDIT=./comit.so ./main ; \
	done;

loop:
	for i in 1 2 3 4; do \
        echo $$i; \
	done; 

ifdeftest: recomp
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so ./main


default: libfake.so ../src/comit.so libsneaky.so main
	 LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so ./main

../src/comit.so: ../src/practice.c
	gcc -c -fPIC ../src/practice.c
	gcc -shared -o comit.so practice.o -ldl

libfake.so: fakelib.c
	gcc -c -fPIC fakelib.c
	gcc -shared -o libfake.so fakelib.o

libsneaky.so: sneaky.c
	gcc -c -fPIC sneaky.c
	gcc -shared -o libsneaky.so sneaky.o

main: 
	gcc main.c -o main -ldl


mem: libfake.so libsneaky.so main
	gcc -c -ggdb -g -fPIC ../src/practice.c
	gcc -shared -g -o comit.so practice.o -ldl
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so valgrind --leak-check=full --show-leak-kinds=all  --track-origins=yes ./main

clean: 
	rm *.o  main 

superclean:
	rm vgcore.* *.o *.core main .*.swp .*.swo

reset: libsneaky.so libfake.so



