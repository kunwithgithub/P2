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


static uthread_t TID;
static queue_t ready, running, block, zombie;

struct Thread{
  uthread_t tid;
  void *stackPtr;
  enum state state_of_uthread;
  char stack[STACK_SIZE];
  ucontext_t ctx;
};

void uthread_yield(void)
{
	/* TODO Phase 2 */
  struct Thread *from;
  struct Thread *to;
  queue_dequeue(running,(void *)from);
  queue_enqueue(ready,to);
  uthread_ctx_switch((void *)from, (void *)to);
  from->state_of_uthread = RUNNING;
  queue_enqueue(running, to);

}

uthread_t uthread_self(void)
{
	/* TODO Phase 2 */

  

}

int uthread_create(uthread_func_t func, void *arg)
{
	/* TODO Phase 2 */
  
  if(TID == 1){
    ready = queue_create();
    running = queue_create();
    block = queue_create();
    zombie = queue_create();
  }
  struct Thread *newThread = (struct Thread*)malloc(sizeof(struct Thread));
  if(newThread == NULL){
    return -1;
  }
  newThread->stackPtr = NULL;
  newThread->state_of_uthread = READY;
  newThread->tid = TID;
  newThread->ctx = NULL;
  

  int ctxInitializationSuccess = uthread_ctx_init(newThread->ctx, newThread->stackPtr, func, arg);

  queue_enqueue(ready, newThread);
  TID++;
  return newThread->tid;
}

void uthread_exit(int retval)
{
	/* TODO Phase 2 */
}

int uthread_join(uthread_t tid, int *retval)
{
	/* TODO Phase 2 */
	/* TODO Phase 3 */
}
