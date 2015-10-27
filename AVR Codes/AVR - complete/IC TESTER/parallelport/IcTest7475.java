//IcTest7475.java
//Testing IC7475

import javax.swing.JOptionPane;
import parport.ParallelPort1;


public class IcTest7475
{
	public void result7475()
	{
	 	out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin5[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin6[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin7[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin8[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0x18);//setting upperside of  gate
		declaration.DDRD(0x7e);//setting lowerside of  gate	
		
		
		
		//testing for zeros
		
		//check E=1	
		declaration.PORTB(0x10);
		declaration.PORTD(0x18);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,1,fin4,1);
		ret=declaration.BITCHK(inp,8,fin4,4);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin4,2);
		ret=declaration.BITCHK(inp,6,fin4,3);
		
		ret=declaration.BITCHK(inp,1,fin3,1);
		ret=declaration.BITCHK(inp,2,fin3,2);
		ret=declaration.BITCHK(inp,7,fin3,3);
		ret=declaration.BITCHK(inp,8,fin3,4);
		
			//check E=0
		declaration.PORTB(0x00);
		declaration.PORTD(0x08);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,1,fin4,5);
		ret=declaration.BITCHK(inp,8,fin4,8);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin4,6);
		ret=declaration.BITCHK(inp,6,fin4,7);
		
		ret=declaration.BITCHK(inp,1,fin3,5);
		ret=declaration.BITCHK(inp,2,fin3,6);
		ret=declaration.BITCHK(inp,7,fin3,7);
		ret=declaration.BITCHK(inp,8,fin3,8);
		
		//check E=1	
		declaration.PORTB(0x10);
		declaration.PORTD(0x7e);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,1,fin2,1);
		ret=declaration.BITCHK(inp,8,fin2,4);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin2,2);
		ret=declaration.BITCHK(inp,6,fin2,3);
		
		ret=declaration.BITCHK(inp,1,fin1,1);
		ret=declaration.BITCHK(inp,2,fin1,2);
		ret=declaration.BITCHK(inp,7,fin1,3);
		ret=declaration.BITCHK(inp,8,fin1,4);
		
		
		//check E=0
		declaration.PORTB(0x00);
		declaration.PORTD(0x6e);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,1,fin2,5);
		ret=declaration.BITCHK(inp,8,fin2,8);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,3,fin2,6);
		ret=declaration.BITCHK(inp,6,fin2,7);
		
		ret=declaration.BITCHK(inp,1,fin1,5);
		ret=declaration.BITCHK(inp,2,fin1,6);
		ret=declaration.BITCHK(inp,7,fin1,7);
		ret=declaration.BITCHK(inp,8,fin1,8);
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		
		if(t.dec(fin1)==255&&t.dec(fin2)==0&&t.dec(fin4)==255&&t.dec(fin3)==0)
		string+="\n IC IS GOOD";
		else
		string+="\n IC IS BAD"+" "+t.dec(fin1)+" "+t.dec(fin2)+" "+t.dec(fin3)+" "+t.dec(fin4);		
		
		
		JOptionPane.showMessageDialog(null,string,"Test Result of Ic7475",
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
