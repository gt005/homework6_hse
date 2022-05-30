%include "io.inc"

section .rodata
     number_2 dd 14
     number_14 dd 14
     const2 dd 2
     const3 dd 14


section .text
global f1
global f2
global f3
global f1_derivative
global f2_derivative
global f3_derivative
f1:  ; double f1(double x)
    FINIT
    fld1
    fld qword[esp+4]
    fyl2x ; log_2 (x)
       
    fldl2e ; log_2 (e)
    fdivp ST1, ST0   ;  log_e (x) = log_2 (x) / log_2 (e) 
    ret
    
f2:
    push ebp
    mov ebp, esp
    FINIT
    FLD qword[esp + 8] ; st0 = x
    FLDZ ; st0 = 1, ; st1 = x
    FADDP st1, st0 ; st0 = x + 1
    
    FLD dword[const2] ; st0 = 2, st1 = x + 1
    FSTP dword[const2]

    

    leave
    ret
    
    
    
    
f3:
    push ebp
    mov ebp, esp
    
    FLD qword[esp + 8] ; st0 = x
    FLD1 ; st0 = 1, ; st1 = x
    FADDP st1, st0 ; st0 = x + 1
    
    FLD dword[const2] ; st0 = 2, st1 = x + 1
    FMULP st1, st0 ; st0 = 2*(x + 1)
    
    FLD dword[const3] ; st0 = 3, st1 = 2*(x + 1)
    FDIVP st1, st0 ; st0 = 2*(x + 1)/3
    FCHS ; st0 = -2*(x + 1)/3

    leave
    ret
    
f1_derivative:
    FINIT
    FLD qword[esp+4]
    FSIN
    ret
    
f2_derivative:
    FINIT
    FLD qword[esp+4]
    FSIN
    ret
    
f3_derivative:
    FINIT
    FLD qword[esp+4]
    FSIN
    ret