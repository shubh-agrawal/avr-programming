//IcTest7486.java
//Testing IC7486

import javax.swing.JOptionPane;
import parport.ParallelPort1;


public class IcTest7489
{
	int d,b;
	public  void result7489()
	{
	 	
	 	out t=new out();
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		int inp,ret,fin1[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},fin2[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},fin3[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},fin4[]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
		String string=" ";
		Declaration declaration=new Declaration();
		lpt1.writeControlPort(0x0b);
		declaration.DDRB(0xfa);//setting upperside of or gate
		declaration.DDRD(0xf5);//setting lowerside of or gate		
		declaration.PORTB(0x80);
		declaration.PORTD(0x00);
		for(int i=1;i<=16;i++)
		{
			
			b=(128*(i-(i%2)));
			switch(i)
			{
				case 1:
						d=128;
						break;	
				case 2:
						d=128;
						break;	
				case 3:
						d=192;
						break;	
				case 4:
						d=192;
						break;	
				case 5:
						d=160;
						break;	
				case 6:
						d=160;
						break;
				case 7:
						d=224;
						break;	
				case 8:
						d=224;
						break;	
				case 9:
						d=144;
						break;	
				case 10:
						d=144;
						break;	
				case 11:
						d=208;
						break;	
				case 12:
						d=208;
						break;	
				case 13:
						d=176;
						break;	
				case 14:
						d=176;
						break;	
				case 15:
						d=240;
						break;	
				case 16:
						d=240;
						break;	
			}
			declaration.PORTB(d);
			declaration.PORTD(b);
			b=(128*(i-(i%2)))+32;
			declaration.PORTD(b);
		
		inp=declaration.PIND();
		t.prin(inp);
		ret=declaration.BITCHK(inp,5,fin1,i);		
		ret=declaration.BITCHK(inp,7,fin2,i);
		inp=declaration.PINB();
		t.prin(inp);
		ret=declaration.BITCHK(inp,6,fin4,i);		
		ret=declaration.BITCHK(inp,8,fin3,i);				
	}
						
			
		if(t.dec(fin1)==32768&&t.dec(fin2)==32768&&t.dec(fin3)==32768&&t.dec(fin4)==32768)
		string+="\nWR 0 SUCCESSFUL"+" "+t.dec(fin1)+" "+t.dec(fin2)+" "+t.dec(fin3)+" "+t.dec(fin4);
		else
		string+="\nWR 0 FAILED"+" "+t.dec(fin1)+" "+t.dec(fin2)+" "+t.dec(fin3)+" "+t.dec(fin4);
		
	for(int i=1;i<=16;i++)
		{
			
			b=(128*(i-(i%2)));
			switch(i)
			{
				case 1:
						d=128;
						break;	
				case 2:
						d=128;
						break;	
				case 3:
						d=192;
						break;	
				case 4:
						d=192;
						break;	
				case 5:
						d=160;
						break;	
				case 6:
						d=160;
						break;
				case 7:
						d=224;
						break;	
				case 8:
						d=224;
						break;	
				case 9:
						d=144;
						break;	
				case 10:
						d=144;
						break;	
				case 11:
						d=208;
						break;	
				case 12:
						d=208;
						break;	
				case 13:
						d=176;
						break;	
				case 14:
						d=176;
						break;	
				case 15:
						d=240;
						break;	
				case 16:
						d=240;
						break;	
			}
			declaration.PORTB(d+20);
			declaration.PORTD(b+10);
			b=(128*(i-(i%2)))+32;
			declaration.PORTD(b+10);
		
		inp=declaration.PIND();
		t.prin(inp);
		ret=declaration.BITCHK(inp,5,fin1,i);		
		ret=declaration.BITCHK(inp,7,fin2,i);
		inp=declaration.PINB();
		t.prin(inp);
		ret=declaration.BITCHK(inp,6,fin4,i);		
		ret=declaration.BITCHK(inp,8,fin3,i);				
	}
						
			
		if(t.dec(fin1)==0&&t.dec(fin2)==0&&t.dec(fin3)==0&&t.dec(fin4)==0)
		string+="\nWR 1 SUCCESSFUL"+" "+t.dec(fin1)+" "+t.dec(fin2)+" "+t.dec(fin3)+" "+t.dec(fin4);
		else
		string+="\nWR 1 FAILED"+" "+t.dec(fin1)+" "+t.dec(fin2)+" "+t.dec(fin3)+" "+t.dec(fin4);
			
			JOptionPane.showMessageDialog(null,string,"Test Result of Ic7489",
				JOptionPane.INFORMATION_MESSAGE);
	}//end of main
	
	
public static class out
	{			
		public void prin(int long inp)
		{
			int long a,b[]={0,0,0,0,0,0,0,0,},i;
			a=inp;
			for(i=0;a!=0;i++)
			{
				b[i]=a%2;
				a=a/2;
			}
			
		}
		public int  long dec(int a[])
		{
		int i;
		i=(1*a[1])+(2*a[2])+(4*a[3])+(8*a[4])+(16*a[5]+(32*a[6])+(64*a[7])+(128*a[8])+(256*a[9])+(512*a[10])+(1024*a[11])+(2048*a[12])+(4096*a[13])+(8192*a[14])+(16384*a[15])+(32768*a[16]));
		return(i);
		}
	}
}
