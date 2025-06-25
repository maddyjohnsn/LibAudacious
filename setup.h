
#ifndef SETUP_H 
#define SETUP_H

typedef struct library_load_params1{
        char* libName;
        char* newPath;
        //could be added - another char*
}lib_load_param;

//must change manually in two places if 10 changes
const size_t libloadsize = 10;
typedef char*(*LibLoad)(char*);
void setloadlisttest(LibLoad* funcstoset);
typedef int(*LibLoadFuncs)(lib_load_param*);
void setloadlist(LibLoadFuncs* funcstoset);
void on_library_load(int(*fptr)(lib_load_param));


void set_block_list(char* blockArray[], int arrLength);

#endif



