
#ifndef SETUP_H 
#define SETUP_H
typedef struct CallFuncChar1{
    int flag; 
    char* (*fptr)(char*);
    struct CallFuncChar1 *next; 
}CallFuncChar;

//somehow define flags here :q
//


#endif



