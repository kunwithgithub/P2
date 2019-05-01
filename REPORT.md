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
and return it; 
2. For *queue_destroy*, we free the **queue**;
3. For *queue_enqueue*, we create a newNode to store the 
address of data, let **back**'s **next** points to it, make it
new **back**, and increment the **length**;
4. For *queue_dequeue*, we make current **front**'s next to be 
the new **front** and disconnect current **front** from the queue;
5. For *queue_delete*, we iterate through the queue until the
targeted node is found as cursor pointed node's next, then 
disconnect it from queue by connect the cursor pointed node to 
the targeted node's **next**;
6. For *queue_iterate*, we iterate through the queue and keep calling
the function that is passed into the function; for *queue_length*,
we return the length stored in the struct **queue**.

reference: suggestions given by tutor Bendam.
