#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/init.h>

extern long user_pid;
extern unsigned long *syscall_array;
extern int pid_position;
extern int log_switch;  

void setPID(long pid);
long getPID(void);
void sysarray_init(void);
unsigned long *get_sysarray(void);
void set_switch(void);


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
}

unsigned long get_sysarray(void)
{
  return syscall_array;
}

void set_switch(int onoff)
{
  log_switch = onoff;
}
