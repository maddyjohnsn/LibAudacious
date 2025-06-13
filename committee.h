
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

COMMITTEE_EXPORT void callback_one_param(int (*userFunc) (char*), char * path)


#endif
