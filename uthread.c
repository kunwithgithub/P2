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

queue_t ready, block, zombie;
//queue_t running

struct Thread{
  uthread_t tid;
  void *stackPtr;
  enum state state_of_uthread;
//char stack[STACK_SIZE];
  ucontext_t ctx;
};

struct Thread *currentRunningThread;

void uthread_yield(void)
{
	/* TODO Phase 2 */
  struct Thread *from;
  struct Thread *to;

  queue_dequeue(ready,(void*)to);
  from = currentRunningThread;

  uthread_ctx_switch((void *)from, (void *)to);
  currentRunningThread = to;
  currentRunningThread->state_of_uthread = RUNNING;
  queue_enqueue(ready, (void*)from);
//  queue_enqueue(running, (void *)to);
}

uthread_t uthread_self(void)
{
	/* TODO Phase 2 */
  if(currentRunningThread == NULL){
  struct Thread *to;
  queue_dequeue(ready,(void *)to);
  uthread_ctx_switch((void *)currentRunningThread, (void *)to);
  to->state_of_uthread = RUNNING;
  currentRunningThread = to;
//  queue_enqueue(running, to);
  }
  return currentRunningThread->tid;
}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
  if(TID == 1){
    ready = queue_create();
  //  running = queue_create();
    block = queue_create();
    zombie = queue_create();
  }
  struct Thread *newThread = (struct Thread*)malloc(sizeof(struct Thread));
  if(newThread == NULL){
    return -1;
  }
  newThread->stackPtr = uthread_ctx_alloc_stack();
  newThread->state_of_uthread = READY;
  newThread->tid = TID;
//newThread->ctx = NULL;

  int ctxInitializationSuccess = uthread_ctx_init(&(newThread->ctx), newThread->stackPtr, func, arg);

  queue_enqueue(ready, newThread);
  TID++;
  return newThread->tid;
}

void uthread_exit(int retval)
{
	/* TODO Phase 2 */
  /*if(currentRunningThread->state_of_uthread == ZOMBIE){
    uthread_ctx_destroy_stack(currentRunningThread->stackPtr);
  }*/
  if(retval > 0){
    uthread_ctx_destroy_stack(currentRunningThread->stackPtr);
    free(currentRunningThread);
  }else{
    queue_enqueue(zombie,(void *)currentRunningThread);
  }

}

int uthread_join(uthread_t tid, int *retval)
{
	/* TODO Phase 2 */
  if(tid == 0){
    return -1;
  }
  while(1){
    int length = queue_length(ready);
    if(length == 0){
      break;
    }
    uthread_yield();
  }
  return 0;
	/* TODO Phase 3 */
}
