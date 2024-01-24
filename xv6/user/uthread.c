#include "types.h"
#include "stat.h"
#include "user.h"
#include "param.h"

int 
thread_create(void (*start_routine)(void*),void *arg){
  void *stack=malloc(PGSIZE);
  
  if(stack==0)
    return -1;
  
  stack = (void*)((((uint)stack) + PGSIZE - 1) & ~(PGSIZE - 1));

  int pid=clone(start_routine,arg,stack);

  if(pid<0){
    free(stack);
    return -1;
  }

  return pid;
}

int 
thread_join(){
  void *stack=NULL;
  int pid=join(&stack);

  if(stack!=NULL){
    free(stack);
  }
  
  return pid;
}