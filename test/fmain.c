#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "buildfile.c"
#include "../include/committee.h"

/*
extern fclose_t getfclosewrapee(char* wrappee_name);
extern fileopen_t getfopenwrapee(char* wrappee_name);
extern fptr_t get_wrappee(char *wrappee_name);
*/
int main(int argc, char** argv){
    printf("Start of main%c\n", '!');
  //  buildinit();
    
    //FILE* fptr = fopen("../test/random.txt","r");
    FILE* fptr = fopen("newfile.txt", "w");

    fprintf(stderr,"file pointer in %s = %p\n",__func__,fptr);
    if (fptr == NULL){
        fprintf(stderr, "null file pointer\n");
        return 0;
    }
    fprintf(fptr, "hihihihihihihihi\n");
    fputs("merrymerry\n", fptr); 
#ifdef USEGETC
    int k = fgetc(fptr);
    printf( "The char:%c.\n",k);
#endif
    fclose(fptr); 
    fprintf(stdout, "End of Main\n");
}
