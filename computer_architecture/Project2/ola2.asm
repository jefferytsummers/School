;;Name: 	    Ryan Florida
;;Project: 	  OLA2
;;Instructor: Dr. Phillips
;;Description:
;	1. Create a function which takes four 64-bit integer arguments (eg. W, X, Y, Z).
;		Your function should compute (W * X) - (Y * Z), and leave the result in RAX when it returns.
;		Your function should accept the four arguments using appropriate conventions (see registers listed in the lecture slides).
;		Your function should NOT print anything - it should ONLY perform the math, and return the result.
;	2. Use a loop to compute the above function over an array of size 16 (A[0], A[1], ..., A[15])
;		Declare an array (in memory) containing 16 reasonable 64-bit integer values (of your choosing).
;		Use a loop to iterate over the elements of the array, and use your function (above) to calculate the value of every four consecutive array values.
;		For example, rax = (A[0] * A[1]) - (A[2] * A[3]), then rax = (A[1] * A[2]) - (A[3] * A[4]), etc.
;		For each iteration, print out the calculation, the result, and start a newline (exactly like this): (5 * 2) - (3 * 4) = -2
;		The last iteration should compute rax = (A[12] * A[13]) - (A[14] * A[15]) ... (i.e. don't calculate past the end of the array!)

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
	strf	db	"%s", 0
	intf	db	"%ld", 0
	nwl     db	10, 0

	;my 16 element array
	a	dq	75,54,75,48,94,54,46,66,28,55,32,95

;******************************************************************************

segment	.text

	main:

		mov 	rcx , 0	;for count 9 times, start from 0,
		jmp	loop


	loop:

		cmp	rcx, 72		;72 = 9 times * 8 bytes, everytime add 8 bytes, execute 9 times
		je	exit		;when it already excuted 9 times, then quit
		mov  	r8,  [a+rcx]
		mov	r9,  [a+rcx+8]
		mov 	r10, [a+rcx+16]
		mov	r11, [a+rcx+24]
		push	rcx
		push    r8
		push    r9
		push    r10
		push    r11
		call	print_the_expression ;print the front part of the expression
	;	pop 	rcx
	;	push 	rcx
		call	compute_numbers	;compute  the answer
	;	pop 	rcx
	;	push	rcx
		call	print_answer	;print the answer out
		pop	r11
		pop	r10
		pop	r9
		pop	r8
		pop	rcx
		add	rcx, 8  ;update the loop condition
		jmp	loop
	
;print the part of expression before the answer
	print_the_expression:

		push	leftp
		call 	print_str
		pop 	rax
		push	r8
		call	print_int
		pop	rax
	
		push	mulstr
		call	print_str
		pop	rax
		push	r9
		call	print_int
		pop	rax

		push	rightp
		call 	print_str
		pop	rax
		push	substr
		call 	print_str
		pop 	rax
		push	leftp
		call 	print_str
		pop 	rax
		push	r10
		call	print_int
		pop	rax


		push	mulstr
		call	print_str
		pop	rax
	

		push	r11
		call	print_int
		pop	rax
		push	rightp
		call 	print_str
		pop 	rax
		push	eqlstr
		call	print_str
		pop	rax
		ret

	;compute the four numbers for the answer
	compute_numbers:

		sub	r8,  r9
		sub 	r10, r11
		add 	r10, r8
		;-------------------------------------------------
		;;leave the result in rax
		mov	rax, r10
		ret
	
	;print out the answer
	print_answer:

		push	rax
		call	print_int
		pop	rax
		call	print_nwl

		ret

	;print out the every single string
	print_str:
		mov	rdi, strf
		mov	rsi, [rsp+8]
		mov	al, 0
		call 	printf
		ret

	;print out the every integer
	print_int:
		mov	rdi, intf
		mov	rsi, [rsp+8]
		mov	al, 0
		call 	printf
		ret
	
	;move on to the new line
	print_nwl:
		mov	rdi, nwl
		mov	al, 0
		call	printf
		ret
	
	;exit this program
	exit:
        	mov    	 eax, 60
        	mov   	 rdi, 0
        	syscall
