;
; DA1B.asm
;s
; Created: 2/23/2019 6:34:59 PM
; Author : TheodorePele
;

;TASK1
;Store 99 num starting from 0x200 location
;Populate by adding high(add) and low(add)
;use x/y/z as pointers to fill up 99 nums that are (>10 <255)
;either consecutive or random
start:
	ldi yL, 0x00  ;LOW(0X0200)
	ldi yh, 0x02  ;HIGH(0X0200)
	ldi r18,0x00
	ldi r16,0x00  ;initialize addition
	ldi r17,0x02 
l1:
    add r18, r17  ;adding high(add) and low(add)
	brcs l1      ;<255 means no carry bit detected 0x100 = 256
	cpi r18, 11	  ;checking for less than 11
	brlt l1  ;if true invalid result increment addresses
	st y, r18	  ;so its valid and can be stored
	inc r16
	mov r18, r16
	inc yl		  ;inc address
	cpi yl, 99	  ;checking for 99 nums
	brne l1	  ;load next address and add again
	nop


;TASK2
;use x/y/z register to parse through 99 nums
;if divisible by 3 store that num starting at 0x400
;else 0x600
	ldi yL, 0x00  ;RESTART YPOINTER AT 0X200
	ldi yh, 0x02  
	ldi xl, 0x00  ;starting x pointer for 0x400
	ldi xh, 0x04
	ldi zl, 0x00  ;starting z pointer at 0x600
	ldi zh, 0x06
	ldi r16, 3	  ;constant to check for divisible by 3
	ldi r18, 100	  ;constant for checking if all 99 were parsed
parse1:
	dec r18		;set properly and enables branch checks
	breq parseDone1
	ld r17, y	  ;loads value from memory
test3:
	sub r17, r16
	brcs notdiv3;not divisible by 3
	breq isdiv3;is divisible by 3
	rjmp test3 ;needs to keep subtracting if not fully done
notdiv3:
	ld r17, y ;reload value from y pointer
	st z, r17 ;load into address starting from 0x600
	inc zl	  ;increase to next position
	inc yl	  ;increase the y pointer as well
	rjmp parse1 ; return to parsing
isdiv3:
	ld r17, y ;load value again from y 0x02XX address
	st x, r17 ;store value into addresses 0x04XX
	inc xl	  ;increase pointer position
	inc yl    ;increase pointer position
	rjmp parse1  ;return to parsing between 0x02XX addresses.
parseDone1:
	nop

;Task 3
;use x/y/z register addressing to add num from 0x400 and 0x600
;store sums at r16:r17 and r18:r19 (*watch for overflow)
	ldi xl, 0x00  ;initialize pointers to addresses 0x0400 and 0x600
	ldi xh, 0x04  ;HIGH(0X400)
	ldi zl, 0x00  ;LOW(0X600)
	ldi zh, 0x06  ;HIGH(0X600)
	ldi r17, 0
	ldi r16, 0
	ldi r18, 0
	ldi r19, 0
	ldi r20, 100  ;will parse 99 times in both 0x400 and 0x600 addresses
getNum1:
	dec r20
	breq sumDone1 ;sum is done when it parses 99 times
	ld r15, x	  ;load num from 0x400 into r15
	add r17, r15  ;summing 0x400 into r16:r17
	brcc nocflag1 ;checking for overflow to add into r16
	inc r16		  ;adding the overflow into r16
nocflag1:
	ld r15, z	  ;load num from 0x600 into r15
	add r19, r15  ;summing 0x600 into r18:r19
	brcc nocflag2 ;checking for overflow to add into r18
	inc r18		  ;adding the overflow into r18
nocflag2:
	inc xl		  ;inc address
	inc zl		  ;inc address
	rjmp getNum1  ;loops after parsing both addresses
sumDone1:
	nop
end: rjmp end
;Task 4 Verfiy using C or any high level program???

;Task 5 Determine execution time @ 16Mhz/#cycles of your algorithm using the simulation.
;