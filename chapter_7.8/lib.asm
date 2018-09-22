segment .data     
msg	db 'Hello, world!',0xa   ;our dear string
len	equ	$ - msg          ;length of our dear string
base: 	dd 	1.0   
x: 	dd 	9.0  

segment .bss
    c: resd 4    ;the result ‒ length of side c
    
segment .text

;------------------------
;------------------------
global func_asm
func_asm:
push rbp
mov rbp, rsp

mov eax, esi
add eax, edi

pop rbp
RET
;-----------------------
;-----------------------
global call_func
call_func:
push rbp
mov rbp, rsp

mov rax, rdi
mov rdi, 777
mov si, 'q'
call rax

pop rbp
RET
;-----------------------
;-----------------------
extern _Z4testic
global call_func_2
call_func_2:

push rbp
mov rbp, rsp

mov edi, 12345
mov si, 'P'
call _Z4testic

pop rbp
RET
