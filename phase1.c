#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

struct queue {
	/* TODO Phase 1 */
	void *data;
	int length;
	struct queue *front;
	struct queue *back;
//	struct queue *next; 
};



queue_t queue_create(void)
{
	/* TODO Phase 1 */
	
		
	struct queue *head = (struct queue*)malloc(sizeof(struct queue));
	head->front=NULL;
	head->back=NULL;
	head->next=NULL;
	head->data=NULL;
	head->length=0;
	return head;	
}

int queue_destroy(queue_t queue)
{
	/* TODO Phase 1 */

}

int queue_enqueue(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	struct queue *newNode = (struct queue*)malloc(sizeof(struct queue));
	if(newNode == NULL){
		return -1;
	}
	if(queue->length == 0){
		
	}
	newNode->data = data;
	queue->front;
	newNode->length = queue->length+1;
	queue->back = newNode;
	
}

int queue_dequeue(queue_t queue, void **data)
{
	/* TODO Phase 1 */
}

int queue_delete(queue_t queue, void *data)
{
	/* TODO Phase 1 */
	int length=queue->length;
	struct queue *head=queue->front;
	for(int i=0;i<length;i++){
		if(head==NULL || head->data=NULL){
			return -1;
		}
		if(head->data=data){
			free(head->data);
			head->data=NULL;
		}
	}
	return 0;
}

int queue_iterate(queue_t queue, queue_func_t func, void *arg, void **data)
{
	/* TODO Phase 1 */
	struct queue *head=queue->front;
	while(head!=NULL){
		int test=func(head->data,arg);
		if(test==-1){
			*data = head;
			return -1;
		}
		if(head->next!=NULL){
			head=head->next;
		}
	}
	return 0;
	
}

int queue_length(queue_t queue)
{
	/* TODO Phase 1 */
	return queue->length;
}
