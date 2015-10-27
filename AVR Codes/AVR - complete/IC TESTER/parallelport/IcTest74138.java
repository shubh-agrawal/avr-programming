//IcTest7432.java
//Testing IC7432

import javax.swing.JOptionPane;
import parport.ParallelPort1;


public class IcTest74138 
{
	public void result74138()
	{
	 	out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin5[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin6[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin7[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin8[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0x80);//setting upperside of or gate
		declaration.DDRD(0xfd);//setting lowerside of or gate		
		declaration.PORTB(0x80);


		
			declaration.PORTD(0x04);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,2,fin1,1);
			ret=declaration.BITCHK(inp,3,fin2,1);
			ret=declaration.BITCHK(inp,4,fin3,1);
			ret=declaration.BITCHK(inp,5,fin4,1);
			ret=declaration.BITCHK(inp,6,fin5,1);
			ret=declaration.BITCHK(inp,7,fin6,1);
			ret=declaration.BITCHK(inp,8,fin7,1);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,7,fin8,1);
		
			declaration.PORTD(0x84);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,2,fin1,2);
			ret=declaration.BITCHK(inp,3,fin2,2);
			ret=declaration.BITCHK(inp,4,fin3,2);
			ret=declaration.BITCHK(inp,5,fin4,2);
			ret=declaration.BITCHK(inp,6,fin5,2);
			ret=declaration.BITCHK(inp,7,fin6,2);
			ret=declaration.BITCHK(inp,8,fin7,2);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,7,fin8,2);
			
			declaration.PORTD(0x44);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,2,fin1,3);
			ret=declaration.BITCHK(inp,3,fin2,3);
			ret=declaration.BITCHK(inp,4,fin3,3);
			ret=declaration.BITCHK(inp,5,fin4,3);
			ret=declaration.BITCHK(inp,6,fin5,3);
			ret=declaration.BITCHK(inp,7,fin6,3);
			ret=declaration.BITCHK(inp,8,fin7,3);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,7,fin8,3);
			
			declaration.PORTD(0xc4);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,2,fin1,4);
			ret=declaration.BITCHK(inp,3,fin2,4);
			ret=declaration.BITCHK(inp,4,fin3,4);
			ret=declaration.BITCHK(inp,5,fin4,4);
			ret=declaration.BITCHK(inp,6,fin5,4);
			ret=declaration.BITCHK(inp,7,fin6,4);
			ret=declaration.BITCHK(inp,8,fin7,4);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,7,fin8,4);
			
			declaration.PORTD(0x24);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,2,fin1,5);
			ret=declaration.BITCHK(inp,3,fin2,5);
			ret=declaration.BITCHK(inp,4,fin3,5);
			ret=declaration.BITCHK(inp,5,fin4,5);
			ret=declaration.BITCHK(inp,6,fin5,5);
			ret=declaration.BITCHK(inp,7,fin6,5);
			ret=declaration.BITCHK(inp,8,fin7,5);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,7,fin8,5);
			
			declaration.PORTD(0xa4);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,2,fin1,6);
			ret=declaration.BITCHK(inp,3,fin2,6);
			ret=declaration.BITCHK(inp,4,fin3,6);
			ret=declaration.BITCHK(inp,5,fin4,6);
			ret=declaration.BITCHK(inp,6,fin5,6);
			ret=declaration.BITCHK(inp,7,fin6,6);
			ret=declaration.BITCHK(inp,8,fin7,6);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,7,fin8,6);
			
			declaration.PORTD(0x64);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,2,fin1,7);
			ret=declaration.BITCHK(inp,3,fin2,7);
			ret=declaration.BITCHK(inp,4,fin3,7);
			ret=declaration.BITCHK(inp,5,fin4,7);
			ret=declaration.BITCHK(inp,6,fin5,7);
			ret=declaration.BITCHK(inp,7,fin6,7);
			ret=declaration.BITCHK(inp,8,fin7,7);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,7,fin8,7);
			
			declaration.PORTD(0xe4);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,2,fin1,8);
			ret=declaration.BITCHK(inp,3,fin2,8);
			ret=declaration.BITCHK(inp,4,fin3,8);
			ret=declaration.BITCHK(inp,5,fin4,8);
			ret=declaration.BITCHK(inp,6,fin5,8);
			ret=declaration.BITCHK(inp,7,fin6,8);
			ret=declaration.BITCHK(inp,8,fin7,8);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,7,fin8,8);
		
				
		if(t.dec(fin1)==254&&t.dec(fin2)==253&&t.dec(fin3)==251&&t.dec(fin4)==247&&t.dec(fin5)==239&&t.dec(fin6)==223&&t.dec(fin7)==191&&t.dec(fin8)==127)
		string+="\nIC IS GOOD";
		else
		string+="\nIC IS BAD"+" "+t.dec(fin1)+" "+t.dec(fin2)+" "+t.dec(fin3)+" "+t.dec(fin4)+" "+t.dec(fin5)+" "+t.dec(fin6)+" "+t.dec(fin7)+" "+t.dec(fin8);
		JOptionPane.showMessageDialog(null,string,"Test Result of Ic74138",
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
