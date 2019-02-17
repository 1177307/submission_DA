;16bit-mul 8 bit w/out mul
start:
;INITIALIZE EVERY REGISTER
; R26|R25|R24 ARE EACH 16 BIT
; SINCE 8*16 BIT MAXIMUM IS 32-BIT
	LDI R26, 0X00
	LDI R25, 0XFF
	LDI R24, 0XFF
	LDI R22, 0XFF
	LDI R20, 0
	LDI R19, 0
	LDI R18, 0
	LDI R17, 1 ;in case lower 8 addition detects carry 
	LDI R16, 9 ;counter for shifting the multiplier loop will start at 8 since check is at beginning
xLp:
	dec r16
	breq done ;IF MULTIPLIER IS SHIFTED 8 BITS THEN MUL OPERATION IS COMPLETE
	LSR R22 ;only flags are set and we'll check to see if we add or not
	BRCC noLp ;if zero no change
	add r18, R24
	BRCC xOne ;IF OVERFLOW, ADD 1 TO NEXT 16-BITS
	add r19, R17
	BRCS xSpecial ;special case where adding 1 caused overflow
xOne:
	add r19, R25
	BRCC xxOne;if second half makes carry the upper 16 needs to be added one
	add r20, r17
xxOne:
	add r20, r26
	rjmp noLp
xSpecial:
	add r20, r17
	rjmp xOne


;SHIFTING THE MULTIPLIER AND MAKING SURE TO SHIFT 16BIT INTO 32BIT
noLp:
	LSL R24
	BRCS plusOne ;couldn't find a ASL so we're shifting then adding one when it overflows
	;so that it goes from r15 - r16 and r31 - r32 when needed
	LSL R25
	BRCS plusTwo ;checks after the second 16-31 for overflow
	LSL R26
	rjmp xLp
plusOne:
	LSL R25
	BRCS plusXTwo
	ADD R25, R17
	LSL R26
	rjmp xLp
plusXTwo:
	ADD R25, R17
plusTwo:
	LSL R26
	ADD R26, R17
	rjmp xLp
done:
	NOP
end: rjmp end
