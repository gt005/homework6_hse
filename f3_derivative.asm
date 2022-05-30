section .rodata
a dq 4.0

section .text
global f3_derivative
f3_derivative:
    fld1
    fld qword[esp + 4]
    fmul qword[esp + 4]  ; x*x
    fld qword[a]
    fmul qword[esp + 4]
    fsubp st1, st0  ; x*x - 4x
    fadd qword[a]  ; x*x - 4x + 4
    fdivp st1, st0  ; 1 / (x*x - 4x + 4)
    ret