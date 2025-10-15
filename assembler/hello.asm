;; hello.asm

section .data
	msg db "hello, world!"

section .text
	global _start



_start:
	;; write syscall
	mov rax, 1 

	;; 1 is stdout
	mov rdi, 1
	mov rsi, msg
	;; len of msg
	mov rdx, 13

	syscall

	;; exit

	mov rax, 60
	mov rdi, 0
	syscall