//IcTest4051.java
//Testing IC4051

import javax.swing.JOptionPane;
import parport.ParallelPort1;


public class IcTest4051
{
	public void result4051()
	{
	 	out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin5[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin6[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin7[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin8[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0xff);//setting upperside of  gate
		declaration.DDRD(0xdf);//setting lowerside of  gate		
		declaration.PORTB(0x80);
		declaration.PORTD(0x00);
		
		//checking all for zeros
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin1,1);
		
		declaration.PORTB(0x84);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin1,2);
		
		declaration.PORTB(0x82);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin1,3);
		
		declaration.PORTB(0x86);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin1,4);
		
		declaration.PORTB(0x81);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin1,5);
		
		declaration.PORTB(0x85);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin1,6);
		
		declaration.PORTB(0x83);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin1,7);
		
		declaration.PORTB(0x87);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin1,8);
		
		//checking for all 11's
		declaration.PORTB(0xf8);
		declaration.PORTD(0xd8);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin2,1);
		
		declaration.PORTD(0xfc);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin2,2);
		
		declaration.PORTD(0xfa);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin2,3);
		
		declaration.PORTD(0xfe);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin2,4);
		
		declaration.PORTD(0xf9);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin2,5);
		
		declaration.PORTD(0xfd);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin2,6);
		
		declaration.PORTD(0xfb);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin2,7);
		
		declaration.PORTD(0xff);
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,3,fin2,8);
		
		
		
		
		
		
		
		
		
		
		
		
		if(t.dec(fin1)==0&&t.dec(fin2)==255)
		string+="\nIC IS GOOD";
		else
		string+="\nIC IS BAD"+" "+t.dec(fin1)+" "+t.dec(fin2);
		
		JOptionPane.showMessageDialog(null,string,"Test Result of Ic4051",
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
