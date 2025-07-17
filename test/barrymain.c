


#include <stdio.h>

int main(){

    FILE *fp = fopen("foo.txt", "r");
    printf(":blah daisfyowuaesfug;o\n");
    int k = fgetc(fp);
    
    fprintf(stderr, "line 2:%c.\n",k);
    fclose(fp) ;
    return 0; 
} 
