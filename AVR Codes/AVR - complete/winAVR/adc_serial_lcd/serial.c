

/*----------------------------------------------------------------
-----------------FUNCTIONS---------------------------------------
-----------------------------------------------------------------*/

void InitUART( unsigned char baudrate );
unsigned char ReceiveByte( void );
void TransmitByte( unsigned char data );

/*----------------------------------------------------------------
-----------------MAIN FUNCTION------------------------------------
-----------------------------------------------------------------*/
  
  
  
/*----------------------------------------------------------------
------------FUNCTIONS TO Initialize UART--------------------------
-----------------------------------------------------------------*/

 void InitUART( unsigned char baudrate )
  {
    UBRRL =  baudrate;                   /*  Set the baud rate */
    UCSRB = (UCSRB | _BV(RXEN) | _BV(TXEN) );  /* Enable UART   receiver and transmitter */
  }
/*----------------------------------------------------------------
------------FUNCTIONS TO READ UART-------------------------------
-----------------------------------------------------------------*/
  unsigned char ReceiveByte( void )
  {
   while ( !(UCSRA &  (_BV(RXC))) );     /*  Wait for incomming data   */
   return UDR;/* Return the   data */
  }

/*----------------------------------------------------------------
------------FUNCTIONS TO WRITE UART-------------------------------
-----------------------------------------------------------------*/
  void TransmitByte( unsigned char data )
  {
   while ( !(UCSRA & (_BV(UDRE))) );        /* Wait for   empty transmit buffer */
   UDR =  data;  /* Start transmittion   */
  }