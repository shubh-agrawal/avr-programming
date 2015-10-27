/* This program is not a general program which
converts hex to BCD, Here r17 register contains the
number that has to be converted to BCD.
This works for 8bit BCD
This is the fastest algo for 8bit BC*/


.cseg
.org 0x00
rjmp RESET
/*
1. Clear result MSD.
2. Subtract 10 from the 8-bit input number.
3. If result negative, add back 10 to 8-bit input number and return.
4. Increment result MSD and goto step 2.
*/

RESET:
ldi r17,0x0f	; r17=hexadecimal no. to be converted
                ; to BCD
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

break



