; ------------------------------------------------------------------
;
;               KeyGrabber  -  DIY version
; 
; ------------------------------------------------------------------
;
; Keyboard Data  			= 	P3.4
; Keyboard Clock 			=	P3.3 (INT1)
; EEPROM Data			=	P3.7
; EEPROM Clock			=	P3.5
; Push-Button			=	P3.2 (INT0)
;
; ------------------------------------------------------------------
; NEW STUFF
;
; - last EEPROM write position memorized every 10 seconds
; - last position transmitted to PC 
; - EEPROM size transmitted to PC
; - no-write block in EEPROM (00h:00h - 00h:7fh)
; - timer 0 for reseting bit counter
; - timer 1 for position memorizing
;
; ------------------------------------------------------------------
;     MAX EEPROM ADDRESS
;
;     set this according to the used EEPROM chip
;
; ------------------------------------------------------------------
;	.equ	EEMAX,1		; 24C02
;	.equ	EEMAX,2		; 24C04
;	.equ	EEMAX,4		; 24C08
;	.equ	EEMAX,8		; 24C16
;	.equ	EEMAX,16		; 24C32
;	.equ	EEMAX,32		; 24C64
;	.equ	EEMAX,64		; 24C128
;	.equ	EEMAX,128		; 24C256
	.equ	EEMAX,0		; 24C512
;
; ------------------------------------------------------------------

      .ORG 0000h
      LJMP start

;--------------------------------------------------------------------- 
; push button interrupt

       .ORG 0003h
       LJMP pushbutton

;--------------------------------------------------------------------- 
; timera 0 interrupt

       .ORG 000Bh
       MOV R7,#0
       CLR TR0
       RETI

;--------------------------------------------------------------------- 
; keyboard clock interrupt

       .ORG 0013h
       LJMP kbclk      

;--------------------------------------------------------------------- 
; timer 1 interrupt

       .ORG 001Bh
       INC DPTR
       RETI


;--------------------------------------------------------------------- 
start: 

       ; -----------

       MOV P3,#255
       MOV P1,#255

       ACALL delay1s
       
       MOV TMOD,#00100010b
       MOV TH1,#1
       MOV TH0,#1


       MOV TCON,#00000100b

       MOV IE,#11001111b
       MOV IP,#00000100b

       CLR TR0
       CLR TR1

       MOV P3,#255
       MOV P1,#255

       CLR P3.5

       
       ; ----- 

       MOV R7,#0
       MOV R3,#0
       ACALL get_ee
       MOV R5,A
       
       ACALL delay200ms


       ; ----- 

       MOV R7,#0
       MOV R3,#1
       ACALL get_ee
       MOV R6,A


       ; -----
     
       MOV A,#EEMAX
       DEC A
       ANL A,R5
       MOV R5,A

       ; -----

       CJNE R5,#0,nie80
       MOV A,R6
       ORL A,#10000000b
       MOV R6,A
nie80:


       ; -----
       MOV R0,#60
       MOV R1,#60
       MOV R2,#0
       MOV R3,#0
       MOV R4,#0
       MOV R7,#0

       SETB TR1

;--------------------------------------------------------------------- 
; main program loop
loop: 
       MOV A,R1
       XRL A,R0
       JZ savepos
       ACALL trans
       SJMP loop

savepos:					
       MOV A,DPH
       CJNE A,#255,loop

       MOV DPTR,#0

	 CJNE	R4,#0,savepos2
       SJMP loop
savepos2:
       ACALL zap_poz
       SJMP loop 
;---------------------------------------------------------------------
; save current position to EEPROM (00h:00h)
zap_poz:

       ACALL start_con
       MOV A,#10100000b
       ACALL nad_zn
       ACALL ackn
       MOV A,#0
       ACALL nad_zn
       ACALL ackn
       MOV A,#0
       ACALL nad_zn
       ACALL ackn
       MOV A,R5
       ACALL nad_zn
       ACALL ackn
       ACALL stop_con

       ACALL wait_wr

       ACALL start_con
       MOV A,#10100000b
       ACALL nad_zn
       ACALL ackn
       MOV A,#0
       ACALL nad_zn
       ACALL ackn
       MOV A,#1
       ACALL nad_zn
       ACALL ackn
       MOV A,R6
       ACALL nad_zn
       ACALL ackn
       ACALL stop_con
        
       ACALL wait_wr


;--------  debug -------------;
;                             ;
;      ACALL changep16         ;
;                             ;
;-----------------------------;


	 MOV R4,#0
       MOV DPTR,#0
       
       RET
