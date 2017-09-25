#include <LPC213X.H> 

int main(void)
{
	IO0DIR &= ~((1<<7)) ; // explicitly making P0.7 as Input - even though by default its already Input
	IO0DIR |= (1<<30); // Configuring P0.30 as Output 

	while(1)
	{
		if( !(IO0PIN & (1<<7)) ) // Evaluates to True for a 'LOW' on P0.7
		{
			IO0SET |= (1<<30); // drive P0.30 High
		}
	}
	return 0; // this wont execute ever :P
}	