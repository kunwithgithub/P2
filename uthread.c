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
  uthread_t parent;
  uthread_t child;
  int willBeCollected;
  
};

struct Thread *currentRunningThread;

 int find_item(void *data, void *arg)
{
    uthread_t tid = (*(uthread_t*)arg);
  
    if (tid == ((struct Thread*)data)->tid)
    {
        //printf("match\n");
        return 1;
    }

    return 0;
}


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
  /*
	struct Thread *temp = currentRunningThread;
	queue_enqueue(zombie,temp);
	uthread_yield();
	temp->state_of_uthread = ZOMBIE;
  */
  
  int d = 0;
  struct Thread *unblocking;
  currentRunningThread->willBeCollected = retval;
  //
 
 d = queue_iterate(block, find_item, (void *)&(currentRunningThread->parent), (void **)&unblocking);


 if(d==1)
 {
  unblocking->state_of_uthread = READY;
  queue_delete(block, (void *)unblocking);
  queue_enqueue(ready,(void *)unblocking);
 }
  
  currentRunningThread->state_of_uthread = ZOMBIE;
  queue_enqueue(zombie,(void*)currentRunningThread);
  uthread_yield();
  
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

   if(tid == 0 || tid == currentRunningThread->tid){
    
    return -1;
  }

  int isInBlocked = 0;
  int isInReady = 0;
  int isInZombie = 0;


  struct Thread *blocked;
  struct Thread *zombied;
  struct Thread *readied;
  //struct Thread *free;
  struct Thread *child;
//  struct Thread *parent;


  isInReady = queue_iterate(ready, find_item, (void *)&tid, (void **)&readied);
  

  isInBlocked = queue_iterate(block, find_item,(void *)&tid, (void **)&blocked);

 

  isInZombie = queue_iterate(zombie,find_item, (void *)&tid, (void **)&zombied);
  
  if(isInReady == 0 && isInBlocked ==0 && isInZombie ==0){
    

    return -1;
  }

 


  
  if(isInReady == 1){
  
    readied->parent = currentRunningThread->tid;
    currentRunningThread->state_of_uthread = BLOCK;
    queue_enqueue(block, (void *)currentRunningThread);
    blocked = currentRunningThread;
    
    queue_dequeue(ready,(void **)&currentRunningThread);
    blocked->child = currentRunningThread->tid;
    uthread_ctx_switch(&(blocked->ctx),&(currentRunningThread->ctx));
   

    //uthread_exit(5);
   
   }else if(isInZombie == 1){

    zombied->willBeCollected = *retval;


    return *retval;

  }else if(isInBlocked == 1){
    blocked->tid = currentRunningThread->tid;
    currentRunningThread->state_of_uthread = BLOCK;
    queue_enqueue(block, (void *)currentRunningThread);
    blocked = currentRunningThread;
    queue_dequeue(ready,(void **)&currentRunningThread);
    uthread_ctx_switch(&(blocked->ctx),&(currentRunningThread->ctx));

  }

   //collect
   //get return value of zombie queue, and free
    printf("dddc\n");
  
    
    

   //parent->willBeCollected = *retval;
  
    int success = queue_iterate(zombie, find_item, (void *)&currentRunningThread->child, (void **)&child);

    printf("child is %d found\n",success);

    
    uthread_t deleted = child->tid;
    
  
    printf("child is %d \n",currentRunningThread->child);
    queue_delete(zombie, (void *)child);



    uthread_ctx_destroy_stack(child->stackPtr);

    return 0;
}
