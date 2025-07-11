//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <dlfcn.h>
#include <assert.h>
#include "../include/committee.h"
int passedTest = 0;

int tool_printf(char *format,...) {
    printf("Inside of tool_printf\n");
   fptr_t printfx =  (fptr_t)get_wrappee("printf");
//   fprintf(stderr,"%s %d\n", __func__, __LINE__);
   printfx("%s ^from og print\n",format);
    return 0;  
}

int tool_atoi(char* r){
    printf("in %s, just observing\n",__func__);
    typedef int (*og)(char*);
    og ogfunc = (og)get_wrappee("atoi");
    int k = ogfunc(r);
     return k;
}


char* tool_fgets(char *s, int size, FILE *stream){
    printf("in %s, just observing\n",__func__);
    typedef char* (*og)(char *s, int size, FILE *stream); 
    og ogfunc = (og)get_wrappee("fgets"); 
    char* ret = ogfunc(s,size,stream);
    return ret; 
}

int tool_fgetc(FILE *stream){
     printf("in %s, just observing\n",__func__);
    typedef int (*og)( FILE *stream);
    og ogfunc = (og)get_wrappee("fgetc");
    int ret = ogfunc(stream);
    return ret;
}

double tool_fabs(double k){
    printf("always negative\n");
    typedef double (*og)(double);
    og ogfunc = (og)get_wrappee("fabs");
    k = ogfunc(k);
    return -1 * k;
}


int tool_rand() {
    printf("In %s\n",__func__); 
    typedef int (*og)(); 

    og ogfunc = (og)get_wrappee("rand");
    printf("rand number from og %d\n",ogfunc());
    return 5;
   }

int switchlib(lib_load_param* params){
    if(strcmp(params->libName, "./libfake.so")==0){
    params->newPath = "./libsneaky.so"; }
   // printf("current name %s new name %s\n", params->libName, params->newPath);
    return 0;
}

//for this one to actually work it qould need to change to params->libName = NULL
int makelibnull(lib_load_param* params){
    params->newPath = NULL;
   // printf("current name %s new name %s\n", params->libName, params->newPath);
    return 0;
}

int  buildinit(){
#ifndef MY_MACRO
   int MY_MACRO = 0;
#endif

	if(MY_MACRO == 0){
		printf("Testing blocklist with preloaded library: \n");
		char *toBlockList[] = {"one", "./libfake.so", "three"};
		passedTest = set_block_list(toBlockList, 3);
		if(passedTest == 0){
                        printf("Test Passed\n");
                }
                else{
                        printf("Test Failed\n");
                }
	printf("\n");
	}

	if(MY_MACRO == 1){
		printf("Testing blocklist with too many libraries: \n");
		char *toBlockList[] = {"./libfake.so", "two", "three"};
		passedTest = set_block_list(toBlockList, 100);
		if(passedTest == 1){
			printf("Test Passed\n");
		}
		else{
			printf("Test Failed\n");
		}
	printf("\n");
	}
    if(MY_MACRO == 2){
        printf("Testing blocklist with one library: \n");
        char *toBlockList[] = {"./lib.so.6"};
        passedTest = set_block_list(toBlockList, 1);
		if(passedTest == 0){
			printf("Test Passed\n");
		}
		else{
            printf("Test Failed\n");
        }
    printf("\n");
    }


    if(MY_MACRO == 3){
	    printf("Testing with no preloaded libraries and with no functions being used");
printf("\n");
    }



    if(MY_MACRO == 4){

	printf("Testing onlibload: \n");
    	    setloadlist(&switchlib);
        setloadlist(&makelibnull);
    printf("\n");
    }

	if(MY_MACRO==5){
		printf("Testing wrap with one function: \n");
    		wrap("rand", (fptr_t)&tool_rand);
		printf("\n");
    }

	if(MY_MACRO==6){
		printf("Testing wrap with two functions: \n");
		wrap("rand", (fptr_t)&tool_rand);
    		wrap("printf",(fptr_t)&tool_printf);
		printf("\n");
	}

	if(MY_MACRO==7){
		 printf("Testing wrap with max functions: \n");
		wrap("rand", (fptr_t)&tool_rand);
    		wrap("atoi", (fptr_t)&tool_atoi);
    		wrap("fgets",(fptr_t)&tool_fgets);
    		wrap("fgetc", (fptr_t)&tool_fgetc);
    		printf("\n");
	}

	if(MY_MACRO==8){
		printf("Testing wrap with more than max functions: \n");
	wrap("printf",(fptr_t)&tool_printf);
    wrap("rand", (fptr_t)&tool_rand);
    wrap("atoi", (fptr_t)&tool_atoi);
    wrap("fgets",(fptr_t)&tool_fgets);
    wrap("fgetc", (fptr_t)&tool_fgetc);
    		 printf("\n");
	}

	if(MY_MACRO ==9){

		printf("Testing allow list: \n");
		char* tester[] = {"libdl.so.2", "/packages/mcscn/packages/curl_8.7.1/lib64/libdl.so.2", "/packages/mcscn/packages/openssl_3.2.1/lib64/libdl.so.2", "/packages/mcscn/packages/expat_2.6.2/lib64/libdl.so.2", "/packages/spack/opt/spack/linux-opensuse15-x86_64/gcc-7.5.0/gcc-12.2.0-jjn6m6jhvxv2bzzmeiyvzqg6q4zlsxih/lib64/libdl.so.2", "/packages/spack/opt/spack/linux-opensuse15-x86_64/gcc-7.5.0/gcc-12.2.0-jjn6m6jhvxv2bzzmeiyvzqg6q4zlsxih/lib/libdl.so.2", "", "/packages/mcscn/packages/ncurses6.5/lib/libdl.so.2", "/packages/mcscn/packages/ncurses6.5/lib/libdl.so.2", "libc.so.6", "/packages/mcscn/packages/curl_8.7.1/lib64/libc.so.6", "/packages/mcscn/packages/openssl_3.2.1/lib64/libc.so.6", "/packages/mcscn/packages/expat_2.6.2/lib64/libc.so.6", "/packages/spack/opt/spack/linux-opensuse15-x86_64/gcc-7.5.0/gcc-12.2.0-jjn6m6jhvxv2bzzmeiyvzqg6q4zlsxih/lib64/libc.so.6", "/packages/spack/opt/spack/linux-opensuse15-x86_64/gcc-7.5.0/gcc-12.2.0-jjn6m6jhvxv2bzzmeiyvzqg6q4zlsxih/lib/libc.so.6", "/packages/mcscn/packages/ncurses6.5/lib/libc.so.6", "/lib64/libc.so.6", "/lib64/tls/x86_64/x86_64/libdl.so.2",  "/lib64/tls/x86_64/libdl.so.2", "/lib64/tls/x86_64/libdl.so.2", "/lib64/tls/libdl.so.2", "/lib64/x86_64/x86_64/libdl.so.2", "/lib64/x86_64/libdl.so.2", "/lib64/x86_64/libdl.so.2", "/lib64/libdl.so.2", "/usr/lib64/tls/x86_64/x86_64/libdl.so.2", "/usr/lib64/tls/x86_64/libdl.so.2", "/usr/lib64/tls/x86_64/libdl.so.2", "/usr/lib64/tls/libdl.so.2", "/usr/lib64/x86_64/x86_64/libdl.so.2", "/usr/lib64/x86_64/libdl.so.2", "/usr/lib64/x86_64/libdl.so.2", "/usr/lib64/libdl.so.2"};
		set_allow_list(tester, 32);

	}

	return 0;


	

}


