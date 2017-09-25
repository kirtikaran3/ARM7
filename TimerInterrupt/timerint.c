#include <LPC213X.H>

#define PLOCK 0x00000400
#define MR0I (1<<0) //Interrupt When TC matches MR0
#define MR0R (1<<1)	//Reset TC when TC matches MR0

#define DELAY_MS 500 //0.5 Seconds Delay
#define PRESCALE 60000 //60000 PCLK clock cycles to increment TC by 1 

void delayMS(unsigned int milliseconds);

void initTimer0(void);
__irq void T0ISR(void);




int main(void)
{

	initTimer0(); //Initialize Timer0

    IO0DIR = 0xFFFFFFFF; //Configure all pins on Port 0 as Output
   	IO0PIN = 0xF;
	
	T0TCR = 0x01; //Enable timer

    while(1); //Infinite Idle Loop

    //return 0; //normally this wont execute ever	:P
}

void initTimer0(void)
{
    /*Assuming that PLL0 has been setup with CCLK = 60Mhz and PCLK also = 60Mhz.*/
   
    //----------Configure Timer0-------------

    T0CTCR = 0x0;

    T0PR = PRESCALE-1; //(Value in Decimal!) - Increment T0TC at every 60000 clock cycles
                   //Count begins from zero hence subtracting 1
                   //60000 clock cycles @60Mhz = 1 mS

	T0MR0 = DELAY_MS-1; //(Value in Decimal!) Zero Indexed Count - hence subtracting 1
	
	T0MCR = MR0I | MR0R; //Set bit0 & bit1 to High which is to : Interrupt & Reset TC on MR0  

	//----------Setup Timer0 Interrupt-------------

	VICVectAddr4 = (unsigned )T0ISR; //Pointer Interrupt Function (ISR)

	VICVectCntl4 = 0x20 | 4; //0x20 (i.e bit5 = 1) -> to enable Vectored IRQ slot
							   //0x4 (bit[4:0]) -> this the source number - here its timer0 which has VIC channel mask # as 4
							   //You can get the VIC Channel number from Lpc214x manual R2 - pg 58 / sec 5.5
	
	VICIntEnable = 0x10; //Enable timer0 int

	T0TCR = 0x02; //Reset Timer
}

__irq void T0ISR(void)
{
    long int regVal;
    regVal = T0IR; //Read current IR value
		
	IO0PIN = ~IO0PIN; //Toggle the state of the Pins

	T0IR = regVal; //Write back to IR to clear Interrupt Flag
	VICVectAddr = 0x0; //This is to signal end of interrupt execution
}

