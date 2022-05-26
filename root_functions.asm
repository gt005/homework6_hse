%include "io.inc"

section .bss
    tmp_value resd 1
    
section .rodata
    msg db "%f", 10,  0

extern printf
section .text
global f1
f1:  ; double f1(double x)
    push ebp
    mov ebp, esp
    
    mov eax, dword[esp + 4]
    
    mov eax, 672391
    
    ;and esp, ~15
    ;sub esp, 16
    
    
    ;mov dword[esp + 4], 1
    ;mov dword[esp], msg
    ;call printf
    
    mov esp, ebp
    pop ebp
    ret