
#ifndef SETUP_H 
#define SETUP_H
typedef struct CallFuncChar1{
    int flag; 
    char* (*fptr)(char*);
    struct CallFuncChar1 *next; 
}CallFuncChar;

typedef struct library_load_params1{
        char* libName;
        char* newPath;
        //could be added - another char*
}lib_load_param;
/*
typedef struct rah1{
    int flag;
    int(*fptr)(lib_load_param); 
    struct rah1 *next;
}LibLoadFuncs;
*/
typedef char*(*LibLoad)(char*);
void setloadlist(LibLoad* funcs);
typedef int(*LibLoadFuncs)(lib_load_param);
void on_library_load(int(*fptr)(lib_load_param));
void set_block_list(char*, char* blockArray[], int arrLength);

#endif



