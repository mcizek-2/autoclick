#include "pipe.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
static int fd;
static char filepath[128];
bool pipe_init(){
  const char* homedir = getenv("HOME");
  const char* loc = "/.local/tmp/aclick";
  strncpy(filepath,homedir,sizeof(filepath));
  strncat(filepath,loc,(sizeof(filepath)-strlen(filepath)));
  struct stat st;
  bool exists= (stat(filepath, &st)==0);
  if(!exists){
    mkfifo(filepath,0666);
  }
  return exists;
}
bool read_pipe(){
 char value;
 fd=open(filepath,O_RDONLY);
 read(fd, &value,sizeof(char));
 return(value==1);
}
void close_pipe(){
  close(fd);
  remove(filepath);
}

void send_close_message(){
  fd=open(filepath,O_WRONLY);
  char msg = 1;
  write(fd,&msg,sizeof(char));
  close(fd);
}
