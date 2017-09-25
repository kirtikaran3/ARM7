#include <LPC213X.H>

/****************LCD DIRECTIVES***************/
#define LCD_CLEAR        0x01
#define CURSOR_OFF     0x0C
#define FIRST_ROW        0x80
#define SECOND_ROW    0xC0
#define Enable_Pulse()    IOSET0|=1<<EN;Delay_ms(1);IOCLR0=1<<EN;Delay_ms(1);
/*Pin Configuration for LCD*/
#define        RS                2
#define        RW                3
#define        EN                4
/*********************************************/

/*********************************************/
/**************Function Prototypes************/
void UART0_Init(void);
void UART0_Write(unsigned char value);
void UART0_Write_Text(unsigned char msg[]);
unsigned char UART0_Read(void);

void Lcd_Init(void);
void Lcd_Cmd(unsigned char value);
void Lcd_Write(unsigned char value);
void Lcd_Write_Text(unsigned char msg[]);
void Lcd_Data_Shift(unsigned char value);

void Delay_ms(unsigned long times);

/*********************************************/

int main()
{
    unsigned char msg[] = "DKOP Labs";
    unsigned char echo_test[] = "Workshop Demo";
    unsigned char received_data[] = "RECEIVED DATA:";
    
    unsigned char temp;
    
    Lcd_Init();
    UART0_Init();
    Delay_ms(10);
    UART0_Write_Text(msg);
    UART0_Write(10);
    UART0_Write(13);
    UART0_Write_Text(echo_test);
    UART0_Write(10);
    UART0_Write(13);
    
    Lcd_Write_Text(msg);
    Lcd_Cmd(SECOND_ROW);
    Lcd_Write_Text(echo_test);
    Delay_ms(1000);
    Lcd_Cmd(LCD_CLEAR);                    //Clear the LCD
    Lcd_Write_Text(received_data);
    Lcd_Cmd(SECOND_ROW);
    while(1)
    {
        Lcd_Cmd(SECOND_ROW);
        temp = UART0_Read();
        UART0_Write(temp);
        Lcd_Write(temp);
    }
}

/****************Function Definition**********/

/****************Delay Function***************/
void Delay_ms(unsigned long times)
{
    unsigned long i,j;
    for(j=0;j<times;j++)
        for(i=0;i<7500;i++);
}
/*********************************************/

/*****************LCD Functions***************/
void Lcd_Init(void)
{
    IODIR0 |= (1<<RS);                    //RS Pin as Output Pin
    IODIR0 |= (1<<RW);                    //RW Pin as Output Pin
    IODIR0 |= (1<<EN);                    //EN Pin as Output Pin
    
    IODIR0 |= 0x0000FF00;                //P0.8 to P0.15 as Data Line of LCD
    
    Lcd_Cmd(0x38);                            //Send 8-bit initialization command to lcd
    Delay_ms(10);
    Lcd_Cmd(CURSOR_OFF);                //Cursor OFF
    Delay_ms(10);
    Lcd_Cmd(LCD_CLEAR);
    Delay_ms(1);
    Lcd_Cmd(FIRST_ROW);
}

void Lcd_Data_Shift(unsigned char value)
{
    /*
    This Function will shift the eight bit data stored in variable value,
    to the Port Pin P0.8 to P0.15 Successfully.
    */
    unsigned char i;
    
    for(i=0;i<8;i++)
    {
        if(value & 0x01)
        {
            IOSET0 |= (1<<(i+8));
        }
        else
        {
            IOCLR0 |= (1<<(i+8));
        }
        value = value >> 1;
    }
}

void Lcd_Cmd(unsigned char value)
{
    /*Configure LCD for receiving Command Data*/
    IOCLR0 |= (1<<RS);
    IOCLR0 |= (1<<RW);
    IOSET0 |= (1<<EN);
    Lcd_Data_Shift(value);
    Enable_Pulse();
}

void Lcd_Write(unsigned char value)
{
    /*Configure LCD for receiving Display Data*/
    IOSET0 |= (1<<RS);
    IOCLR0 |= (1<<RW);
    IOSET0 |= (1<<EN);
    Lcd_Data_Shift(value);
    Enable_Pulse();
}

void Lcd_Write_Text(unsigned char msg[])
{
    while(*msg)
    {
        Lcd_Write(*msg);
        msg++;
    }
}

/*********************************************/

/***************UART-0 Functions**************/
void UART0_Init(void)
{
    PINSEL0 = 0x00000005;                //P0.0 as TX0 and P0.1 as RX0
    U0LCR = 0x83;                                //Enable access to Divisor Latches
    //and Set 8 bit Character Length with 1 Stop bit and Parity Disabled
    //Access to Divisor Latches is Enabled, in order to write Baud Rate Generator Registers
    
    //Values to be written in Baud Rate Registers U0DLM and U0LL
    /*
    Formula is
    
    Baud_Rate = PCLK*MulVal / [(16*(256*U0DLM+U0DLL)*(MulVal + DivAddVal))]
    
    Example:-
    MulVal = 1;
    DivAddVal = 0;
    Baud_Rate = 9600;
    PCLK = 15MHz
    U0DLM = 0;
    
    Hence,
    U0DLL = 15000000/(9600*16) = 97.65625 = 98
    U0DLL = 98 = 0x62
    */
    U0DLM = 0x00;
    U0DLL = 0x62;                                    //Baud Rate of 9600
    U0LCR = 0x03;                                    //Disable Access to Divisor Latches
}

void UART0_Write(unsigned char value)
{
    /*    
    THRE bit can be extracted by this U0LSR & 0x20
    THRE = 0 means data is present.
    THRE = 1 means register is empty.
    In order to transmit data, we have to wait will the THRE = 1,
    then only we can transmit data.
    */
    
    while(!(U0LSR&0x20));                        //THRE = 0 stay here
    U0THR = value;
}

void UART0_Write_Text(unsigned char msg[])
{
    while(*msg)
    {
        UART0_Write(*msg);
        msg++;
    }
}

unsigned char UART0_Read(void)
{
    /*
    Receiver Data Ready = U0LSR.0 bit
    RDR bit can be extracted by this U0LSR & 0x01
    RDR = 0 means no Data is Received in U0RBR
    RDR = 1 means that Data is present in U0RBR
    */
    while(!(U0LSR & 0x01));                        //RDR = 0 stay here
    return (U0RBR);
}