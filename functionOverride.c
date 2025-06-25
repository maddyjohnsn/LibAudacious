#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>
#include <dlfcn.h>

int printf(const char *format, ...){

        void *handle;

        handle = dlopen("libc.so.6", RTLD_LAZY);
        if (!handle){
                //if failed to load the library
                fprintf(stderr, "Error: %s\n", dlerror());
                return EXIT_FAILURE;
        }



        
        int (*printf_ptr)(const char *format, ...) = dlsym(handle, "printf");
        if (!printf_ptr) {
                //if symbol can't be found (should be the needed function I'm replacing)
                fprintf(stderr, "Error: %s\n", dlerror());
                dlclose(handle);
                return EXIT_FAILURE;
        }

        //uses my printf and then closes the library! Yay!


        //gets the initial time from gettimeofday. tv is the time
        struct timeval tv;

        struct tm *today;

        gettimeofday(&tv, NULL);
        today = localtime(&tv.tv_sec);

        printf_ptr("Time: %d:%0d:%0d.%d\n", today->tm_hour, today->tm_min, today->tm_sec, tv.tv_usec);


        printf_ptr(format);

        dlclose(handle);
        
        return 0;
}