;---------------------------------------------------------------------
start_con:
       SETB P3.7                       ;data=1
       SETB P3.5                       ;clk=1
       CLR P3.7                        ;data=0!
       CLR P3.5				;clk=0
       RET
;---------------------------------------------------------------------
stop_con:
       CLR P3.7                        ;data=0
       SETB P3.5                       ;clk=1
       SETB P3.7                       ;data=1!
       CLR P3.5			       ;clk=0
       RET
;---------------------------------------------------------------------
; send acc to EEPROM
nad_zn:
       MOV R2,#8
dal:
       CLR C
       RLC A
       MOV P3.7,C
       NOP
daw:   SETB P3.5                       ;clk=1
       NOP
       CLR P3.5			       ;clk=0
       DJNZ R2,dal
       RET
;---------------------------------------------------------------------
; acknowledge
ackn:
       SETB P3.7                       ;data=1
       SETB P3.5                       ;clk=1
       CLR P3.5                        ;clk=0
       RET
;---------------------------------------------------------------------
; check if EEPROM ready
wait_wr: 
       ACALL start_con
       
       MOV A,#10100000b                ;device address
       ACALL nad_zn
       SETB P3.7                       ;data=1
       SETB P3.5                       ;clk=1
       MOV C,P3.7
       CLR P3.5                        ;clk=0
       JC wait_wr
       RET
;---------------------------------------------------------------------
; transmit one character to EEPROM from circular buffer
trans: 
       INC R0
       CJNE R0,#128,noprzep0
       MOV R0,#60
noprzep0:

       ACALL start_con
       MOV A,#10100000b
       ACALL nad_zn
       ACALL ackn
       MOV A,R5 
       ACALL nad_zn
       ACALL ackn
       MOV A,R6 
       ACALL nad_zn
       ACALL ackn
       MOV A,@R0


;-------- debug --------------;
;                             ;
;      CJNE A,#0f8h,bbop      ;
;      ACALL changep17         ;
;                             ;
;bbop:                        ;
;-----------------------------;


       ACALL nad_zn
       ACALL ackn 
       ACALL stop_con

       INC R6
       CJNE R6,#0,nprzekr
       INC R5
       CJNE R5,#EEMAX,nprzekr
       MOV R5,#0		
       MOV R6,#80h

nprzekr:
       ACALL wait_wr

	 MOV R4,#1

       RET
;---------------------------------------------------------------------
; keyboard clock interrupt
kbclk:
       MOV TL0,#1  
 
       MOV PSW.5,C 
       MOV B,A

       MOV A,R7
       DEC A
       ANL A,#11111000b
       JNZ kl2
       

       MOV A,R3
       MOV C,P3.4  
       RRC A
       MOV R3,A

       CJNE R7,#8,kl2

       INC R1 
       CJNE R1,#128,noprzep1
       MOV R1,#60
noprzep1:
       MOV @R1,A
       MOV TL0,#1 
;       SETB TR0 

kl2:  

       SETB TR0 


       INC R7
       MOV A,B
       MOV C,PSW.5

      
       RETI
;---------------------------------------------------------------------
; delay 1s

delay1s:
       MOV R0,#5
ydelay1:MOV R7,#255
ydelay2:MOV R3,#255
ydelay3:DJNZ R3,ydelay3               
       DJNZ R7,ydelay2
       DJNZ R0,ydelay1
       
       RET
;---------------------------------------------------------------------
; delay 200ms

delay200ms:
	 MOV R7,#255
zdelay2:MOV R3,#255
zdelay3:DJNZ R3,zdelay3               
       DJNZ R7,zdelay2

       RET
;---------------------------------------------------------------------
; read EEPROM character

get_ee:
       ACALL start_con
       MOV A,#10100000b
       ACALL nad_zn
       ACALL ackn 
       MOV A,R7 
       ACALL nad_zn
       ACALL ackn
       MOV A,R3  
       ACALL nad_zn
       ACALL ackn 
       ACALL start_con
       MOV A,#10100001b 
       ACALL nad_zn
       ACALL ackn 

       MOV R2,#8
       MOV A,#0
gal3:
       CLR C       
       SETB P3.5
       NOP
       NOP
       JNB P3.7,tra3
       SETB C
tra3:   
       CLR P3.5 
       NOP
       RLC A
       DJNZ R2,gal3
       
       ACALL ackn
       ACALL stop_con

       RET

;---------------------------------------------------------------------
; test procedure
changep17:
       JNB P1.7,bb17
       CLR P1.7
       RET
