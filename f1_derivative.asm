section .text
global f1_derivative
f1_derivative:
    fld1
    fdiv qword[esp + 4]
    ret