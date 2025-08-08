/*
 ******************************************************************************
 *
 * \file committee.h
 *
 * \brief   Header file containing the external libAudacious interface
 *
 ******************************************************************************
 */
#include "./libAud_internal.h"
#ifndef COMMITTEE_H
#define COMMITTEE_H
/*
 ******************************************************************************
 *
 * \fn int wrap(char*, fptr_t)
 *
 * \brief Given a function name, replaces the wrapped function with wrapper
 *
 * \param wrappee__name		The original function to be wrapped
 * \param wrapper		The user's function to replace wrappee_name 
 *
 ******************************************************************************
 */

int wrap(char* wrappee_name, void*  wrapper);

/*
 ******************************************************************************
 *
 * \fn int set_block_list(char*, int)
 *
 * \brief Given a library path, each path in the list will be blocked from loading 
 *
 * \param blockArray	The array of path names to be block
 * \param arrLength	The number of paths the user is blocking 
 *
 ******************************************************************************
 */

int set_block_list(char* blockArray[], int arrLength);

/*
 * Same as set_block_list, except blockArray can be a list of regular expressions 
 * Each regular expression included in a library path name will be blocked
 */

int set_block_reglist(char* blockArray[], int arrLength);
/*
 ******************************************************************************
 *
 * \fn int set_allow_list(char*, int)
 *
 * \brief Given a library path, each path in the list and only these paths will be allowed to load 
 *
 * \param allowArray	The array of path names to allow
 * \param arrLength	The number of paths the user is allowing 
 *
 ******************************************************************************
 */


int set_allow_list(char* allowArray[], int arrLength);

/*
 * Same as set_allow_list, except phraseArray can be a list of regular expressions 
 * Each regular expression included in a library path name will be allowed
 * Can use both set_allow_list and set_allow_groups at the same time
 */

int set_allow_groups(char* phraseArray[], int arrLength);

/*struct setup to store list of library paths loaded in a program*/
typedef struct library_load_params1{
        char* libName;
        char* newPath;
        //could be added - another char*
}lib_load_param;

int librarycensus();
typedef int(*LibLoadFuncs)(lib_load_param*);
int setloadlist(LibLoadFuncs funcstoset);

/* external */



#endif
