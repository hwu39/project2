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
