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

.equ LCD_CPort	=$15	;portc
.equ LCD_Rs	=2
.equ LCD_Rw	=1
.equ LCD_En	=0

	
.equ sph	=$3e		;stack pointer
.equ spl	=$3d


.equ ee_cnt 	=$12
.equ ee_scl		=1
.equ ee_sda		=0
.equ ee_wp		=3
.equ add_wr		=0x00
.def value		=r23



.equ remotedata=$10
.equ inpin=2
.equ sreg =$3f
.equ mcucr=$35
.equ mcucsr=$34
.equ gicr=$3b
.equ gifr=$3a
.def startdata=r21
.def data1=r22
.def data2=r25
.def actualdata1=r24

.equ data_pc=$18
.equ data_frompc=$16
.equ control_outtopc=$12
.equ control_infrompc=$10
.equ infrompc1	=6
.equ infrompc0	=5
.equ outtopc1	=4
.equ outtopc0	=3

.equ impulse_input=$13
.equ impulse_datapin=7

.equ startpower=$15
.equ startpin=6

.cseg
.org   0
	jmp reset
	jmp ext_int0


reset:
	ldi r16,0x02			;initialising stack pointer
	out sph,r16
	ldi r16,0xff
	out spl,r16

	ldi r16,0xff
	out ddra,r16
	out ddrb,r16
	ldi r16,0x5f
	out ddrc,r16
	ldi r16,0x9b
	out ddrd,r16
	ldi r16,0x00
	out control_outtopc,r16

	rcall LCD_Intia	
	ldi r16,0x64
	mov r9,r16

	ldi r16,0x00
	mov r3,r16


loop:
	ldi r16,0x00
	mov r3,r16
	ldi r29,0x01
	rcall LCD_Cmnd_Out
	
	ldi r31,high(2*idle)
	ldi r30,low(2*idle)
	rcall loadbyte

	sbi startpower,startpin

	cbi control_outtopc,outtopc1
	cbi control_outtopc,outtopc0
	
	rcall disable_remote_interrupt
	

	sbic pinc,5
	rjmp loop

	ldi r29,0x01
	rcall LCD_Cmnd_Out
	
	ldi r31,high(2*impulse)
	ldi r30,low(2*impulse)
	rcall loadbyte	

	rcall impulsevalue_display
	
	sbi startpower,startpin


; ============================= 
;    delay loop generator 
;     300000000 cycles:
; ----------------------------- 
; delaying 49939965 cycles:
delay5min:
          ldi  R17, $FF
WGLOOP0:  ldi  R18, $FF
WGLOOP1:  ldi  R19, $FF
WGLOOP2:  sbrc r3,0
		  rjmp loop
		  rcall monitoragain
		  dec  R19
          brne WGLOOP2
          dec  R18
          brne WGLOOP1
		  
          dec  R17
          brne WGLOOP0
; ----------------------------- 
; delaying 49939965 cycles:
          ldi  R17, $FF
WGLOOP3:  ldi  R18, $FF
WGLOOP4:  ldi  R19, $FF
WGLOOP5:  sbrc r3,0
		  rjmp loop
		  rcall monitoragain
		  dec  R19
          brne WGLOOP5
          dec  R18
          brne WGLOOP4
		  
          dec  R17
          brne WGLOOP3
; ----------------------------- 
; delaying 49939965 cycles:
          ldi  R17, $FF
WGLOOP6:  ldi  R18, $FF
WGLOOP7:  ldi  R19, $FF
WGLOOP8:  sbrc r3,0
		  rjmp loop
		  rcall monitoragain
		  dec  R19
          brne WGLOOP8
          dec  R18
          brne WGLOOP7
		  
          dec  R17
          brne WGLOOP6
; ----------------------------- 
; delaying 49939965 cycles:
          ldi  R17, $FF
WGLOOP9:  ldi  R18, $FF
WGLOOP10: ldi  R19, $FF
WGLOOP111: sbrc r3,0
		  rjmp loop
		  rcall monitoragain
		  dec  R19
          brne WGLOOP111
          dec  R18
          brne WGLOOP10
		  
          dec  R17
          brne WGLOOP9
; ----------------------------- 
; delaying 49939965 cycles:
          ldi  R17, $FF
WGLOOP121: ldi  R18, $FF
WGLOOP13: ldi  R19, $FF
WGLOOP14: sbrc r3,0
		  rjmp loop
		  rcall monitoragain
		  dec  R19
          brne WGLOOP14
          dec  R18
          brne WGLOOP13
		  
          dec  R17
          brne WGLOOP121
