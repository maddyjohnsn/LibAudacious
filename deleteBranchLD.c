#include <stdio.h>
#define _GNU_SOURCE
#include <stdlib.h>
#include <string.h>
#define __USE_GNU
#include <link.h>
#include <dlfcn.h>

unsigned int la_version(unsigned int version) {
    //get env returns null or what the variable contains
    return version;
}

void la_activity( uintptr_t *cookie, unsigned int flag){
	printf("into Activity\n");
	printf( "%s:%s flag:%d%s\n", __FILE__, __func__,flag,
        flag & LA_ACT_CONSISTENT ? "LA_ACT_CONSISTENT"  :
        flag & LA_ACT_DELETE  ? "LA_ACT_DELETE"  :
        flag & LA_ACT_ADD  ? "LA_ACT_ADD"  :
        "UNKNOWN_FLAG");
}
//void tester(){
//	printf("testing!\n");
//}
