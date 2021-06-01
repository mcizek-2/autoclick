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
  }
int main(){
  if(!pipe_init()){
    stop=false;
    pthread_t th;
    pthread_create(&th, NULL, listen , NULL);
    display = XOpenDisplay(NULL);
    while(!stop){
      //usleep(100000);
      sleep(2);
      XTestFakeButtonEvent(display, 1, True, CurrentTime);
      usleep(10);
      XTestFakeButtonEvent(display, 1, False, CurrentTime);
      XFlush(display);
    }
    close_pipe();
    XCloseDisplay(display);
    return 1;
  }
  else{
    send_close_message();
    return 1;
  }

}
