section .text
global f1
global f2
global f3
global f1_derivative
global f2_derivative
global f3_derivative
f1:  ; double f1(double x)
    FINIT
    FLD qword[esp+4]
    FSIN
    ret
    
f2:
    FINIT
    FLD qword[esp+4]
    FSIN
    ret
    
f3:
    FINIT
    FLD qword[esp+4]
    FSIN
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