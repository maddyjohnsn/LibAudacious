#define _GNU_SOURCE
#include <stdlib.h>
#include <stdint.h>
#include <link.h>
#include <elf.h>
#include <stdio.h>
#include "../test/buildfile.c"
#include <string.h>
#include "../include/committee.h"

__attribute__((constructor))
 void init(void) { 
    buildinit();
   //fprintf(stderr,"%s %d %s\n", __FILE__, __LINE__, __func__);
}
__attribute__((destructor))void tini(void){}
//size vars ? <- do we want organize like that? or initialize right before theyre used?

//set up wrapped function structs
WrappedFunctions wrappedarray[4];
size_t funcsize = 4; 
//ret val -> 1 for too many, 2 for null name/ptr. otherwise 0.  
int wrap(char* wrappee_name, fptr_t  wrapper){
  //  fprintf(stderr,"top of wrap %s %d\n", __func__, __LINE__); //DEBUG
    if(!wrapper || !wrappee_name){
       fprintf(stderr,"func: %s: Func pointer(%p) or name(%s) is null.\n",__func__,wrapper,wrappee_name); 
       return 2;
    } 
    for(int i= 0; i<funcsize; i++){
        if (wrappedarray[i].wrappee == NULL){
            wrappedarray[i].wrappee = wrappee_name;
            wrappedarray[i].fptr = wrapper; 
            fprintf(stderr,"wrapped %s.\n",wrappedarray[i].wrappee);
            return 0; 
        }
    }

    fprintf(stderr, "func: %s: Max wrap reached. Cannot add %s\n", __func__,wrappee_name);
    return 1; 
}
//ret the fptr, if not found returns 0 
fptr_t get_wrappee(char *wrappee_name)
{
    //gets next occurance of wrappeename and its ptr 
    fptr_t ret = (fptr_t)dlsym(RTLD_NEXT, wrappee_name);
    if (!ret) {
        fprintf(stderr, "func: %s line: %d Error: %s\n",__func__,__LINE__, dlerror());
        return 0;
    }
    return  ret; 
}


//CREATING MULTIPLE FNCTIONS TO RUN DURING LIB LOAD 
int libloadsize = 10; 
LibLoadFuncs funcs[10]= {0};
int setloadlist(LibLoadFuncs functoset){
   // fprintf(stderr, "start of %s line: %d\n", __func__, __LINE__);  
    
    for(int i = 0; i < libloadsize; i++){
        if(funcs[i] == 0){
	    	funcs[i] = functoset;
            fprintf(stderr,"func: %s: Added to loadlist.\n",__func__);
            return 0; 
        }

    }
     fprintf(stderr, "func: %s: Exceeded max libload. Cannot add %p\n", __func__,functoset);
     return 1;
}


int on_library_load(lib_load_param *params){
    int i = 0;
   //fprintf(stderr, "%s\n",__func__); 
   //potench problem: funcs not sequential in func list  
    while(i < libloadsize && funcs[i] != 0){
        funcs[i](params);
        i++;
    }
}

//BLOCK LIST 
char DONOTLOADLIST[100][4096];
int DONOTLOADLENGTH = 0;
int set_block_list(char* blockArray[], int arrLength){
	if(arrLength < 1 ){
                printf("TOO FEW LIBRARIES\n");
                return 1;
        }
	if(arrLength >99 ){
		printf("TOO MANY LIBRARIES\n");
		return 1;
	}

	for (int i = 0; i<arrLength ; i++){
		strcpy(DONOTLOADLIST[i], blockArray[i]);
	}

		
	DONOTLOADLENGTH = arrLength;
	return 0;
}

int allowOn = 0;
char ALLOWLIST[100][4096];
int ALLOWLENGTH = 0;
int set_allow_list(char* allowArray[], int arrLength){
	for (int i = 0; i<arrLength ; i++){
                strcpy(ALLOWLIST[i], allowArray[i]);
        }
	ALLOWLENGTH = arrLength;
	allowOn = 1;
	return 0;

}

void on_library_load_real( lib_load_param *params){
    int i = 0;
   //potench problem: funcs not sequatial in func list  
    while(i < libloadsize && funcs[i] != 0){ 
	//printf("Debug Statement: user function number %d is loading\n", i);
    	funcs[i](params);
	    i++;
    }  
}

unsigned int la_version(unsigned int version) {
     return version;
}
char* la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag){
    lib_load_param libparams;
    libparams.libName = (char *) name;
    libparams.newPath = 0; 
	on_library_load(&libparams);

	for(int i = 0; i < DONOTLOADLENGTH; i++){
        	if(strcmp(name, (char*) DONOTLOADLIST[i])==0){
		     	return NULL;
        	}

	}
	//printf("%s\n", name);
	int inList = 0;
	if(allowOn != 0){
		for(int i = 0; i < ALLOWLENGTH; i++){
        	        if(strcmp(name, (char*) ALLOWLIST[i])==0){
                		inList =1;
			}

        	}
		//printf("%d", inList);
		if(inList !=1){
			return NULL;
		}

	}

   if(!libparams.newPath){ 
    return (char*)name; 
   }
   return libparams.newPath; 
}


unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie){
    //TODO figure out if we can selectively do this or if its fine as is  
    return LA_FLG_BINDTO | LA_FLG_BINDFROM; 
}


uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname) {

    for(int i = 0;wrappedarray[i].wrappee != NULL && i <funcsize; i++){
        if(strcmp(wrappedarray[i].wrappee, symname) == 0){
            fprintf(stderr,"DEBUG: wrappee: %s symname: %s\n",wrappedarray[i].wrappee,symname);
            return (uintptr_t)wrappedarray[i].fptr; 
        }
    }
    return sym->st_value; 

}




