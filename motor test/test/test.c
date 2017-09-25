#include <LPC213X.H> 

int main(){

IO0DIR =0x0000000F; 
IO1DIR =0xffff0000;	
while(1){

 if(((IO1PIN & (1<<16)))&&(!(IO1PIN & (1<<17))))

            {     
							IO0SET |=(1<<0); 
							IO0SET |=(1<<2);
            }

  else if((!(IO1PIN & (1<<16)))&&((IO1PIN & (1<<17)))){
					IO0SET |=(1<<3); 
							IO0SET |=(1<<1);
}
}
}