#include <LPC213X.H>  

void delay(){
int i,j; 
	
		for(i=0;i<1000;i++){
			for(j=0;j<100;j++);
		}

}
int main(){

		PINSEL0 =0x00000000; 
		PINSEL1 =0x00000000; 
   	
		IODIR1 = 0x000000FF; 
	  IODIR0 = 0x00000000; 
	
			
	while(1){
		
			if(!(IOPIN0&(1<<1))&&(IOPIN0&(1<<0))){
			
				IOSET1=0xFFFFFFFF; 
					delay();
			} 
			
			if(!(IOPIN0&(1<<0))&&(IOPIN0&(1<<1))){
				IOCLR1=0xFFFFFFFF;
				delay();
			}


		}

}
