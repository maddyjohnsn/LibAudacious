//#include "deleteBranchLD.c"
//#include "practiceAud.h"
#include "practiceAud.c" 

#include <stdio.h> 

int main(){
	
	printf("yay!\n");
	struct libList myPracStruct;
       myPracStruct = getLibList();
       printf("%s\n", myPracStruct.path);
    return 0;
}
