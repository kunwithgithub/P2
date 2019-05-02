/*
 * Thread creation and yielding test
 *
 * Tests the creation of multiples threads and the fact that a parent thread
 * should get returned to before its child is executed. The way the printing,
 * thread creation and yielding is done, the program should output:
 *
 * thread1
 * thread2
 * thread3
 */
#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "queue.h"
#include "context.h"
#include "preempt.h"
#include "uthread.h"


int thread1(void* arg)
{ 
    while(1){
      
    } 
		printf("thread1\n");

    
	return 0;
}

int main(void)
{

  	uthread_create(thread1, NULL);

    uthread_yield();
  printf("preemption case passed!\n");

	return 0;
}
