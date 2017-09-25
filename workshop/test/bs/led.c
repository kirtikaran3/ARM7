#include <LPC213X.H> 

void delay(int i){
int j,k; 
	
for(j=0;j<i;j++){
for(k=0;k<j;k++);
}

}

int main(){

IO0DIR=0x000000ff; 
	
while(1){

IO0SET=0x000000ff; 
delay(1000); 
IO0CLR=0x000000ff; 
delay(1000);
}


}
