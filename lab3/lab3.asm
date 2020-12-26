; Assuming user will only enter ' ' 0-9 *+/-
;
;
;
.ORIG x3000
; Your code goes here    
INPUT
	LD R1,START_ADDR
INPUT_LOOP
	GETC	
	OUT
	JSR DECODE	
	ADD R5,R5,#-1
	BRn INPUT_LOOP   
HALT
START_ADDR	.FILL x5000       
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; Subroutine: DECODE
; input: R0 holds the input
; output: R0 holds numerical value or negation of the ascii value
;   find the numerical value of if input is an operand, 
;   or find the negation of the ascii value if the input is an operator

DECODE
; Your code goes here
; Remember to clear the registers.
; Remember to save R7	
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
;The challenge of writing a number like 34 into memory can be solved as follows:
;If previous input is SPACE: Everything normal.
;If the previous value is a number, then move back the pointer and restore the 10*pre_value + new_input.
ST_DIGIT
	LD R2,ZERO	;Change from ASCII to number.
	ADD R0,R0,R2	
	STR R0,R1,#0	
	ADD R1,R1,#1
	BRnzp DECODE_DONE	
ST_OP
	NOT R0,R0	;Store the operators.
	ADD R0,R0,#1
	STR R0,R1,#0
	ADD R1,R1,#1
	BRnzp DECODE_DONE
SKIP			;Detect a space getting keyed in.
	BRnzp DECODE_DONE
DECODE_NEWLINE		;Finish the decoding process.
	ADD R5,R5,#1
	NOT R0,R0
	ADD R0,R0,#1
	STR R0,R1,#0
	ADD R1,R1,#1
	BRnzp DECODE_DONE
INVALID			;Invalid things like "q",".","#","=",etc..
	LD R0,POS_NEWLINE
	OUT
	LEA R0,ErrorMsg
	PUTS
	HALT	
DECODE_DONE
	RET
NEWLINE		.FILL xFFF6		;lc3sim
;NEWLINE	.FILL xFFF3		;lc3sim-tk
POS_NEWLINE	.FILL x000A		;lc3sim
;POS_NEWLINE	.FILL x000D		;lc3sim-tk
SPACE		.FILL xFFE0
ZERO		.FILL xFFD0
NINE		.FILL xFFC7
ErrorMsg	.STRINGZ "Error invalid input"
NEG_PLUS	.FILL xFFD5
NEG_MINUS	.FILL xFFD3
NEG_MULTIPLY	.FILL xFFD6
NEG_DIVIDE	.FILL xFFD1

.END

