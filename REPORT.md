#Introduction

In this project, students' goal is to study and research the 
development and implementation of *User-level thread library*
under supervision and guidance of professor, Joel Porquet.

##Processing

Phase One
    
In this Phase, the main goal is to implement a simple FIFO
queue according to the API documentation in *queue.h*. 
We implemented the queue with the idea of *linked-list* 
and two *structs* (The struct **node** contains a pointer
points to the data that needs to be stored and a pointer
points to **next**; the struct **queue** stores the **length**
of the queue, and nodes **front** and **back** of the queue). 

1. For *queue_create*, we set up and allocate memory for the queue 
and return it; for *queue_destroy*, we free the **queue**;

2. For *queue_enqueue*, we create a newNode to store the 
address of data, let **back**'s **next** points to it, make it
new **back**, and increment the **length**; for *queue_dequeue*,
we make current **front**'s next to be the new **front** and 
disconnect current **front** from the queue;

3. For *queue_delete*, we iterate through the queue until the targeted node is found as 
cursor pointed node's next, then disconnect it from queue by 
connect the cursor pointed node to the targeted node's **next**;

4. For *queue_iterate*, we iterate through the queue and keep calling
the function that is passed into the function; for *queue_length*,
we return the length stored in the struct **queue**.


reference: suggestions given by tutor Brendan Gerrity.

Phase Two
   
   In this Phase, the goal is creating treads and make them can be
runned,be joined,and be exited. 
1. We create a **struct** to simulate a TCB and global value to 
hold *currentRunningThread* .
   
2. For creating tread,we divide it into two parts. The first part is 
creating a main tread when tid equal to 0. In this part, we use *queue_create()*
creating three **queue** for holding the threads whose states are *ready*, 
*block*,and *zombie*. Next step, we change its state to be *running* and 
make it to be *currentRunningThread*.Finally, increasing the tid. The second 
part is creating normal thread when tid > 0. In this part, we use some functions
inside **context.c**.For example, we use *uthread_ctx_alloc_stack()* to allcocate 
memory to stack pointer.and use *uthread_ctx_init()* to initialize the context 
inside the thread. Next, we set the thread to be *ready* and use *queue_enqueue* 
to put the thread inside the *ready queue*. Finally, increase the tid and return
it.
  
3. In the second part of this phase, we use **uthread_yield()** to make the 
thread which in the *ready queue* to be runned.In this part, we use
*strcut *Thread from* to hold the *currentRunningThread* which is *enqueue* into
*ready queue*. On the other hand, we use *struct *Thread to* to hold the address 
of the thread which is *dequeue* from *ready queue*. After that, we use function
*uthread_ctx_switch()* to make */to/* become *currentRunningThread*. (*swapcontext()*
inside *uthread_ctx_switch()* has this function.)

4. The main goal of this phase is testing if implementing **uthread_yield()** and 
**uthread_create()** correctly, so in the **uthread_join()**, we just use a 
infinite loop to check the length of *ready queue*. If it is 0, we break the loop.
Otherwise, we *yield* it. Inside the **uthread_exit()**, it also simple. We just
enqueue *currentRuningThread* into *zombie queue* and *yield* it and change its 
state to be *zombie*.


Phase Three
   
In this phase, we have to implement a thread can join another thread. 

1. In first step,we create a new function named **find_item()** and use *queue_iterate()* 
to find the tid of child thread if is inside the *ready queue*,*block queue*,and 
*zombie queue*.If the child is inside the *ready queue* or *block queue*, we 
use a new valuable in the **struct** named *parent* to hold the tid of parent thread. 
After that, we change the the state of parent(here is *currentRunningThread*) to be 
block and  *enqueue* into the *block queue*. Next, we use *dequeue* to take out the 
child thread from *ready queue* or *block queue* and make it to be *currentRunningThread*.
We use a new valuable in **struct** name *child* to hold the tid of the child.Finally, we
use *uthread_ctx_switch()* to be running. 

2. When the child thread is dead, we unblock the parent thread. We do this inside 
the **uthread_exit()**. First, we use a new valuable in **struct** named 
*returnValue* the hold the *retval*. Next, we use *queue_iterate()* 
check if the parent thread inside the *block queue*. If it exist, we use 
*queue_delete()*to delete it in the *block queue* and change its state to be *raady* 
and *enqueue* it to the *ready queue*. Inside **uthread_exit()**, we also need to 
change the state of child thread(here is *currentRunningThread*) to be *zombie* and 
*enqueue* it into *zombie queue*.Finally, we use *yield()* to next 
thread inside the *ready queue* to be runned. 

3. When the parent thread which is inside the *ready queue* is running again. It will
collect the child thread. In this part, we use *queue_iterate()* to check the tid 
of child thread if in the *zombie queue*. If it is yes, we use *queue_delete()* to 
delete it inside the *zombie queue* and use *uthread_ctx_destroy_stack()* free it.
Finally, the parent thread get the return value of dead child.

4. In the the case of the child thread is already dead when the parent thread joins the child
The parent thread have to collect the child thread right away. The process is similar with 
*point 3*.


reference: suggestions given by tutor Brendan Gerrity, Sean Young, Shadi Othman.
