#include<LPC21xx.h>
void delay(int k){
  for(int i=0;i<k;i++){
  for(int j=0;j<i;j++);
  }

}
int main()
{ 
  IO0DIR=0x0000ffff; 
  
  while(1){
  IO0SET=0x0000ffff; 
  delay(1000); 
  IO0CLR=0x0000ffff; 
  delay(1000);
  }
  return 0;
}
