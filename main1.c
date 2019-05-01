#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"
#include <ucontext.h>
/*
void test_create(void)
{
    queue_t q;

    q = queue_create();
    assert(q != NULL);
}


void test_queue_simple(void)
{
    queue_t q;
    int a = 0;
    int b = 0;
    //int data = 3, *ptr;
    char data = 'a', *ptr;
    int data1 = 5;
    int date2 = 6;


    q = queue_create();
    queue_enqueue(q, &data1);
    queue_enqueue(q, &data);
    queue_enqueue(q, &data1);
    //b = queue_enqueue(q, &data);
    queue_dequeue(q, (void**)&ptr);
    queue_dequeue(q, (void**)&ptr);
   // queue_dequeue(q, (void**)&ptr);
    //queue_destroy(q);
   // q#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"


void test_create(void)
{
    queue_t q;
    q = queue_create();
    assert(q != NULL);
}


void test_queue_simple(void)
{
    queue_t q;
    int a = 0;
    int b = 0;
    //int data = 3, *ptr;
    char data = 'a', *ptr;
    int data1 = 5;
    int date2 = 6;
    q = queue_create();
    queue_enqueue(q, &data1);
    queue_enqueue(q, &data);
    queue_enqueue(q, &data1);
    //b = queue_enqueue(q, &data);
    queue_dequeue(q, (void**)&ptr);
    queue_dequeue(q, (void**)&ptr);
   // queue_dequeue(q, (void**)&ptr);
    //queue_destroy(q);
   // queue_delete(q, &data);
    //queue_delete(q, &data1);
    //b = queue_delete(q,&data1);
    a = queue_length(q);
    
   printf("ptr is %c\n",*ptr);
    printf("a is %d\n", a);
    #include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"


void test_create(void)
{
    queue_t q;
    q = queue_create();
    assert(q != NULL);
}


void test_queue_simple(void)
{
    queue_t q;
    int a = 0;
    int b = 0;
    //int data = 3, *ptr;
    char data = 'a', *ptr;
    int data1 = 5;
    int date2 = 6;
    q = queue_create();
    queue_enqueue(q, &data1);
    queue_enqueue(q, &data);
    queue_enqueue(q, &data1);
    //b = queue_enqueue(q, &data);
    queue_dequeue(q, (void**)&ptr);
    queue_dequeue(q, (void**)&ptr);
   // queue_dequeue(q, (void**)&ptr);
    //queue_destroy(q);
   // queue_delete(q, &data);
    //queue_delete(q, &data1);
    //b = queue_delete(q,&data1);
    a = queue_length(q);
    
   printf("ptr is %c\n",*ptr);
    printf("a is %d\n", a);
    
    printf("b is %d\n", b);
    //assert(ptr == &data);
}

static int inc_item(void *data, void *arg)
{
    int *a = (int*)data;
    int inc = (int)(long)arg;

    *a += inc;

    return 0;
}

/* Callback function that finds a certain item according to its value */
static int find_item(void *data, void *arg)
{
    int *a = (int*)data;
    int match = (int)(long)arg;

    if (*a == match)
    {
        //printf("match\n");
        return 1;
    }

    return 0;
}

static int print_item(void *data,void *arg)
{
    int *a = (int*)data;
    
    printf("data in queue: %d\n", *a);
    return 0;
}


static int multiply(void *data, void *arg)
{
  int *a = (int*)data;
  int mul = (int)(long)arg;
  *a = *a * mul;
  return 0;
}

void test_iterator(void)
{
    printf("\n\n\niterator test start\n");
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    int *ptr;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    printf("queue created!\n");
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Add value '1' to every item of the queue */
    queue_iterate(q, inc_item, (void*)1, NULL);
    printf("data[0] is %d:\n",data[9]);
    assert(data[0] == 2);
    
    /* Find and get the item which is equal to value '5' */
    ptr = NULL;
   int b = queue_iterate(q, find_item, (void*)6, (void**)&ptr);
    printf("ptr is %d:\n",*ptr);
    printf("b is %d:\n",b);
    assert(ptr != NULL);
    assert(*ptr == 6);
    assert(ptr == &data[4]);
   
    queue_iterate(q, multiply, (void*)3, NULL);
    printf("data[3] is %d:\n",data[3]);




}

