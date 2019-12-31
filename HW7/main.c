#include <nds32_intrinsic.h>
#include "WT58F2C9.h"
#include "gpio.h"
#include "pwm.h"


void delay1(unsigned int nCount)
{
   volatile unsigned int i;
   for (i=0;i<nCount;i++);
}


/* Intrrupt memory address */
#define INT_MEM_ADDR_BASE			(0x00200D00)
#define rINT0_IE0_ENABLE			(INT_MEM_ADDR_BASE+0x00)
#define rINT0_IE1_ENABLE			(INT_MEM_ADDR_BASE+0x04)
#define rINT0_IE2_ENABLE			(INT_MEM_ADDR_BASE+0x08)
#define rINT1_IE0_ENABLE			(INT_MEM_ADDR_BASE+0x10)
#define rINT1_IE1_ENABLE			(INT_MEM_ADDR_BASE+0x14)
#define rINT1_IE2_ENABLE			(INT_MEM_ADDR_BASE+0x18)

#define rINT0_IE0_FLAG				(INT_MEM_ADDR_BASE+0x20)
#define rINT0_IE1_FLAG				(INT_MEM_ADDR_BASE+0x24)
#define rINT0_IE2_FLAG				(INT_MEM_ADDR_BASE+0x28)
#define rINT1_IE0_FLAG				(INT_MEM_ADDR_BASE+0x30)
#define rINT1_IE1_FLAG				(INT_MEM_ADDR_BASE+0x34)
#define rINT1_IE2_FLAG				(INT_MEM_ADDR_BASE+0x38)


inline void GIE_ENABLE();

void DRV_EnableHWInt (void)
{
	/* enable SW0, HW0 and HW1 */
	__nds32__mtsr(0x10003, NDS32_SR_INT_MASK);
	/* Enable SW0 */
	//__nds32__mtsr(0x10000, NDS32_SR_INT_MASK);
	/* Enable global interrupt */
	GIE_ENABLE();
}

void DRV_BlockIntDisable(void)
{
	// Disable all interrupt
	OUTW(rINT0_IE0_ENABLE, 0x0000);
	OUTW(rINT0_IE1_ENABLE, 0x0000);
	OUTW(rINT0_IE2_ENABLE, 0x0000);
	OUTW(rINT1_IE0_ENABLE, 0x0000);
	OUTW(rINT1_IE1_ENABLE, 0x0000);
	OUTW(rINT1_IE2_ENABLE, 0x0000);
}

void DRV_IntInitial(void)
{
	// Disable all interrupt
	DRV_BlockIntDisable();

	// Enable all HW interrupt
	DRV_EnableHWInt();				//Enable global Hardware interrupt, Assembly command

	// Enable default Block interrupt
	//DRV_BlockIntEnable();			//Enable each block device interrupt

}

#define rSYS_OPTION1	(0x00200004)

void DRV_SysXtal(U8 u8XtalMode)
{

	#if(EXTERNAL_XTAL == XTAL_MODE)
		//-----External Crystal
		//-----24MHz
		OUTW(rSYS_OPTION1,((INW(rSYS_OPTION1)&0xFFFFFF00) | 0x0012)); //Use HXTAL and divide 2
		//-----Crystal 12MHz
		//OUTW(rSYS_OPTION1, (INW(rSYS_OPTION1) | 0x000A));

		//OUTW(rSYS_OPTION1,(INW(rSYS_OPTION1) | (XTAL<<2) | (HSE_OSC_ON <<1)));
		//OUTW(rSYS_CLOCK_SELECT,(INW(rSYS_CLOCK_SELECT) | 0x0001));
	#else
		//-----Internal RC
		//-----24MHz
		//OUTW(rSYS_OPTION1,(INW(rSYS_OPTION1) | 0x0012));
		//-----Crystal 12MHz
		//OUTW(rSYS_OPTION1, (INW(rSYS_OPTION1) | 0x000A));

		//OUTW(rSYS_OPTION1,(INW(rSYS_OPTION1) | (XTAL<<2)));
		//OUTW(rSYS_CLOCK_SELECT,(INW(rSYS_CLOCK_SELECT));
	#endif
	//-----MCU Clock Output Test
	//OUTW(rSYS_OPTION3,0x0090);
}

