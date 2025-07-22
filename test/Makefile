CFLAGS= -Wall -Wextra -Og -g
DBUG=-D BLOCKONE -D WRAPONE -D LIBONE
#every flag BLOCKONE BLOCKTWO BLOCKMAX BLOCKOVER WRAPONE WRAPTWO WRAPMAX WRAPOVER

teststard:
	 gcc main.c -o main -ldl ./libtest.so
	#gcc main.c -o main -ldl -libtest.so
	gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D TOOLFOPEN -D TOOLFCLOSE
	LD_AUDIT=./comit.so ./main
die:
	./ftest.sh


hatred:
	gcc -Og fmain.c -o fmain -ldl
	gcc -Og -shared -fPIC ../src/practice.c -o comit.so -ldl
	LD_AUDIT=./comit.so ./fmain

wflags: recomp
	gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -lm -g
	LD_PRELOAD=./libfake.so:libtest.so LD_AUDIT=./comit.so ./main 14   

defr: recomp 
	gcc -c -fPIC ../src/practice.c -D NOTHING
	gcc -shared -o comit.so practice.o -ldl -D WRAPONE
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so ./main

recomp:
	gcc main.c -o main -ldl -lm -g

barry: 
	gcc -g -Og -c barrymain.c
	gcc -g -Og  -o hw barrymain.o -lm
	gcc -g -Og  -o rtld.so barryaudit.c -shared -fpic -lm
	LD_AUDIT=./rtld.so ./hw 

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

libtest.so: testlib.c
	gcc -shared -fPIC testlib.c -o libtest.so
main: 
	gcc main.c -o main -ldl


mem: libfake.so libsneaky.so recomp
	gcc -c -ggdb -g -fPIC ../src/practice.c
	gcc -shared -g -o comit.so practice.o -ldl -lm
	LD_PRELOAD=./libfake.so LD_AUDIT=./comit.so valgrind --leak-check=full --show-leak-kinds=all  --track-origins=yes ./main

clean: 
	rm *.o  main 

superclean:
	rm vgcore.* *.o *.core main .*.swp .*.swo

reset: libsneaky.so libfake.so libtest.so

fmem:
	 gcc fmain.c -o fmain -ldl
	 gcc -shared -fPIC ../src/practice.c -o comit.so -ldl -D TOOLFOPEN -D TOOLFCLOSE
	 LD_AUDIT=./comit.so valgrind --leak-check=full --show-leak-kinds=all  --track-origins=yes ./fmain

