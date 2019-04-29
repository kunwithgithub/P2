#include <assert.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <ucontext.h>
#include "context.h"
#include "preempt.h"
#include "queue.h"
#include "uthread.h"

/* TODO Phase 2 */
#define STACK_SIZE 32768

enum state{READY,RUNNING,BLOCK,ZOMBIE};


uthread_t TID;
int V = 5; 

queue_t ready, block, zombie;
//queue_t running

struct Thread{
  uthread_t tid;
  void *stackPtr;
  enum state state_of_uthread;
  
  //comment before
  char stack[STACK_SIZE];
  uthread_ctx_t ctx;
  int value;
  
};

struct Thread *currentRunningThread;

void uthread_yield(void)
{
	/* TODO Phase 2 */
 
  queue_enqueue(ready, currentRunningThread); 
  struct Thread *from;
  struct Thread *to;
  from = currentRunningThread;
  queue_dequeue(ready, (void**)&to);
  currentRunningThread = to;
  uthread_ctx_switch(&(from->ctx), &(currentRunningThread->ctx));
  currentRunningThread->state_of_uthread=RUNNING;

}

uthread_t uthread_self(void)
{
	/* TODO Phase 2 */
  
  return currentRunningThread->tid;
}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
  printf("create begin\n");
 struct Thread *mainThread = malloc(sizeof(struct Thread));
  if(TID == 0){
    ready = queue_create();
  //  running = queue_create();
    block = queue_create();
    zombie = queue_create();
   
	mainThread->tid = TID;
    mainThread->state_of_uthread = RUNNING;
    currentRunningThread = mainThread;
    currentRunningThread->stackPtr = uthread_ctx_alloc_stack();
	 	 
    TID++;
  }
  
  struct Thread *newThread = malloc(sizeof(struct Thread));
  
  
  //have to do someting
  
  if(newThread == NULL){
    return -1;

  }
  newThread->stackPtr = uthread_ctx_alloc_stack();
  newThread->state_of_uthread = READY;
  newThread->tid = TID;
 
//newThread->ctx = NULL;

  uthread_ctx_init(&(newThread->ctx), newThread->stackPtr, func, arg);

 
  queue_enqueue(ready, newThread);
//  uthread_yield();
  TID++;

  return newThread->tid;
}

void uthread_exit(int retval)
{
	/* TODO Phase 2 */
	struct Thread *temp = currentRunningThread;
	queue_enqueue(zombie,temp);
	uthread_yield();
	temp->state_of_uthread = ZOMBIE;

}

static int find_item(void *data, void *arg)
{
    uthread_t tid = (*(uthread_t*)arg);
    
    if (tid == ((struct Thread*)data)->tid)
    {
        //printf("match\n");
        return 1;
    }

    return 0;
}

int uthread_join(uthread_t tid, int *retval)
{
	/* TODO Phase 2 */
  /*
  
  if(tid == 0){
    return -1;
  }
  while(1){
    int length = queue_length(ready);
    if(length == 0){
      printf("length is %d\n",length);
      break;
    }
    uthread_yield();
 
  }
  return 0;
  */
	/* TODO Phase 3 */
  
  int a = 0;
  int b = 0;
  int c = 0;
  struct Thread *join;
  struct Thread *blocked;
  struct Thread *readyed;
  struct Thread *skull;

  for(int i = 0; i< queue_length(block); i++)
  { 
  
     b = queue_iterate(block, find_item, &tid, (void**)&blocked);
  }

  for(int j = 0; j<queue_length(ready); j++)
  {
    a = queue_iterate(ready, find_item, &tid, (void**)&readyed);
  }
  
 

  if(a == 1 || b ==1)
  { 
    join = currentRunningThread;
    join->state_of_uthread = BLOCK;
    queue_enqueue(block,join);
   
    if(a==1)
    {
      blocked = currentRunningThread;
    }

    else if(b==1)
    {
      readyed = currentRunningThread;
    }
    
    uthread_yield();
   
     for(int k = 0; k<queue_length(zombie); k++)
    {
       c = queue_iterate(zombie, find_item, &tid,(void**)&skull);
    }
    
    
    if(c==1 && a==1)
    {  
      queue_enqueue(block, (void*)&join);
      join->state_of_uthread=READY;
      queue_enqueue(ready,join);
      readyed->value = V;
      *retval = readyed->value;
      return *retval;
    }
  
   else if(c==1 && b ==1)
   {
      queue_enqueue(block, (void*)&join);
      join->state_of_uthread=READY;
      queue_enqueue(ready,join);
      blocked->value = V;
      *retval = blocked->value;
      return *retval;
   }
  
  }

  else 
  { 
      for(int k = 0; k<queue_length(zombie); k++)
    {
       c = queue_iterate(zombie, find_item, &tid,(void**)&skull);
    }
    
    if(c==1)
    {
      join = currentRunningThread;
      join->value=V;
    
      *retval = join->value;
      return *retval;
    }
    
    uthread_yield();

  }
  
  
  
}
