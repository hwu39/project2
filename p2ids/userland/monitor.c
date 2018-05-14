#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>
#include <linux/kernel.h>
#include <sys/syscall.h>

#define __NR_setPID 333
#define __NR_getPID 334
#define __NR_sysarray_init 335
#define __NR_get_sysarray 336
#define __NR_set_switch 337
#define __NR_num_syscalls 338

/*
int user_pid;
unsigned long *syscall_array;
int pid_position;
int log_switch;
*/

int read_line(char *buf);
unsigned long monitor(char *sys_calls, unsigned int id);
unsigned long sequence_init(unsigned int *sequence, unsigned int id);

/*
typedef struct sequence {
  unsigned int seq;
  unsigned int id;
} sequence;

sequence **buffer; //buffer array to store all system calls


unsigned long sequence_init(unsigned int *syscall_sequence, unsigned int id)
{
  if (buffer  == NULL) {
    buffer[0] = malloc(10 * sizeof(syscall_sequence));
    buffer[0]->id = id;
    buffer[0]->seq = syscall_sequence;
  }
  else {
    return -1;
  }
}

unsigned long monitor(char *sys_calls, unsigned int id)
{
  //for instance, system calls are O,R,M,W,C
  int i;
  unsigned int *syscall;
  for (i=0; i<sizeof(sys_calls); i++) {
    if (!strcmp(syscall,sys_calls[i])) {
      buffer[i] = 1;
    }
    else {
      buffer[i] = 0;
    }
  }
  if (sequence_init(syscall, id) == -1) {
    //sequence_detector(syscall,id);
  }
}
*/
int read_line(char *buf)
{
  int i,j;
  i = 0;
  do {
    j = fgetc(stdin);
    if (j == '\n' || j == EOF) {
      return i;
    }
    else {
      buf[i] = j;
      i++;
    }
  }while (1);
  return i;
}

int main(int argc, char *argv[])
{
  pid_t pid;
  printf("IDS\n");
  int u_pid;
  while (1) {
    const char *ps[2];
    ps[0] = "ps";
    ps[1] = NULL;

    pid = fork();
    if (pid == 0) {
      execvp(ps[0],ps);
    }
    else {
      pid = wait(NULL);
    }
    int user_pid;
    int sw;
    
    printf("Press 1 to start tracking system calls\n");    
    scanf("%d",&sw);
    while (sw != 1) {
      printf("Please enter a valid choice.\n");
      scanf("%d",&sw);
    }
    printf("Enter the PID you want to track\n");
    syscall(__NR_set_switch,sw);
    scanf("%d",&user_pid);
    syscall(__NR_setPID,user_pid);
    u_pid = syscall(__NR_getPID);
    printf("The pid you are tracking: %d\n",u_pid);
    while  (sw == 1) {
      printf ("Press 1 to continue tracking, 0 to stop\n");
      
      scanf("%d",&sw);
      syscall(__NR_set_switch,sw);
    }

    int window_size;
    printf("Enter a window size for capturing system calls\n");
    
    scanf("%d",&window_size);
    unsigned long *syscall_array = malloc(sizeof(unsigned long));
    long int sys = syscall(__NR_get_sysarray, syscall_array, window_size);

    //once kernel array obtained, compare system calls
    int hamming_distance = 0;
    unsigned long temp_array[window_size/4];
    int j;
    for (j = 0; j < window_size; j++) {
      if (j > 0 && j < window_size/4) {
	temp_array[j] = syscall_array[j];
      }
      else if (j >= window_size/4 && j < window_size) {
	char val = temp_array[j] ^ syscall_array[j];
	while (val) {
	  ++hamming_distance;
	  val &= val - 1;
	}
      }
    }

    if (hamming_distance == 0) {
      printf("Excellent Condition\n");
    }
    else if (hamming_distance > 0 || hamming_distance <= 10) {
      printf("Acceptable Condition\n");
    }
    else {
      printf("Process is under attack\n");
    }
  }
  return 0;
}
