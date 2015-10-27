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
.equ remotedata=$10
.equ inpin=2
.equ sreg =$3f
.equ mcucr=$35
.equ mcucsr=$34
.equ gicr=$3b
.equ gifr=$3a
.def startdata=r21
.def data1=r22
.def data2=r23
.def actualdata1=r24
.def actualdata2=r25


.equ LCD_CPort	=$12	;portd
.equ LCD_Rs	=4
.equ LCD_Rw	=5
.equ LCD_En	=6

.equ LCD_DPort	=$1b	;porta

.cseg
.org 0
	jmp reset
	jmp ext_int0
reset:
	ldi r16,0x02
	out $3e,r16
	ldi r16,0xff
	out $3d,r16
	ldi r16,0xff
	out ddra,r16
	ldi r16,0xfb
	out ddrd,r16
	rcall LCD_Intial

	ldi r29,0x30
	rcall LCD_Data_Out
	
	ldi r16,0x00
	out mcucr,r16
	ldi r16,0x80
	out sreg,r16
	ldi r16,0x40
	out gicr,r16
	
here:
	rjmp here


startremote:
	ldi startdata,0x00
	ldi data1,0x00
	ldi data2,0x00
	ldi r20,0x18
nextstartdata:
	clc
	sbic remotedata,inpin
	sec
	rol data2
	rol data1
	rol startdata
	rcall delay590us
	dec r20
	brne nextstartdata

/*	ldi r29,0x30
	rcall LCD_Data_Out

	ldi r27,0x00
	ldi r20,0x04
startcheckbits1:
	rol data2
	rol data1
	rol startdata
	rol r27
	dec r20
	brne startcheckbits1


	mov r26,startdata
	rcall displaybyte
	rcall delay3s	
	ldi r29,0x01
	rcall LCD_Cmnd_Out

	mov r26,data1
	rcall displaybyte
	rcall delay3s	
	ldi r29,0x01
	rcall LCD_Cmnd_Out

	mov r26,data2
	rcall displaybyte
	rcall delay3s	
	ldi r29,0x01
	rcall LCD_Cmnd_Out

	mov r26,data3
	rcall displaybyte
	rcall delay3s	
	ldi r29,0x01
	rcall LCD_Cmnd_Out

	mov r26,data4
	rcall displaybyte
	rcall delay3s	
	ldi r29,0x01
	rcall LCD_Cmnd_Out*/

	rcall Display_Number
	cpi actualdata1,0x0a
	breq nodisplay
	ldi r29,0x30
	add r29,actualdata1
	rcall LCD_Data_Out
	rcall delay0p1s
nodisplay:
	ret

ext_int0:
    rcall startremote
	reti



displaybyte:
	ldi r20,0x08
	ldi r27,0x00
nextbit:
	ldi r29,0x30
	rol r26
	adc r29,r27
	rcall LCD_Data_Out
	dec r20
	brne nextbit	
	ret


Display_Number:
	ldi actualdata1,0x0a
	ldi r27,0x00
	ldi r20,0x04
startcheckbits:
	rol data2
	rol data1
	rol startdata
	rol r27
	dec r20
	brne startcheckbits
	cpi r27,0x00
	brne error

		
	andi data1,0xf0
	


key1:	
	cpi startdata,0b10101010
	brne key2
	cpi data1,0b10100000
	brne key2
	ldi actualdata1,0x01	
	rjmp error

key2:
	cpi startdata,0b10010101
	brne key3
	cpi data1,0b01010000
	brne key3
	ldi actualdata1,0x02	
	rjmp error

key3:
	cpi startdata,0b10100101
	brne key4
	cpi data1,0b01010000
	brne key4
	ldi actualdata1,0x03	
	rjmp error

key4:
	cpi startdata,0b10010010
	brne key5
	cpi data1,0b10100000
	brne key5
	ldi actualdata1,0x04	
	rjmp error

key5:
	cpi startdata,0b10101001
	brne key6
	cpi data1,0b01010000
	brne key6
	ldi actualdata1,0x05	
	rjmp error

error:
	ret

key6:
	cpi startdata,0b10010100
	brne key7
	cpi data1,0b10100000
	brne key7
	ldi actualdata1,0x06	
	rjmp error

key7:
	cpi startdata,0b10100100
	brne key8
	cpi data1,0b10100000
	brne key8
	ldi actualdata1,0x07	
	rjmp error

key8:
	cpi startdata,0b10010010
	brne key9
	cpi data1,0b01010000
	brne key9
	ldi actualdata1,0x08	
	rjmp error

key9:
	cpi startdata,0b10101010
	brne key0
	cpi data1,0b01010000
	brne key0
	ldi actualdata1,0x09	
	rjmp error

key0:
	cpi startdata,0b10010101
	brne keydisplay
	cpi data1,0b00100000
	brne keydisplay
	ldi actualdata1,0x00	
	rjmp error

keydisplay:
	cpi startdata,0b10010100
	brne error
	cpi data1,0b10010000
	brne error
	ldi actualdata1,0x0a
	ldi r29,0x01
	rcall LCD_Cmnd_Out	
	rjmp error
	




Data2bitschange:
	ldi r26,0x02
	ldi r27,0x00
datacheckbits:
	rol data2
	rol data1
	rol startdata
	rol r27
	dec r26
	brne datacheckbits
	cpi r27,0x02
	brne error
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


LCD_Intial:
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
	ldi r18,0x80
	ldi r19,0x00
delay_loop:
	dec r19
	brne delay_loop
	dec r18
	brne delay_loop
	ret



data:
.db "project",0


; ============================= 
;    delay loop generator 
;     100000 cycles:
; ----------------------------- 
; delaying 99990 cycles:
delay0p1s:
          ldi  R17, $A5
WGLOOP01:  ldi  R18, $C9
WGLOOP11:  dec  R18
          brne WGLOOP11
          dec  R17
          brne WGLOOP01
; ----------------------------- 
; delaying 9 cycles:
          ldi  R17, $03
WGLOOP21:  dec  R17
          brne WGLOOP21
; ----------------------------- 
; delaying 1 cycle:
          nop
		  ret
; ============================= 



; ============================= 
;    delay loop generator 
;     285 cycles:
; ----------------------------- 
; delaying 285 cycles:
delay285us:
          ldi  R17, $5F
WGLOOP0:  dec  R17
          brne WGLOOP0
		  ret
; ============================= 




; ============================= 
;    delay loop generator 
;     590 cycles:
; ----------------------------- 
; delaying 588 cycles:
delay590us:
          ldi  R17, $C4
WGLOOP05:  dec  R17
          brne WGLOOP05
; ----------------------------- 
; delaying 2 cycles:
          nop
          nop
		  ret
; ============================= 





;; ============================= 
;    delay loop generator 
;     3000000 cycles:
; ----------------------------- 
; delaying 2999856 cycles:
delay3s:
          ldi  R17, $10
WGLOOP03:  ldi  R18, $F8
WGLOOP13:  ldi  R19, $FB
WGLOOP23:  dec  R19
          brne WGLOOP23
          dec  R18
          brne WGLOOP13
          dec  R17
          brne WGLOOP03
; ----------------------------- 
; delaying 144 cycles:
          ldi  R17, $30
WGLOOP33:  dec  R17
          brne WGLOOP33
		  ret
; ============================= 




; ============================= 
;    delay loop generator 
;     1000000 cycles:
; ----------------------------- 
; delaying 999999 cycles:
delay1s:
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
