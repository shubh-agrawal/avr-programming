//Declaration.java
//to declare methods DDRB,DDRD,PORTB,PORTD,PINB,PIND

import parport.ParallelPort1;

class thrd extends Thread
{
	public void delay()
	{
		try
		{
			Thread.sleep(1);
		}catch(InterruptedException e){}
	}
}	

public class Declaration extends Object{
	ParallelPort1 lpt1=new ParallelPort1(0x378);
	thrd t=new thrd();
	private int l,m,j,a;
	
	public Declaration()
	{
	}
	
	public void DDRB(int a)
	{
		
		m=a/16&0x0f;
		l=a&0x0f;
		lpt1.writeControlPort(0x03);
		t.delay();
		lpt1.writeDataPort(m);
		t.delay();
		lpt1.writeControlPort(0x01);
		t.delay();
		lpt1.writeControlPort(0x03);
		t.delay();
		lpt1.writeDataPort(l);
		t.delay();
		lpt1.writeControlPort(0x02);
		t.delay();
		lpt1.writeControlPort(0x03);
		t.delay();
		lpt1.writeControlPort(0x0b);
		t.delay();

	}//end of DDRB
	
	
	public void DDRD(int a)
	{
		m=a/16&0x0f;
		l=a&0x0f;
	lpt1.writeControlPort(0x03);
	t.delay();
	lpt1.writeDataPort(m);
	t.delay();
	lpt1.writeControlPort(0x05);
	t.delay();
	lpt1.writeControlPort(0x03);
	t.delay();
	lpt1.writeDataPort(l);
	t.delay();
	lpt1.writeControlPort(0x06);
	t.delay();
	lpt1.writeControlPort(0x03);
	t.delay();
	lpt1.writeControlPort(0x0b);
	t.delay();

	}////end of DDRD
	
	public void DDRC(int a)
	{
	m=a/16&0x0f;
	l=a&0x0f;
	lpt1.writeControlPort(0x03);
	t.delay();
	lpt1.writeDataPort(m);
	t.delay();
	lpt1.writeControlPort(0x07);
	t.delay();
	lpt1.writeControlPort(0x03);
	t.delay();
	lpt1.writeDataPort(l);
	t.delay();
	lpt1.writeControlPort(0x00);
	t.delay();
	lpt1.writeControlPort(0x03);
	t.delay();
	lpt1.writeControlPort(0x0b);
	t.delay();

	}////end of DDRC*/
	
	
	public void PORTB(int a)
	{
	m=a/16&0x0f;
	l=a&0x0f;
	lpt1.writeControlPort(0x0f);
	t.delay();
	lpt1.writeDataPort(m);
	t.delay();
	lpt1.writeControlPort(0x0d);
	t.delay();
	lpt1.writeControlPort(0x0f);
	t.delay();
	lpt1.writeDataPort(l);
	t.delay();
	lpt1.writeControlPort(0x0e);
	t.delay();
	lpt1.writeControlPort(0x0f);
	t.delay();
	lpt1.writeControlPort(0x0b);
	t.delay();

	}//end of portb
	
	public void PORTD(int a)
	{
	m=a/16&0x0f;
	l=a&0x0f;
	lpt1.writeControlPort(0x0f);
	t.delay();
	lpt1.writeDataPort(m);
	t.delay();
	lpt1.writeControlPort(0x05);
	t.delay();
	lpt1.writeControlPort(0x0f);
	t.delay();
	lpt1.writeDataPort(l);
	t.delay();
	lpt1.writeControlPort(0x06);
	t.delay();
	lpt1.writeControlPort(0x0f);
	t.delay();
	lpt1.writeControlPort(0x0b);
	t.delay();

	}//end of PORTD
	
	public void PORTC(int a)
	{
	m=a/16&0x0f;
	l=a&0x0f;
	lpt1.writeControlPort(0x0f);
	t.delay();
	lpt1.writeDataPort(m);
	t.delay();
	lpt1.writeControlPort(0x07);
	t.delay();
	lpt1.writeControlPort(0x0f);
	t.delay();
	lpt1.writeDataPort(l);
	t.delay();
	lpt1.writeControlPort(0x0c);
	t.delay();
	lpt1.writeControlPort(0x0f);
	t.delay();
	lpt1.writeControlPort(0x0b);
	t.delay();

	}//end of PORTC*/
	
	
	public int PINB()
	{
	lpt1.writeControlPort(0x29);
	t.delay();
	j=0;
	lpt1.writeControlPort(0x2d);	
	t.delay();
	a=lpt1.readDataPort();
	t.delay();
	j=a*16;
	lpt1.writeControlPort(0x28);	
	t.delay();
	a=lpt1.readDataPort();
	t.delay();
	j+=a;
	lpt1.writeControlPort(0x0b);
	t.delay();
	return(j);
	}//end PINB
	
	public int PIND()
	{
	lpt1.writeControlPort(0x29);
	t.delay();
	j=0;
	lpt1.writeControlPort(0x25);	
	t.delay();
	a=lpt1.readDataPort();
	t.delay();
	j=a*16;
	lpt1.writeControlPort(0x20);	
	t.delay();
	a=lpt1.readDataPort();
	t.delay();
	j+=a;
	lpt1.writeControlPort(0x0b);
	t.delay();
	return(j);
	}//end PIND

	public int PINC()
	{
	lpt1.writeControlPort(0x29);
	t.delay();
	j=0;
	lpt1.writeControlPort(0x21);	
	t.delay();
	a=lpt1.readDataPort();
	t.delay();
	j=a*16;
	lpt1.writeControlPort(0x2c);	
	t.delay();
	a=lpt1.readDataPort();
	t.delay();
	j+=a;
	lpt1.writeControlPort(0x0b);
	t.delay();
	return(j);
	}//end PINC*/

	
	public int BITCHK(int n,int p,int f[],int pof)
	{
	int b[]={0,0,0,0,0,0,0,0,};
	for(int i=0;n!=0;i++)
	{
		b[i]=n%2;
		n/=2;
	}
	p=8-p;
	f[pof]=b[p];
	return(b[p]);
	}

}//end class Declaration

