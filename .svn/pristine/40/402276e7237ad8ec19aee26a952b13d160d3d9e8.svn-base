

.ORIG x4000

;;prepare for testing here


; implement this subroutine following the run-time stack convention presented in lectures
; use OUT trap to print 
INORDER
	; leave space for return value
	ADD R6, R6, #-1
	; push return address (R7)
	ADD R6, R6, #-1
	STR R7, R6, #0
	; push caller’s frame pointer (R5)
	ADD R6, R6, #-1
	STR R5, R6, #0
	; set new frame pointer
	ADD R5, R6, #-1
	;;now R5 has x4FFC, R6 has x4FFD
	LDR R1, R5, #4			
	ADD R2, R1, #1		
	LDR R2, R2, #0			
	AND R3, R3, #0		
	ADD R3, R2, R3
	BRz ELSE
	;;another call of function
	ADD R6, R5, #0			
	LDR R1, R5, #4
	ADD R2, R1, #1
	LDR R2, R2, #0
	STR R2, R6, #0
	
	JSR INORDER
	LDR R0, R6, #0
	ADD R6, R6, #2
	LDR R1, R5, #4		
	LDR R0, R1, #0		
	OUT
	LD R0, SPACE
	OUT
	BRnzp NEXT_IF

	ELSE
	LDR R1, R5, #4
	LDR R0, R1, #0
	OUT
	LD R0, SPACE
	OUT
	; pop local variables
	ADD R6, R5, #1		
	; pop caller’s frame pointer (into R5)
	LDR R5, R6, #0		
	ADD R6, R6, #1			
	; pop return addr (into R7)
	LDR R7, R6, #0
	ADD R6, R6, #1			
	RET
	NEXT_IF
	LDR R1, R5, #4
	ADD R2, R1, #2
	LDR R0, R2, #0
	AND R3, R3, #0
	ADD R3, R2, R3
	BRz DONE
	ADD R6, R6, #-1
	STR R0, R6, #0
	JSR INORDER
	LDR R0, R6, #0
	ADD R6, R6, #2
	DONE
	; pop local variables
	ADD R6, R5, #1			
	; pop caller’s frame pointer (into R5)
	LDR R5, R6, #0			
	ADD R6, R6, #1			
	; pop return addr (into R7)
	LDR R7, R6, #0
	ADD R6, R6, #1			
	RET

SPACE .FILL x0020

;;information to be filled



.END
