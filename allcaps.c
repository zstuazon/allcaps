@ hardware to the assembler
	.arch armv6
	.cpu cortex-a53
	.syntax unified

@ external functions
	.extern putchar
	.global main

@ Define constants
	.equ EXIT_SUCCESS, 0	@ success return from main
	.equ EOF, -1
	.equ FP_OFFSET, 4	@ fp offset in stack frame
	.equ UC_A, 0x41		@ upper case A
	.equ UC_Z, 0x5A		@ upper case Z
	.equ lc_a, 0x61
	.equ lc_z, 0x7a
	.equ NULL, 0x0		@ '\0'

@Define data segment where you will define your string
	.section .rodata	@start of read-only literals
mesg:	.asciz "1234567890 !!! ?///"

	.text
	.type	main, %function

main:
	stmfd	sp!,{r0-r4, fp, lr}	
	
	mov 	r1, 0		@ initialize counter
	ldr	r2, =mesg
	ldrb	r0, [r2]	@ get next char in the string
	cmp 	r0, NULL	@ if end of string then done
	beq	done
loop1:
	cmp	r0, lc_a	@ compare to lowercase a
	blt	next		@ if below upper-case A, skip char
	cmp	r0, lc_z	@ compare to lowercase z
	bgt	next
	add	r0, r0, UC_A-lc_a

next:
	stmfd	sp!, {r2}
	bl	putchar
	ldmfd	sp!, {r2}

	add	r2, r2, 1	@ increment char index
	ldrb	r0, [r2]	@ Get next character in the string
	cmp	r0, NULL	@ Checks if we are at end of string
	bne	loop1		@ If not, we get next character
done:	
	
	mov 	r0, EXIT_SUCCESS
	ldmfd	sp!, {r0-r4, fp, pc}
.end
