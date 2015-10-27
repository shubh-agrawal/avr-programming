 //Project.java
//Main window of project

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import javax.swing.event.*;


public class Project extends JFrame{
	private JList icList;
	private JButton button;
	private JLabel label0,label1,label2;
	private Container container;
	IcTest7400 ic=new IcTest7400();
	IcTest7402 ic1=new IcTest7402();
	IcTest7404 ic2=new IcTest7404();
	IcTest7408 ic3=new IcTest7408();
	IcTest7410 ic4=new IcTest7410();	
	IcTest7411 ic5=new IcTest7411();	
	IcTest7427 ic6=new IcTest7427();
	IcTest7432 ic7=new IcTest7432();
	IcTest7447 ic8=new IcTest7447();
	IcTest7474 ic9=new IcTest7474();
	IcTest7475 ic10=new IcTest7475();
	IcTest7486 ic11=new IcTest7486();
	//IcTest7489 ic12=new IcTest7489();
	IcTest7490 ic13=new IcTest7490();
	IcTest7493 ic14=new IcTest7493();
	IcTest74138 ic15=new IcTest74138();
	IcTest74157 ic17=new IcTest74157();
	IcTest4001 ic18=new IcTest4001();
	IcTest4009 ic19=new IcTest4009();
	IcTest4010 ic20=new IcTest4010();
	IcTest4011 ic21=new IcTest4011();
	IcTest4022 ic22=new IcTest4022();
	IcTest4030 ic23=new IcTest4030();
	IcTest4049 ic24=new IcTest4049();
	IcTest4050 ic25=new IcTest4050();
	IcTest4051 ic26=new IcTest4051();
	IcTest4069 ic27=new IcTest4069();
	IcTest4070 ic28=new IcTest4070();
	IcTest4071 ic29=new IcTest4071();
	IcTest4081 ic30=new IcTest4081();
	IcTest74148 ic16=new IcTest74148();
	
	
	private final String icNumbers[]={"7400","7402","7404","7408",
			"7410","7411","7427","7432","7447","7474","7475","7486",
			"7489","7490","7493","74138","74148","74157","4001","4009","4010","4011",
			"4022","4030","4049","4050","4051","4069","4070","4071",
			"4081"};
			
	//set up GUI
	public Project()
	{
	
		super("IC TESTER");
		
		// Set icon
    
		//get content pane and set its layout
		container=getContentPane();
		container.setLayout(new FlowLayout());
		container.setBackground(new Color(219,241,241));
		
		Icon icon0=new ImageIcon("MICRCHIP.jpg");
		label0=new JLabel(" ",icon0,SwingConstants.CENTER);
		container.add(label0);
		
		//create Ic list
		icList=new JList(icNumbers);
		icList.setVisibleRowCount(20);
		container.add(icList);
		
		
		
		//do not allow multiple selections
		icList.setSelectionMode(ListSelectionModel.SINGLE_SELECTION);
		
		//add a JScrollPane containing JList to content pane
		container.add(new JScrollPane(icList));
		
		
		
		
		
		icList.addListSelectionListener(
			
			new ListSelectionListener()
			{ //start of annonymous inner class
				public void valueChanged(ListSelectionEvent event)
				{
				
				  
						
					switch(icList.getSelectedIndex())
					{
						case 0:
								ic.result00();
								break;
						case 1:
								ic1.result02();
								break;
								
						case 2:
								ic2.result7404();
								break;
								
						case 3:
								ic3.result08();
								break;
		
								
						case 4:
								ic4.result7410();
								break;
		
						case 5:
								ic5.result7411();
								break;
						case 6:
								ic6.result7427();
								break;
						case 7:
								ic7.result32();
								break;
						case 8:
								ic8.result7447();
								break;
						case 9:
								ic9.result7474();
								break;				
						case 10:
								ic10.result7475();
								break;	
						case 11:
								ic11.result86();
								break;	
						/*case 12:
								ic12.result7489();
								break;*/
						case 13:
								ic13.result90();
								break;
						case 14:
								ic14.result93();
								break;
						case 15:
								ic15.result74138();
								break;
						case 16:
								ic16.result74148();
								break;
								
						case 17:
								ic17.result74157();
								break;	
								
						case 18:
								ic18.result4001();
								break;	
								
						case 19:
								ic19.result4009();
								break;	
								
						case 20:
								ic20.result4010();
								break;	
								
						case 21:
								ic21.result4011();
								break;	
								
						case 22:
								ic22.result4022();
								break;	
								
						case 23:
								ic23.result4030();
								break;	
								
						case 24:
								ic24.result4049();
								break;	
								
						case 25:
								ic25.result4050();
								break;	
						case 26:
								ic26.result4051();
								break;	
						case 27:
								ic27.result4069();
								break;	
						case 28:
								ic28.result4070();
								break;	
						case 29:
								ic29.result4071();
								break;	
								
						case 30:
								ic30.result4081();
								break;	
						
								
								
														
									
					}
					
			
				}
			}//end of anonymous inner class
			
		);
		
		setSize(800,570);
		setVisible(true);
	}//end Project constructor
	
	public void paint(Graphics g)
		{
			super.paint(g);
			g.setColor(Color.BLUE);
			g.setFont(new Font("Serif",Font.BOLD,18));
			g.drawString("Click to Check IC",650,200);
			
			g.setFont(new Font("Serif",Font.BOLD+Font.ITALIC,16));
			g.drawString("Under Guidance of",600,430);
			g.drawString("Dr.HARANATH KAR",600,450);
			
			g.drawString("Developed by:",600,470);
			g.drawString("BIBIN JOHN",600,490);
			g.drawString("ANIL K.M",600,510);
			g.drawString("ATHUL K.S",600,530);
			g.drawString("BALSARAJ P.R",600,550);
			
	    }
	    
	public static void main(String args[])
	{
		
		Project application=new Project();
		application.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	}
	
}//end class Project