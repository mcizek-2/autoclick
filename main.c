#include "pipe.h"
#include <time.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <pthread.h>
static Display *display;
static bool stop;
static bool stopt;
static bool pause_clicking;
static bool right_pressed;
void *listen(){//Thread that waits for the stop message.
  stop = read_pipe(); //Listens on FIFO waiting for the stop message.
  return(NULL);
}
void *right_click(){
  XEvent *event_return;
  while(!stop){
    if(XCheckMaskEvent(display, ButtonPressMask , event_return) ||
       XCheckMaskEvent(display, ButtonReleaseMask, event_return))
      {
        if(event_return->type == ButtonPress && (event_return->xbutton).button == Button2){
          pause_clicking = true; //If the right button is pressed, pause the clicking
        }
        if(event_return->type == ButtonRelease && (event_return->xbutton).button == Button2){
          pause_clicking = false; //If it is released resume clicking
        }
      }
  }
  stopt = true;
  return(NULL);
}

void simulate_click(){
  XTestFakeButtonEvent(display, 1, True, CurrentTime);
  XTestFakeButtonEvent(display, 1, False, CurrentTime);
  XFlush(display);
}
int main(){
  if(!pipe_init()){//If the FIFO has not been created yet.
    XInitThreads();
    right_pressed = false;
    stopt=false;
    stop=false;
    pthread_t th;
    pthread_create(&th, NULL, listen , NULL); //Start listening for the stop message.
    display = XOpenDisplay(NULL);
    while(!stop){//While the stop message hasn't been sent.
      usleep(100000);//Wait 100 ms.
      simulate_click();
          }
    close_pipe();// Close the FIFO and delete the corresponding file.
    while(!stopt){// Wait for the thread to close
      usleep(100);
    }
    XCloseDisplay(display); //Close the display
    return 0;
  }
  else{
    send_close_message();
    return 0;
  }

}
