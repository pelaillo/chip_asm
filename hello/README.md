## Hello world from chip_asm
###Assembly development for c.h.i.p. computer

This is the typical programming book first example, mandatory to respect tradition. It's not very useful per se but once you run it succesfully for the first time, there is a burst of satisfaction that never fades away no matter how many times and in how many devices you have seen it working.

Don't underestimate the hello example neither. There is a lot in there in order to have this silicon hearted machine welcoming you.

###Linux
We are not programming bare metal. We instead are using the Linux operating system kernel services in order to print several characters on screen and then exiting gracefully to the console. Being more precise, we are using the Embedded Application Binary Interface or EABI in order to pass parameters to several system calls. And we are using the standard names and conventions found on the Linux kernel sources.

###ELF executable
We are instructing the assembler to produce an ELF executable. This is a binary format that follows an standard which is understood by the operating system. Linux will load the different segments it in memory and then it will set the execution pointer to the memory position pointed by `start` but only if the segment `executable` permission flag is set.

###ARM Cortex-A8
Once the operating system pass the execution to our program start, the processor will interpret and execute the instructions, one by one. Those instructions are stored as a sequence of higher and lower voltages that enter on the processor gates (transistors) and according to the layout of the processor, a new set of higher and lower voltages will change the memory contents or the status of peripherals connected to the processor.
For simplicity, we call `1` to the higher voltage and `0` to the lower one. As there are only two values, the system ys called binary. Every binary computer works in that way. The difference is in the layout of the gates inside.
The layout of the c.h.i.p. processor is called ARM Cortex-A8

#####*hello.asm*
```asm
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
```

Or, let's continue with a nontrivial example here [Working with bitmaps](https://github.com/pelaillo/chip_asm/README.md)
