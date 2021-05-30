#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include "sharedmemory.h"
static Display *display;

int main(){
    const char* homedir = getenv("HOME");
    const char* loc = "/.local/var/aclick";
    char filepath[128];
    strncpy(filepath,homedir,sizeof(filepath));
    strncat(filepath,loc,(sizeof(filepath)-strlen(filepath)));
    char* stop = attach_memory_block(filepath,BLOCK_SIZE);
    if(*stop == 1){
        *stop=0;
        display = XOpenDisplay(NULL);
        while(*stop==0){
         usleep(100000);
         XTestFakeButtonEvent(display, 1, True, CurrentTime);
         XTestFakeButtonEvent(display, 1, False, CurrentTime);
         XFlush(display);
        }
        detach_memory_block(stop);
        destroy_memory_block(filepath);
        return 1;
    }
    else{
    *stop = 1;
    detach_memory_block(stop);
    return 1;
    }
    
    return 1;
}
