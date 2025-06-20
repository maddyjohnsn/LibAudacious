
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
COMMITTEE_EXPORT void *committee_get_wrappee(committee_wrappee_handle_t handle);

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


struct library_load_params{
	char* libName; 
	char* newPath;
	//could be added - another char*

};


//on lib load, tell what lib was loaded
//on library load- call user function
COMMITTEE_EXPORT void on_libray_load(int (*userFunc) (struct library_load_params *params));

//user calls toolinit
//toolinit gets called by audit
//user point ld audit at tool combined with committee- then ld audit looks up toolPrint etc- worry about later
//have la version call toolinit
//tool_init__();
//	on_library_load(toolPrint);


int toolPrint(struct library_load_params *params);
	//print params->path;
	//params->newPath = "/foo";
	//new path becomes /foo after printing path
	//could return an int as an error code
	//could return 0 as succes -1 as failure
	
//}
//can have const do not load- if they point at it do not load
//can make a struct that passes the data to the callback- then can add more parameters without breaking
//could be a replace function too^^

//- maybe want to register when certain functions are called- toolinit gives function for what happens when that function is called
//	ex on symbol binding or something like that- don't have to use callbacks for things like this necessarily
//


/*function to return a list of all libraries loaded in a program*/
struct libList * getLibList();


/*struct setup to store library pointers for switch library path function */
typedef struct CallFuncChar1{
    int flag; 
    char* (*fptr)(char*);
    struct CallFuncChar1 *next; 
}CallFuncChar;


/*struct setup to store list of library paths loaded in a program*/
struct libList {
        char* path;
        int size;
};
//people will want to know load address
//pointer to the dynamic section
//
#endif
