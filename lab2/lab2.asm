; Programming Lab 2 
; assignment: develop a code to print a value stored in register R3
;             as a hexadecimal number to the monitor
; algorithm: turnin each group of four bits into a digit
;            calculate the corresponding ASCII character;
;            print the character to the monitor

.ORIG x3000
PRINT_HEX
	AND R0,R0,#0
	AND R1,R1,#0
	AND R2,R2,#0
	LD R3,VALUE_R3
	AND R4,R4,#0
	AND R5,R5,#0
	AND R6,R6,#0
	
HEX_TO_ASCII
	LD R5,TEMP3		;Load temp values into R5.
	LD R2,MINUS_4096
	AND R5,R5,R3
	BRn NEG_NUM
	BRnzp RIGHT_SHIFT_III
NEG_NUM
	BRnzp RIGHT_SHIFT_III_NEG
RIGHT_SHIFT_III			;To get the rightmost byte of the hex.
	ADD R4,R4,#1
	ADD R5,R5,R2		
	BRzp RIGHT_SHIFT_III
	ADD R5,R4,#-1
	;The result is stored in R5!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ST R5,SAVE_BYTE3
	BRnzp NEXT_BYTE
RIGHT_SHIFT_III_NEG
	ADD R4,R4,#1
	ADD R5,R5,R2
	BRnp RIGHT_SHIFT_III_NEG
	ADD R5,R4,#0
	;The result is stored in R5!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ST R5,SAVE_BYTE3
NEXT_BYTE
	LD R5,TEMP2		;Load temp values into R5.
	LD R2,MINUS_256
	AND R5,R5,R3
	AND R4,R4,#0
RIGHT_SHIFT_II			;To get the rightmost byte of the hex.
	ADD R4,R4,#1
	ADD R5,R5,R2
	BRzp RIGHT_SHIFT_II
	ADD R5,R4,#-1
	;The result is stored in R5!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!	
	ST R5,SAVE_BYTE2
	LD R5,TEMP1		;Load temp values into R5.
	LD R2,MINUS_SIXTEEN
	AND R5,R5,R3
	AND R4,R4,#0
RIGHT_SHIFT_I			;To get the rightmost byte of the hex.
	ADD R4,R4,#1
	ADD R5,R5,R2
	BRzp RIGHT_SHIFT_I
	ADD R5,R4,#-1
	;The result is stored in R5!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ST R5,SAVE_BYTE1 
	AND R4,R4,#0
	LD R5,TEMP0		;Load temp values into R5.
	AND R5,R5,R3
	;The result is stored in R5!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ST R5,SAVE_BYTE0
	AND R5,R5,#0
	LEA R2,SAVE_BYTE3
	AND R6,R6,#0
	ADD R6,R6,#4
	AND R4,R4,#0

TRANSLATION
	AND R0,R0,#0 
	AND R4,R4,#0
	LDR R5,R2,#0
	ADD R4,R5,#-9		;Choose different numbers to add to get the ASCII code.
	BRp A_TO_F
DIGIT	LD R4,ASCII_BUF_DIGIT
	ADD R5,R5,R4
	ADD R0,R0,R5
	OUT
	ADD R2,R2,#1
	ADD R6,R6,#-1
	BRp TRANSLATION
	BRnzp DONE
A_TO_F	LD R4,ASCII_BUF_AF
	ADD R5,R5,R4
	ADD R0,R5,R0
	OUT
	ADD R2,R2,#1
	ADD R6,R6,#-1
	BRp TRANSLATION		;There are four bytes of information to translate.



DONE	HALT			; done



; stop the computer
HALT

; program data section starts here
VALUE_R3	.FILL x8F09
TEMP3		.FILL xF000
TEMP2		.FILL x0F00
TEMP1		.FILL x00F0
TEMP0		.FILL x000F
ASCII_BUF_DIGIT	.FILL x0030
ASCII_BUF_AF	.FILL x0037
MINUS_SIXTEEN	.FILL xFFF0
MINUS_256	.FILL xFF00
MINUS_4096	.FILL xF000
SAVE_BYTE3	.BLKW 1
SAVE_BYTE2	.BLKW 1
SAVE_BYTE1	.BLKW 1
SAVE_BYTE0	.BLKW 1

.END

