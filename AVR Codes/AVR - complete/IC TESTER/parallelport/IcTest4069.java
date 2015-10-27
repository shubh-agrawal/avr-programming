//IcTest4069.java
//Testing IC4069

import javax.swing.JOptionPane;
import parport.ParallelPort1;


public class IcTest4069 
{
	public void result4069()
	{
	 	out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin5[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin6[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin7[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin8[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0xd4);//setting upperside of or gate
		declaration.DDRD(0xaa);//setting lowerside of or gate		
		//for all 1
		declaration.PORTB(0xff);
		declaration.PORTD(0xfc);
		
			
			inp=declaration.PINB();
			
			ret=declaration.BITCHK(inp,3,fin4,1);
			ret=declaration.BITCHK(inp,5,fin5,1);
			ret=declaration.BITCHK(inp,7,fin6,1);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,6,fin3,1);
			ret=declaration.BITCHK(inp,2,fin1,1);
			ret=declaration.BITCHK(inp,4,fin2,1);
			
			
			//for all 0
		declaration.PORTB(0x80);
		declaration.PORTD(0x00);
		
			
			inp=declaration.PINB();
			
			ret=declaration.BITCHK(inp,3,fin4,1);
			ret=declaration.BITCHK(inp,5,fin5,1);
			ret=declaration.BITCHK(inp,7,fin6,1);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,6,fin3,1);
			ret=declaration.BITCHK(inp,2,fin1,1);
			ret=declaration.BITCHK(inp,4,fin2,1);
			
			
		
		
		if(t.dec(fin1)==2)
		string+="\nOUTPUT ON PIN 2 IC IS GOOD";
		else
		string+="\nOUTPUT ON PIN 2 IC IS BAD";
		
		if(t.dec(fin2)==2)
		string+="\nOUTPUT ON PIN 4 IC IS GOOD";
		else
		string+="\nOUTPUT ON PIN 4 IC IS BAD";
		
		if(t.dec(fin3)==2)
		string+="\nOUTPUT ON PIN 6 IC IS GOOD";
		else
		string+="\nOUTPUT ON PIN 6 IC IS BAD";
		
		if(t.dec(fin4)==2)
		string+="\nOUTPUT ON PIN 12 IC IS GOOD";
		else
		string+="\nOUTPUT ON PIN 12 IC IS BAD";
		
		if(t.dec(fin5)==2)
		string+="\nOUTPUT ON PIN 10 IC IS GOOD";
		else
		string+="\nOUTPUT ON PIN 10 IC IS BAD";
		
		if(t.dec(fin6)==2)
		string+="\nOUTPUT ON PIN 8 IC IS GOOD";
		else
		string+="\nOUTPUT ON PIN 8 IC IS BAD";
		
		
		JOptionPane.showMessageDialog(null,string,"Test Result of Ic4069",
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
