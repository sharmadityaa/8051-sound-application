//code to generate an octave of music using Buzzer and 8051

#include <reg51.H>
// initalise port 3 pin 0 for buzzer
sbit BUZZER=P3^0;
// declare variable for counting and frequency of the buzzer
int count,freq;
// initialization routine of timer 1
void timer()
{
	ET1=1;			// Enable timer 1 int.
	TMOD=0x20;		//Timer 1 in Mode 2*
	TH1=206;		//Timer 150 ms count
	TR1=1;			//Run timer 1
	EA=1;			//Enable interrupts
}
// Timer 1 interrupt service routine
timer1()interrupt 3
{
	count++;	//Increment count
	if(count == freq)
	{
	count=0;	//Reset count
	BUZZER=~BUZZER;
	}
}
// Start of main program
main()
{
	unsigned char key_pressed;
	count=0;				//Initialize count
	BUZZER=0;				//Set initial buzzer to 0
	timer();				//Initialize timer

	while(1)					//forever loop
	{
		if(P1 != 0xFF)			//IF the input of P1 is not zero (i.e.,a  key is pressed)		
		{
			TR1=1;
			key_pressed=~P1;
			
			//Switch case for push buttons
			//push buttons are connected to each pin of port 1
			//thus, when they are pressed individually, only the corresponding bit of port 1 is high
			//this results in cases 10000000,01000000,00100000,00010000....00000010,00000001
			//Converting these to binary, we get cases 128,64,32,16,8,4,2 and 1
			//which are used in below switch case

			//the value of freq represents the buzzer frequency, as specified in timer 1 interrupt service routine.
			//count is incremented until it is equal to variable freq, which is different for each value of push button
			//this varies the delay given to the 8051 wrt different push button pressed
			//which in turn varies the note generated via the buzzer

			//the frequency is determined with the help of a set ratio for notes in an octave as follows as follows
			//NOTE->	C		D		E		F		G		A		B		C
			//FREQ->	1		1.125	1.25	1.333	1.5		1.667	1.875	2
	
			
			switch(key_pressed)
			{
				case 1:
					 freq=40;
					 break;
				
				case 2:
					 freq=45;
					 break;
			
				case 4:
					 freq=49;
					 break;

				case 8:
					 freq=54;
					 break;				

				case 16:
					 freq=62;
					 break;
				
				case 32:
					 freq=67;
					 break;
			
				case 64:
					 freq=74;
					 break;

				case 128:
					 freq=80;
					 break;
				}
		}
		else
		{
			//No key pressed
			BUZZER = 0;
			count = 0;		//Reset count
			TR1 = 0;		//Stop timer
		}
	}
}