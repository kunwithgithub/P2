#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "queue.h"

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

// Callback function that finds a certain item according to its value */
/*
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
    printf("\n\n\n----literator test start----\n");
    queue_t q;
    int data[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int i;
    int *ptr;

    //Initialize the queue and enqueue items 
    q = queue_create();
    printf("queue created!\n");
    for (i = 0; i < sizeof(data) / sizeof(data[0]); i++)
        queue_enqueue(q, &data[i]);
   printf("-----------------------------------\n");
   printf("Test the print function\n");
   queue_iterate(q, print_item, NULL,NULL);


    //Add value '1' to every item of the queue 
    printf("-----------------------------------\n");
    printf("Test the incrment funtion by two\n");
    printf("Before incremnt:\n");
    queue_iterate(q, print_item, NULL,NULL);
    queue_iterate(q, inc_item, (void*)2, NULL);
    printf("After incremnt:\n");
    queue_iterate(q, print_item, NULL,NULL);
    printf("the first item is :%d\n",data[0]);
    assert(data[0] == 3);
    printf("the second item is :%d\n",data[1]);
    assert(data[1] == 4);
    printf("the third item is %d\n",data[2]);
    assert(data[2] == 5);
    printf("the first three cases is pass!\n");
    
    //Find and get the item which is equal to value '5' 
    printf("-----------------------------------\n");
    printf("Test the find item funtion\n");
    ptr = NULL;
    queue_iterate(q, find_item, (void*)6, (void**)&ptr);
    printf("Find the number equal %d\n",*ptr);
    assert(*ptr == 6);
    assert(ptr == &data[3]);
    printf("pass!\n");
    queue_iterate(q, find_item, (void*)7, (void**)&ptr);
    printf("Find the number equal %d\n",*ptr);
    assert(*ptr == 7);
    assert(ptr == &data[4]);
    printf("pass!\n");
    queue_iterate(q, find_item, (void*)8, (void**)&ptr);
    printf("Find the number equal %d\n",*ptr);
    assert(*ptr == 8);
    assert(ptr == &data[5]);
    printf("pass!\n");
    printf("-----------------------------------\n");
    printf("Test the multiply by 3 funtion\n");
    printf("Before multiply:\n");
    queue_iterate(q, print_item, NULL,NULL);
    printf("After multiply:\n");
    queue_iterate(q, multiply, (void*)3, NULL);
    queue_iterate(q, print_item, NULL,NULL);
    printf("the first item is %d:\n",data[0]);
    assert(data[0] == 9);
    printf("pass!\n");
    printf("the four item is %d:\n",data[3]);
    assert(data[3] == 18);
    printf("pass!\n");

    printf("-----------------------------------\n");
    printf("Test delete\n");
    printf("Test the third item\n");
    queue_delete(q, &data[2]);
    queue_iterate(q, print_item, NULL,NULL);


    printf("---------finish testing---------\n");


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

  printf("\nnow we dequeue 1 item. The length before dequeue is %d \ndequeue started\n", queue_length(q));



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

  printf("\n");
  
  printf("Test destroy\n");
  int a = queue_destroy(q);
  assert(a == 0);
  printf("pass!\n");
   

  printf("\n\n\n-------enqueue/dequeue test finished-------\n\n\n");


}
