//IcTest74148.java
//Testing IC74148

import javax.swing.JOptionPane;
import parport.ParallelPort1;


public class IcTest74148
{
	public void result74148()
	{
	 	out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin5[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin6[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin7[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin8[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0x9e);//setting upperside of  gate
		declaration.DDRD(0xf9);//setting lowerside of  gate	
		
		
		//check EH=1	
		declaration.PORTB(0xff);
		declaration.PORTD(0xfe);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,1);
		ret=declaration.BITCHK(inp,7,fin2,1);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,8,fin3,1);
		ret=declaration.BITCHK(inp,2,fin4,1);
		ret=declaration.BITCHK(inp,3,fin5,1);
		
		//check EH=1 all H	
		declaration.PORTB(0xff);
		declaration.PORTD(0xf0);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,2);
		ret=declaration.BITCHK(inp,7,fin2,2);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,8,fin3,2);
		ret=declaration.BITCHK(inp,2,fin4,2);
		ret=declaration.BITCHK(inp,3,fin5,2);
		
		//check EH=1 I7=L	
	
		declaration.PORTD(0xe0);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,3);
		ret=declaration.BITCHK(inp,7,fin2,3);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,8,fin3,3);
		ret=declaration.BITCHK(inp,2,fin4,3);
		ret=declaration.BITCHK(inp,3,fin5,3);
		
		//check EH=1 I6=L	
	
		declaration.PORTD(0xd0);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,4);
		ret=declaration.BITCHK(inp,7,fin2,4);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,8,fin3,4);
		ret=declaration.BITCHK(inp,2,fin4,4);
		ret=declaration.BITCHK(inp,3,fin5,4);
		
		//check EH=1 I5=L	
	
		declaration.PORTD(0xb0);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,5);
		ret=declaration.BITCHK(inp,7,fin2,5);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,8,fin3,5);
		ret=declaration.BITCHK(inp,2,fin4,5);
		ret=declaration.BITCHK(inp,3,fin5,5);
		
		//check EH=1 I4=L	
	
		declaration.PORTD(0x70);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,6);
		ret=declaration.BITCHK(inp,7,fin2,6);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,8,fin3,6);
		ret=declaration.BITCHK(inp,2,fin4,6);
		ret=declaration.BITCHK(inp,3,fin5,6);
		
		//check EH=1 I3=L	
	
		declaration.PORTD(0xf0);
		declaration.PORTB(0x8f);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,7);
		ret=declaration.BITCHK(inp,7,fin2,7);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,8,fin3,7);
		ret=declaration.BITCHK(inp,2,fin4,7);
		ret=declaration.BITCHK(inp,3,fin5,7);
		
		//check EH=1 I2=L	
	
		declaration.PORTD(0xf0);
		declaration.PORTB(0x96);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,6,fin1,8);
		ret=declaration.BITCHK(inp,7,fin2,8);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,8,fin3,8);
		ret=declaration.BITCHK(inp,2,fin4,8);
		ret=declaration.BITCHK(inp,3,fin5,8);
		
		
		
		
		
		if(t.dec(fin1)==195&&t.dec(fin2)==51&&t.dec(fin3)==171&&t.dec(fin4)==253&&t.dec(fin5)==3)
		{
		
			for(int i=0;i<16;i++)
		{
			fin1[i]=0;	
			fin2[i]=0;
			fin3[i]=0;
			fin4[i]=0;
			fin5[i]=0;
		}	
		
			
			//check EH=1 all I0=L
			declaration.PORTB(0xff);
			declaration.PORTD(0xf0);
		
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,6,fin1,2);
			ret=declaration.BITCHK(inp,7,fin2,2);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,8,fin3,2);
			ret=declaration.BITCHK(inp,2,fin4,2);
			ret=declaration.BITCHK(inp,3,fin5,2);
			
			//EI=L and I1=L
			declaration.PORTB(0x9a);
		
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,6,fin1,1);
			ret=declaration.BITCHK(inp,7,fin2,1);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,8,fin3,1);
			ret=declaration.BITCHK(inp,2,fin4,1);
			ret=declaration.BITCHK(inp,3,fin5,1);
		
		
			if(t.dec(fin1)==3&&t.dec(fin2)==3&&t.dec(fin3)==2&&t.dec(fin4)==0&&t.dec(fin5)==3)	
			string+="\n IC IS GOOD";
			else
			string+="\n IC IS BAD"+" "+t.dec(fin1)+" "+t.dec(fin2)+" "+t.dec(fin3)+" "+t.dec(fin4)+" "+t.dec(fin5);			
			}
		else
		string+="\n IC IS BAD"+" "+t.dec(fin1)+" "+t.dec(fin2)+" "+t.dec(fin3)+" "+t.dec(fin4)+" "+t.dec(fin5);		
		
		
		JOptionPane.showMessageDialog(null,string,"Test Result of Ic74148",
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
