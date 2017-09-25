#include <LPC213X.H>


int main(){

	IODIR0 |=(1<<7); 
	
	IODIR1 &=!(1<<16); 
	
	while(1){
			if((IOPIN1&(1<<16))){
			
			blink();
			} 
			else if((!(IOPIN1&(1<<16))){
			
			toggle();
			}
	


		}

}