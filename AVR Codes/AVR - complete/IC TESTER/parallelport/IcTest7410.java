//IcTest7410.java
//Testing IC7410

import javax.swing.JOptionPane;
import parport.ParallelPort1;


public class IcTest7410
{
	public void result7410()
	{
	 	out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin5[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin6[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin7[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin8[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0xdc);//setting upperside of  gate
		declaration.DDRD(0xfa);//setting lowerside of  gate	
		
		//check 000	
		declaration.PORTB(0x80);
		declaration.PORTD(0x00);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,1);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin2,1);
		ret=declaration.BITCHK(inp,7,fin3,1);
		
		//check 001	
		declaration.PORTB(0xc4);
		declaration.PORTD(0x08);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,2);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin2,2);
		ret=declaration.BITCHK(inp,7,fin3,2);
		
		//check 010	
		declaration.PORTB(0x88);
		declaration.PORTD(0x50);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,3);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin2,3);
		ret=declaration.BITCHK(inp,7,fin3,3);
		
		//check 011	
		declaration.PORTB(0xcc);
		declaration.PORTD(0x58);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,4);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin2,4);
		ret=declaration.BITCHK(inp,7,fin3,4);
		
		//check 100	
		declaration.PORTB(0x90);
		declaration.PORTD(0xa0);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,5);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin2,5);
		ret=declaration.BITCHK(inp,7,fin3,5);
		
		//check 101
		declaration.PORTB(0xd4);
		declaration.PORTD(0xa8);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,6);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin2,6);
		ret=declaration.BITCHK(inp,7,fin3,6);
		
		//check 110	
		declaration.PORTB(0x98);
		declaration.PORTD(0xf0);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,7);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin2,7);
		ret=declaration.BITCHK(inp,7,fin3,7);
		
		//check 111
		declaration.PORTB(0xdc);
		declaration.PORTD(0xf8);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,8);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin2,8);
		ret=declaration.BITCHK(inp,7,fin3,8);
			
		
		
		if(t.dec(fin1)==127)
		string+="\nOUTPUT AT PIN6 IC IS GOOD";
		else
		string+="\nOUTPUT AT PIN6 IC IS BAD"+" "+t.dec(fin1);
		
		if(t.dec(fin2)==127)
		string+="\nOUTPUT AT PIN12 IC IS GOOD";
		else
		string+="\nOUTPUT AT PIN12 IC IS BAD"+" "+t.dec(fin2);
		
		if(t.dec(fin3)==127)
		string+="\nOUTPUT AT PIN8 IC IS GOOD";
		else
		string+="\nOUTPUT AT PIN8 IC IS BAD"+" "+t.dec(fin3);
		
		JOptionPane.showMessageDialog(null,string,"Test Result of Ic7410",
		JOptionPane.INFORMATION_MESSAGE);
	}//end of main
	
	
public static class out
	{			
		public void prin(int inp)
		{
			int a,b[]={0,0,0,0,0,0,0,0,},i;
			a=inp;
			for(i=0;a!=0;i++)
			{
				b[i]=a%2;
				a=a/2;
			}
			
		}
		public int dec(int a[])
		{
		int i;
		i=((a[1]*1)+(a[2]*2)+(a[3]*4)+(a[4]*8)+(a[5]*16)+(a[6]*32)+(a[7]*64)+(a[8]*128));
		return(i);
		}
	}
}
