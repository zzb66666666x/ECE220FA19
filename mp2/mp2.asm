; Assuming user will only enter ' ' 0-9 *+/-
; Result can be either negative or positive
;
;INTRO
;This is the complete version of mp2 with the challenge problems solved.
;The code will first read the input, ie. the expression and store the expression in memory with nice format.
;After that, the EVALUATE will check the expression and call the subroutines(PLUS, DIVIDE, MULTIPLY, MINUS) to calculate the result.
;After getting the right value into the R6, the program will then try to print the result using the subroutine PRINT. 
;This was achieved by using the alogorithm: 1. Check sign of result and print "-".
;2. The divide the result by 10 for several times and store the remainders, these remainders can separate numbers like 256 into 2, 5 and 6.
;3. For each digit, add the offset "0" and print them out.

;Registers table.
;R0: stores the input and output for subroutines and the I/O devices.
;R1: pointers of current address of expression from x5000
;R2: flexible usage
;R3: flexible usage
;R4: flexible usage/provide previous number to DECODE to realize the function in challenges.
;R5: flags about failure or success
;R6: store the final result

.ORIG x3000

; your main program should be just a few calls to subroutines, e.g.,
LD R1,START_ADDR
JSR INPUT
JSR EVALUATE
JSR PRINT

START_ADDR	.FILL x5000
HALT


;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; get input from the keyboard and store it in memory per MP2 specifications
; input: R1 - starting address of the memory to store the expression string
; output: input from the keyboard stored in memory starting from the address passed in R1
INPUT
;The expression will be stored in the memory with the first address of x5000 which will be used by the DECODE.
;The R1 stores the beginning address and R0 will be used for reading values from keyboard.
;After getting values form keyboard, it will call the DECODE subroutine for checking and storing.
;R1: pointer of memory beginning at x5000
;R2: flexible
;R3: flexible
;R4: exchange value with DECODE(contains the previous input)
;R5: flags about whether the expression comes to an end
;R6: flexible
;R7: need to saved for using other subroutines
	ST R7,INPUT_SAVE_R7
INPUT_LOOP
	GETC	
	OUT
	LD R4,PRE_VALUE	;Provide the value of input of last time to the DECODE subroutine.
	JSR DECODE	
	ST R4,PRE_VALUE	;Update the value for R4, i.e. the number which was stored last time.
	ADD R5,R5,#-1
	BRn INPUT_LOOP
	LD R7,INPUT_SAVE_R7
	RET
PRE_VALUE	.FILL xFFE0
INPUT_SAVE_R7	.BLKW 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; find the real value of operand, or keep the 2's complement ASCII value if operator
; input: R0 holds the input
; output: R0
; This subroutine takes the value of the input and check for what to store in the memory.
; The challenge of detecting invalid input: 
; 	Two conditions for checking the invalid input: the input is greater than 9 or lower than 0.
;	In the first condition, the input must be invalid. In the second condition, the input can also be operators, so I make further check.
;The challenge of writing a number like 34 into memory can be solved as follows:
;	If previous input is SPACE: Everything normal.
;	If the previous value is a number, then move back the pointer and restore the 10*pre_value + new_input.
;R1: pointer(begins at x5000)
;R2: flexible
;R3: flexible
;R4: exchange values with INPUT
;R5: flags about whether the expression finishes.
;R6: flexible
DECODE
; add your code from Lab 3 here
; Remember to clear the registers.
; Remember to save R7
	ST R7,DECODE_SAVE_R7	
	AND R5,R5,#0
	AND R2,R2,#0
	AND R3,R3,#0	
	LD R2,NEWLINE
	ADD R2,R0,R2
	BRz DECODE_NEWLINE	;Detect the end of the expression.
	LD R2,SPACE
	ADD R2,R0,R2
	BRz SKIP		;Detect a space which should be ignored.
	LD R2,ZERO
	LD R3,NINE		;Check the range of integers.
	ADD R2,R0,R2
	BRn IS_OPERATOR		;Check if the input is an operator.
	ADD R3,R0,R3
	BRp INVALID		;Detect illegal input.
	BRnzp ST_DIGIT
IS_OPERATOR
	LD R2,NEG_PLUS		;Check the kind of operators.
	ADD R2,R0,R2
	BRz ST_OP
	LD R2,NEG_MINUS
	ADD R2,R0,R2
	BRz ST_OP
	LD R2,NEG_MULTIPLY
	ADD R2,R0,R2
	BRz ST_OP
	LD R2,NEG_DIVIDE
	ADD R2,R0,R2
	BRz ST_OP
	BRnzp INVALID	
