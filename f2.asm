section .rodata
a dq 2.0
b dq 14.0

section .text
global f2
f2:
    FLD qword[esp+4]
    FMUL qword[a]
    FCHS
    FADD qword[b]
    ret
