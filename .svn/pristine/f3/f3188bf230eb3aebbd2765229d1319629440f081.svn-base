.ORIG x3000

; setup minimal activation record for main
; =============
; init stack top
LD R6, STACK
ADD R6, R6, #1 ; stack is empty

; init frame pointer
ADD R5, R6, #-1 ; first memory location available for local vars
; =============

; int a, b, c;
ADD R6, R6, #-3

; a = 5;
AND R0, R0, #0
ADD R0, R0, #5
STR R0, R5, #0

; b = -1
AND R0, R0, #0
ADD R0, R0, #-1
STR R0, R5, #-1
; save place for c
; R6 here points to c which is blank now
; c = myf(a,b);
; push a
LDR R0, R5, #0
ADD R6, R6, #-1
STR R0, R6, #0
; push b
LDR R0, R5, #-1
ADD R6, R6, #-1
STR R0, R6, #0

; call function
JSR MYF

; c = 
; pop ret val
LDR R0, R6, #0 ; R0 <- ret val
ADD R6, R6, #1
; assign it to c
STR R0, R5, #-2

; pop parameter(s)
ADD R6, R6, #2

; destroy minimal activation record for main
; ============
; pop a and b and c before returning from main
ADD R6, R6, #3
; ============

; stop main
HALT

STACK .FILL x30FF

; myf implementation
MYF
; add bookkeeping info region
ADD R6, R6, #-1 ; space for ret val
ADD R6, R6, #-1 ; push R7
STR R7, R6, #0  
ADD R6, R6, #-1 ; push R5
STR R5, R6, #0

; setup new frame pointer
ADD R5, R6, #-1

;calculate = a + b;
LDR R0, R5, #5
LDR R1, R5, #4
ADD R0, R0, R1
AND R1, R1, #0

; return a+b;
; prepare ret val
STR R0, R5, #3

;restore R5 and R7
LDR R5, R6, #0 ; pop R5
ADD R6, R6, #1
LDR R7, R6, #0 ; pop R7
ADD R6, R6, #1

; return
RET

.END




