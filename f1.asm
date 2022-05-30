section .text
global f1
f1:
    fld1
    fld qword[esp+4]
    fyl2x ; log_2 (x)
       
    fldl2e ; log_2 (e)
    fdivp ST1, ST0   ;  log_e (x) = log_2 (x) / log_2 (e) 
    ret
