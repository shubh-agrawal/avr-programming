//IcTester7400.java
//Testing Ic7400 called from main function

import java.util.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;
import parport.ParallelPort1;

public class IcTest7400{
	

	
	public void result00()
	{
		
		
		
		
		
		out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0xec);//setting upperside of or gate
		declaration.DDRD(0xda);//setting lowerside of or gate		
		declaration.PORTB(0x80);
		declaration.PORTD(0x00);
		inp=declaration.PIND();
		t.prin(inp);
		ret=declaration.BITCHK(inp,3,fin1,1);		
		ret=declaration.BITCHK(inp,6,fin2,1);				
		declaration.PORTD(0x48);
		inp=declaration.PIND();
		t.prin(inp);
		ret=declaration.BITCHK(inp,3,fin1,2);		
		ret=declaration.BITCHK(inp,6,fin2,2);		
		declaration.PORTD(0x90);
		inp=declaration.PIND();
		t.prin(inp);
		ret=declaration.BITCHK(inp,3,fin1,3);		
		ret=declaration.BITCHK(inp,6,fin2,3);		
		declaration.PORTD(0xd8);
		inp=declaration.PIND();
		t.prin(inp);
		ret=declaration.BITCHK(inp,3,fin1,4);		
		ret=declaration.BITCHK(inp,6,fin2,4);		
		declaration.PORTB(0x80);
		inp=declaration.PINB();
		t.prin(inp);
		ret=declaration.BITCHK(inp,4,fin3,1);
		ret=declaration.BITCHK(inp,7,fin4,1);
		declaration.PORTB(0xa4);
		inp=declaration.PINB();
		t.prin(inp);
		ret=declaration.BITCHK(inp,4,fin3,2);
		ret=declaration.BITCHK(inp,7,fin4,2);
		declaration.PORTB(0xc8);
		inp=declaration.PINB();
		t.prin(inp);
		ret=declaration.BITCHK(inp,4,fin3,3);
		ret=declaration.BITCHK(inp,7,fin4,3);
		declaration.PORTB(0xec);
		inp=declaration.PINB();
		t.prin(inp);
		ret=declaration.BITCHK(inp,4,fin3,4);
		ret=declaration.BITCHK(inp,7,fin4,4);			
			if(t.dec(fin1)==14)
			string+="\nOUTPUT AT PIN3 GATE IS GOOD";
			else
			string+="\nOUTPUT AT PIN3 GATE IS BAD";
			
			if(t.dec(fin2)==14)
			string+="\nOUTPUT AT PIN6 GATE IS GOOD";
			else
			string+="\nOUTPUT AT PIN6 GATE IS BAD";
			
			if(t.dec(fin3)==14)
			string+="\nOUTPUT AT PIN11 GATE IS GOOD";
			else
			string+="\nOUTPUT AT PIN11 GATE IS BAD";
			
			if(t.dec(fin4)==14)
			string+="\nOUTPUT AT PIN9 GATE IS GOOD";
			else
			string+="\nOUTPUT AT PIN9 GATE IS BAD";
			JOptionPane.showMessageDialog(null,string,"Ic Test 7400",
				JOptionPane.INFORMATION_MESSAGE);
			
			
	}//end of constructor
	
	
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
		i=(1*a[4])+(2*a[3])+(4*a[2])+(8*a[1]);
		return(i);
		}
	}
}
	