void test_enqueueAndDequeue(void){
 
  queue_t q;
  int *ptr;
  printf("\n\n\n ------enqueue/dequeue test start:------- \n\n\n");
  q = queue_create();
  assert(q != NULL);
  assert(queue_length(q) == 0);

  printf("Queue create case pass. empty just created queue case pass. Before enqueue: the length is %d. \n", queue_length(q));

  printf(" \n\n\n single enqueue/dequeue test:\n");
  printf("Enqueue 1 item from data[] = {1,2,3,4,5,6,7,8,9,10}: \n");
  int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  queue_enqueue(q,&data[0]);
  assert(queue_length(q) == 1);
  printf("enqueue 1 item case pass! Now queue length is : %d\n",queue_length(q));

  queue_iterate(q, print_item, NULL, NULL);
  printf("dequeue started!\n");
  queue_dequeue(q,(void **)&ptr);
  assert(queue_length(q) == 0);
  assert(ptr != NULL);
  printf("dequeue finished! now queue length is: %d\n", queue_length(q));

  printf("\n\n multiple enqueue test start: \n");
  for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++){

    queue_enqueue(q, &data[i]);
    printf("enqueued %d items in total\n", i+1);

  }
  int size = sizeof(data) / sizeof(data[0]);
  assert(queue_length(q) == size);

  printf("multiple enqueue test case passed. All data in data[] has been enqueued the length of data[] is %d, the queue length is %d, data length matches!", size, queue_length(q));

  printf("\nnow we dequeue 1 item. The length before dequeue is %d \n dequeue started\n", queue_length(q));

  queue_dequeue(q,(void **)&ptr);
  assert(ptr != NULL);
  size = sizeof(data)/sizeof(data[0])-1;
  assert(queue_length(q) == size);

  printf("dequeue finished \nnow the length is %d, dequeue 1 item case pass \n", queue_length(q));
      printf("\n\n\n multiple dequeue test start: \n\n\n");
      printf("Before dequeue, now the length is %d, \n", queue_length(q));

  int length = queue_length(q);
   for (int i = 0; i < length; i++){
     struct Thread *temp;
    queue_dequeue(q, (void **)&temp);
    printf("dequeued %d items in totoal\n",i+1);

  }



  assert(queue_length(q)==0);

printf("now the length is %d, dequeue multiple item case pass \n", queue_length(q));



  printf("\n\n\n-------enqueue/dequeue test finished-------\n\n\n");


}


int main()
{
  //test_create();
  test_iterator();
  test_enqueueAndDequeue();

}
    printf("b is %d\n", b);
    //assert(ptr == &data);
}

static int inc_item(void *data, void *arg)
{
    int *a = (int*)data;
    int inc = (int)(long)arg;

    *a += inc;

    return 0;
}

/* Callback function that finds a certain item according to its value */
static int find_item(void *data, void *arg)
{
    int *a = (int*)data;
    int match = (int)(long)arg;

    if (*a == match)
    {
        //printf("match\n");
        return 1;
    }

    return 0;
}

static int print_item(void *data,void *arg)
{
    int *a = (int*)data;
    
    printf("data in queue: %d\n", *a);
    return 0;
}


static int multiply(void *data, void *arg)
{
  int *a = (int*)data;
  int mul = (int)(long)arg;
  *a = *a * mul;
  return 0;
}

