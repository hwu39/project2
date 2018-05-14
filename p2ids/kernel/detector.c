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

asmlinkage unsigned long *get_sysarray(unsigned long *syscall_buffer, int size)
{
  mutex_lock(&lock);

  mutex_unlock(&lock);
  return syscall_array;
}

asmlinkage void set_switch(int on_off)
{
  mutex_lock(&lock);
  log_switch = on_off;
  mutex_unlock(&lock);
}

asmlinkage void num_syscalls(void)
{
  return pid_position;
}
