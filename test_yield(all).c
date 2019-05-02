int thread3(void* arg)
{
	uthread_yield();
	printf("thread%d\n", uthread_self());
	return 0;
}

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

void test1()
{
	uthread_join(uthread_create(thread1, NULL), NULL); 
	//return 0;
}



int thread4(void* arg)
{
  printf("thread4\n");
  return 5;
}

void test2()
{
   int ret1;
   uthread_t tid1;    
   tid1 = uthread_create(thread4, NULL);    
   uthread_join(tid1, &ret1);
   printf("thread4 returned %d\n", ret1);
}


uthread_t tid[2];

int thread6(void* arg)
{int ret;printf("thread6\n");   
 uthread_join(tid[0], &ret);
 printf("thread5 returned %d\n", ret);
 return 2;}
 
 int thread5(void* arg)
 {   
    tid[1] = uthread_create(thread6, NULL);
    printf("thread5\n");
    return 1;}

void test3()
{ 
  int ret;    
  tid[0] = uthread_create(thread5, NULL);    
  uthread_yield();    
  uthread_join(tid[1], &ret);
  printf("thread6 returned %d\n", ret);
  
}

int main()
{ 
  //test1();
 // test2();
  test3();
}