; ----------------------------- 
; delaying 49939965 cycles:
          ldi  R17, $FF
WGLOOP15: ldi  R18, $FF
WGLOOP16: ldi  R19, $FF
WGLOOP171: sbrc r3,0
		  rjmp loop
		  rcall monitoragain
	      dec  R19
          brne WGLOOP171
          dec  R18
          brne WGLOOP16
		  
          dec  R17
          brne WGLOOP15
; ----------------------------- 
; delaying 360207 cycles:
          ldi  R17, $09
WGLOOP181: ldi  R18, $3A
WGLOOP19: ldi  R19, $E5
WGLOOP20: sbrc r3,0
		  rjmp loop
		  rcall monitoragain
		  dec  R19
          brne WGLOOP20
          dec  R18
          brne WGLOOP19
		  
          dec  R17
          brne WGLOOP181
; ----------------------------- 
; delaying 3 cycles:
          ldi  R17, $01
WGLOOP211: 
		  dec  R17
          brne WGLOOP211
; ============================= 
		  dec r9
		  brne dec_1kwh
		  ldi r16,0x64
		  mov r9,r16
		  rcall eeprom_rd
		  dec value
		  breq stopped
		  rcall eeprom_wr

dec_1kwh:

		  rcall impulsevalue_display
		  rjmp delay5min


stopped:
	sbi startpower,startpin
	ldi r29,0x01
	rcall LCD_Cmnd_Out

	ldi r31,high(2*stopped_display)
	ldi r30,low(2*stopped_display)
	rcall loadbyte	

	rcall delay3s
	rcall delay3s
	rjmp loop



impulsevalue_display:
	ldi r29,0x8b
	rcall LCD_Cmnd_Out
	mov r16,r9
	swap r16
	rcall displaydata
	mov r16,r9
	rcall displaydata

	ldi r29,0xc0
	rcall LCD_Cmnd_Out
	ret



monitoragain:
;	rcall delay0p1s
	sbis impulse_input,impulse_datapin	
	rjmp ad7751off
	cbi startpower,startpin
	mov r5,r17
	mov r6,r18
	mov r7,r19
	nop  
	nop 
	in r26,control_infrompc
	andi r26,0x60
	cpi r26,0x00
	breq tv_remote
	cpi r26,0x40
	breq eeprom_read
	cpi r26,0x20
	breq eeprom_write
;	rjmp monitoragain
monitorcomplete:
	mov r17,r5
	mov r18,r6
	mov r7,r19
	ret
	

here:
	rjmp here



ad7751off:
	ldi r29,0x01
	rcall LCD_Cmnd_Out

	ldi r31,high(2*stopped_display)
	ldi r30,low(2*stopped_display)
	rcall loadbyte
	rcall delay3s
	ldi r16,0x01
	mov r3,r16
	ret


ext_int0:
    rcall startremote
	cpi actualdata1,0x0a
	breq notvaliddata
	ldi r29,0x30
	add r29,actualdata1
	rcall LCD_Data_Out
	rcall disable_remote_interrupt
	cpi actualdata1,0x0b
	breq enter_key
	out data_pc,actualdata1
	sbi control_outtopc,outtopc1
	cbi control_outtopc,outtopc0
	rjmp monitoragain_00_remote
enter_key:
	sbi control_outtopc,outtopc1
	sbi control_outtopc,outtopc0
monitoragain_00_remote:
	sbis control_infrompc,infrompc1
	rjmp monitoragain_00_remote
	sbis control_infrompc,infrompc0
	rjmp monitoragain_00_remote
outofloop:
	cbi control_outtopc,outtopc1
	cbi control_outtopc,outtopc0
	rcall delay0p5s
notvaliddata:
	reti



tv_remote:
	rcall remotepassdisplay
	ldi actualdata1,0x0a
	rcall enable_remote_interrupt
	rcall nodiplay
	rcall disable_remote_interrupt
	rjmp monitorcomplete






eeprom_read:
;	ldi r29,0x39
;	rcall LCD_Data_Out
	rcall eepromreaddisplay
	rcall eeprom_rd
	out data_pc,value
	sbi control_outtopc,outtopc1
	sbi control_outtopc,outtopc0
monitoragain_00_eeprom_rd:
	sbis control_infrompc,infrompc1
	rjmp monitoragain_00_eeprom_rd
	sbis control_infrompc,infrompc0
	rjmp monitoragain_00_eeprom_rd
	cbi control_outtopc,outtopc1
	cbi control_outtopc,outtopc0
	rcall nodiplay
	rjmp monitorcomplete







