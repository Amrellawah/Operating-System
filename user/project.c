#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

struct proc_info {
  int pid;
  char name[16];
  char state[10];
  uint64 cputime;
  uint64 memusage;
  int exit_status;
};

#define MAX_PROC 64

int main(int argc, char *argv[]) {
  struct proc_info infos[MAX_PROC];
  int n = procinfo(infos, MAX_PROC);

  printf("\n%-5s %-16s %-10s %-9s %-14s %-12s\n", "PID", "Name", "State", "CPU Time", "Memory Usage", "Exit Status");
  printf("-------------------------------------------------------------------------------\n");
  for(int i = 0; i < n; i++) {
    printf("%-5d %-16s %-10s %-9lu %-14lu ", infos[i].pid, infos[i].name, infos[i].state, infos[i].cputime, infos[i].memusage);
    if(infos[i].exit_status != -1)
      printf("%-12d\n", infos[i].exit_status);
    else
      printf("%-12s\n", "-");
  }
  exit(0);
} 