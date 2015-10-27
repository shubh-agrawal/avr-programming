import parport.ParallelPort;

class SimpleIO {
   public static void main ( String []args )
   {
      ParallelPort lpt1 = new ParallelPort(0x378); // 0x378 is normally the base address for the LPT1 port
      int aByte;
      aByte = lpt1.read(); // read a byte from the port's STATUS pins
      System.out.println("Input from parallel port: " + aByte);
      aByte = aByte >> 2; // a simple and irrelevant operation
      lpt1.write(aByte); // write a byte to the port's DATA pins
      System.out.println("Output to port: " + aByte);
   }
}