eeprom_write:
;	ldi r29,0x36
;	rcall LCD_Data_Out
	rcall eepromwritedisplay	
	ldi r16,0x00
	out ddrb,r16
monitoragain_00_eeprom_wr1:
	sbic control_infrompc,infrompc1
	rjmp monitoragain_00_eeprom_wr1
	sbis control_infrompc,infrompc0
	rjmp monitoragain_00_eeprom_wr1

	in value,data_frompc
	mov r16,value
	swap r16
	rcall displaydata
	mov r16,value
	rcall displaydata
	rcall eeprom_wr
	sbi control_outtopc,outtopc1
	sbi control_outtopc,outtopc0
monitoragain_00_eeprom_wr:
	sbis control_infrompc,infrompc1
	rjmp monitoragain_00_eeprom_wr
	sbis control_infrompc,infrompc0
	rjmp monitoragain_00_eeprom_wr
	
	cbi control_outtopc,outtopc1
	cbi control_outtopc,outtopc0
	ldi r16,0xff
	out ddrb,r16
	rcall nodiplay
	rjmp monitorcomplete



remotepassdisplay:
	ldi r29,0xc0
	rcall LCD_Cmnd_Out
	ldi r31,high(2*remote_pass_display)
	ldi r30,low(2*remote_pass_display)
	rcall loadbyte
	ret

eepromreaddisplay:
	ldi r29,0xc0
	rcall LCD_Cmnd_Out
	ldi r31,high(2*eeprom_read_display)
	ldi r30,low(2*eeprom_read_display)
	rcall loadbyte
	ret

eepromwritedisplay:
	ldi r29,0xc0
	rcall LCD_Cmnd_Out
	ldi r31,high(2*eeprom_write_display)
	ldi r30,low(2*eeprom_write_display)
	rcall loadbyte
	ret

nodiplay:
	ldi r29,0xc0
	rcall LCD_Cmnd_Out
	ldi r31,high(2*no_display)
	ldi r30,low(2*no_display)
	rcall loadbyte
	ret




enable_remote_interrupt:
	ldi r16,0x00
	out mcucr,r16
	ldi r16,0x80
	out sreg,r16
	ldi r16,0x40
	out gicr,r16
	ret


disable_remote_interrupt:
	ldi r16,0x00
	out mcucr,r16
	ldi r16,0x00
	out sreg,r16
	ldi r16,0x00
	out gicr,r16
	ret




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


impulse:
.db "IMPULSES :",0

eeprom_read_display:
.db "EEPROM RD ",0

eeprom_write_display:
.db "EEPROM WR ",0

remote_pass_display:
.db "PASSWORD: ",0

no_display:
.db "                    ",0

idle:
.db 	"      IDLE      ",0

stopped_display:
.db		"    STOPPED     ",0

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
	ldi r17,0x20
	ldi r19,0x20
delay_loop:
	dec r19
	brne delay_loop
	dec r17
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
	
	ldi r16,0x9a
	out ddrd,r16
	rcall rd_8bit
	mov value,r16
	
	ldi r16,0x9b
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
	ldi r20,0x05
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
	ret




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
	ldi r20,0x05
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
	ldi actualdata1,0x0b
;	ldi r29,0x01
;	rcall LCD_Cmnd_Out	
	rjmp error
	




; ============================= 
;    delay loop generator 
;     500000 cycles:
; ----------------------------- 
; delaying 499995 cycles:
delay0p5s:
          ldi  R17, $0F
WGLOOP01:  ldi  R18, $37
WGLOOP11:  ldi  R19, $C9
WGLOOP21:  dec  R19
          brne WGLOOP21
          dec  R18
          brne WGLOOP11
          dec  R17
          brne WGLOOP01
; ----------------------------- 
; delaying 3 cycles:
          ldi  R17, $01
WGLOOP31:  dec  R17
          brne WGLOOP31
; ----------------------------- 
; delaying 2 cycles:
          nop
          nop
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



; ============================= 
;    delay loop generator 
;     100000 cycles:
; ----------------------------- 
; delaying 99990 cycles:
delay0p1s:
          ldi  R17, $A5
WGLOOP02:  ldi  R18, $C9
WGLOOP12:  dec  R18
          brne WGLOOP12
          dec  R17
          brne WGLOOP02
; ----------------------------- 
; delaying 9 cycles:
          ldi  R17, $03
WGLOOP22:  dec  R17
          brne WGLOOP22
; ----------------------------- 
; delaying 1 cycle:
          nop
		  ret
; ============================= 




