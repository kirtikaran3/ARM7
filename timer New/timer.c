
#include <LPC213X.H>


#define PRESCALE 10000   //60000 PCLK clock cycles to increment TC by 1 

void delayMS(unsigned int milliseconds);

void initTimer0(void);


int main(void)
{
	
	initTimer0(); //Initialize Timer0
    IO0DIR = 0xFFFFFFFF; //Configure all pins on Port 0 as Output
   
    while(1)
    {
        IO0SET = 0xFFFFFFFF; //Turn on LEDs
        delayMS(1000); //0.5 Second(s) Delay
        IO0CLR = 0xFFFFFFFF; //Turn them off
        delayMS(1000);
    }
    //return 0; //normally this wont execute ever :P
	
}

void initTimer0(void)
{
    /*Assuming that PLL0 has been setup with CCLK = 60Mhz and PCLK also = 60Mhz.*/
   
    T0CTCR = 0x0;
    T0PR = PRESCALE-1; //(Value in Decimal!) - Increment T0TC at every 60000 clock cycles
                     //Count begins from zero hence subtracting 1
                     //60000 clock cycles @60Mhz = 1 mS

	T0TCR = 0x02; //Reset Timer
}

void delayMS(unsigned int milliseconds) //Using Timer0
{
	T0TCR = 0x02; //Reset Timer

    T0TCR = 0x01; //Enable timer
   
    while(T0TC < milliseconds); //wait until timer counter reaches the desired delay
   
    T0TCR = 0x00; //Disable timer
}