bb17:	 SETB P1.7
       RET
;---------------------------------------------------------------------
; test procedure
changep16:
       JNB P1.6,bb16
       CLR P1.6
       RET
bb16:	 SETB P1.6
       RET

;---------------------------------------------------------------------
; delay 30us 
delay:  
       MOV R0,#10
delay1: DEC R0           
       CJNE R0,#0,delay1
       RET
;---------------------------------------------------------------------
; check if EEPROM ready for read

wait_rd: 
       ACALL start_con
       
       MOV A,#10100001b
       ACALL nad_zn
       SETB P3.7 
       SETB P3.5 
       MOV C,P3.7
       CLR P3.5  
       JC wait_rd
       RET
;----------------------------------------------------------------------------------------------
; PS/2 timeout
kb_timeout:
       MOV R2,#100
kbtm1:		
       ACALL delay
       DEC R2
       CJNE R2,#0,kbtm1
       RET
;---------------------------------------------------------------------
; transmit one character to computer
tocomp:        
  
       JB P3.3,int_free
not_free:			
       ACALL kb_timeout
       JNB P3.3,not_free
int_free:


       MOV R4,#0 
       ACALL zero
       
       MOV R2,#8
nada:  CLR C   
       RRC A
       JNC nc
       ACALL jeden
       INC R4
       LJMP jedz       
nc:    ACALL zero      
jedz:  DEC R2
       CJNE R2,#0,nada
       
       CLR C 
       MOV A,R4
       RRC A
       JNC odd
       ACALL zero
       LJMP jedz2
odd:   ACALL jeden
jedz2: 
       ACALL jeden 

       MOV R4,#60
sdelay2:        
       ACALL delay
       DJNZ R4,sdelay2

      RET
;--------------------------------------------------------------------- 
; send logic zero
zero:  SETB P3.3
       CLR P3.4
       ACALL delay
       CLR P3.3
       ACALL delay
       SETB P3.3
       RET
;--------------------------------------------------------------------- 
; send logic one
jeden: SETB P3.3
       SETB P3.4
       ACALL delay
       CLR P3.3
       ACALL delay
       SETB P3.3
       RET
;--------------------------------------------------------------------- 
; send character in hex

dekod:
      MOV DPTR,#0350h
      MOVC A,@A+DPTR
	MOV B,A	
	ACALL tocomp
	MOV A,#0f0h	
	ACALL tocomp
	MOV A,B
	ACALL tocomp
	RET
;---------------------------------------------------------------------
; service button press
pushbutton:

       MOV IE,#00000000b
       MOV TCON,#00000100b

       ACALL delay1s

       ACALL zap_poz

       MOV A,R5
       MOV R7,A
       MOV A,R6
       MOV R3,A

	 ; ------
       MOV A,#EEMAX
       ANL A,#11110000b	
       SWAP A
       ACALL dekod
       MOV A,#EEMAX			
       ANL A,#00001111b
       ACALL dekod
	 ; ------
       MOV A,R5
       ANL A,#11110000b	
       SWAP A
       ACALL dekod
       MOV A,R5			
       ANL A,#00001111b
       ACALL dekod
	 ; ----
       MOV A,R6
       ANL A,#11110000b	
       SWAP A
       ACALL dekod
       MOV A,R6			
       ANL A,#00001111b
       ACALL dekod

       ; ----------

pet2:  
       ACALL get_ee

       MOV R1,A
       ANL A,#11110000b	
       SWAP A
       ACALL dekod
       MOV A,R1
       ANL A,#00001111b
       ACALL dekod

       JNB P3.2,pkon 

       DEC R3  
       CJNE R3,#255,nocarr
       DEC R7

nocarr:
       CJNE R7,#0,pet2	
       CJNE R3,#07fh,pet2
 
       MOV R3,#255
       MOV R7,#EEMAX
       DEC R7
       LJMP pet2

       ; ---------
pkon:
      
       ACALL delay1s	

       MOV R0,#60
       MOV R1,#60
       MOV R2,#0
       MOV R3,#0
       MOV R4,#0
       MOV R7,#0


       MOV TCON,#00000100b

       MOV IE,#11001111b  
       MOV IP,#00000100b 
       SETB TR1


       RETI

;---------------------------------------------------------------------
; translation table
      .org 0350h
      .db 45h, 16h, 1eh, 26h, 25h, 2eh, 36h, 3dh, 3eh, 46h, 1ch, 32h, 21h, 23h, 24h, 2bh, 22h


;---------------------------------------------------------------------