; ARM syscalls interfaces

; arch/ABI   instruction     syscall #   retval Notes
; --------------------------------------------------------------
; arm/OABI   svc NR          -           a1     NR is syscall #
; arm/EABI   svc 0x0         r7          r0

; arch/ABI      arg1  arg2  arg3  arg4  arg5  arg6  arg7  Notes
; ------------------------------------------------------------------
; arm/OABI      a1    a2    a3    a4    v1    v2    v3
; arm/EABI      r0    r1    r2    r3    r4    r5    r6

EABI_CALL   = 0x00

sys_exit    = 0x01   ; int error_code  -       -       -       -       kernel/exit.c:1046
sys_fork    = 0x02   ; struct pt_regs *        -       -       -       -       arch/alpha/kernel/entry.S:716
sys_read    = 0x03   ; unsigned int fd char __user *buf        size_t count    -       -       fs/read_write.c:391
sys_write   = 0x04   ; unsigned int fd const char __user *buf  size_t count    -       -       fs/read_write.c:408
sys_open    = 0x05   ; const char __user *filename     int flags       int mode        -       -       fs/open.c:900
sys_close   = 0x06   ; unsigned int fd -       -       -       -       fs/open.c:969
sys_waitpid = 0x07   ; pid_t pid       int __user *stat_addr   int options     -       -       kernel/exit.c:1771
sys_creat   = 0x08   ; const char __user *pathname     int mode        -       -       -       fs/open.c:933
sys_link    = 0x09   ; const char __user *oldname      const char __user *newname      -       -       -       fs/namei.c:2520
sys_unlink  = 0x0a   ; const char __user *pathname     -       -       -       -       fs/namei.c:2352

O_ACCMODE  = 0003o
O_RDONLY   = 0000o
O_WRONLY   = 0001o
O_RDWR     = 0002o
O_CREAT    = 0100o
O_EXCL     = 0200o
O_NOCTTY   = 0400o
O_TRUNC    = 1000o
O_APPEND   = 2000o
O_NONBLOCK = 4000o

S_ISUID    = 4000o
S_ISGID    = 2000o
S_ISVTX    = 1000o
S_IRUSR    = 0400o
S_IWUSR    = 0200o
S_IXUSR    = 0100o
S_IRGRP    = 0040o
S_IWGRP    = 0020o
S_IXGRP    = 0010o
S_IROTH    = 0004o
S_IWOTH    = 0002o
S_IXOTH    = 0001o

STDIN_FILENO  = 0
STDOUT_FILENO = 1
STDERR_FILENO = 2

EX_OK          = 0       ; successful termination

EX__BASE       = 64      ; base value for error messages

EX_USAGE       = 64      ; command line usage error
EX_DATAERR     = 65      ; data format error
EX_NOINPUT     = 66      ; cannot open input
EX_NOUSER      = 67      ; addressee unknown
EX_NOHOST      = 68      ; host name unknown
EX_UNAVAILABLE = 69      ; service unavailable
EX_SOFTWARE    = 70      ; internal software error
EX_OSERR       = 71      ; system error (e.g., can't fork)
EX_OSFILE      = 72      ; critical OS file missing
EX_CANTCREAT   = 73      ; can't create (user) output file
EX_IOERR       = 74      ; input/output error
EX_TEMPFAIL    = 75      ; temp failure; user is invited to retry
EX_PROTOCOL    = 76      ; remote error in protocol
EX_NOPERM      = 77      ; permission denied
EX_CONFIG      = 78      ; configuration error

EX__MAX        = 78      ; maximum listed value
 
