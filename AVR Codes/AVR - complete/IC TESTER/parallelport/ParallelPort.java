package parport;

public class ParallelPort {

   /** The port base address (e.g. 0x378 is base address for LPT1) */
   private int portBase;

   /** To cunstruct a ParallelPort object,
     * you need the port base address
   */
   public ParallelPort (int portBase)
   {
      this.portBase = portBase;
   }

   /** Reads one byte from the STATUS pins of the parallel port.
     *
     * The byte read contains 5 valid bits, corresponing to 5 pins of input
     * from the STATUS pins of the parallel port (the STATUS is located
     * at "portBase + 1", e.g. the STATUS address for LPT1 is 0x379).
     * 
     * This diagram shows the content of the byte:
     *
     *  Bit | Pin # | Printer Status  | Inverted
     * -----+-------+-----------------+-----------
     *   7  |  ~11  | Busy            |   Yes
     *   6  |   10  | Acknowledge     |
     *   5  |   12  | Out of paper    |
     *   4  |   13  | Selected        |
     *   3  |   15  | I/O error       |
     * 
     * Note that Pin 11 is inverted, this means that "Hi" input on pin
     * means 0 on bit 7, "Low" input on pin means 1 on bit 7.
   */
   public int read ()
   {
      return ParallelPort.readOneByte (this.portBase+1);
   }

   /** Writes one byte to the DATA pins of parallel port.
     * The byte is written to the DATA pins of the port. The DATA pins are
     * located at the base address of the port (e.g. DATA address for LPT1
     * is 0x378).
     *
     * This diagram shows how the byte is written:
     *
     *  Bit | Pin # | Printer DATA
     * -----+-------+--------------
     *   7  |   9   |   DATA 7
     *   6  |   8   |   DATA 6
     *   5  |   7   |   DATA 5
     *   4  |   6   |   DATA 4
     *   3  |   5   |   DATA 3
     *   2  |   4   |   DATA 2
     *   1  |   3   |   DATA 1
     *   0  |   2   |   DATA 0
   */
   public void write (int oneByte)
   {
      ParallelPort.writeOneByte (this.portBase, oneByte);
   }

   /** Reads one byte from the specified address.
     * (normally the address is the STATUS pins of the port)
     */
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
