#include <LPC213X.H>


#define THRE (1<<5) // Transmit Holding Register Empty
#define RDR (1<<0) // Receiver Data Ready
#define MULVAL 15
#define DIVADDVAL 1
#define NEW_LINE 0xA // Character for new line .. analogus '\n'
#define ENTER 0xD // Ascii code for Enter 

void initUART0(void); // same code as in example 1

char U0Read(void); 

int main(void){
 
	initUART0();
	
	while(1){
		char c = U0Read(); // Read Data from Rx
		}
	
	//return 0;
} 
void initUART0(void)
{
	PINSEL0 = 0x5;  /* Select TxD for P0.0 and RxD for P0.1 */
	U0LCR = 3 | (1<<7) ; /* 8 bits, no Parity, 1 Stop bit | DLAB set to 1  */
	U0DLL = 110;
	U0DLM = 1;   
	U0FDR = (MULVAL<<4) | DIVADDVAL; /* MULVAL=15(bits - 7:4) , DIVADDVAL=0(bits - 3:0)  */
	U0LCR &= 0x0F; // Set DLAB=0 to lock MULVAL and DIVADDVAL
	//BaudRate is now ~9600 and we are ready for UART communication!
}

char U0Read(void){
	while( !(U0LSR & RDR ) ); // wait till any data arrives into Rx FIFO
	return U0RBR;
}