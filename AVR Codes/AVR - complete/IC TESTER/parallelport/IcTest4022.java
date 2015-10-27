//IcTest7432.java
//Testing IC7432

import javax.swing.JOptionPane;
import parport.ParallelPort1;


public class IcTest4022 
{
	public void result4022()
	{
	 	out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin5[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin6[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin7[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,},fin8[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0xf0);//setting upperside of or gate
		declaration.DDRD(0x01);//setting lowerside of or gate		
		declaration.PORTB(0xe0);
		declaration.PORTD(0x00);
		for(int i=1;i<=8;i++)
		{
			declaration.PORTB(0x80);
			inp=declaration.PINB();
			ret=declaration.BITCHK(inp,6,fin5,i);
			ret=declaration.BITCHK(inp,7,fin8,i);
			inp=declaration.PIND();
			ret=declaration.BITCHK(inp,1,fin2,i);
			ret=declaration.BITCHK(inp,2,fin1,i);
			ret=declaration.BITCHK(inp,3,fin3,i);
			ret=declaration.BITCHK(inp,4,fin6,i);
			ret=declaration.BITCHK(inp,5,fin7,i);
			ret=declaration.BITCHK(inp,7,fin4,i);
			declaration.PORTB(0xa0);
		}
		
		if(t.dec(fin1)==1&&t.dec(fin2)==2&&t.dec(fin3)==4&&t.dec(fin4)==8&&t.dec(fin5)==16&&t.dec(fin6)==32&&t.dec(fin7)==64&&t.dec(fin8)==128)
		string+="\nIC IS GOOD";
		else
		string+="\nIC IS BAD"+" "+t.dec(fin1)+" "+t.dec(fin2)+" "+t.dec(fin3)+" "+t.dec(fin4)+" "+t.dec(fin5)+" "+t.dec(fin6)+" "+t.dec(fin7)+" "+t.dec(fin8);
		
		JOptionPane.showMessageDialog(null,string,"Test Result of Ic4022",
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
