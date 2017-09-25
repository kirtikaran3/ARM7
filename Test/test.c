#include <LPC213X.H> 

void delay(){
int i,j;
	for( i=0;i<100;i++){
		for( j=0;j<1000;j++);
	}

}
int main(){

	PINSEL0=0x00000000; 
	PINSEL1=0x00000000;
	IODIR0 |=(1<<1)|(1<<2)|(1<<0);  
	IODIR1 &=!(1<<16)|(1<<17);
	
	while(1){
	
		if(((IOPIN1&(1<<16))&&(IOPIN1&(1<<17)))){
		IO0SET=0x00000003; 
		delay(); 
		IO0CLR=0x00000003;
		delay();
		} 
		
				else if(((IOPIN1&(1<<16))&&(!(IOPIN1&(1<<17))))){
							
									IO0SET=0x0000002; 
									delay(); 
									IO0CLR=0x00000002;
									delay();
					} 
		
							else if((!(IOPIN1&(1<<16))&&(IOPIN1&(1<<17)))){
		
									IO0SET=0x0000004; 
									delay(); 
									IO0CLR=0x00000004;
									delay();
							} 
								
							else if((!(IOPIN1&(1<<16))&&(!(IOPIN1&(1<<17))))){
								IO0SET=0x0000007; 
									delay(); 
									IO0CLR=0x00000007;
									delay();
							}
	
			} 
	
} 

