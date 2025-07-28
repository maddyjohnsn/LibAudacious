/*
 ******************************************************************************
 *
 * \file libAud_internal.h
 *
 * \brief   Header file containing the internal libAudacious interface
 *
 ******************************************************************************
 */

#ifndef LIBAUD_INTERNAL_H
#define LIBAUD_INTERNAL_H
 typedef int (*fptr_t)(const char *format, ...);
typedef char*(*LibLoad)(char*);
typedef struct expir{
    char* wrappee;
    fptr_t fptr;
    fptr_t  ogfptr;
}WrappedFunctions;

fptr_t get_wrappee(char *wrappee_name);

#endif
