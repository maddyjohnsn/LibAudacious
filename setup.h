
#ifndef SETUP_H 
#define SETUP_H
typedef struct CallFuncChar1{
    int flag; 
    char* (*fptr)(char*);
    struct CallFuncChar1 *next; 
}CallFuncChar;


struct library_load_params{
        char* libName;
        char* newPath;
        //could be added - another char*
};

void on_library_load(int(*fptr)(struct library_load_params*));
void set_block_list(char*, char* blockArray[], int arrLength);

#endif



