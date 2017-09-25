#include <LPC213X.H> 

int main(){

IO0DIR=0x000000ff; 
IO1DIR=0x00000000; 
	
	while(1){
	
	if(!(IO1PIN&(1<<16))){
	IO0SET=0x00000055; 
	IO0CLR=0x000000aa;
	} 
	if(!(IO1PIN&(1<<17))){
	IO0SET=0x000000aa; 
	IO0CLR=0x00000055;
	}
		
	}
	



}
