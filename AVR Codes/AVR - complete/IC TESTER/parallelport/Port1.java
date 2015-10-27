//Port1.java
//checking ParallelPort1.java

import parport.ParallelPort1;

public class Port1{
	
	//start of main
	public static void main(String args[])
	{
		ParallelPort1 lpt1=new ParallelPort1(0x378);
		
		int a=32;
		
		lpt1.writeDataPort(0x77);
		
		lpt1.writeControlPort(0x0b);
		
		//a=lpt1.readControlPort();
		//System.out.println("Data from Control Port"+a);
		//a=lpt1.readDataPort();
		//System.out.println("Data from Data Port"+a);
		
		
	}//end of main
	
}//end class Port1