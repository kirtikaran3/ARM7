#include <LPC213X.H>

//Function Prototype
__irq void Timer0_IRQ(void);


/*Main Function Starts*/
int main()
{
    //Port-0.0 tp Port-0.7 pins as Output Pin
    IODIR0 = 0x000000FF;

    //Timer-0 Configuration
    T0PR  = 0x00000000;                                //Pre-Scalar is Zero
    T0MR0 = 7500000L;                                    //Value Loaded in MR0 Register(Match Register)
    //500 msec Delay
    
    T0MCR = 3;                                                //Match Control Register
    //When TC = MR0, MR0 interrupt will Occur

    T0TC = 0x00;                                            //Value in Timer-Control Register
    T0TCR = 0x00000001;                                //Start Timer-0

    VICVectAddr4 = (unsigned)Timer0_IRQ;
    VICVectCntl4 = (0x20 | 4);
    VICIntEnable = (1UL << 4);                //Enable Timer0 Interrupt

    while(1)
    {
        //Stay in Loop For-Ever
    }
}


/*Function Definitions*/
/*Timer-0 IRQ Interrupt Service Routine Code*/
__irq void Timer0_IRQ(void)            // Timer0 ISR
{
    IO0PIN ^= 0x000000FF;                    // Toggle P0.0 Output
  T0IR = (1UL<<0);                            //Clear Timer Match0 Interrupt Flag
    VICVectAddr = 0;                            // Acknowledge Interrupt
}
