#include <LPC213X.H> 

#define sw1 0x00010000 
#define led 0x00010000 

int main(){

IO1DIR=0xffff0000; 
	IO1CLR=0x00000000; 
	IO0DIR=0x00000000; 
	while(1){
	if(!((sw1&IO0PIN)>>16)==1){
	IO1SET=led; 
	} 
	else
	{
	IO1CLR=led;
	}
}
}
