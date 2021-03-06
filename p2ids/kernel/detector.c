#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/types.h>
#include <asm/uaccess.h>

//int user_pid;
//unsigned long *syscall_array;
//int pid_position;
//int log_switch;  
/*
void setPID(long pid);
long getPID(void);
void sysarray_init(void);
unsigned long *get_sysarray(void);
void set_switch(int on_off);
*/

DEFINE_MUTEX(lock);

asmlinkage void setPID(int pid)
{
  mutex_lock(&lock);
  user_pid = pid;
  mutex_unlock(&lock);
}

asmlinkage int getPID(void)
{
  return user_pid;
}

asmlinkage void sysarray_init(void)
{
  mutex_lock(&lock);
  syscall_array = (unsigned long*)kmalloc(sizeof(unsigned long), GFP_KERNEL);
  pid_position = 0;
  mutex_unlock(&lock);
}

asmlinkage unsigned long *get_sysarray(unsigned long *syscall_buffer, int window_size)
{
  int i;
  unsigned long res;
  //shrink array down to window_size
  unsigned long *temp_array[window_size];
  
  mutex_lock(&lock);
  
  //get last block of system calls in array according to window size
  for (i = 0; i < window_size; i++) {
    temp_array[0] = syscall_array[pid_position - window_size + i];
  }
  res = copy_to_user(syscall_buffer, temp_array, sizeof(unsigned long));
  mutex_unlock(&lock);
  return syscall_array;
}

asmlinkage void set_switch(int on_off)
{
  mutex_lock(&lock);
  log_switch = on_off;
  mutex_unlock(&lock);
}

asmlinkage int num_syscalls(void)
{
  return pid_position;
}
