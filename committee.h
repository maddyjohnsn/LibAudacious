
#ifndef COMMITTEE_H
#define COMMITTEE_H

/* Allows functions to be visible to all other parts of the library */
#define COMMITTEE_EXPORT __attribute__((__visibility__("default")))

/*Function that can cancel a library call, and/or change a libray path when a library is called */

GOTCHA_EXPORT char* COMMITTEE_EDIT_LIB(char* path);

/*Function that override a given function with a custom version*/



/*Function that can bring back original version of overridden function*/

/*Function with ability to monitor function and library calls */

#endif
