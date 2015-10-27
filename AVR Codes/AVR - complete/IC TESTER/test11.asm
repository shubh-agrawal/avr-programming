

;equ temp,r16
.equ DDRA=$1A
.equ DDRB=$17
.equ DDRC=$14
.equ DDRD=$11
;equ DDR,r27
;equ zero,r25
;equ one2,r26
;equ one,r17
;equ two,r18
;equ three,r19
;equ four,r20
;equ five,r21
;equ six,r22
;equ eight,r28
.equ PORTA=$1B
.equ PORTB=$18
.equ PORTC=$15
.equ PORTD=$12
.equ PINA=$19
.equ PINB=$16
.equ PINC=$13
.equ PIND=$10
;equ data,r23
;equ newdata,r24
.cseg
.org 0x00

rjmp RESET

RESET:

ldi r25,0x00
ldi r26,0x01
ldi r17,0x01
ldi r18,0x02
ldi r19,0x03
ldi r20,0x04
ldi r21,0x05
ldi r22,0x06
ldi r28,0x08
ldi r16,0x00
out DDRA,r16


START:


ldi r16,0x00
out DDRA,r16
sbic PINA,3
rjmp DDRSTORE
sbic PINA,2
rjmp OUT_TO_IC
sbic PINA,1
rjmp IN_FROM_IC
rjmp START

DDRSTORE:



in r23,PINA
sbis PINA,3
rjmp START
in r16,PINA
andi r16,0x07
cpse r16,r25
rjmp CONTINUE
rjmp DDRSTORE

CONTINUE:

cpse r16,r17
rjmp ONE_CONTINUE
swap r23
andi r23,0x0f
in r27,DDRB
andi r27,0xf0
or r27,r23
out DDRB,r27
mov r24,r16

check_for_newdata:

in r16,PINA
andi r16,0x07
cpse r24,r16
rjmp DDRSTORE
rjmp check_for_newdata

ONE_CONTINUE:

cpse r16,r18
rjmp TWO_CONTINUE
andi r23,0xf0
in r27,DDRB
andi r27,0x0f
or r27,r23
out DDRB,r27
mov r24,r16
rjmp check_for_newdata

TWO_CONTINUE:

cpse r16,r19
rjmp THREE_CONTINUE
swap r23
andi r23,0x0f
in r27,DDRC
andi r27,0xf0
or r27,r23
out DDRC,r27
mov r24,r16
rjmp check_for_newdata
	
THREE_CONTINUE:

cpse r16,r20
rjmp FOUR_CONTINUE
andi r23,0xf0
in r27,DDRC
andi r27,0x0f
or r27,r23
out DDRC,r27
mov r24,r16
rjmp check_for_newdata

FOUR_CONTINUE:

cpse r16,r21
rjmp FIVE_CONTINUE
swap r23
andi r23,0x0f
in r27,DDRD
andi r27,0xf0
or r27,r23
out DDRD,r27
mov r24,r16
rjmp check_for_newdata

FIVE_CONTINUE:

cpse r16,r22
rjmp DDRSTORE
andi r23,0xf0
in r27,DDRD
andi r27,0x0f
or r27,r23
out DDRD,r27
mov r24,r16
rjmp check_for_newdata



;completed DDRstore



OUT_TO_IC:

ldi r16,0x00
out DDRA,r16
in r23,PINA
sbis PINA,2
rjmp START
in r16,PINA
andi r16,0x0b
mov r24,r16
mov r29,r28
and r29,r16
asr r29
or r16,r29
andi r16,0x07
cpse r16,r25
rjmp CONTINUE_OUT
rjmp OUT_TO_IC

CONTINUE_OUT:

cpse r16,r17
rjmp one_continue_out
swap r23
andi r23,0x0f
sbrc r23,3
sbi PORTB,3
sbrs r23,3
cbi PORTB,3

sbrc r23,2
sbi PORTB,2
sbrs r23,2
cbi PORTB,2

sbrc r23,1
sbi PORTB,1
sbrs r23,1
cbi PORTB,1

sbrc r23,0
sbi PORTB,0
sbrs r23,0
cbi PORTB,0



out_checkfornewdata:

in r16,PINA
andi r16,0x0b
cpse r24,r16
rjmp OUT_TO_IC
rjmp out_checkfornewdata

one_continue_out:

cpse r16,r18
rjmp two_continue_out
andi r23,0xf0
sbrc r23,4
sbi PORTB,4
sbrs r23,4
cbi PORTB,4

sbrc r23,5
sbi PORTB,5
sbrs r23,5
cbi PORTB,5

sbrc r23,6
sbi PORTB,6
sbrs r23,6
cbi PORTB,6

sbrc r23,7
sbi PORTB,7
sbrs r23,7
cbi PORTB,7


rjmp out_checkfornewdatA

two_continue_out:

cpse r16,r19
rjmp three_continue_out
swap r23
andi r23,0x0f
sbrc r23,0
sbi PORTC,0
sbrs r23,0
cbi PORTC,0

sbrc r23,1
sbi PORTC,1
sbrs r23,1
cbi PORTC,1

sbrc r23,2
sbi PORTC,2
sbrs r23,2
cbi PORTC,2

sbrc r23,3
sbi PORTC,3
sbrs r23,3
cbi PORTC,3


rjmp out_checkfornewdata

three_continue_out:

