
#ifndef COMMITTEE_H
#define COMMITTEE_H


/*!
 ******************************************************************************
 * \def COMMITTEE_MAKE_FUNCTION_PTR(name, ret_type, ...)
 * \brief Makes a function pointer with a given name, return type, and
 *        parameters
 * \param name     The name of the function you want to get a pointer to
 * \param ret_type The return type of the function you want a pointer to
 * \param ...      A comma separated list of the types of the parameters
 * 		   to the function you're getting a pointer to
 ******************************************************************************
 */

#define COMMITTEE_MAKE_FUNCTION_PTR(name, ret_type, ...) \
  ret_type (*name)(__VA_ARGS__)


/* Allows functions to be visible to all other parts of the library */
#define COMMITTEE_EXPORT __attribute__((__visibility__("default")))

/*!
 ******************************************************************************
 *
 * \fn char* COMMITTEE_EDIT_LIB(char* path);
 *
 * \brief allows COMMITTEE to edit a library path 
 *
 * \param path  original file path name 
 *
 ******************************************************************************
 */


COMMITTEE_EXPORT char* committee_edit_lib(char* path);

/*!
 ******************************************************************************
 *
 * \fn enum void* committee_get_wrappee(committee_wrappee_handle_t)
 *
 * \brief Given a COMMITTEE wrapper's handle, returns the wrapped function for it
 *to call
 *
 * \param handle The wrappee handle to return the function pointer for
 *
 ******************************************************************************
 */
//COMMITTEE_EXPORT void *committee_get_wrappee(committee_wrappee_handle_t handle);

/*Function that overrides a built-in function with a custom version*/

COMMITTEE_EXPORT char* committee_edit_func(char* func_name);

/*Function that can bring back original version of overridden function*/

COMMITTEE_EXPORT char* committee_return_func(char* func_name);

//a later implementation
/*Function with ability to monitor functions and library calls */

COMMITTEE_EXPORT char* committee_return_func();

/*!
 ******************************************************************************
 *
 * \fn enum void* callback_one_param(int (*userFunc) (char*), char * path)
 *
 * \brief Given a user's function that takes in one param and returns an int,
 * this function calls back and executes the user's function
 *
 * \param userFunc The user's function to execute
 * \param path The user's library path 
 *
 ******************************************************************************
 */



/*struct setup to store list of library paths loaded in a program*/
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

void set_block_list(char* blockArray[], int arrLength);


//on lib load, tell what lib was loaded
//on library load- call user function
void on_library_load(int(*fptr)(lib_load_param));




/*function to return a list of all libraries loaded in a program*/
struct libList * getLibList();


/*struct setup to store library pointers for switch library path function */
typedef struct CallFuncChar1{
    int flag; 
    char* (*fptr)(char*);
    struct CallFuncChar1 *next; 
}CallFuncChar;


/*struct setup to store list of library paths loaded in a program*/
#endif
