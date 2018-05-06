#include <stdio.h>
//#include <sys/type.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <sys/wait.h>

int read_line(char *buf);
unsigned long monitor(char *sys_calls, unsigned int id);

unsigned long monitor(char *sys_calls, unsigned int id)
{
  //for instance, system calls are O,R,M,W,C
  Int I;
  Unsigned int *sequence;
  for (i=o; i<sizeof(sys_calls); i++) {
    if (!strcmp(“some system call”,sys_calls[i])) {
      sequence[i] = 1;
    }
    else {
      Sequence[i] = 0;
    }
  }
  If (sequence_init(sequence, id) == -1) {
    sequence_detector(sequence,id);
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
  while (1) {
    char *token = malloc(sizeof(char)), *temp;
    int size = read_line(token);
    //tokenize string
    temp = strtok(token," ");
    int counter = 0;
    char *arg[size];
    while (temp != NULL) {
      arg[counter++] = temp;
      temp = strtok(NULL, " ");
    }

    if (size > 0) {
      if (pid < 0) {
	fprintf(stderr,"Fork Failed"); //an error has occurred
      }
      else if (pid == 0) {
	if (execvp(arg[0],arg) == -1) {
	  return 1;
	}
      }
    }
  }
  return 0;
}
