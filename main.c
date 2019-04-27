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
*/
/*
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

*/


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

    /* Initialize the queue and enqueue items */
    q = queue_create();
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



int main()
{
  //test_create();
  test_iterator();
}
