#include "pipe.h"
#include <time.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <pthread.h>
static Display *display;
static bool stop;
void *listen(){
  stop = read_pipe();
  pthread_exit(NULL);
}
void click(){
/*
  XTestFakeButtonEvent(display, 1, True, CurrentTime);
  XTestFakeButtonEvent(display, 1, False, CurrentTime);
  XFlush(display);
*/
  printf("Testing... \n");
}
int main(){
  if(!pipe_init()){
    stop=false;
    pthread_t th;
    pthread_create(&th, NULL, listen , NULL);
    while(!stop){
      //usleep(100000);
      sleep(3);
      click();
    }
    close_pipe();
    return 1;
  }
  else{
    send_close_message();
    return 1;
  }

}
