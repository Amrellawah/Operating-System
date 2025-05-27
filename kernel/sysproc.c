uint64
sys_procinfo(void)
{
  uint64 uaddr;
  int max;
  argaddr(0, &uaddr);
  argint(1, &max);
  return procinfo((struct proc_info*)uaddr, max);
} 