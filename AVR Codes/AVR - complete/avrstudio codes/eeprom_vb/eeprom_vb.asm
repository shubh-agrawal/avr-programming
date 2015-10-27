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


.equ ee_cnt 	=$12
.equ ee_scl		=1
.equ ee_sda		=0
.equ ee_wp		=3
.equ add_wr		=0x00
.def value		=r23


	.cseg
	.org   0
	ldi r16,0x02			;initialising stack pointer
	out sph,r16
	ldi r16,0xff
	out spl,r16

	ldi r16,0xff
	out ddra,r16
	out ddrc,r16
	ldi r16,0x00
	out ddrb,r16
	ldi r16,0xfb
	out ddrd,r16

	
	rcall LCD_Intia

	ldi r29,0x37
	rcall LCD_Data_Out

	
notvaliddata:
nextdata:
	in value,pinb
	cpi value,0x80
	brcc notvaliddata
	
	rcall eeprom_wr

	rcall eeprom_rd
	mov r16,value
	swap r16
	rcall displaydata
	mov r16,value
	rcall displaydata

;	mov r29,value
;	rcall LCD_Data_Out
	
	rcall delay3s
	ldi r29,0x01
	rcall LCD_Cmnd_Out
	rjmp nextdata	



here:
	rjmp here



displaydata:
	ldi r29,0x30
	andi r16,0x0f
	cpi r16,0x0a
	brcs decimaldisplay
	ldi r17,0x07
	add r29,r17
decimaldisplay:
	add r29,r16
	rcall LCD_Data_Out
	ret


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


eeprom_wr:
;	cbi ee_cnt,ee_wp
	cbi ee_cnt,ee_scl
	sbi ee_cnt,ee_sda
	sbi ee_cnt,ee_scl
	rcall delay2us
	cbi ee_cnt,ee_sda
	rcall delay2us
	cbi ee_cnt,ee_scl

	ldi r16,0xa0
	rcall wr_8bit
	
	ldi r16,add_wr
	rcall wr_8bit
	
	mov r16,value
	rcall wr_8bit

	cbi ee_cnt,ee_sda
	rcall delay2us
	sbi ee_cnt,ee_scl
	rcall delay2us
	sbi ee_cnt,ee_sda
	rcall delay2us
	rcall delay2us
	cbi ee_cnt,ee_scl
	ret



wr_8bit:
	ldi r20,0x08
shiftr16_wr:
	rol r16
	brcs carryset
	cbi ee_cnt,ee_sda
	rjmp continue
carryset:
	sbi ee_cnt,ee_sda
continue:
	rcall delay2us
	rcall delay2us
	sbi ee_cnt,ee_scl
	rcall delay2us
	cbi ee_cnt,ee_scl
	dec r20
	brne shiftr16_wr

	rcall delay2us
	rcall delay2us
	sbi ee_cnt,ee_scl
	rcall delay2us
	cbi ee_cnt,ee_scl
	ret
	




; ============================= 
;    delay loop generator 
;     16 cycles:
; ----------------------------- 
; delaying 15 cycles:
delay2us1:
          ldi  R17, $ff
WGLOOP04:  dec  R17
          brne WGLOOP04
; ----------------------------- 
; delaying 1 cycle:
          nop
		  ret
; ============================= 


; ============================= 
;    delay loop generator 
;     2000 cycles:
; ----------------------------- 
; delaying 1998 cycles:
delay2us:
          ldi  R17, $03
WGLOOP07:  ldi  R18, $DD
WGLOOP17:  dec  R18
          brne WGLOOP17
          dec  R17
          brne WGLOOP07
; ----------------------------- 
; delaying 2 cycles:
          nop
          nop
		  ret
; ============================= 


eeprom_rd:
;	cbi ee_cnt,ee_wp
	cbi ee_cnt,ee_scl
	sbi ee_cnt,ee_sda
	sbi ee_cnt,ee_scl
	rcall delay2us
	cbi ee_cnt,ee_sda
	rcall delay2us
	cbi ee_cnt,ee_scl
	
	ldi r16,0xa0
	rcall wr_8bit

	ldi r16,add_wr
	rcall wr_8bit

	sbi ee_cnt,ee_sda
	sbi ee_cnt,ee_scl
	rcall delay2us
	cbi ee_cnt,ee_sda
	rcall delay2us
	cbi ee_cnt,ee_scl

	ldi r16,0xa1
	rcall wr_8bit
	
	ldi r16,0xfa
	out ddrd,r16
	rcall rd_8bit
	mov value,r16
	
	ldi r16,0xfb
	out ddrd,r16
	
	sbi ee_cnt,ee_sda
	rcall delay2us
	sbi ee_cnt,ee_scl
	rcall delay2us
	cbi ee_cnt,ee_scl
	rcall delay2us
	cbi ee_cnt,ee_sda
	rcall delay2us
	rcall delay2us
	sbi ee_cnt,ee_scl
	rcall delay2us
	sbi ee_cnt,ee_sda
	rcall delay2us	
	ret


rd_8bit:
	ldi r20,0x08
	ldi r16,0x00
getshifted_data:
	rcall delay2us	
	rcall delay2us
	sbi ee_cnt,ee_scl
	sbic pind,ee_sda
	rjmp continue1
	clc
	rjmp continue2
continue1:
	sec
continue2:
	rol r16
	rcall delay2us
	cbi ee_cnt,ee_scl
	rcall delay2us
	dec r20
	brne getshifted_data	
	ret






; ============================= 
;    delay loop generator 
;     3000000 cycles:
; ----------------------------- 
; delaying 2999856 cycles:
delay3s:
          ldi  R17, $10
WGLOOP08:  ldi  R18, $F8
WGLOOP18:  ldi  R19, $FB
WGLOOP28:  dec  R19
          brne WGLOOP28
          dec  R18
          brne WGLOOP18
          dec  R17
          brne WGLOOP08
; ----------------------------- 
; delaying 144 cycles:
          ldi  R17, $30
WGLOOP38:  dec  R17
          brne WGLOOP38
		  ret
; ============================= 





