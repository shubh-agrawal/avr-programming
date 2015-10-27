//ParallelPort1.java
//test pgm for parallel port created by Bibin John

package parport;

public class ParallelPort1 {

   /** The port base address (e.g. 0x378 is base address for LPT1) */
   private int portBase;

   /** To cunstruct a ParallelPort object,
     * you need the port base address
   */
   public ParallelPort1 (int portBase)
   {
      this.portBase = portBase;
   }

   
   public int readStatusPort ()
   {
      return ParallelPort.readOneByte (this.portBase+1);
   }

   
   public void writeDataPort (int oneByte)
   {
      ParallelPort.writeOneByte (this.portBase, oneByte);
   }

	public int readDataPort()
	{
		int a;
		a=readControlPort();
		a=a&0x0f;
		a=a+32;
		writeControlPort(a);
		return ParallelPort.readOneByte (this.portBase);
		
		}


	public void writeControlPort (int oneByte)
   {
      ParallelPort.writeOneByte (this.portBase+2, oneByte);
   }
   
   public int readControlPort ()
   {
      return ParallelPort.readOneByte (this.portBase+2);
   }
   
   
   public static native int readOneByte (int address);

   /** Writes one byte to the specified address
     * (normally the address is the DATA pins of the port)
     */
   public static native void writeOneByte (int address, int oneByte);

   static
   {
      System.loadLibrary("parport");
   }
}
