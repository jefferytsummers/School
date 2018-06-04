; Author:     Ryan Florida
; Course:     CSCI 3130
; Assignment: OLA1
; Date:       1/20/2017

;Make DisplayHaiku function global.
global DisplayHaiku

segment .text
;Define DisplayHaiku function.
DisplayHaiku:
	mov rsi, rdi ; Move string address to rsi.
	mov rax, 1   ; write
	mov rdi, 1   ; stdout
	mov rdx, 93  ; length of haiku.
	syscall	     ; call kernel
	ret	     ; back to C
