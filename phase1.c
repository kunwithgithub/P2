#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

struct node {
  void *data;
  struct node *next;

};

struct queue {
	/* TODO Phase 1 */
	int length;
	struct node *front;
	struct node *back;

};



queue_t queue_create(void)
{
	/* TODO Phase 1 */
  struct queue *myQueue = (struct queue*)malloc(sizeof(struct queue));
	myQueue->front = NULL;
  myQueue->back = NULL;
	myQueue->length = 0;
	return myQueue;	
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */
  if(queue == NULL){
    return -1;
  }

  struct node *currentNode = queue->front;

  while(queue->front != NULL)
  {
    queue->front = queue->front->next;
    free(currentNode);
  }
  
  queue->front = NULL;
  queue->back = NULL;
  queue->length = 0;
  return 0;
}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
  struct node *newNode = (struct node*)malloc(sizeof(struct node));
  if(data == NULL||queue == NULL||newNode == NULL){
    return -1;
  }
	
  newNode->data = data;
  newNode->next = NULL;
  if(queue->length == 0){
      queue->front = newNode;
      queue->back = newNode;
      queue->length++;
      return 0;
  }
  queue->back->next = newNode;
  queue->back = newNode;
  queue->length++;
	
  return 0;
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
  if(queue->length == 0 || queue == NULL || queue->front->data == NULL){
    return -1;
  }
  struct node *frontNode = queue->front;
  queue->front = queue->front->next;
  *data = frontNode->data;
  frontNode = NULL;
  queue->length--;

  return 0;
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	int length = queue->length;
  if(queue->length == 0||queue == NULL|| data == NULL){
    return -1;
  }
	struct node *head = queue->front;
  
  if(head->data == data){
    queue->front = head->next;
    free(head);
    head = NULL;
    queue->length--;
    return 0;
    
  }
	
  for(int i=1;i<length;i++){
		if(head->next->data == data){
      struct node *willbedelete = head->next;
      head->next = head->next->next;
      free(willbedelete);
      willbedelete = NULL;
      queue->length--; 
      return 0;
    }

		
    head = head->next;
    
  }

   
	return -1;

}

int queue_iterate(queue_t queue, queue_func_t func, void *arg, void **data)
{
	/* TODO Phase 1 */
	struct node *head=queue->front;
  if(queue == NULL || func == NULL)
  {
    return -1;
  }
	//while(head!=NULL){
    while(head != NULL)
    {
		  int test=func(head->data,arg);
		
    if(test==1){
			*data = head->data;
			return 0;
		}
		
    //if(head->next!=NULL){
		//	head=head->next;
		//}
    head = head ->next;
	}
	
  return 0;

	
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
	return queue->length;
}
