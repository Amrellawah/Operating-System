struct proc_info {
  int pid;
  char name[16];
  char state[10];
  uint64 cputime;
  uint64 memusage;
  int exit_status;
};

int
procinfo(struct proc_info *uinfo, int max)
{
  struct proc *p;
  int count = 0;

  for(p = proc; p < &proc[NPROC] && count < max; p++){
    acquire(&p->lock);
    if(p->state != UNUSED){
      struct proc_info kinfo;
      kinfo.pid = p->pid;
      safestrcpy(kinfo.name, p->name, sizeof(kinfo.name));
      switch(p->state){
        case SLEEPING: safestrcpy(kinfo.state, "SLEEPING", sizeof(kinfo.state)); break;
        case RUNNABLE: safestrcpy(kinfo.state, "RUNNABLE", sizeof(kinfo.state)); break;
        case RUNNING:  safestrcpy(kinfo.state, "RUNNING",  sizeof(kinfo.state)); break;
        case ZOMBIE:   safestrcpy(kinfo.state, "ZOMBIE",   sizeof(kinfo.state)); break;
        default:       safestrcpy(kinfo.state, "OTHER",    sizeof(kinfo.state)); break;
      }
      kinfo.cputime = p->cputime;
      kinfo.memusage = p->sz;
      kinfo.exit_status = (p->state == ZOMBIE) ? p->xstate : -1;

      if(copyout(myproc()->pagetable, (uint64)&uinfo[count], (char*)&kinfo, sizeof(kinfo)) < 0){
        release(&p->lock);
        break;
      }
      count++;
    }
    release(&p->lock);
  }
  return count;
} 