void OS_PowerOnDriverInitial(void)
{
	//========================= << Typedef Initial  >>
	//SYS_TypeDefInitial();
	//========================= << System Clock Initial >>
	//-----External Crystal
	DRV_SysXtal(EXTERNAL_XTAL);
	//========================= << Interrupt Initial >>
	DRV_IntInitial();
	//========================= << GPIO Initial >>
	//DRV_GpioInitial();
	//========================= << UART Initial >>
	//DRV_UartInitial();
	//========================= << Timer Initial >>
	//DRV_TimerInitial(TIMER_0, SIMPLE_TIMER);
	//DRV_TimerInitial(TIMER_1, SIMPLE_TIMER);
	//========================= << PWM Initial >>
	//DRV_PwmInitial();
	//========================= << SPI Initial >>
	//DRV_SpiInitial(SPI_CH2);
	//========================= << Watchdog Initial >>
}




//-----  UART Functions  -----
#define UART3_ADDR_BASE		(0x0020B400)
#define UART3_CR1			(UART3_ADDR_BASE+0x00)
#define UART3_CR2			(UART3_ADDR_BASE+0x04)

//0:1 Start bit/8 Data bits/1 Stop bit,
#define	UART_FORMAT_N81	0
//1:1 Start bit/9 Data bits/1 Stop bit
#define	UART_FORMAT_N91	1

#define UART_EN				(1<<17)	//0:Disable, 1:Enable
#define UART_TX_EN			(1<<15)
#define UART_RX_EN			(1<<14)
#define UART_OVER8			(1<<13)
#define UART_OVER16			(0<<13)
#define UART_WORD_LENGTH	(UART_FORMAT_N81<<12)//	//0:1 Start bit/8 Data bits/1 Stop bit, //1:1 Start bit/9 Data bits/1 Stop bit
#define UART_TX_DMA_EN		(1<<11) //0:Disable, 1:Enable
#define UART_RX_DMA_EN		(1<<10)	// 0:Disable, 1:Enable
#define UART_RX_WAKEUP		(0<<9)	// 0:In active mode, 1:In mute mode
#define UART_WAKEUP_METHOD	(0<<8)	// 0:Idle mode, 1:Address mark
#define UART_UART_ADDR_NODE	(0x5<<4)	//Data 0x0=xxxx0000b ~ 0xF=xxxx1111b,
#define UART_PARITY_EN		(0<<2)//SET_BIT1//(n<<1) //0:Disable, 1:Enable
#define UART_PARITY_SEL		(1<<1)// O:Even 1:Odd
#define UART_STOP_BIT	0// O:1-bit 1:2-bit

#define UART_SET_CTL_PARA	UART_EN|UART_TX_EN|UART_RX_EN|UART_WORD_LENGTH\
							|UART_RX_WAKEUP|UART_WAKEUP_METHOD|UART_UART_ADDR_NODE\
							|UART_PARITY_EN|UART_PARITY_SEL|UART_STOP_BIT

