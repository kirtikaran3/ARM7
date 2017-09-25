#include <LPC213X.H> 
void delay(int ch){
int i,j; 
	for(i=0;i<ch;i++){
	for(j=0;j<i;j++);
	}

}
int main()
{
    unsigned char i;
    unsigned status;

    //Port-0.0 tp Port-0.7 pins as Output Pin
    IODIR0 = 0x000000FF;

    //Do Pin Toggling 8-times
    for(i=0;i<8;i++)
    {
        IOSET0 = 0x000000FF;    //P0.0 to P0.7 are high 
				delay(1000);
        IOCLR0 = 0x000000FF; 
				delay(1000);			//P0.0 to P0.7 are low
    }

    //Now we will read the status of the Pin P0.8
    //and Clear the Ports when Button is Pressed, otherwise Ports are High

    while(1)
    {
        status = IOPIN0;
        status = status & 0x00000100;
        if(status == 0x00000100)
        {
            IOSET0 = 0x000000FF;
        }
        else
        {
            IOCLR0 = 0x000000FF;
        }
    }
}