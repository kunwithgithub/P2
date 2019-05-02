#include <signal.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "preempt.h"
#include "uthread.h"

/*
 * Frequency of preemption
 * 100Hz is 100 times per second
 */
#define HZ 100

 struct sigaction sa;
 struct itimerval timer;

void timer_handle (int signum)
{
 static int count = 0;
 printf ("timer expired %d times\n", ++count);
}

void preempt_disable(void)
{
	/* TODO Phase 4 */
  /* Reference: */
  sigset_t sigprof;
  sigemptyset(&sigprof);
  sigaddset(&sigprof,SIGPROF);

  if(sigprocmask(SIG_BLOCK, &sigprof, NULL) == -1){

    perror("sigprocmask");
    abort();
  }

}

void preempt_enable(void)
{
	/* TODO Phase 4 */
    sigset_t sigprof;
    sigemptyset(&sigprof);
    sigaddset(&sigprof,SIGPROF);
    if(sigprocmask(SIG_UNBLOCK, &sigprof, NULL) == -1){
      perror("sigprocmask");
      abort(); 
    }

}

void preempt_start(void)
{
	/* TODO Phase 4 */
  /*
 * preempt_start - Start thread preemption
 *
 * Configure a timer that must fire a virtual alarm at a frequency of 100 Hz and
 * setup a timer handler that forcefully yields the currently running thread.
 */
/* Install timer_handler as the signal handler for SIGVTALRM. */
 memset (&sa, 0, sizeof (sa));
 sa.sa_handler = &timer_handle;
 sigaction (SIGVTALRM, &sa, NULL);

 /* Configure the timer to expire after 250 msec... */
 timer.it_value.tv_sec = 0;
 timer.it_value.tv_usec = 1000000/HZ;
 /* ... and every 250 msec after that. */
 timer.it_interval.tv_sec = 0;
 timer.it_interval.tv_usec = 1000000/HZ;


 setitimer (ITIMER_VIRTUAL, &timer, NULL);




}