cpse r16,r20
rjmp four_continue_out
andi r23,0xf0
sbrc r23,4
sbi PORTC,4
sbrs r23,4
cbi PORTC,4

sbrc r23,5
sbi PORTC,5
sbrs r23,5
cbi PORTC,5

sbrc r23,6
sbi PORTC,6
sbrs r23,6
cbi PORTC,6

sbrc r23,7
sbi PORTC,7
sbrs r23,7
cbi PORTC,7


rjmp out_checkfornewdata

four_continue_out:

cpse r16,r21
rjmp five_continue_out
swap r23
andi r23,0x0f
sbrc r23,0
sbi PORTD,0
sbrs r23,0
cbi PORTD,0

sbrc r23,1
sbi PORTD,1
sbrs r23,1
cbi PORTD,1

sbrc r23,2
sbi PORTD,2
sbrs r23,2
cbi PORTD,2

sbrc r23,3
sbi PORTD,3
sbrs r23,3
cbi PORTD,3


rjmp out_checkfornewdata

five_continue_out:

cpse r16,r22
rjmp OUT_TO_IC
andi r23,0xf0
sbrc r23,4
sbi PORTD,4
sbrs r23,4
cbi PORTD,4

sbrc r23,5
sbi PORTD,5
sbrs r23,5
cbi PORTD,5

sbrc r23,6
sbi PORTD,6
sbrs r23,6
cbi PORTD,6

sbrc r23,7
sbi PORTD,7
sbrs r23,7
cbi PORTD,7


rjmp out_checkfornewdata




;completed PORT storing




IN_FROM_IC:


ldi r16,0xf0
out DDRA,r16
sbis PINA,1
rjmp START
in r16,PINA
andi r16,0x0d
mov r24,r16
mov r29,r26
and r29,r16
asr r16
andi r16,0x06
or r16,r29
cpse r16,r25
rjmp CONTINUE_IN
rjmp IN_FROM_IC

CONTINUE_IN:

cpse r16,r17
rjmp ONE_CONTINUE_IN
in r23,PINB
andi r23,0x0f
swap r23
sbrc r23,4
sbi PORTA,4
sbrs r23,4
cbi PORTA,4

sbrc r23,5
sbi PORTA,5
sbrs r23,5
cbi PORTA,5

sbrc r23,6
sbi PORTA,6
sbrs r23,6
cbi PORTA,6

sbrc r23,7
sbi PORTA,7
sbrs r23,7
cbi PORTA,7

check_fornewdata:

in r16,PINA
andi r16,0x0d
cpse r24,r16
rjmp IN_FROM_IC
rjmp check_fornewdata

ONE_CONTINUE_IN:

cpse r16,r18
rjmp TWO_CONTINUE_IN
in r23,PINB
andi r23,0xf0
sbrc r23,4
sbi PORTA,4
sbrs r23,4
cbi PORTA,4

sbrc r23,5
sbi PORTA,5
sbrs r23,5
cbi PORTA,5

sbrc r23,6
sbi PORTA,6
sbrs r23,6
cbi PORTA,6

sbrc r23,7
sbi PORTA,7
sbrs r23,7
cbi PORTA,7

rjmp check_fornewdata

TWO_CONTINUE_IN:

cpse r16,r19
rjmp THREE_CONTINUE_IN
in r23,PINC
andi r23,0x0f
swap r23
sbrc r23,4
sbi PORTA,4
sbrs r23,4
cbi PORTA,4

sbrc r23,5
sbi PORTA,5
sbrs r23,5
cbi PORTA,5

sbrc r23,6
sbi PORTA,6
sbrs r23,6
cbi PORTA,6

sbrc r23,7
sbi PORTA,7
sbrs r23,7
cbi PORTA,7

rjmp check_fornewdata

THREE_CONTINUE_IN:

cpse r16,r20
rjmp FOUR_CONTINUE_IN
in r23,PORTC
andi r23,0xf0
sbrc r23,4
sbi PORTA,4
sbrs r23,4
cbi PORTA,4

sbrc r23,5
sbi PORTA,5
sbrs r23,5
cbi PORTA,5

sbrc r23,6
sbi PORTA,6
sbrs r23,6
cbi PORTA,6
sbrc r23,7
sbi PORTA,7
sbrs r23,7
cbi PORTA,7

rjmp check_fornewdata


FOUR_CONTINUE_IN:

cpse r16,r21
rjmp FIVE_CONTINUE_IN
in r23,PIND
andi r23,0x0f
swap r23
sbrc r23,4
sbi PORTA,4
sbrs r23,4
cbi PORTA,4

sbrc r23,5
sbi PORTA,5
sbrs r23,5
cbi PORTA,5

sbrc r23,6
sbi PORTA,6
sbrs r23,6
cbi PORTA,6

sbrc r23,7
sbi PORTA,7
sbrs r23,7
cbi PORTA,7

rjmp check_fornewdata


FIVE_CONTINUE_IN:

cpse r16,r22
rjmp IN_FROM_IC
in r23,PIND
andi r23,0xf0
sbrc r23,4
sbi PORTA,4
sbrs r23,4
cbi PORTA,4

sbrc r23,5
sbi PORTA,5
sbrs r23,5
cbi PORTA,5

sbrc r23,6
sbi PORTA,6
sbrs r23,6
cbi PORTA,6

sbrc r23,7
sbi PORTA,7
sbrs r23,7
cbi PORTA,7

rjmp check_fornewdata


  