ST_DIGIT
	LD R2,ZERO		;Change from ASCII to number.
	ADD R0,R0,R2
	LD R2,SPACE
	NOT R2,R2
	ADD R2,R2,#1
	ADD R2,R4,R2		;If the previous input is a SPACE, then minus x0020 will be in R4.
	BRp DIGITS		;Check R4 to determine whether the user's input is a continuous number.
	STR R0,R1,#0		;Decriment the pointer to restore the value.
	AND R4,R4,#0
	ADD R4,R0,R4
	ADD R1,R1,#1
	BRnzp DECODE_DONE
DIGITS				;Various digits like 34,1001,256,etc..
	LD R2,TEN
LOOP_10	ADD R0,R0,R4
	ADD R2,R2,#-1
	BRp LOOP_10
	ADD R1,R1,#-1		;Point back and change the value stored before.
	STR R0,R1,#0
	ADD R1,R1,#1		;Increment the memory pointer.
	AND R4,R4,#0
	ADD R4,R4,R0
	BRnzp DECODE_DONE	
ST_OP
	NOT R0,R0		;Store the operators.
	ADD R0,R0,#1
	STR R0,R1,#0
	ADD R1,R1,#1
	BRnzp DECODE_DONE
SKIP				;Detect a space getting keyed in.
	AND R4,R4,#0	
	ADD R4,R4,R0		;Now minus x0020(a space) in R0.
	NOT R4,R4
	ADD R4,R4,#1
	BRnzp DECODE_DONE
DECODE_NEWLINE			;Finish the decoding process.
	ADD R5,R5,#1
	NOT R0,R0
	ADD R0,R0,#1
	STR R0,R1,#0
	ADD R1,R1,#1
	BRnzp DECODE_DONE
INVALID				;Invalid things like "q",".","#","=",etc..
	LD R0,POS_NEWLINE
	OUT
	LEA R0,ErrorMsg
	PUTS
	HALT	
DECODE_DONE
	LD R7,DECODE_SAVE_R7	
	RET
NEWLINE		.FILL xFFF6
;NEWLINE	.FILL xFFF3
POS_NEWLINE	.FILL x000A
;POS_NEWLINE	.FILL x000D
SPACE		.FILL xFFE0
ZERO		.FILL xFFD0
NINE		.FILL xFFC7
TEN		.FILL #10
DECODE_SAVE_R7	.BLKW 1
ErrorMsg	.STRINGZ "Error invalid input"
NEG_PLUS	.FILL xFFD5
NEG_MINUS	.FILL xFFD3
NEG_MULTIPLY	.FILL xFFD6
NEG_DIVIDE	.FILL xFFD1

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Print value stored in register R0 in decimal format
; input: R0 - holds the input
; output: signed decimal value printed on the display
; This subroutine prints the calculation result stored in R6.
; I will first check the sign of the result and determine whether to print "-".
; Then I will print the value using the following algorithm:
; 	For example, 34/10 can give the remainder 4 and the quotient is 3.
;	Then, 3/10 gives the remainder 3.
;	By printing the remainders, I get the 34.
;R0: I/O
;R1: remainder from DIVIDE
;R2: flexible
;R3 and R4: oprands for DIVIDE
;R5: flags about stack error
;R6: calculation result

PRINT
; This subroutine is to print the calculation result.
; add your code here
; We get the result in R6
	ST R7,PRINT_SAVE_R7
	AND R0,R0,#0
	AND R1,R1,#0
	AND R2,R2,#0
	AND R3,R3,#0
	AND R4,R4,#0
	AND R5,R5,#0
	ADD R6,R6,#0
	BRn PRINT_NEG
	ADD R3,R6,R3		;The calculation result is now in R3(eg. 253). It's also the value to be divided by 10.
	BRnzp PRINT_LOOP
PRINT_NEG			;Print out the "-" and inverse the value, then everything is the same with positive numbers.
	LD R0,POS_MINUS
	OUT
	AND R0,R0,#0
	NOT R3,R6
	ADD R3,R3,#1
PRINT_LOOP			;Implementing the "divide by 10" algorithm
	LD R4,TEN	
	JSR DIVIDE	
	AND R3,R3,#0	
	ADD R3,R0,R3
	AND R0,R0,#0
	ADD R0,R0,R1		;The remainder should be pushed in the stack.
	JSR PUSH
	ADD R5,R5,#0
	BRp StackError
	AND R0,R0,#0
	AND R1,R1,#0
	ADD R3,R3,#0
	BRp PRINT_LOOP		;Begin to print out the values from stack.	
	AND R3,R3,#0
	AND R1,R1,#0
	LD R3,STACK_TOP
	ADD R3,R3,#1
	LD R2,STACK_START
	NOT R2,R2
	ADD R2,R2,#1
