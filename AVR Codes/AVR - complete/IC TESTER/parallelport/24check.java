//IcTest7432.java
//Testing IC7432

import javax.swing.JOptionPane;
import parport.ParallelPort1;


public class check 
{
	public void resultcheck()
	{
	 	out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0xc8);//setting upperside of or gate
		declaration.DDRD(0xff);//setting lowerside of or gate		
		declaration.PORTB(0x80);
		declaration.PORTD(0xf8);
		for(int i=1;i<=8;i++)
		{
			declaration.PORTD(0x88);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,4,fin1,i);
			ret=declaration.BITCHK(inp,7,fin2,i);
			ret=declaration.BITCHK(inp,6,fin3,i);
			declaration.PORTD(0x08);
		}
		
		if(t.dec(fin1)==240&&t.dec(fin2)==204&&t.dec(fin3)==170)
		string+="\nMOD-8 COUNTER IS GOOD";
		else
		string+="\nMOD-8 COUNTER IS BAD"+" "+t.dec(fin1)+" "+t.dec(fin2)+" "+t.dec(fin3);
		
		declaration.PORTD(0xf8);
		declaration.PORTD(0x88);
		for(int i=1;i<=2;i++)
		{
			declaration.PORTB(0x80);
			declaration.PORTD(0x88);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,3,fin4,i);
			declaration.PORTB(0x00);
			//declaration.PORTD(0x08);
		}
		if(t.dec(fin4)==2)
		string+="\nMOD-2 COUNTER IS GOOD";
		else
		string+="\nMOD-2 COUNTER IS BAD"+t.dec(fin4);
			
		
			JOptionPane.showMessageDialog(null,string,"Test Result of Ic7493",
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
