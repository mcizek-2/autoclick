#include "sharedmemory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

#define IPC_RESULT_ERROR (-1)

static int get_shared_block(char* filename, int size){
  int id;
  char* writer;
  key_t key;
  // Request a key
  // The key is linked to a filename, so that other programs can access it.
  key = ftok(filename, 0);
  if (key == IPC_RESULT_ERROR){
    return IPC_RESULT_ERROR;
  }
  id = shmget(key,size,0644);
  if(id<=0){
    id = shmget(key,size,0644 | IPC_CREAT);
    writer=shmat(id,NULL,0);
    *writer = 1;
    shmdt(writer);
  }
  return id;
}

char* attach_memory_block(char *filename,int size){
  int shared_block_id = get_shared_block(filename, size);
  char* result;
  if (shared_block_id ==IPC_RESULT_ERROR){
    return NULL;
  }
  // map the shared block into this process's memory
  // and give me a pointer to it
  result = shmat(shared_block_id,NULL,0);
  if (result ==(char *)IPC_RESULT_ERROR){
    return NULL;
  }
  return result;
}

bool detach_memory_block(char* block){
  return(shmdt(block) != IPC_RESULT_ERROR);
}

bool destroy_memory_block(char* filename){
  int shared_block_id =get_shared_block(filename, 0);

  if(shared_block_id ==IPC_RESULT_ERROR){
    return NULL;
  }
  return (shmctl(shared_block_id, IPC_RMID,NULL) != IPC_RESULT_ERROR);
}
