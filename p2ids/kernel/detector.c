#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/init.h>
#include <linux/types.h>

//int user_pid;
//unsigned long *syscall_array;
//int pid_position;
//int log_switch;  

void setPID(long pid);
long getPID(void);
void sysarray_init(void);
unsigned long *get_sysarray(void);
void set_switch(int on_off);


void setPID(long pid)
{
  user_pid = pid;
}

long getPID(void)
{
  return user_pid;
}

void sysarray_init(void)
{
  syscall_array = (long*)kmalloc(sizeof(long), GFP_KERNEL);
  pid_position = 0;
}

unsigned long *get_sysarray(void)
{
  return syscall_array;
}

void set_switch(int on_off)
{
  log_switch = on_off;
}

