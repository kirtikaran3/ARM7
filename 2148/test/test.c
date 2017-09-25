#include <LPC213X.H> 


 
#define switch_1 (IO0PIN&0X01)
#define led (0xff<<1)
 
void delay();
 
int main()
   {
        PINSEL0=0X00000000;
        IO0DIR=0Xfffffffe;
        IO0CLR=led;
        while(1)
          {
                if(switch_1==1)
                  {
                        IO0SET=led;
                        delay();
                        IO0CLR=led;
                        delay();
                   }
          }
  }
 
void delay()
  {
        int i,j;
        for(i=0;i<100;i++)
           for(j=0;j<600;j++);
  }
