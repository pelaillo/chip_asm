        format ELF executable
        entry start

include 'arm_sys.inc'
include 'gdi.inc'

        segment readable executable

start:
        pop     {r6}      ; argument count, first arg
        mov     r2,#0
        pop     {r1}      ; first argument is command invocation
        mov     r3,r1
;        adr     r0,p_cmdline
;        str     r1,[r0]
  parse_command:
        add     r2,r2,#1
        ldrb    r0,[r3],#1
        add     r3,r3,#1
        cmp     r0,#0
        bne     parse_command

        mov     r7,sys_write
        mov     r0,STDOUT_FILENO
;        ldr     r1,[p_cmdline]
        svc     EABI_CALL
        b       salta
        sub     r6,#1
        ble     no_command

        mov     r7,sys_write
        mov     r0,STDOUT_FILENO
        pop     {r1}
        ;mov     r1,r5
        ;add     r1,pc,cmd-$-8
        mov     r2,cmd.len
        svc     EABI_CALL
        ;pop     {r6}
        cmp     r6,#0
        bne     parse_command
  no_command:
        mov     r7,sys_open
        ldr     r0,[p_file_in]
        mov     r1,O_CREAT
        mov     r2,O_RDWR
        svc     EABI_CALL
        mov     r7,sys_write
        ldr     r1,[p_help]   ; add     r1,pc,help-$-8
        mov     r2,help.len
        svc     EABI_CALL
  salta:
        mov     r7,sys_write
        mov     r0,STDOUT_FILENO
        ldr     r1,[p_help]   ; add     r1,pc,help-$-8
        mov     r2,help.len
        svc     EABI_CALL
        mov     r7,sys_exit
        mov     r0,6
        svc     EABI_CALL

p_help  dw      help
p_file_in  dw   file_out

file_in  db     'chip.bmp',0
file_out db     'chip_bn.bmp',0

help    db 'bmper [option] [input_file] [output_file]',10,10
        db 'Simple command line tool to manipulate bitmap files',10
        db '  Valid options:',10
        db '  -g   Converts an input bitmap file to grayscale',10
        db '  -i   Prints bitmap information',10
    .len=$-help

        segment readable writable

p_cmdline       dw 0
