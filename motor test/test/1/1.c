#include <LPC213X.H> 
void delay(int i){
int j,k; 
	
	for(j=0;j<i;j++){
	for(k=0;k<j;k++);
	}


}

int main(){

IO0DIR=0x000000ff;  
IO1DIR=0x00000000;

	while(1){
	if(!(IO1PIN&(1<<16))&&((IO1PIN&(1<<17)))){
	IO0SET=0x00000ff; 
	delay(1000);
 IO0CLR=0x00000ff;
delay(1000);		
	}

}
