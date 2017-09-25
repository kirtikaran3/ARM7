#include <LPC213X.H> 

#define RS	0x10000
#define RW	0x20000
#define EN	0x40000

void lcd_cmd  (unsigned char);
void lcd_data (unsigned char);
void lcd_initialize (void);
void lcd_display (void);
void LCD4_Convert(unsigned char);

const unsigned char cmd[4] = {0x28,0x0c,0x06,0x01};				//lcd commands

unsigned char msg[] = {"This is DKOP Labs"};						//msg
unsigned char msg1[]= {" and embedded is awesome"};						//msg1


void delay(unsigned int n)
{
	unsigned int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<12000;j++)
		{;}
	}
}
//----------------------------------
//		LCD Command Send
//----------------------------------
void lcd_cmd(unsigned char data)
{
	
	IOCLR0	|= RS;			//0x1000;		//RS
	IOCLR0	|= RW;			//0x2000;		//RW
	LCD4_Convert(data);
}

void lcd_initialize(void)
{
	int i;
	for(i=0;i<4;i++)
	{
		IOCLR0 = 0xF << 19;			//IOCLR 0/1
		lcd_cmd(cmd[i]);
		delay(15); 
	}
}


//----------------------------------
//		LCD Data Send
//----------------------------------
void lcd_data (unsigned char data)
{
	
	IOSET0	|= RS;			//0x1000;		//RS
	IOCLR0	|= RW;			//0x2000;		//RW
	LCD4_Convert(data);
}



//----------------------------------
//		LCD Display Msg
//----------------------------------
void lcd_display (void)
{
	char i;

	/* first line message */
	lcd_cmd(0x80);
	delay(15); 
	i=0;
	while(msg[i]!='\0')
	{
		delay(5);
		lcd_data(msg[i]);
		i++;
	}
	delay(15); 

	/* second line message */

	lcd_cmd(0xc0);
	delay(15); 
	i=0;
	while(msg1[i]!='\0')
	{
		delay(5);
		lcd_data(msg1[i]);
		i++;
	}
	delay(15); 
}

void LCD4_Convert(unsigned char c)
{

	if(c & 0x80) IOSET0 = 1 << 22; else IOCLR0 = 1 << 22;
	if(c & 0x40) IOSET0 = 1 << 21; else IOCLR0 = 1 << 21;
	if(c & 0x20) IOSET0 = 1 << 20; else IOCLR0 = 1 << 20;
	if(c & 0x10) IOSET0 = 1 << 19; else IOCLR0 = 1 << 19;

	IOSET0	= EN;											//0x4000;		//EN
	delay(8); 
	IOCLR0	= EN;											//0x4000;		//EN

	if(c & 0x08) IOSET0 = 1 << 22; else IOCLR0 = 1 << 22;
	if(c & 0x04) IOSET0 = 1 << 21; else IOCLR0 = 1 << 21;
	if(c & 0x02) IOSET0 = 1 << 20; else IOCLR0 = 1 << 20;
	if(c & 0x01) IOSET0 = 1 << 19; else IOCLR0 = 1 << 19;

	IOSET0	= EN;											//0x4000;		//EN
	delay(8); 
	IOCLR0	= EN;											//0x4000;		//EN
}


void main()
{
	PINSEL1	=	0; 								//Configure P0.16 - P0.31 as GPIO
	IODIR0	=	0xFF << 16;						//Configure Pins P0.16 - P0.22 as Output Pins
	lcd_initialize();							//Initialize LCD!
	lcd_display();								//Display Message in LCD
	while(1);
}

