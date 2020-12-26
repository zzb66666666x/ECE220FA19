;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram				Initialize the memory space.
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here							Begin to calculate the frequency.
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string			The R2 is based on the base+offset. It's a string character.
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character				The string character has been subtracted by "@".
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count					The non-alpha is the first entry of the hist.
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A			;								At least A, then figure out if it's within A-Z.
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry			Write to the hist.
	LDR R6,R2,#0		; load the count					Get the original value of the count and add 1 to it.
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z			;							Check for the upper case characters.
	ADD R2,R2,R5		; subtract '`' - '@' from the character				The string has been substracted by the difference of "`" and "@".
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



; you will need to insert your code to print the histogram here				After calculating the frequency, it's time to print them out.
; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments

;    R0 holds the content that should be on the display.
;    R1 holds a pointer to the current block of memory (The data).
;    R2 holds the loop counter, the MINUS_SIXTEEN (or other values like MINUS_4096) and the address of bytes from hex values. 
;    R3 holds the data of from the memory(hex).
;    R4 holds the ASCII_BUF and also some temporary uses.
;    R5 is used as a temporary register.
;    R6 is used as a temporary register.
;The algorithm is to first print the header of each bin and read the hex value into registers and try to print this value in the form of hex, but actually as ASCII code.
;The code has two parts, the first part is to divide the 16-bit hex value into four values and store them in memory.
;After that, I will read values form these memory and translate them into ASCII code by adding a specific value.
PRINT_HIST
	AND R0,R0,#0
	LD R1,HIST_ADDR
	LD R2,NUM_BINS
	AND R3,R3,#0
	AND R4,R4,#0
	AND R5,R5,#0
	AND R6,R6,#0
PRINT_OUTERLOOP			;Connect with the PRINT_NEXT label.
	ADD R2,R2,#-1	
	BRn DONE		;Check the end of everything. 
	ST R2,SAVE_OUTERLOOP
	LDR R3,R1,#0		;R3 contains the hex value from the entry of hist.
	LD R0,ALPHA_ASCII	
	OUT
	ADD R0,R0,#1
	ST R0,ALPHA_ASCII	;Increment the alpha at the beginning of each line and store back to memory.
	LD R0,SPACE
	OUT			;Print out the space.
	AND R0,R0,#0		;Clear the R0 and wait for another thing to display.
	AND R4,R4,#0		;Clear R4 which contains the ASCII_BUF in the previous loop.
HEX_TO_ASCII
	LD R5,TEMP3		;Load temp values into R5.
	AND R5,R5,R3
	LD R2,MINUS_4096
RIGHT_SHIFT_III			;To get the rightmost byte of the hex.
	ADD R4,R4,#1
	ADD R5,R5,R2		
	BRzp RIGHT_SHIFT_III
	ADD R5,R4,#-1
	;The result is stored in R5!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	ST R5,SAVE_BYTE3
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
	BRnzp PRINT_NEXT
A_TO_F	LD R4,ASCII_BUF_AF
	ADD R5,R5,R4
	ADD R0,R5,R0
	OUT
	ADD R2,R2,#1
	ADD R6,R6,#-1
	BRp TRANSLATION		;There are four bytes of information to translate.
PRINT_NEXT	
	AND R0,R0,#0 
	LD R0,LINEFEED
	OUT
	LD R2,SAVE_OUTERLOOP	;The number of outerloop is back to R2.
	ADD R1,R1,#1
	BRnzp PRINT_OUTERLOOP


DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address
SPACE		.FILL x0020	; the space
LINEFEED 	.FILL x000A	; the "\n"
ALPHA_ASCII	.FIll x0040	; the "@" at the beginning
TEMP3		.FILL xF000
TEMP2		.FILL x0F00
TEMP1		.FILL x00F0
TEMP0		.FILL x000F
ASCII_BUF_DIGIT	.FILL x0030
ASCII_BUF_AF	.FILL x0037
SAVE_OUTERLOOP	.BLKW 1
MINUS_SIXTEEN	.FILL xFFF0
MINUS_256	.FILL xFF00
MINUS_4096	.FILL xF000
SAVE_BYTE3	.BLKW 1
SAVE_BYTE2	.BLKW 1
SAVE_BYTE1	.BLKW 1
SAVE_BYTE0	.BLKW 1
; for testing, you can use the lines below to include the string in this
; program...
;STR_START	.FILL STRING	; string starting address
;STRING		.STRINGZ "When I was young, I learned the sentence that people used to learn typing: \"The quick brown fox jumped over the lazy dog.\"  If you look carefully, or less than carefully at a correctly-produced histogram, you will notice that it contains all of the letters in the English language.  This aspect gives the sentence its value in teaching typing skills.  Can you type it, I wonder?"



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
