
#ifndef COMMITTEE_H
#define COMMITTEE_H


//fix this later lowk its fine the way it is ?????? 
typedef int (*fptr_t)(const char *format, ...); 


/* external */
//int wrap(char* wrappee_name, fptr_t wrapper);

typedef struct expir{
    char* wrappee; 
    fptr_t fptr; 
    struct expir* next; 
}WrappedFunctions; 
int wrap(char* wrappee_name, fptr_t wrapper);
/*
 ******************************************************************************
 *
 * \fn fptr_t get_wrappee(char*)
 *
 * \brief Given a COMMITTEE wrapper's handle, returns the wrapped function for it
 *to call
 *
 * \param handle The wrappee handle to return the function pointer for
 *
 ******************************************************************************
 */
fptr_t get_wrappee(char *wrappee_name);


/* Allows functions to be visible to all other parts of the library */
#define COMMITTEE_EXPORT __attribute__((__visibility__("default")))

/*Function that overrides a built-in function with a custom version*/

COMMITTEE_EXPORT char* committee_edit_func(char* func_name);

//a later implementation
/*Function with ability to monitor functions and library calls */

COMMITTEE_EXPORT char* committee_return_func();
/*struct setup to store list of library paths loaded in a program*/
typedef struct library_load_params1{
        char* libName;
        char* newPath;
        //could be added - another char*
}lib_load_param;


/* external sets the library*/ 
typedef int(*LibLoadFuncs)(lib_load_param*);
int setloadlist(LibLoadFuncs funcstoset);

/* external */
int set_block_list(char* blockArray[], int arrLength);
int returnBlockNum();

//on lib load, tell what lib was loaded
//on library load- call user function
int on_library_load(lib_load_param*);


#endif
