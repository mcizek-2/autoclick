#include "pipe.h"
#include <time.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <pthread.h>
static Display *display;
static bool stop;
void *listen(){//Thread that waits for the stop message.
  stop = read_pipe(); //Listens on FIFO waiting for the stop message.
  pthread_exit(NULL);
}
int main(){
  if(!pipe_init()){//If the FIFO has not been created yet.
    stop=false;
    pthread_t th;
    pthread_create(&th, NULL, listen , NULL); //Start listening for the stop message.
    display = XOpenDisplay(NULL);
    while(!stop){//While the stop message hasn't been sent.
      usleep(100000);//Wait 100 ms.
      XTestFakeButtonEvent(display, 1, True, CurrentTime);
      XTestFakeButtonEvent(display, 1, False, CurrentTime);
      XFlush(display);//Simulate a button click
    }
    close_pipe();// Close the FIFO and delete the corresponding file.
    XCloseDisplay(display);
    return 1;
  }
  else{
    send_close_message();
    return 1;
  }

}