//HXTAL = HXTAL_24M (OVER8=0)
//9600 = 156.25
#define BUARRATE_9600_MANTISSA_24MHZ	156
#define BUARRATE_9600_FRACTION_24MHZ	4
//19200 = 78.125
#define BUARRATE_19200_MANTISSA_24MHZ	78
#define BUARRATE_19200_FRACTION_24MHZ	2
//38400 = 39.0625
#define BUARRATE_38400_MANTISSA_24MHZ	39
#define BUARRATE_38400_FRACTION_24MHZ	1
//57600 = 26.0625
#define BUARRATE_57600_MANTISSA_24MHZ	26
#define BUARRATE_57600_FRACTION_24MHZ	1
//115200 = 13.0
#define BUARRATE_115200_MANTISSA_24MHZ	13
#define BUARRATE_115200_FRACTION_24MHZ	0
//230400 = 6.5
#define BUARRATE_230400_MANTISSA_24MHZ	6
#define BUARRATE_230400_FRACTION_24MHZ	8
//921600 = 1.625
#define BUARRATE_921600_MANTISSA_24MHZ	1
#define BUARRATE_921600_FRACTION_24MHZ	10


#define FALSE 0
#define TRUE  1
#define UART_TXD_BUFFER_SIZE	24
#define _EOS_	'\0' //End of string

char u8TxdBuf[UART_TXD_BUFFER_SIZE];

void DRV_PutChar(char u8Char)
{
	U16 u16Count;

	OUTW(UART3_ADDR_BASE+0x0C, u8Char);

	u16Count = 0;
	//Wait transmission complete then clear by SW write to 0
	while((INW(UART3_ADDR_BASE+0x08)&0x00000020) == 0)
	{
	#if 1 //Don't delete.
		//-----Time out
		u16Count++;
		if(u16Count >= 1000)
		{
			break;
		}
	#endif
	}
	OUTW(UART3_ADDR_BASE+0x08, INW(UART3_ADDR_BASE+0x08) & 0xFFFFFFDF);
}

void DRV_PutStr(const char *pFmt)
{
	U8 u8Buffer;	//Character buffer

	while (1)
	{
		u8Buffer = *pFmt; //Get a character
		if(u8Buffer == _EOS_) //Check end of string
			break;

		DRV_PutChar(u8Buffer); //Put a character
		pFmt++;
	}
}

void DRV_IntToStr(U16 u16Val, U8 u8Base, char *pBuf, U8 u8Length)
{
	U8 bShowZero = FALSE;
	U16 u16Divider;
	U8 u8Disp;
	U16 u16Temp;

	u8Length -= 1;
	if(u8Base == 16) //Hex
	{
		u16Temp = 0x01 << u8Length;
	}
	else //Dec
	{
		u16Temp = 1;
		while(u8Length--)
		{
			u16Temp *= 10;
		}
	}

	if( 0 == u16Val )
	{
		if( 16 == u8Base )
		{
			pBuf[0] = '0';
			pBuf[1] = '0';
			pBuf[2] = '0';
			pBuf[3] = '0';
			pBuf[4] = '\0';
		}
		else
		{
			pBuf[0] = '0';
			pBuf[1] = '0';
			pBuf[2] = '0';
			pBuf[3] = '0';
			pBuf[4] = '0';
			pBuf[5] = '\0';
		}
		return;
	}

	if( 16 == u8Base )
	{
		u16Divider = 0x1000;
	}
	else
	{
		u16Divider = 10000;
	}

	while( u16Divider )
	{
		u8Disp = u16Val / u16Divider;
		u16Val = u16Val % u16Divider;

		if(u16Temp == u16Divider)
		{
			bShowZero = TRUE;
		}
		if( u8Disp || bShowZero || (u16Divider>0))
		{
			if( u8Disp < 10 )
				*pBuf = '0' + u8Disp;
			else
				*pBuf = 'A' + u8Disp - 10;
			pBuf ++;
		}

		if( 16 == u8Base )
		{
			u16Divider /= 0x10;
			if(bShowZero)
				u16Temp /= 0x10;
		}
		else
		{
			u16Divider /= 10;
			if(bShowZero)
				u16Temp /= 10;
		}
	}
	*pBuf = '\0';
}