void test_iterator(void)
{
    printf("\n\n\niterator test start\n");
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    int *ptr;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    printf("queue created!\n");
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Add value '1' to every item of the queue */
    queue_iterate(q, inc_item, (void*)1, NULL);
    printf("data[0] is %d:\n",data[9]);
    assert(data[0] == 2);
    
    /* Find and get the item which is equal to value '5' */
    ptr = NULL;
   int b = queue_iterate(q, find_item, (void*)6, (void**)&ptr);
    printf("ptr is %d:\n",*ptr);
    printf("b is %d:\n",b);
    assert(ptr != NULL);
    assert(*ptr == 6);
    assert(ptr == &data[4]);
   
    queue_iterate(q, multiply, (void*)3, NULL);
    printf("data[3] is %d:\n",data[3]);




}

void test_enqueueAndDequeue(void){
 
  queue_t q;
  int *ptr;
  printf("\n\n\n ------enqueue/dequeue test start:------- \n\n\n");
  q = queue_create();
  assert(q != NULL);
  assert(queue_length(q) == 0);

  printf("Queue create case pass. empty just created queue case pass. Before enqueue: the length is %d. \n", queue_length(q));

  printf(" \n\n\n single enqueue/dequeue test:\n");
  printf("Enqueue 1 item from data[] = {1,2,3,4,5,6,7,8,9,10}: \n");
  int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  queue_enqueue(q,&data[0]);
  assert(queue_length(q) == 1);
  printf("enqueue 1 item case pass! Now queue length is : %d\n",queue_length(q));

  queue_iterate(q, print_item, NULL, NULL);
  printf("dequeue started!\n");
  queue_dequeue(q,(void **)&ptr);
  assert(queue_length(q) == 0);
  assert(ptr != NULL);
  printf("dequeue finished! now queue length is: %d\n", queue_length(q));

  printf("\n\n multiple enqueue test start: \n");
  for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++){

    queue_enqueue(q, &data[i]);
    printf("enqueued %d items in total\n", i+1);

  }
  int size = sizeof(data) / sizeof(data[0]);
  assert(queue_length(q) == size);

  printf("multiple enqueue test case passed. All data in data[] has been enqueued the length of data[] is %d, the queue length is %d, data length matches!", size, queue_length(q));#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"


void test_create(void)
{
    queue_t q;
    q = queue_create();
    assert(q != NULL);
}


void test_queue_simple(void)
{
    queue_t q;
    int a = 0;
    int b = 0;
    //int data = 3, *ptr;
    char data = 'a', *ptr;
    int data1 = 5;
    int date2 = 6;
    q = queue_create();
    queue_enqueue(q, &data1);
    queue_enqueue(q, &data);
    queue_enqueue(q, &data1);
    //b = queue_enqueue(q, &data);
    queue_dequeue(q, (void**)&ptr);
    queue_dequeue(q, (void**)&ptr);
   // queue_dequeue(q, (void**)&ptr);
    //queue_destroy(q);
   // queue_delete(q, &data);
    //queue_delete(q, &data1);
    //b = queue_delete(q,&data1);
    a = queue_length(q);
    
   printf("ptr is %c\n",*ptr);
    printf("a is %d\n", a);
    
    printf("b is %d\n", b);
    //assert(ptr == &data);
}

static int inc_item(void *data, void *arg)
{
    int *a = (int*)data;
    int inc = (int)(long)arg;

    *a += inc;

    return 0;
}

/* Callback function that finds a certain item according to its value */
static int find_item(void *data, void *arg)
{
    int *a = (int*)data;
    int match = (int)(long)arg;

    if (*a == match)
    {
        //printf("match\n");
        return 1;
    }

    return 0;
}

static int print_item(void *data,void *arg)
{
    int *a = (int*)data;
    
    printf("data in queue: %d\n", *a);
    return 0;
}


static int multiply(void *data, void *arg)
{
  int *a = (int*)data;
  int mul = (int)(long)arg;
  *a = *a * mul;
  return 0;
}

