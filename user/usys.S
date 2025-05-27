.global procinfo
procinfo:
  li a7, SYS_procinfo
  ecall
  ret 