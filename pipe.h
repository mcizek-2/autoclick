#ifndef PIPE_H_
#define PIPE_H_
#include<stdbool.h>
#include<stdio.h>
#include<unistd.h>
bool pipe_init();
bool read_pipe();
void close_pipe();
void send_close_message();


#endif // PIPE_H_
