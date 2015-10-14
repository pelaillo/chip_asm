        format ELF executable
        entry start

EABI_CALL     = 0x00
EX_OK         = 0x00
STDOUT_FILENO = 0x01
sys_exit      = 0x01
sys_write     = 0x04

        segment readable executable

start:  mov     r0, STDOUT_FILENO
        add     r1, pc, hello-$-8
        mov     r2, hello.len
        mov     r7, sys_write
        svc     EABI_CALL
        mov     r0, EX_OK
        mov     r7, sys_exit
        svc     EABI_CALL

hello:  db      'Hello world',10
     .len = $-hello
