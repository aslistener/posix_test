#include "functions.h"

static int g_count = 0;

static pthread_mutex_t user_mutex_;
static pthread_cond_t condition_;

/*
  ++g_count : 1, before fork
  ++count : 1, before fork
  g_count+1 : 2, parent fork
  count+1 : 2, parent fork
  g_count+2 : 3, child  fork
  count+2 : 3, child fork
  child_id : 7559, after fork
  child_id : 0, after fork
  child_id : 7559, after fork
  child_id : 0, after fork
根据执行结果， 猜测进程调用fork时，会把自己当前进程的PCB快照发送给系统，
然后继续执行；
系统据此开启一个新的进程，并且立即让它进入调度队列
也就是说，新进程的执行环境和上一个进程完全一样，并且只会执行 fork 以后的代码
*/


void test_fork(){
  int count = 0; 
  PRINT_VAL_MSG(++g_count, "before fork");
  PRINT_VAL_MSG(++count, "before fork");

  int child_id = fork();
  if(child_id == 0){
    PRINT_VAL_MSG(g_count+2, "child  fork");
    PRINT_VAL_MSG(count+2, "child fork");
  } else{
    PRINT_VAL_MSG(g_count+1, "parent fork");
    PRINT_VAL_MSG(count+1, "parent fork");
  }

  this_thread::sleep_for(2s);
  PRINT_VAL_MSG(child_id, "after fork");
  this_thread::sleep_for(2s);
  PRINT_VAL_MSG(child_id, "after fork");

}

static void* ReadFunction(void *data) {
  unsigned long id = *(unsigned long*)data;

  struct timespec tv;
  clock_gettime(CLOCK_MONOTONIC, &tv);
  tv.tv_sec += 20; // 设置20秒后没收到事件超时返回
  int rv = pthread_cond_timedwait(&condition_, &user_mutex_, &tv);
  printf("mutex owner: %ld, thread id %d\n", user_mutex_.__data.__owner, pthread_self());
  clock_gettime(CLOCK_MONOTONIC, &tv);
  printf("now time:%ld, current thread: %ld\n", tv.tv_nsec, id);
  pthread_mutex_unlock(&user_mutex_);
}

static void* BroadFunction(void *data) {
  unsigned long id= *(unsigned long*)data;
  sleep(2);
  printf("current thread: %ld\n", id);
  pthread_cond_broadcast(&condition_);
}

static void* SignalFunction(void *data) {
  unsigned long id = *(unsigned long*)data;

  for(int i = 0; i < 10; i++) {
    sleep(2);
    printf("current thread: %ld\n", id);
    pthread_cond_signal(&condition_);  
  }
}


void MutexTest() {
  g_count = 10;
  pthread_condattr_t attrs;
  pthread_mutex_init(&user_mutex_, NULL);
  auto rv = pthread_condattr_init(&attrs);
  pthread_condattr_setclock(&attrs, CLOCK_MONOTONIC);
  rv = pthread_cond_init(&condition_, &attrs);
  pthread_condattr_destroy(&attrs);

  pthread_attr_t attr;
  /* 为了兼容性，使用属性指明线程可被连接 */
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  pthread_t *tid = new pthread_t[g_count];
  
  int i1 = 1;
  pthread_create(&tid[0], &attr, SignalFunction, &tid[0]);

  // pthread_t tid[1];
  // pthread_create(&tid[1], &attr, BroadFunction, 1);

  int i = 2;
  for(; i < g_count; i++) {
    pthread_create(&tid[i], &attr, ReadFunction, &tid[i]);
  }

  for(int j = 2; j < g_count; j++) {
    pthread_join(tid[j], NULL);
  }

  pthread_join(tid[0], NULL);


  pthread_attr_destroy(&attr);
  pthread_cond_destroy(&condition_);
  pthread_mutex_destroy(&user_mutex_);
  pthread_exit(0);
}

