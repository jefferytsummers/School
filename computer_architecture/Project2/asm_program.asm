;;Name: 	     Ryan Florida
;;Project: 	   OLA2
;;Instructor:  Dr. Phillips
;;Description: This program will compute the difference of the products of
;;             elements in an array of length 16. After this computation has
;;             been carried out, the original equation, as well as the result,
;;             will be displayed to the screen via standard output.

;******************************************************************************

global main
extern printf
;******************************************************************************

segment .data

	leftp   db	" ( ", 0
	rightp	db	" ) ", 0
	eqlstr	db	" = ", 0
	substr	db	" - ", 0
	mulstr	db	" * ", 0
	strf	  db	"%s", 0
	intf	  db	"%ld", 0
	nline   db	10,0

	;my 16 elements array
	a	dq	0,1,1,2,3,5,8,13,21,34,55,89,144,233,377,610

;******************************************************************************

segment	.text

	main:

		mov 	rcx , 0	;Initialize count to 0.
		jmp	  loop


	loop:

		cmp	  rcx, 104
;Exit loop after 13 iterations.
		pop     rax
		je	  exit
		push    rcx
		mov  	rdi, [a+rcx]
		mov	  rsi, [a+rcx+8]
		mov 	rcx, [a+rcx+16]
		mov	  rdx,  [a+rcx+24]
	;	push	rcx
;Print rhs of the equation.
		call	printRHS
	;	pop 	rcx
	;	push 	rcx
		mov  	rdi, [a+rcx]
		mov	  rsi, [a+rcx+8]
		mov 	rcx, [a+rcx+16]
		mov	  rdx,  [a+rcx+24]
    ;Perform arithmetic.
		call	compute_numbers
	;	pop 	rcx
	;	push	rcx
    ;Print lhs of the equation.
		call	printLHS
		pop	  rcx
    ;Update the loop counter.
		add	  rcx, 8
		jmp	  loop

;Print the right hand side of the equation.
	printRHS:

    ;Push contents of all registers onto the stack.
		push    rdx
		push	  rcx
		push    rsi
		push    rdi

    ;First left parenthesis.
		push	  leftp
		call 	  print_str
		pop 	  rax

    ;Print first operand.
		call	  print_int

    ;Print first operator.
		push	  mulstr
		call	  print_str
		pop	    rax

    ;Print second operand.
		pop     r9
		pop     r14
		push    r9
		push    r14
		call  	print_int
		pop     r9
		pop     r14
		pop     rbx
		push    r9
		push    r14
		push    rbx

    ;First right parenthesis.
		push  	rightp
		call  	print_str
		pop    	rax

    ;Print second operator.
		push  	substr
		call  	print_str
		pop   	rax

    ;Second left parenthesis.
		push  	leftp
		call  	print_str
		pop   	rax

    ;Print third operand.
		call  	print_int

    ;Print third operator.
		push  	mulstr
		call  	print_str
		pop   	rax

    ;Print fourth operand.
		pop     rbx
		pop     r14
		pop     r9
		pop     r8
		push    r14
		push    r9
		push    rbx
		push    r8
		call  	print_int

    ;Second right parenthesis.
		push  	rightp
		call  	print_str
		pop   	rax

    ;Equal string.
		push  	eqlstr
		call  	print_str
		pop   	rax

    ;Take clutter out of stack.
		pop     r8
		pop     rbx
		pop     r9
		pop     r14

		ret

	;Carry out computation, store result in RAX.
	compute_numbers:
		push    rdx
		push    rcx
		push    rsi
		push    rdi

		pop     rax
		pop     r14
		mul     r14
		mov     rbx, rax
		pop     rax
		pop     r15
		mul     r15
 		mov     r14, rax
		sub   	rbx, r14
		mov   	rax, rbx
		ret

	;Print left hand side of the equation.
	printLHS:

		push	  rax
		call	  print_int
		pop	    rax
		call  	print_nline

		ret

	;Prints strings.
	print_str:
		mov   	rdi, strf
		mov   	rsi, [rsp+8]
		mov   	al, 0
		call   	printf
		ret

	;Print integers.
	print_int:
		mov   	rdi, intf
		mov   	rsi, [rsp+8]
		mov   	al, 0
		call   	printf
		ret

	;Prints a new line.
	print_nline:
		mov	    rdi, nline
		mov	    al, 0
		call  	printf
		ret

	;Exit program.
	exit:
    mov  	  eax, 60
    mov   	rdi, 0
    syscall
