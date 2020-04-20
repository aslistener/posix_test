#include "functions.h"

static int g_count = 0;

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