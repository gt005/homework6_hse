section .rodata
a dq -2.0

section .text
global f2_derivative
f2_derivative:
    FLD qword[a]
    ret