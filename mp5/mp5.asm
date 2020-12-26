.ORIG x3000
;;Intro paragraph:
;;This program simulates the behaviour of a C program in the lc3 code.
;;In another word, this code simulates the compiler of C based on lc3 instruction.
;;The function execution is based the run-time stack.
;;Reigster table:
;;R5 - frame pointer
;;R6 - stack pointer
;;R3 - temporary
;;R1 - temporary 
;;R2 - temporary

;;MAIN - DO NOT CHANGE ANY CODE HERE
  LD R6, STACK
  LD R5, STACK

  ADD R6, R6, #-2 				; make space for local variables
;;Now R6 = x3FFE	R5 = x4000
  ; fake scanf("%d %d", &x, &y); 
  LD R0, X_VAL
  STR R0, R5, #0 ; x <- 5		; x4000 has x=5
  LD R0, Y_VAL
  STR R0, R5, #-1 ; y <- 4		; x3FFF has y=4
;;x3FFE is the place for variable z
;;CALL FOO1 SUBROUTINE - DO NOT CHANGE ANY CODE HERE
  ADD R6, R6, #-1  				; push address of y on to run-time stack: R6 = x3FFD
  ADD R3, R5, #-1				; R3 = x3FFF
  STR R3, R6, #0   				; Input the address of y which is x3FFF in the stack: x3FFD
  ADD R6, R6, #-1  				; push address of x on to run-time stack: R6 = x3FFC
  STR R5, R6, #0   				; R5 equal to x4000 which is the address of x=5
;;By now, R6 = x3FFC	R6 = x4000
  JSR FOO1

;;STACK TEAR-DOWN FOR FOO1 - DO NOT CHANGE ANY CODE HERE
  LDR R0, R6, #0
  ST R0, Z_VAL     ; fake printf("z = %d\n", z);
  ADD R6, R6, #3   ; pop retval and parameters from the stack
 
;;“return 0“ - DO NOT CHANGE ANY CODE HERE
  ADD R6, R6, #3
HALT

STACK .FILL x4000

X_VAL .FILL x5
Y_VAL .FILL x4
Z_VAL .BLKW #1



 
;;IMPLEMENT ME: FOO1 SUBROUTINE
FOO1
;;By now, R6 = x3FFC	R6 = x4000	However, the R7 has been changed
ADD R6, R6, #-1					; Move up the pointer, save space for the return value, R6 = x3FFB
ADD R6, R6, #-1					; Save R7, R6 = x3FFA
STR R7, R6, #0
ADD R6, R6, #-1					; the x4000 in R5 is now saved in address R6 = x3FF9
STR R5, R6, #0
ADD R5, R6, #-1					; the new R5 has the value x3FF8
;;time for local variables
ADD R6, R5, #0					; the place for variable total is x3FF8, R6 = x3FF8
AND R1, R1, #0
STR R1, R6, #0					; Save 0 to the place x3FF8 = R5 = R6 (place for total)
;;implement the for loop
LOOP
LDR R2, R5, #4					; Load the address of input x from stack into R2, the value in R2 is x4000
LDR R1, R2, #0					; x is now in R1, the value is 5
BRnz EXIT 
;;then save argument for the next function
;;pass *y whhich is 
LDR R1, R5, #5					; Load the address of the input y into R1, the value in R1 is x3FFF
LDR R1, R1, #0					; read the value of y into R1
;;I want the value of y 
;;PUSH the value of y
ADD R6, R6, #-1					; R6 = x3FF7
STR R1, R6, #0
;;PUSH the value of variable total
ADD R6, R6, #-1					; R6 = x3FF6
LDR R1, R5, #0
STR R1, R6, #0
;;JSR
JSR FOO2
LDR R0, R6, #0					; R6 = x3FF5
STR R0, R5, #0					; Save the result back to x3FF8
ADD R6, R6, #3					; POP
LDR R2, R5, #4					; Load the address of input x from stack into R2, the value in R2 is x4000
LDR R1, R2, #0					; x is now in R1, the value should be decremented
ADD R1, R1, #-1					; do the x-1
STR R1, R2, #0
BRnzp LOOP
;;time to return to main
EXIT
LDR R0, R5, #0					; R5 here is x3FF8
STR R0, R5, #3					; the place for return is x3FFB
ADD R6, R5, #1					; POP everything (local variables)
LDR R5, R6, #0					; R5 is back, R5 = x4000
ADD R6, R6, #1
LDR R7, R6, #0					; R7 is back
ADD R6, R6, #1					; pop the R7 in the stack
;;Now R6 = x3FFB which points to the return value: total
RET


;;IMPLEMENT ME: FOO2 SUBROUTINE
FOO2
;;book keeping
ADD R6, R6, #-1					; R6 = x3FF5	for return value
ADD R6, R6, #-1					; R6 = x3FF4
STR R7, R6, #0					; Save R7 in x3FF4
ADD R6, R6, #-1					; R6 = x3FF3
STR R5, R6, #0					; the x3FF8 is old R5, here in x3FF3
ADD R5, R6, #-1					; new R5 = x3FF2
LDR R0, R5, #4					; the value of total is now in R0
LDR R1, R5, #5					; take the value of y into R1
ADD R0, R0, R1					; this is the return value
STR R0, R5, #3					; store the return value in x3FF5
ADD R6, R5, #1					; Release all the local variables
LDR R5, R6, #0					; Retrieve the old R5
ADD R6, R6, #1
LDR R7, R6, #0					; Retrieve R7 from R6 = x3FF4
ADD R6, R6, #1					; R6 = x3FF5 which is the address for return value
RET

.END
