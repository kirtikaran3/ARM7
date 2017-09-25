#include <LPC213X.H>
void delay(int i){
int j,k; 
	
	for(j=0;j<i;j++){
	for(k=0;k<j;k++);
	
	}

}
int main(){

int array[]={0x3f,0x06,0x6f}; 
int i;
IO0DIR=0x0000ffff; 
IO1DIR=0x00000000; 
while(1){
if(!(IO1PIN&(1<<16))){
for(i=0;i<3;i++){
	
	IO0SET=array[i]; 
	delay(300); 
	IO0CLR=array[i]; 
	delay(300);
}
}
}
}