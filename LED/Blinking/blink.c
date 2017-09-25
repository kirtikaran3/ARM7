#include <LPC213X.H>
void delay(int ch){
int i=0,j=0; 
	for(i=0;i<ch;i++){
	for(j=0;j<i;j++);{
	}
} 
} 
int main(){

PINSEL0=0x00000000; 
IODIR0=0xffffffff; 

while(1){
IOSET0=0xffffffff; 
delay(100); 
IOCLR0=0xffffffff; 
delay(100);	
//return 0;

}	


}