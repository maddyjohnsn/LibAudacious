//tests if wrap can work with max amount wrap function 
#define _GNU_SOURCE
#include <stdio.h> 
#include <string.h>
#include <dlfcn.h>
#include <assert.h>
#include "../include/committee.h"
int passedTest = 0;
FILE* tool_fopen(const char *pathname, const char *mode){
   printf("in %s, just observing\n",__func__);
   // typedef FILE* (*og)(const char*, const char*);
    fptr_t  ogfunc = get_wrappee("fopen");
    printf("Have fptr\n"); 
     FILE* ret = ogfunc(pathname,mode);
    printf("Have file ptr\n");
    // char buffer[100];
   //fprintf(stderr, "line %d\n",__LINE__);
  // fgets(buffer, sizeof(buffer), ret);
    fprintf(stderr,"%p\n",ret);
    //fprintf(stderr,"line 1: %s%p", buffer,ret);
    
    return ret; 
}
int tool_fclose(FILE* stream){
    printf("in %s, just observing\n",__func__);
    typedef int (*og)(FILE*);
    og ogfunc = (og)get_wrappee("fclose");
    int k = ogfunc(stream);
   // fprintf(stderr,"%p\n",stream);
    printf("retval fclose: %d\n",k);
   return k;  
}


//lowkey might just leave these out? cause a bunch use them?? or should i not...

int tool_printf(char *format,...) {
    fprintf(stderr,"Inside of tool_printf\n");
   fptr_t printfx =  (fptr_t)get_wrappee("printf");
//   fprintf(stderr,"%s %d\n", __func__, __LINE__);
   printfx("%s ^from og print\n",format);
    return 0;  
}

	
int tool_atoi(char* r){
    printf("super fun atoi that i will amke negative\n");
    typedef int (*og)(char*);
    og ogfunc = (og)get_wrappee("atoi");
    int k = ogfunc(r);
    printf("number from std atoi %d", ogfunc(r)); 
     if(k > 0){
         return -1 * k;
     }
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

//	printf("Testing onlibload: \n");
  //  	    setloadlist(&switchlib);
    //    setloadlist(&makelibnull);
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
		printf("\n");
	}

	if(MY_MACRO ==10){
		printf("Testing allow regex: \n");
		char* tester[] = {"libdl", "lib"};
		set_allow_groups(tester, 2);
		printf("\n");
	}

	if(MY_MACRO ==11){
                printf("Testing allow regex with allow list: \n");
                char* tester[] = {"libdl"};
                set_allow_groups(tester, 1);
		char* tester2[] = { "libc.so.6", "/packages/mcscn/packages/curl_8.7.1/lib64/libc.so.6", "/packages/mcscn/packages/openssl_3.2.1/lib64/libc.so.6", "/packages/mcscn/packages/expat_2.6.2/lib64/libc.so.6", "/packages/spack/opt/spack/linux-opensuse15-x86_64/gcc-7.5.0/gcc-12.2.0-jjn6m6jhvxv2bzzmeiyvzqg6q4zlsxih/lib64/libc.so.6", "/packages/spack/opt/spack/linux-opensuse15-x86_64/gcc-7.5.0/gcc-12.2.0-jjn6m6jhvxv2bzzmeiyvzqg6q4zlsxih/lib/libc.so.6", "/packages/mcscn/packages/ncurses6.5/lib/libc.so.6", "/lib64/libc.so.6"};
		set_allow_list(tester2, 8);
                printf("\n");
        }

	if(MY_MACRO ==13){
                printf("Testing do not allow regex: \n");
                char* tester[] = { "lib"};
                set_block_reglist(tester, 1);
                printf("\n");
        }


	return 0;


	

}


int tool_kab(char a, char* b, char** c, int d, short e, long f, float g, double h){
    printf("in %s\n",__func__);
     printf("a=a:%c\nb=bb:%s\nc=c1:%s c2:%s\nd=1:%d\ne=2:%d\nf=3:%d\ng=4.44:%f\nh=5.55:%f\n",a,b,c[0],c[1],d,e,f,g,h);
     typedef int (*og)(char , char* , char** , int, short , long , float , double );
    og func = (og)get_wrappee("kylieannebogar");
    func(a,b,c,d,e,f,g,h);
    return 1;
}

/*
int  buildinit(){
    //Blocklist tests 
//    wrap("kylieannebogar",(fptr_t)&tool_kab);
   // wrap("fopen",(fptr_t)&tool_fopen); 
   // wrap("fclose",(fptr_t)&tool_fclose);
#ifdef BLOCKONE
    char *toBlockList[] = {"./libfake.so"};
    set_block_list(toBlockList, 1); 
#elif BLOCKTWO
    char *toBlockList[] = {"./libfake.so","one"};
    set_block_list(toBlockList, 2);
#elif BLOCKMAX
    printf("test not created. BLOCKMAX\n");
#elif BLOCKOVER
    printf("test not created. BLOCKOVER\n");
#endif

    //On library load tests this strcuture should be changed 
#ifdef LIBONE
    LibLoadFuncs funcs[10] = {0};
    funcs[0] = &switchlib;
    setloadlist(funcs); 
#elif LIBTWO
    LibLoadFuncs funcs[10] = {0};
    funcs[0] = &switchlib;
    funcs[1] = &makelibnull; 
    setloadlist(funcs);
#elif LIBMAX
     LibLoadFuncs funcs[10] = {0};
     for (int i = 0; i<10; i+=2){
    funcs[i] = &switchlib;
    funcs[i+1] = &makelibnull;
     }
    setloadlist(funcs);
#endif
    //WRAP TESTTTSSS
#ifdef WRAPONE
    wrap("rand", (fptr_t)&tool_rand);
    //if theres 2
#elif WRAPTWO
    wrap("printf",(fptr_t)&tool_printf);
    //    wrap("rand", (fptr_t)&tool_rand);
    //if there the max(four right now) 
#elif WRAPMAX
    wrap("atoi", (fptr_t)&tool_atoi);
    wrap("fgets",(fptr_t)&tool_fgets); 
    wrap("fgetc", (fptr_t)&tool_fgetc);
    wrap("rand", (fptr_t)&tool_rand);

    //if theres more than the max
#elif WRAPOVER
     wrap("rand", (fptr_t)&tool_rand);
     wrap("printf",(fptr_t)&tool_printf);   
     wrap("atoi", (fptr_t)&tool_atoi);
     wrap("fgets",(fptr_t)&tool_fgets); 
     wrap("fgetc", (fptr_t)&tool_fgetc);
#elif WRAPNULLPTR
     wrap("rand", (fptr_t)0);
#elif WRAPBADNAME
     wrap("badname",(fptr_t)&tool_rand); 
#endif //end of wrap tests
    return 0;
}
*/
