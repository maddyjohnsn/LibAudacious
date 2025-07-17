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

typedef FILE* (*fptr_t)(const char*, const char*);
typedef char*(*LibLoad)(char*);
typedef struct expir{
    char* wrappee;
    fptr_t fptr;
    struct expir* next;
}WrappedFunctions;

fptr_t get_wrappee(char *wrappee_name);

#endif
