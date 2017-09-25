#include <LPC213X.H>
 
 
 int main(){
 
 IO0DIR &=~((1<<7)); 
 IO0DIR &=~((1<<8)); 
	IO0DIR |=((1<<30)); 
IO0DIR |=((1<<29)); 

while(1){
if(!(IO0PIN&(1<<7))){
IO0SET |=(1<<30); 
} 
if(!(IO0PIN&(1<<8))){
IO0SET |=(1<<29); 
}
}	 
	 
 
 }