DISPLAY	AND R1,R1,#0	
	LDR R0,R3,#0
	LD R1,POS_ZERO		;Change the number values into ASCII values.
	ADD R0,R0,R1
	OUT
	ADD R3,R3,#1
	ADD R1,R3,R2
	BRnz DISPLAY
	;This is the end.
	LD R7,PRINT_SAVE_R7
	RET

PRINT_SAVE_R7	.BLKW 1 
POS_ZERO	.FILL x0030
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; input: R1 - start address of the expression string
; output: R0 - the numerical value of the end result
; This subroutine calculate the result and determine whether the calculation task has been finished.
; This subroutine first reads value from memory(begin at x5000) and check the value to determine whether it's time to PUSH, POP or execute the calculation.
;R0: return value of subroutines including POP, PLUS, etc..
;R1: pointer
;R2: flexible
;R3: flexible/oprands
;R4: flexible/oprands
;R5: check for stack error
;R6: result
;R7: PC value for RET
EVALUATE
; your code goes here
; This code check the elements of your expression and calls your other subroutines like push, pop, etc. which is like a controller.
	AND R2,R2,#0
	AND R6,R6,#0
	ST R7,EVALUATE_SAVE_R7
READ_MEM			;Read the expression.
	LD R1,EVALUATE_SAVE_R1
	AND R0,R0,#0
	AND R3,R3,#0
	AND R4,R4,#0
	AND R5,R5,#0
	LDR R2,R1,#0		;Read value from the address stored in R1.
	ADD R1,R1,#1		;Increment the pointer for next memory location.
	ST R1,EVALUATE_SAVE_R1	;Now we need to reuse the R1 to save the remainder from DIVIDE.
	AND R1,R1,#0
	LD R3,POS_NEWLINE
	ADD R3,R2,R3
	BRz EVALUATE_DONE
	ADD R2,R2,#0
	BRn FindOperator
	ADD R0,R0,R2		;Else, I find an operand to push.
	JSR PUSH
	ADD R5,R5,#0
	BRp StackError		;Stack error occurs.
	BRnzp READ_MEM
EVALUATE_DONE			;Check if the stack has only one value.
	LD R3,STACK_START 	;x4000
	LD R4,STACK_TOP		;should be x3FFF
	NOT R3,R3
	ADD R3,R3,#1
	ADD R3,R4,R3
	ADD R3,R3,#1
	BRnp StackError
	JSR POP
	ADD R5,R5,#0
	BRp StackError
	ADD R6,R6,R0
	LD R7,EVALUATE_SAVE_R7
	RET
FindOperator			;Locate the right calculation subroutine.
	AND R3,R3,#0
	AND R4,R4,#0
	JSR POP			;R5 will be cleaned by POP
	ADD R5,R5,#0
	BRp StackError
	ADD R4,R4,R0		;R4 contains the second oprand.
	JSR POP 
	ADD R5,R5,#0
	BRp StackError
	ADD R3,R3,R0		;R3 contains the first oprand.
	AND R5,R5,#0
	AND R0,R0,#0		;Clear R0 for receiving the result.
	LD R5,POS_PLUS
	ADD R5,R2,R5
	BRz GOPLUS
	LD R5,POS_MINUS
	ADD R5,R2,R5
	BRz GOMINUS
	LD R5,POS_MULTIPLY
	ADD R5,R2,R5
	BRz GOMULTIPLY
	LD R5,POS_DIVIDE
	ADD R5,R2,R5
	BRz GODIVIDE
	;For safety, I added another branch.	
	BRnzp PUSH_RESULT
GOPLUS				;Go to use the subroutine called PLUS.
	JSR PLUS
	BRnzp PUSH_RESULT
GOMINUS
	JSR MINUS
	BRnzp PUSH_RESULT
GOMULTIPLY
	JSR MULTIPLY
	BRnzp PUSH_RESULT
GODIVIDE
	JSR DIVIDE
	BRnzp PUSH_RESULT
PUSH_RESULT
	JSR PUSH		;Push the result into stack.
	ADD R5,R5,#0
	BRp StackError
	BRnzp READ_MEM		;Read next memory.
StackError
	LEA R0,StackErrorMsg
	PUTS
	HALT
	
NEG_TEN		.FILL xFFF6
POS_PLUS	.FILL x002B
POS_MINUS	.FILL x002D
POS_MULTIPLY	.FILL x002A
POS_DIVIDE	.FILL x002F
EVALUATE_SAVE_R1	.FILL x5000
EVALUATE_SAVE_R7	.BLKW 1
StackErrorMsg	.STRINGZ "Invalid Expression"
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; input: R3, R4
; out: R0
PLUS	
; your code goes here
	ADD R0,R3,R4;
	RET
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; input: R3, R4
; out: R0
MINUS	
; your code goes here
	NOT R4,R4
	ADD R4,R4,#1
	ADD R0,R3,R4
	RET
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; input: R3, R4
; out: R0 = R3 x R4
MULTIPLY	
; Two negative values will make the value also negative.
; In this subroutine, I first check the number of negative values in the input registers.
; 	If there is only one negative value in the input, I will output the inverse of the R0.
;	Two negative inputs won't change the result.
; In this algorithm, R5 will function like a flag to denote the number of negative inputs.
; your code goes here
	ST R5,MULTIPLY_SAVE_R5
	AND R5,R5,#0
	ADD R5,R5,#1
	ADD R3,R3,#0
	BRn MUL_NEGATION_R3	;Find negative value input in R3
