#include "pipe.h"
#include <time.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/extensions/XTest.h>
#include <pthread.h>
#define SLEEP_TIME 100000
static Display *display;
static bool stop;
static bool stopt;
static bool pause_clicking;
void *listen(){//Thread that waits for the stop message.
  stop = read_pipe(); //Listens on FIFO waiting for the stop message.
  return(NULL);
}


void *right_click(){//Thread that monitors when the right button is pressed.
  XLockDisplay(display);
  int revert_to;
  Window win;
  XGetInputFocus(display, &win, &revert_to);
  XUnlockDisplay(display); //Get the current window.
  Window root_return;//Variables for XQueryPointer
  Window child_return;
  int root_x_return;
  int root_y_return;
  int win_x_return;
  int win_y_return;
  unsigned int mask_return;
  while(!stop){
    XLockDisplay(display);
    XQueryPointer(display, win,&root_return, &child_return, &root_x_return, &root_y_return ,
                  &win_x_return,&win_y_return , &mask_return);
    XUnlockDisplay(display);
    pause_clicking = ((Button3Mask & (unsigned long)mask_return) == Button3Mask); //Pause clicking if the right button is pressed.
    usleep(SLEEP_TIME);
  }
  stopt = true; //Indicates that the connection to the X server is safe to close
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
    stopt=false;
    stop=false;
    pthread_t th1;
    pthread_create(&th1, NULL, listen , NULL); //Start listening for the stop message.
    pthread_t th2;
    display = XOpenDisplay(NULL);
    pthread_create(&th2,NULL,right_click,NULL);
    while(!stop){//While the stop message hasn't been sent.
      usleep(SLEEP_TIME);//Wait 100 ms.
      if(!pause_clicking){
        simulate_click();
      }

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
