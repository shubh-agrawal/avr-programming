/* .....................program...........................*/
/*.....................ATMEGA32...........................*/
/*************************************************************/

.equ LCD_DPort	=$1b	;porta

.equ ddrc=$14
.equ ddra=$1a
.equ ddrb=$17
.equ ddrd=$11
.equ portb=$18
.equ portc=$15
.equ porta=$1b
.equ portd=$12
.equ pina=$19
.equ pinb=$16
.equ pinc=$13
.equ pind=$10

.equ LCD_CPort	=$12	;portd
.equ LCD_Rs	=4
.equ LCD_Rw	=5
.equ LCD_En	=6

	
.equ sph	=$3e		;stack pointer
.equ spl	=$3d




	.cseg
	.org   0
	ldi r16,0x02			;initialising stack pointer
	out sph,r16
	ldi r16,0xff
	out spl,r16
;	rcall delay

	ldi r16,0xff
	out ddra,r16
	out ddrd,r16
	out ddra,r16



	
	rcall LCD_Intia

here12:
	

	ldi r29,0x83
	rcall LCD_Cmnd_Out	



	ldi r31,high(2*data)
	ldi r30,low(2*data)
	rcall loadbyte


	ldi r29,0xc5
	rcall LCD_Cmnd_Out
		

	ldi r31,high(2*data1)
	ldi r30,low(2*data1)
	rcall loadbyte

	rcall delay1s1
	

	ldi r29,0x83
	rcall LCD_Cmnd_Out	



	ldi r31,high(2*data2)
	ldi r30,low(2*data2)
	rcall loadbyte


	ldi r29,0xc5
	rcall LCD_Cmnd_Out
		

	ldi r31,high(2*data1)
	ldi r30,low(2*data1)
	rcall loadbyte

	rcall delay1s1
	
	rjmp here12

	rcall delay1
	rcall delay1
	rcall delay1
	rcall delay1
	rcall delay1	
	rcall delay1
	rcall delay1
	rcall delay1

	ldi r29,0x01
	rcall LCD_Cmnd_Out
		

	ldi r31,high(2*data2)
	ldi r30,low(2*data2)
	rcall loadbyte

	rcall delay1
	rcall delay1
	rcall delay1
	rcall delay1
	rcall delay1
	rcall delay1
	rcall delay1
	rcall delay1
	rcall delay1

	ldi r29,0x01
	rcall LCD_Cmnd_Out
		

	ldi r31,high(2*data3)
	ldi r30,low(2*data3)
	rcall loadbyte
here:
	rjmp here


loadbyte:
next:
	lpm
	mov r1,r0
	add r1,r1
	breq here1
	mov r29,r0
	rcall LCD_Data_Out
	ldi r16,0x01
	add r30,r16
	jmp next 
here1:
	ret
	


LCD_Cmnd_Out:
	rcall LCD_Busy_Chk
	out	  LCD_DPort,r29
	cbi   LCD_CPort,LCD_Rs 
	cbi   LCD_CPort,LCD_Rw 
	sbi	LCD_CPort,LCD_En
	cbi   LCD_CPort,LCD_En
	ret


LCD_Data_Out:
	rcall LCD_Busy_Chk
	out   LCD_DPort,r29
	sbi   LCD_CPort,LCD_Rs 	
	cbi   LCD_CPort,LCD_Rw 
	sbi   LCD_CPort,LCD_En
	cbi   LCD_CPort,LCD_En
	ret

LCD_Busy_Chk:
	rcall delay
	ret


LCD_Intia:
	ldi   r29,0x01
	rcall LCD_Cmnd_Out
	ldi   r29,0x38
	rcall LCD_Cmnd_Out
	ldi   r29,0x0C
	rcall LCD_Cmnd_Out
	ldi   r29,0x06
	rcall LCD_Cmnd_Out
	ret

delay:							
	ldi r20,0x20
	ldi r19,0x20
delay_loop:
	dec r19
	brne delay_loop
	dec r20
	brne delay_loop
	ret



delay1:							
	ldi r20,0x40
	ldi r19,0x40
delay_loop1:
	dec r19
	brne delay_loop1
	dec r20
	brne delay_loop1
	ret

data:
.db "ANNIE LOVES ?",0


data1:
.db "BALU",0


data2:
.db "ANNIE       ",0

data3:
.db "RF receive",0


;    delay loop generator 
;     1000000 cycles:
; ----------------------------- 
; delaying 999999 cycles:
delay1s:
          ldi  R17, $09
WGLOOP04:  ldi  R18, $BC
WGLOOP14:  ldi  R19, $C4
WGLOOP24:  dec  R19
          brne WGLOOP24
          dec  R18
          brne WGLOOP14
          dec  R17
          brne WGLOOP04
; ----------------------------- 
; delaying 1 cycle:
          nop
		  ret
; ============================= 


; ============================= 
;    delay loop generator 
;     1000000 cycles:
; ----------------------------- 
; delaying 999999 cycles:
delay1s1:
          ldi  R17, $09
WGLOOP06:  ldi  R18, $BC
WGLOOP16:  ldi  R19, $C4
WGLOOP26:  dec  R19
          brne WGLOOP26
          dec  R18
          brne WGLOOP16
          dec  R17
          brne WGLOOP06
; ----------------------------- 
; delaying 1 cycle:
          nop
		  ret
; ============================= 

