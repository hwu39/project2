#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>

int user_pid;
unsigned long *syscall_array;
int pid_position;
int log_switch;

int read_line(char *buf);
unsigned long monitor(char *sys_calls, unsigned int id);
unsigned long sequence_init(unsigned int *sequence, unsigned int id);

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
  log_switch = 0;
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
    int u_pid;
    int sw;
    printf("Enter the PID you want to track\n");
    if (log_switch == 1) {
      printf("To switch off IDS, press 0\n");
      scanf("%d",&sw);
      log_switch = sw;
    }
    else if(log_switch == 0) {
      printf("To switch on IDS, press 0\n");
      scanf("%d",&sw);
      log_switch = sw;
    }
    if (log_switch == 1) {
      scanf("%d",&u_pid);
    }
  }
  return 0;
}