void test_iterator(void)
{
    printf("\n\n\niterator test start\n");
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    int *ptr;

    /* Initialize the queue and enqueue items */
    q = queue_create();
    printf("queue created!\n");
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    /* Add value '1' to every item of the queue */
    queue_iterate(q, inc_item, (void*)1, NULL);
    printf("data[0] is %d:\n",data[9]);
    assert(data[0] == 2);
    
    /* Find and get the item which is equal to value '5' */
    ptr = NULL;
   int b = queue_iterate(q, find_item, (void*)6, (void**)&ptr);
    printf("ptr is %d:\n",*ptr);
    printf("b is %d:\n",b);
    assert(ptr != NULL);
    assert(*ptr == 6);
    assert(ptr == &data[4]);
   
    queue_iterate(q, multiply, (void*)3, NULL);
    printf("data[3] is %d:\n",data[3]);




}

void test_enqueueAndDequeue(void){
 
  queue_t q;
  int *ptr;
  printf("\n\n\n ------enqueue/dequeue test start:------- \n\n\n");
  q = queue_create();
  assert(q != NULL);
  assert(queue_length(q) == 0);

  printf("Queue create case pass. empty just created queue case pass. Before enqueue: the length is %d. \n", queue_length(q));

  printf(" \n\n\n single enqueue/dequeue test:\n");
  printf("Enqueue 1 item from data[] = {1,2,3,4,5,6,7,8,9,10}: \n");
  int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  queue_enqueue(q,&data[0]);
  assert(queue_length(q) == 1);
  printf("enqueue 1 item case pass! Now queue length is : %d\n",queue_length(q));

  queue_iterate(q, print_item, NULL, NULL);
  printf("dequeue started!\n");
  queue_dequeue(q,(void **)&ptr);
  assert(queue_length(q) == 0);
  assert(ptr != NULL);
  printf("dequeue finished! now queue length is: %d\n", queue_length(q));

  printf("\n\n multiple enqueue test start: \n");
  for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++){

    queue_enqueue(q, &data[i]);
    printf("enqueued %d items in total\n", i+1);

  }
  int size = sizeof(data) / sizeof(data[0]);
  assert(queue_length(q) == size);

  printf("multiple enqueue test case passed. All data in data[] has been enqueued the length of data[] is %d, the queue length is %d, data length matches!", size, queue_length(q));

  printf("\nnow we dequeue 1 item. The length before dequeue is %d \n dequeue started\n", queue_length(q));

  queue_dequeue(q,(void **)&ptr);
  assert(ptr != NULL);
  size = sizeof(data)/sizeof(data[0])-1;
  assert(queue_length(q) == size);

  printf("dequeue finished \nnow the length is %d, dequeue 1 item case pass \n", queue_length(q));
      printf("\n\n\n multiple dequeue test start: \n\n\n");
      printf("Before dequeue, now the length is %d, \n", queue_length(q));

  int length = queue_length(q);
   for (int i = 0; i < length; i++){
     struct Thread *temp;
    queue_dequeue(q, (void **)&temp);
    printf("dequeued %d items in totoal\n",i+1);

  }



  assert(queue_length(q)==0);

printf("now the length is %d, dequeue multiple item case pass \n", queue_length(q));



  printf("\n\n\n-------enqueue/dequeue test finished-------\n\n\n");


}


int main()
{
  //test_create();
  test_iterator();
  test_enqueueAndDequeue();


  printf("\nnow we dequeue 1 item. The length before dequeue is %d \n dequeue started\n", queue_length(q));

  queue_dequeue(q,(void **)&ptr);
  assert(ptr != NULL);
  size = sizeof(data)/sizeof(data[0])-1;
  assert(queue_length(q) == size);

  printf("dequeue finished \nnow the length is %d, dequeue 1 item case pass \n", queue_length(q));
      printf("\n\n\n multiple dequeue test start: \n\n\n");
      printf("Before dequeue, now the length is %d, \n", queue_length(q));

  int length = queue_length(q);
   for (int i = 0; i < length; i++){
     struct Thread *temp;
    queue_dequeue(q, (void **)&temp);
    printf("dequeued %d items in totoal\n",i+1);

  }



  assert(queue_length(q)==0);

printf("now the length is %d, dequeue multiple item case pass \n", queue_length(q));



  printf("\n\n\n-------enqueue/dequeue test finished-------\n\n\n");


}