void DRV_Printf(char *pFmt, U16 u16Val)
{
	U8 u8Buffer;

	//-----Pin configuration for UART3
	GPIO_PTC_FS = 0x0300;
	GPIO_PTC_PADINSEL = 0x0000;
	GPIO_PTC_DIR = 0xFEFF;
	GPIO_PTC_CFG = 0x0000;

	//UART Parameter
	OUTW(UART3_ADDR_BASE+0x00, UART_SET_CTL_PARA);

	//Set Baud rate with default sysclk
	OUTW(UART3_ADDR_BASE+0x14, ((BUARRATE_38400_MANTISSA_24MHZ<<4)|BUARRATE_38400_FRACTION_24MHZ)/2); //38400 for 12MHz MCUCLK

	while((u8Buffer =(U8)*(pFmt++)))
	{
		if(u8Buffer == '%') //check special case
		{
			switch(*(pFmt++)) //check next character
			{
				case 'x': //hexadecimal number
				case 'X':
					DRV_IntToStr(u16Val, 16, u8TxdBuf, 2);
					DRV_PutStr(u8TxdBuf);
				break;
				case 'd': //decimal number
				case 'i':
					DRV_IntToStr(u16Val, 10, u8TxdBuf,5);
					DRV_PutStr(u8TxdBuf);
				break;
				case 'c':
				case 'C':
					DRV_PutChar((char)u16Val);
				break;
			} //switch
		}
		else //general
		{
			DRV_PutChar(u8Buffer); //put a character
		}
	}
}


//-----  PWM Functions  -----
#define PWM_EN			*((volatile unsigned int *)0x00208C00)
#define PWM_BAS_CLK		*((volatile unsigned int *)0x00208C04)
#define PWM_CLK8		*((volatile unsigned int *)0x00208C28)
#define PWM8			*((volatile unsigned int *)0x00208C58)
#define PERIOD_8		*((volatile unsigned int *)0x00208C88)


typedef struct data
{
	int kk;
	int pp;
}Data;


int duration = 300000;
int key = 0xFF,tmp,col,flag = 1 ;
int pitch[3][7] = {
	{{NOTE_C4},{NOTE_D4},{NOTE_E4},{NOTE_F4},{NOTE_G4},{NOTE_A4},{NOTE_B4}},
	{{NOTE_C5},{NOTE_D5},{NOTE_E5},{NOTE_F5},{NOTE_G5},{NOTE_A5},{NOTE_B5}},
	{{NOTE_C6},{NOTE_D6},{NOTE_E6},{NOTE_F6},{NOTE_G6},{NOTE_A6},{NOTE_B6}},
};
int chart[50][2];


void song()
{
	int music [][2]= {{NOTE_G4,1},{NOTE_C5,1},{NOTE_C5,1},{NOTE_E5,1},{NOTE_D5,1},{NOTE_C5,2},
						{NOTE_C5,1},{NOTE_G4,1},{NOTE_C5,1},{NOTE_E5,1},{NOTE_G5,1},{NOTE_G5,1},{NOTE_C5,2},
						{NOTE_E5,1},{NOTE_F5,1},{NOTE_F5,1},{NOTE_F5,1},{NOTE_F5,1},{NOTE_F5,1},{NOTE_E5,1},{NOTE_D5,1},{NOTE_D5,1},{NOTE_D5,1},{NOTE_C5,1},
						{NOTE_D5,1},{NOTE_E5,1},{NOTE_G4,2},
						{NOTE_G4,1},{NOTE_C5,1},{NOTE_C5,1},{NOTE_E5,1},{NOTE_D5,1},{NOTE_C5,2},
						{NOTE_C5,1},{NOTE_G4,1},{NOTE_C5,1},{NOTE_E5,1},{NOTE_G5,1},{NOTE_G5,1},{NOTE_C5,2},
						{NOTE_E5,1},{NOTE_F5,1},{NOTE_F5,1},{NOTE_F5,1},{NOTE_D5,1},{NOTE_E5,1},{NOTE_D5,1},{NOTE_C5,1},{NOTE_E5,1},
						{NOTE_D5,1},{NOTE_G4,1},{NOTE_B4,1},{NOTE_D5,1},{NOTE_C5,2},
			};

	int i;
	//翹翻瞼X繒w聶羸穠繙繙q
	for(i=0;i<sizeof music/sizeof music[0];i++){
		PERIOD_8 = 200000 / music[i][0]; // �喲�
		PWM8 = (int) PERIOD_8 / 100; 	 // �喲�
		delay1(duration*music[i][1]);	 // �瑕漲

		//delay duty cycle = 0
		PWM8 = 0;
		delay1( ONE_SECOND/100);
	}
}

