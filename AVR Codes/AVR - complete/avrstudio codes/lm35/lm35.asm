.cseg
.org 0x000
rjmp RESET



RESET:

ldi r16,0xff
out $17,r16
out $18,r16
rjmp ADC_INIT



ADC_INIT:
ldi r16,0b11100000 ; setting AD1,AD0 in ADCL
					;internal 2.56 reference,Single
					;channel A0
out $07,r16		;setting ADMUX
ldi r16,0b10000101  ;setting control reg. ck/32
out $06,r16			;setting ADCSRA
rjmp ADCSTART


ADCSTART:

sbi $06,6

WAIT:
sbis $06,4
rjmp WAIT
in r16,$04;ADCL
in r17,$05;ADCH
rjmp H2BCD





H2BCD:
ldi r18,0x00 	;using the above algo(MSD)
ldi r19,10		;for addition of 10
ldi r20,0x10    ;for multiplication


SUBTRACTION:

inc r18  
subi r17,10
brmi OUTPUT			;checking if result is negative
rjmp SUBTRACTION

OUTPUT:
add r17,r19
subi r18,1
mul r18,r20 ; instead of shifting MSD
add r0,r17
mov r18,r0
out $18,r18
rjmp DELAY


DELAY:
; ============================= 
;    delay loop generator 
;     8000000 cycles:
; ----------------------------- 
; delaying 7999992 cycles:
          ldi  R20, $48
WGLOOP0:  ldi  R21, $BC
WGLOOP1:  ldi  R22, $C4
WGLOOP2:  dec  R22
          brne WGLOOP2
          dec  R21
          brne WGLOOP1
          dec  R20
          brne WGLOOP0
; ----------------------------- 
; delaying 6 cycles:
          ldi  R20, $02
WGLOOP3:  dec  R20
          brne WGLOOP3
; ----------------------------- 
; delaying 2 cycles:
          nop
          nop
; ============================= 

rjmp ADCSTART
 


