section .rodata
a dq 2.0
b dq 6.0

section .text
global f3
f3:
    fld1
    fld qword[a]
    fsub qword[esp + 4]
    fdivp st1, st0
    fadd qword[b]
    ret