MUL_CHECK_R4
	ADD R4,R4,#0
	BRn MUL_NEGATION_R4	;Find negative value input in R4
MULTIPLY_LOOP
	ADD R0,R0,R3
	ADD R4,R4,#-1
	BRp MULTIPLY_LOOP
	ADD R5,R5,#0
	BRn MUL_NEGATION_RESULT	;R5 = -1. It means that the output should be a negative value.
MULTIPLY_OUT
	LD R5,MULTIPLY_SAVE_R5	;Restore the R5
	RET	

MUL_NEGATION_R3
	NOT R3,R3
	ADD R3,R3,#1
	NOT R5,R5
	ADD R5,R5,#1
	BRnzp MUL_CHECK_R4	
MUL_NEGATION_R4
	NOT R4,R4
	ADD R4,R4,#1
	NOT R5,R5
	ADD R5,R5,#1
	BRnzp MULTIPLY_LOOP
MUL_NEGATION_RESULT
	NOT R0,R0
	ADD R0,R0,#1
	BRnzp MULTIPLY_OUT	
MULTIPLY_SAVE_R5	.BLKW 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; input: R3, R4
; out: R0 - quotient (R0 = R3 / R4), R1 - remainder 
DIVIDE
; your code goes here
; This subroutine can be reused to help you to print out the result.
; This subroutine will check the negative and positive condition of the input and modify the result
; If the value in R4 is 0, that will be a mathmatical mistake which will lead to invalid expression.
	ST R5,DIVIDE_SAVE_R5	;Value of R5 can determine the sign of the output.
	ADD R4,R4,#0
	BRz StackError
	AND R5,R5,#0
	ADD R5,R5,#1		;R5 > 0: the quotient should be positive. R5 < 0: the quotient should be negative.
	ADD R3,R3,#0
	BRn DIV_NEGATION_R3
DIV_CHECK_R4
	ADD R4,R4,#0
	BRn DIV_NEGATION_R4
DIVIDE_PREPARE
	AND R1,R1,#0
	ADD R1,R4,R1		;Save the positive R4 for now.	
	NOT R4,R4
	ADD R4,R4,#1
DIVIDE_LOOP
	ADD R0,R0,#1
	ADD R3,R3,R4
	BRzp DIVIDE_LOOP
	ADD R0,R0,#-1
	ADD R5,R5,#0
	BRn DIV_NEGATION_RESULT
DIVIDE_OUT
	ADD R1,R3,R1		;Save the remainder into R1 by taking R3(minus value)+R1
	LD R5,DIVIDE_SAVE_R5
	RET

DIV_NEGATION_R3
	NOT R5,R5
	ADD R5,R5,#1
	NOT R3,R3 
	ADD R3,R3,#1
	BRnzp	DIV_CHECK_R4
DIV_NEGATION_R4
	NOT R5,R5
	ADD R5,R5,#1
	NOT R4,R4 
	ADD R4,R4,#1
	BRnzp	DIVIDE_PREPARE
DIV_NEGATION_RESULT
	NOT R0,R0 
	ADD R0,R0,#1
	BRnzp	DIVIDE_OUT
DIVIDE_SAVE_R5	.BLKW 1
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; stack subroutines - do not modify

; PUSH subroutine
; IN: R0
; OUT: R5 (0-success, 1-fail/overflow)
; registers used: R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	; save R3
	ST R4, PUSH_SaveR4	; save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACk_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		; stack is full
	STR R0, R4, #0		; no overflow, store value in the stack
	ADD R4, R4, #-1		; move top of the stack
	ST R4, STACK_TOP	; store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET

PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;


; POP subroutine
; OUT: R0, R5 (0-success, 1-fail/underflow)
; registers used: R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	; save R3
	ST R4, POP_SaveR4	; save R3
	AND R5, R5, #0		; clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP	;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP	;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3	;
	LD R4, POP_SaveR4	;
	RET

POP_SaveR3	.BLKW #1	;
POP_SaveR4	.BLKW #1	;

STACK_END	.FILL x3FF0	;
STACK_START	.FILL x4000	;
STACK_TOP	.FILL x4000	;


.END
