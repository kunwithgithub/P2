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
  int willBeCollected;
  
};

struct Thread *currentRunningThread;

 int find_item(void *data, void *arg)
{
    uthread_t tid = (*(uthread_t*)arg);
    //printf("tid we looking for is %d \n",tid);
    uthread_t dataTid = ((struct Thread*)data)->tid;
    if (tid == dataTid)
    { 
   //     printf("struct tid is %d\n",dataTid);
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
 // printf("create begin\n");
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
  struct Thread *unblocking;
  struct Thread *temp = currentRunningThread;
 
  uthread_yield();
   queue_enqueue(zombie,(void*)temp);
  queue_iterate(block, find_item, (void *)&(temp->parent), (void **)&unblocking);
  unblocking->state_of_uthread = READY;
  queue_delete(block, (void *)unblocking);
  queue_enqueue(ready,(void *)unblocking);
  temp->state_of_uthread = ZOMBIE;
 
  
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
  int isInBlocked = 0;
  int isInReady = 0;
  int isInZombie = 0;

  struct Thread *join;
  struct Thread *blocked;
  struct Thread *zombied;
  struct Thread *readied;
  struct Thread *parent;

 // uthread_t testTID = 0;

  isInReady = queue_iterate(ready, find_item, (void *)&tid, (void **)&readied);
 // printf("isready is : %d\n",isInReady);
 // printf("ready length is %d\n",queue_length(ready));
  isInBlocked = queue_iterate(block, find_item,(void *)&tid, (void **)&blocked);

  isInZombie = queue_iterate(zombie,find_item, (void *)&tid, (void **)&zombied);

  if(isInReady == 1){
    readied->parent = currentRunningThread->tid;
    currentRunningThread->state_of_uthread = BLOCK;
    queue_enqueue(block, (void *)currentRunningThread);
    blocked = currentRunningThread;
    queue_dequeue(ready,(void **)&currentRunningThread);
    uthread_ctx_switch(&(blocked->ctx),&(currentRunningThread->ctx));


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


  }else{
    return -1;
  }


  
  
  
}
