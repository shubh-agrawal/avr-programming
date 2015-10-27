//IcTest7474.java
//Testing IC7474

import javax.swing.JOptionPane;
import parport.ParallelPort1;


public class IcTest7474
{
	public void result7474()
	{
	 	out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin5[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin6[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin7[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin8[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0xf8);//setting upperside of  gate
		declaration.DDRD(0xf2);//setting lowerside of  gate	
		
		//check RESET	
		declaration.PORTB(0x88);
		declaration.PORTD(0x50);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,5,fin1,1);
		ret=declaration.BITCHK(inp,6,fin1,2);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,6,fin2,1);
		ret=declaration.BITCHK(inp,7,fin2,2);
		
		//check SET	
		declaration.PORTB(0xc0);
		declaration.PORTD(0x80);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,5,fin1,3);
		ret=declaration.BITCHK(inp,6,fin1,4);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,6,fin2,3);
		ret=declaration.BITCHK(inp,7,fin2,4);
		
		//check D=1	
		declaration.PORTB(0xe8);
		declaration.PORTD(0xdc);
		declaration.PORTB(0xf8);
		declaration.PORTD(0xfc);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,5,fin1,5);
		ret=declaration.BITCHK(inp,6,fin1,6);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,6,fin2,5);
		ret=declaration.BITCHK(inp,7,fin2,6);
		
		//check D=0
		declaration.PORTB(0xc8);
		declaration.PORTD(0x90);
		declaration.PORTB(0xd8);
		declaration.PORTD(0xb0);
		
		inp=declaration.PIND();
		ret=declaration.BITCHK(inp,5,fin1,7);
		ret=declaration.BITCHK(inp,6,fin1,8);
		inp=declaration.PINB();
		ret=declaration.BITCHK(inp,6,fin2,7);
		ret=declaration.BITCHK(inp,7,fin2,8);
		
		if(t.dec(fin1)==165)
		string+="\nCLK AT PIN3 IC IS GOOD";
		else
		string+="\nCLK AT PIN3 IC IS BAD"+" "+t.dec(fin1);		
		
		if(t.dec(fin2)==165)
		string+="\nCLK AT PIN11 IC IS GOOD";
		else
		string+="\nCLK AT PIN11 IC IS BAD"+" "+t.dec(fin2);
		
		JOptionPane.showMessageDialog(null,string,"Test Result of Ic7474",
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
