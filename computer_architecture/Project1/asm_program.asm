; Author:     Ryan Florida
; Course:     CSCI 3130
; Assignment: OLA1
; Date:       1/20/2017

; Make main global.
global main

; Look externally to find DisplayHaiku function definition.
extern DisplayHaiku

segment .text
; Declare main.
main:
	mov  rdi, haiku   ; Move haiku into rdi.
	call DisplayHaiku ; Call DisplayHaiku function (external).
	ret               ; return.

segment .data
; Write haiku
haiku db "Quaternionic Haiku, by Ryan Florida", 10, "The quaternion.", 10, "Imaginary vector,", 10, "with real part scalar." 