void read_key_matrix()
{
	key = 0xFF;
	GPIO_PTA_DIR = 0x0FF0;
	GPIO_PTA_CFG = 0x0000;
	for (col=0; col<4; col++)
	{
		GPIO_PTA_BS = 0x000F;
		GPIO_PTA_BR = 0x0000 | (1 << col);
		tmp = ((~GPIO_PTA_PADIN) & 0xFF0) >> 4;
		if (tmp > 0)//read Key Matrix
		{
			if (tmp & 0x1)
				key = 0*4 + col +1;
			else if (tmp & 0x2)
				key = 1*4 + col +1;
			else if (tmp & 0x4)
				key = 2*4 + col+1;
			else if (tmp & 0x8)
				key = 3*4 + col+1;
			break;
		}
	}

	if (key != 0xFF && flag == 1)
	{
		flag = 0; // separate the Key Matrix
	}

	if(key == 0xFF )
	{
		flag = 1;
	}

}

void sound(int k,int p)
{
	PERIOD_8 = 200000 / pitch[p][k-1]; 
	PWM8 = (int) PERIOD_8 / 100; 	
	delay1(duration*1);	 // �瑕漲
}

void record(int k,int p ,int index)
{
	chart[index][0] = k;
	chart[index][1] = p;
}

void play(int index)
{	
	int i;
	for(i=0;i<index;i++)
	{
		int temp = pitch[chart[i][1]][chart[i][0]-1];
		PERIOD_8 = 200000 / temp ; // �喲�
		PWM8 = (int) PERIOD_8 / 100; 	 // �喲�
		delay1(duration*1);	 // �瑕漲

		//delay duty cycle = 0
		PWM8 = 0;
		delay1( ONE_SECOND/100);
	}
}

int main()
{
	OS_PowerOnDriverInitial();


	DRV_Printf("====================================\r\n", 0);
	DRV_Printf("   ADP-WT58F2C9 PWM demo program   \r\n", 0);
	DRV_Printf("====================================\r\n", 0);


	DRV_Printf("PWM testing ...\r\n", 0);

	GPIO_PTC_FS = 0xF000; //for PWM Function

	PWM_EN = 0x000; //Disable all PWM function

	PWM_BAS_CLK = 0x01;
	PWM_CLK8 = 60;
	PWM8 = 0x0;
	PWM_EN = 0x100; //PWM8

	// sound1();
	int pitch_index = 1;
	int fuck = 0;
	int index = 0 ;

	while(1)
	{
		read_key_matrix();

		if(key == 0xFF)
		{
			PWM8 = 0x0;
		}

		if(key <= 7 && key >= 1)
		{
			sound(key,pitch_index);
			if(fuck == 1)
			{
				record(key,pitch_index,index);
				index += 1;
			}
		}

		if(key <= 11 && key >= 9)
		{
			pitch_index = key - 9;
		}

		if(key == 13)
		{
			delay1(duration);
			if(fuck == 0)
			{
				index = 0;
				fuck = 1;
			}
			else if(fuck == 1)
			{
				fuck = 0;
			}
		}

		if(key == 14)
		{
			play(index);
		}

		if(key == 15)
		{
			song();
		}

		

	}	

	DRV_Printf("====================================\r\n", 0);


	return 0;
}
