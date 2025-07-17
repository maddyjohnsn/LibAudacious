#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv){
    printf("Start of main%c\n", '!');
    
    FILE *fptr = fopen("../test/random.txt","r");
    if (fptr == NULL){
        fprintf(stderr, "null file pointer\n");
        return 0;
    }
    printf("File pointer = %p\n",fptr); 
#ifdef USEGETC
    int k = fgetc(fptr);
    printf( "The char:%c.\n",k);
#endif
    fclose(fptr); 
    fprintf(stdout, "End of Main\n");
}
