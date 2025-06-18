//#include "deleteBranchLD.c"
//#include "practiceAud.h"
#include "practiceAud.c" 

#include <stdio.h> 

int main(){
	
	struct libList* myPracStruct;
       myPracStruct = getLibList();
       printf("path is: %s\n", myPracStruct[0].path);
    return 0;
}
