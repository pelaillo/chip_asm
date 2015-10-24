## chip_asm
###Assembly development for c.h.i.p. computer

The cheapest general purpose computing platform in the history of mankind is here. Let's prepare the terrain for the next billion people that could access the information revolution. And let's hope that many of them are going to be more than information consumers. The platform is not ready yet for that step. Until now, in order to work with current c.h.i.p., another computer is needed.

The c.h.i.p. computer is powered by an ARM Cortex A8 processor. There are many interesting features that hardware designers have devised. And assembly is the key to truly unleash them.

###Assembly, really?
Actually, assembly is living a renaissance thanks to the ubiquity of the ARM processor on the mobile space and on internet of things platforms. A passion in many ways similar to that of mid nineties for the x86 assembly.
The fact is that coding programs for ARM in assembly is easy. One click and your code turns into a tiny executable that simply runs. No need for virtual machines nor big, buggy libraries. Unless you want them. From assembly it is possible to use a library written on any language, any functionality proportioned by the operating system and take advantage of the whole hardware potential. But, what's the catch?
There is a steep learning curve. You need to know the way the machine works, the different instruction sets, the calling conventions, the way to access memory and a lot of other interesting niceties.
I think that the best way to climb that stair is a hands-on approach. Starting from a simple working program and build upon it. I am just tarting to climb and this is my journey's logbook.

###Where to start?
There is a Debian based buildroot that is ready to be flashed to the c.h.i.p. The instructions are in Next Thing website. It's important to learn also how to connect to the c.h.i.p. via ssh or usb cable.
My assembler of choice is the Flat Assembler (FASM), freeware and open source. There is a version of fasm that targets ARM, but the assembler needs an x86-compatible computer to run. Get it on http://arm.flatassembler.net. It is very simple to setup either in windows or in linux and it behaves the same on every platform. For our purposes, it will no matter in which platform do you work. The only condition is that you are already able to connect to the c.h.i.p. console.
Write the following on your text editor of choice and save it:

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
Then compile it with fasm:`fasmarm hello.asm`
Now there is a new file called *hello*. It's an executable file that won't run on your computer because it's composed of ARM instructions. The executable file needs to be copied to the c.h.i.p. from your computer via scp, sshftp or similar.
Once in the c.h.i.p. console, pointing to the folder where the file resides, you need to give the file execution permission and run it. If you call it `./hello`, it will greet you back.
```
# chmod 777 hello
# hello
Hello world
#
``` 
There is no need for anything else. No libraries, no dependecies, no complications. It's a native file ready to run on your ARM platform.

Very well. It was easy but, what does it mean all these cryptic stuff? How does it work?

Let's dissect that example one bit at a time here [Dissecting hello example](https://github.com/pelaillo/chip_asm/tree/master/hello)

Or, let's continue with a nontrivial example here [Working with bitmaps](https://github.com/pelaillo/chip_asm/tree/master/bmper)
