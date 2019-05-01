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
For *queue_create*, we set up and allocate memory for the queue 
and return it; for *queue_destroy*, we free the **queue**;
for *queue_enqueue*, we create a newNode to store the 
address of data, let **back**'s **next** points to it, make it
new **back**, and increment the **length**; for *queue_dequeue*,
we make current **front**'s next to be the new **front** and 
disconnect current **front** from the queue; for *queue_delete*, 
we iterate through the queue until the targeted node is found as 
cursor pointed node's next, then disconnect it from queue by 
connect the cursor pointed node to the targeted node's **next**;
for *queue_iterate*, we iterate through the queue and keep calling
the function that is passed into the function; for *queue_length*,
we return the length stored in the struct **queue**.


reference: suggestions given by tutor Bendam.

Phase Two
   In this Phase, the main goal is creating treads and make them can be
runned,be joined,and be exited. 
   First, we create a **struct** to simulate a TCB and global value to 
hold *currentRunningThread* .
   For creating tread,we divide it into two parts. The first part is 
creating a main tread when tid equal to 0. In this part, we use *queue_create()*
creating three **queue** for holding the threads whose states are *ready*, 
*block*,and *zombie*. Next step, we change its state to be *running* and 
make it to be current running thread.finally, increasing the tid. The second 
part is creating normal thread when tid > 0. In this part, we use some functions
inside **context.c**.For example, we use *uthread_ctx_alloc_stack()* to allcocate 
memory to stack pointer.and use *uthread_ctx_init()* to initialize the context 
inside the thread.Next, we set the thread to be *ready* and use *queue_enqueue* 
to put the thread inside the *ready queue*. Finally, increase the tid and return
it.