int main()
{
  //test_create();
  test_iterator();
  test_enqueueAndDequeue();
ueue_delete(q, &data);
    //queue_delete(q, &data1);
    //b = queue_delete(q,&data1);
    a = queue_length(q);
    

   printf("ptr is %c\n",*ptr);
    printf("a is %d\n", a);
    
    printf("b is %d\n", b);
    //assert(ptr == &data);
}




static int inc_item(void *data, void *arg)
{
    int *a = (int*)data;
    int inc = (int)(long)arg;

    *a += inc;

    return 0;
}

//Callback function that finds a certain item according to its value 
static int find_item(void *data, void *arg)
{
    int *a = (int*)data;
    int match = (int)(long)arg;

    if (*a == match)
    {
        //printf("match\n");
        return 1;
    }

    return 0;
}

static int multiply(void *data, void *arg)
{
  int *a = (int*)data;
  int mul = (int)(long)arg;
  *a = *a * mul;
  return 0;
}

void test_iterator(void)
{
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    int *ptr;

    //Initialize the queue and enqueue items 
    q = queue_create();
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);

    // Add value '1' to every item of the queue 
    queue_iterate(q, inc_item, (void*)1, NULL);
    printf("data[0] is %d:\n",data[9]);
    assert(data[0] == 2);
    
    // Find and get the item which is equal to value '5' 
    ptr = NULL;
   int b = queue_iterate(q, find_item, (void*)6, (void**)&ptr);
    printf("ptr is %d:\n",*ptr);
    printf("b is %d:\n",b);
    assert(ptr != NULL);
    assert(*ptr == 6);
    assert(ptr == &data[4]);
   
    queue_iterate(q, multiply, (void*)3, NULL);
    printf("data[3] is %d:\n",data[3]);

}




 

 //#include <ucontext.h>

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

//#include <stdio.h>
//#include <stdlib.h>

#include <uthread.h>
/* #include <ucontext.h>;
in #include <ucontext.h>;(void* arg)
{
	uthread_yield();
	printf("thread%d\n", uthread_self());
	retu #include <ucontext.h>;rn 0;
}
 #include <ucontext.h>;
int thread2(void* arg)
{
	uthread_create(thread3, NULL);
	uthread_yield();
	printf("thread%d\n", uthread_self());
	return 0;
}

int thread1(void* arg)
{
	uthread_create(thread2, NULL);
	uthread_yield();
	printf("thread%d\n", uthread_self());
	uthread_yield();
	return 0;
}


int main(vo #include <ucontext.h>;id)
{
	uthread_join(uthread_create(thread1, NULL), NULL); #include <ucontext.h>;
 #include <ucontext.h>;
	return 0; #include <ucontext.h>;
}
*/
/*
int thread1(void* arg)
{
  printf("thread1\n");
  return 5;
}


int main(void)
{
    #include <ucontext.h>;
    #include <ucontext.h>;t tid;    
    #include <ucontext.h>;hread_create(thread1, NULL);    
    #include <ucontext.h>;join(tid, &ret);
    #include <ucontext.h>;thread1 returned %d\n", ret);
    #include <ucontext.h>;;
}*/ 

uthread_t tid[2];

int thread2(void* arg)
{int ret;printf("thread2\n");   
 uthread_join(tid[0], &ret);
 printf("thread1 returned %d\n", ret);
 return 2;}
 
 int thread1(void* arg)
 {   
    tid[1] = uthread_create(thread2, NULL);
    printf("thread1\n");
    return 1;}

int main(void)
{ 
  int ret;    
  tid[0] = uthread_create(thread1, NULL);    
  uthread_yield();    
  uthread_join(tid[1], &ret);printf("thread2 returned %d\n", ret);
  return 0;
}
