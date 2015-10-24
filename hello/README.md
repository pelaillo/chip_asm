## Hello world from chip_asm
###Assembly development for c.h.i.p. computer

This example is mandatory to respect tradition. It's not very useful per se but once you run it succesfully for the first time, there is a burst of satisfaction that never fades away no matter how many times and in how many devices you have seen it working.

Don't underestimate the hello example neither. There is a lot in there in order to have this silicon hearted machine welcoming you.

####Linux
We are not programming bare metal. We instead are using the Linux operating system kernel services in order to print several characters on screen and then exiting gracefully to the console. Being more precise, we are using the Embedded Application Binary Interface or EABI in order to pass parameters to several system calls. And we are using the standard names and conventions found on the Linux kernel sources. The assembler will convert those values into binary information for the processor.
```asm
EABI_CALL     = 0x00
EX_OK         = 0x00
STDOUT_FILENO = 0x01
sys_exit      = 0x01
sys_write     = 0x04
```

####ELF executable
We are instructing the assembler to produce an ELF executable. This is a binary format that follows an standard which is understood by the operating system. The Linux console will load the different segments in memory and then it will set the execution pointer to the memory position pointed by `start`, but only if the segment `executable` permission flag is set.
```asm
        format ELF executable
        entry start

        segment readable executable
```

####ARM Cortex-A8
Once the operating system pass the execution to our program start, the processor will interpret and execute the instructions, one by one. Those instructions are stored as a sequence of higher and lower voltages that enter on the processor gates (transistors) and according to the layout of the processor, a new set of higher and lower voltages will change the memory contents or the status of peripherals connected to the processor.
For simplicity, we call `1` to the higher voltage and `0` to the lower one. As there are only two values, the system ys called binary. Every binary computer works in that way. The difference is in the layout of the gates inside.
The layout of the c.h.i.p. processor is called ARM Cortex-A8. It is an evolution of a RISC machine designed several years ago. RISC stands by Reduced Instruction Set Computer but it have grown so that the "reduced" is hardly applicable. However, it is a lot simpler than the x86 architecture.
The other advantage that helped it to gain the popularity it has now is the lower energy compsumption, permitting ARM designs to rule on battery powered mobile devices.
There are only 3 ARM instructions in use for carry on our task: `mov`, `add` and `svc`. Those instructions operate using the information hold on registers `r0`, `r1`, `r2` and `r7`. Registers are physical holders of binary information inside the processor. Our program get encoded by the assembler into binary instructions following ARM conventions as understood by the processor. Here, the encoded values are presented as hexadecimal numbers because if presented as binary numbers will take a lot of space, will mean the same thing and will not make any sense as these ones. Don't worry, they are to be read by the processor, not by humans.
```asm
start:  mov     r0, STDOUT_FILENO	; 0100A0E3
        add     r1, pc, hello-$-8	; 14108FE2
        mov     r2, hello.len		; 0C20A0E3
	mov     r7, sys_write		; 0470A0E3
	svc     EABI_CALL		; 000000EF
	mov     r0, EX_OK		; 0000A0E3
	mov     r7, sys_exit		; 0170A0E3
	svc     EABI_CALL		; 000000EF
```
####Data
The main information exchange of the processor has to do with accessing RAM (Random Access Memory). This memory holds the instructions that are going to be executed. RAM also holds the data that is going to be consulted and modified in order to perform some task.
In our simple example, the data is stored together with the code, after the instruction that returns the execution to the operating system (`sys_exit`). That way, the processor will not try to interpret our data as a sequence of valid instructions, as they are not.
Our data is a two word phrase encoded in ASCII character codes. ASCII (American Standard Code for Information Interchange) is a code that assign a two digit hexadecimal number to each character, to the space between words and for the new line return.
```asm
hello:  db      'Hello world',10        ; 48656C6C6F 20 776F726C64 0A
     .len = $-hello
```

[Return home](https://github.com/pelaillo/chip_asm)
