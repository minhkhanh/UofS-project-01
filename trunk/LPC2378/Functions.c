#include <LPC23xx.H> 
#include "MyDefine.h"

unsigned long Keys[] = 
{ 
	27, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 0,0,0,0, 
	55, 58, 62, 65, 69, 73, 78, 82, 87, 92, 98, 104, 0,0,0,0, 
	110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 0,0,0,0, 
	220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 0,0,0,0, 
	440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 0,0,0,0, 
	880, 932, 988, 1046, 1109, 1175, 1244, 1318, 1397, 1480, 1568, 1661, 0,0,0,0, 
	1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 0,0,0,0, 
	3520, 3729, 3951, 4186 
};

unsigned int arrFreq[] = 
{
	0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 
	0x3A, 0x3B, 0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 
	0x48, 0x49, 0x4A, 0x4B, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 
	0x56, 0x5
};

unsigned short sine_table256[] = 
	{
		0x0200,0x020c,0x0219,0x0225,0x0232,0x023e,0x024b,0x0257,0x0264,0x0270,0x027c,0x0289,0x0295,0x02a1,0x02ad,0x02b8,
		0x02c4,0x02d0,0x02db,0x02e7,0x02f2,0x02fd,0x0308,0x0312,0x031d,0x0327,0x0332,0x033c,0x0345,0x034f,0x0358,0x0362,
		0x036b,0x0373,0x037c,0x0384,0x038c,0x0394,0x039c,0x03a3,0x03aa,0x03b1,0x03b8,0x03be,0x03c4,0x03ca,0x03cf,0x03d5,
		0x03d9,0x03de,0x03e2,0x03e6,0x03ea,0x03ee,0x03f1,0x03f4,0x03f6,0x03f8,0x03fa,0x03fc,0x03fd,0x03fe,0x03ff,0x03ff,
		0x03ff,0x03ff,0x03ff,0x03fe,0x03fd,0x03fb,0x03f9,0x03f7,0x03f5,0x03f2,0x03ef,0x03ec,0x03e8,0x03e4,0x03e0,0x03dc,
		0x03d7,0x03d2,0x03cd,0x03c7,0x03c1,0x03bb,0x03b4,0x03ae,0x03a7,0x03a0,0x0398,0x0390,0x0388,0x0380,0x0378,0x036f,
		0x0366,0x035d,0x0354,0x034a,0x0340,0x0337,0x032c,0x0322,0x0318,0x030d,0x0302,0x02f7,0x02ec,0x02e1,0x02d5,0x02ca,
		0x02be,0x02b3,0x02a7,0x029b,0x028f,0x0282,0x0276,0x026a,0x025e,0x0251,0x0245,0x0238,0x022c,0x021f,0x0212,0x0206,
		0x01f9,0x01ed,0x01e0,0x01d3,0x01c7,0x01ba,0x01ae,0x01a1,0x0195,0x0189,0x017d,0x0170,0x0164,0x0158,0x014c,0x0141,
		0x0135,0x012a,0x011e,0x0113,0x0108,0x00fd,0x00f2,0x00e7,0x00dd,0x00d3,0x00c8,0x00bf,0x00b5,0x00ab,0x00a2,0x0099,
		0x0090,0x0087,0x007f,0x0077,0x006f,0x0067,0x005f,0x0058,0x0051,0x004b,0x0044,0x003e,0x0038,0x0032,0x002d,0x0028,
		0x0023,0x001f,0x001b,0x0017,0x0013,0x0010,0x000d,0x000a,0x0008,0x0006,0x0004,0x0002,0x0001,0x0000,0x0000,0x0000,
		0x0000,0x0000,0x0001,0x0002,0x0003,0x0005,0x0007,0x0009,0x000b,0x000e,0x0011,0x0015,0x0019,0x001d,0x0021,0x0026,
		0x002a,0x0030,0x0035,0x003b,0x0041,0x0047,0x004e,0x0055,0x005c,0x0063,0x006b,0x0073,0x007b,0x0083,0x008c,0x0094,
		0x009d,0x00a7,0x00b0,0x00ba,0x00c3,0x00cd,0x00d8,0x00e2,0x00ed,0x00f7,0x0102,0x010d,0x0118,0x0124,0x012f,0x013b,
		0x0147,0x0152,0x015e,0x016a,0x0176,0x0183,0x018f,0x019b,0x01a8,0x01b4,0x01c1,0x01cd,0x01da,0x01e6,0x01f3,0x0200
	};

void sendchars(char s[])
{							  
	int iLen = strlen(s);
	int i = 0;
	for ( ; i < iLen; ++i)
	{
		sendchar(s[i]);
	}

	//sendchar(13); 	// end stream
}

void reverse(char s[])
 {
     int i, j;
     char c;
 
     for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
         c = s[i];
         s[i] = s[j];
         s[j] = c;
     }
 }


 void itoa(int n, char s[])
 {
     int i, sign;
 
     if ((sign = n) < 0)  
         n = -n;         
     i = 0;
     do {       
         s[i++] = n % 10 + '0';   
     } while ((n /= 10) > 0);   
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }
 void FillChars(char* st, int size)
 {
	int i = 0;
	for( ; i<size; ++i)
		st[i] = 0;
 }
char * GetString(char * des, char * source,int iStart, int iNum)
{
	int i = iStart;
	if (strlen(source)<(iStart+iNum))
	{
		FillChars(des, MAX_SIZE);
		return des;
	}
	for( ; (i-iStart)<iNum; ++i)
		des[i-iStart] = source[i];
	des[iNum] = 0;
	return des;
}
/* Function that initializes LEDs                                             */
void LED_Init(void) {
	PINSEL10 = 0;                         /* Disable ETM interface, enable LEDs */
	FIO2DIR  = 0x000000FF;                /* P2.0..7 defined as Outputs         */
	FIO2MASK = 0x00000000;
}

/* Function that turns on requested LED                                       */
void LED_On (unsigned int num) {
	FIO2SET = (1 << num);
}

/* Function that turns off requested LED                                      */
void LED_Off (unsigned int num) {
	FIO2CLR = (1 << num);
}

/* Function that outputs value to LEDs                                        */
void LED_Out(unsigned int value) {
	FIO2CLR = 0xFF;                       /* Turn off all LEDs                  */
	FIO2SET = (value & 0xFF);             /* Turn on requested LEDs             */
}
void ProcCmdNow(char *sCmd, char *sTemp)
{
	char sec[3];
	char min[3];
	char hour[3];
	char result[9];
	if (strcmp(GetString(sTemp, sCmd, 4, 3), "set") == 0)
	{
		GetString(hour, sCmd, 8, 2);
		GetString(min, sCmd, 11, 2);
		GetString(sec, sCmd, 14, 2);
		RTCSet(atoi(hour), atoi(min), atoi(sec));
		sendchars("Set time complete!\n\r");
	}
	else if (strcmp(GetString(sTemp, sCmd, 4, 3), "get") == 0)
	{
		RTCGet(result);
		sendchars("The time is: ");
		sendchars(result);
		sendchars("\n\r");
	}
	else if ((strcmp(GetString(sTemp, sCmd, 4, 4), "help") == 0)||(strcmp(GetString(sTemp, sCmd, 4, 1), "?") == 0))
	{
		sendchars("Set or get time on Embedded system.\n\r");
		sendchars("   now set hh:mm:ss     set time.\n\r");
		sendchars("   now get              get time.\n\r");
		sendchars("   now ?                show help.\n\r");
	}
	else
	{
		sendchars("The syntax of the command is incorrect.\n\r");
		sendchars("Enter now ? to show help.\n\r");
	}
}
void ProcCmdMSSV()
{
	sendchars("Show MSSV of us.\n\r");
	sendchars("   0812223     Tran Minh Khanh.\n\r");
	sendchars("   0812239     Nguyen Anh Khoi.\n\r");	
}
void ProcCmdReset(char *sCmd, char *sTemp)
{
	int sec = atoi(sCmd+6);
	if (sec>0)
	{
		WDTInit(sec);
	}
	else if (strcmp(GetString(sTemp, sCmd, 6, 4), "feed") == 0)
	{
		WDTFeed();
		sendchars("Feed thanh cong!\n\r");
	}
	else if ((strcmp(GetString(sTemp, sCmd, 6, 4), "help") == 0)||(strcmp(GetString(sTemp, sCmd, 6, 1), "?") == 0))
	{
		sendchars("Hen gio reset Embedded system.\n\r");
		sendchars("   reset n        thiet lap sau n giay se reset.\n\r");
		sendchars("   reset feed     feed lai watch timer.\n\r");
		sendchars("   reset ?        hien huong dan lenh.\n\r");
	}
	else
	{
		sendchars("The syntax of the command is incorrect.\n\r");
		sendchars("Enter reset ? to show help.\n\r");
	}
}
void ProcCmdLed(char *sCmd, char *sTemp)
{
	if (strcmp(GetString(sTemp, sCmd, 4, 2), "on") == 0)
	{
		int led = atoi(sCmd+7);
		if (((led>0 && sCmd[7]!='0')||(led=0 && sCmd[7]=='0' && sCmd[8]==0)) && led<8)
		{
			LED_On(led);
			sendchars("Turn on led complete!\n\r");
		}
		else
		{
			sendchars("The syntax of the command is incorrect.\n\r");
			sendchars("Enter led ? to show help.\n\r");
		}	
	}
	else if (strcmp(GetString(sTemp, sCmd, 4, 3), "off") == 0)
	{
		int led = atoi(sCmd+8);
		if (((led>0 && sCmd[8]!='0')||(led=0 && sCmd[8]=='0' && sCmd[9]==0)) && led<8)
		{
			LED_Off(led);
			sendchars("Turn off led complete!\n\r");
		}
		else
		{
			sendchars("The syntax of the command is incorrect.\n\r");
			sendchars("Enter led ? to show help.\n\r");
		}	
	}
	else if (strcmp(GetString(sTemp, sCmd, 4, 3), "out") == 0)
	{
		int led = atoi(sCmd+8);
		if ((led>0 && sCmd[8]!='0')||(led==0 && sCmd[8]=='0' && sCmd[9]==0))
		{
			LED_Out(led);
			sendchars("Turn out led complete!\n\r");
		}
		else
		{
			sendchars("The syntax of the command is incorrect.\n\r");
			sendchars("Enter led ? to show help.\n\r");
		}	
	}
	else if ((strcmp(GetString(sTemp, sCmd, 4, 4), "help") == 0)||(strcmp(GetString(sTemp, sCmd, 4, 1), "?") == 0))
	{
		sendchars("Turn on/off LED on Embedded system.\n\r");
		sendchars("   led on n        turn on led n.\n\r");
		sendchars("   led off n       turn off led n.\n\r");
		sendchars("   led out n       set led by n.\n\r");
		sendchars("   led ?           show help.\n\r");
	}
	else
	{
		sendchars("The syntax of the command is incorrect.\n\r");
		sendchars("Enter led ? to show help.\n\r");
	}
}
void ProcCmdLcd(char *sCmd, char *sTemp)
{
	if (strcmp(GetString(sTemp, sCmd, 4, 5), "clear") == 0)
	{
		lcd_clear();	
		sendchars("Clear LCD complete!\n\r");
	}
	else if (strcmp(GetString(sTemp, sCmd, 4, 2), "<<") == 0)
	{
		if (strlen(sCmd+7)>0)
		{
			lcd_print((unsigned char *)sCmd+7);
			sendchars("Print to LCD complete!\n\r");
		}
		else
		{
			sendchars("The syntax of the command is incorrect.\n\r");
			sendchars("Enter lcd ? to show help.\n\r");
		}	
	}
	else if ((strcmp(GetString(sTemp, sCmd, 4, 4), "help") == 0)||(strcmp(GetString(sTemp, sCmd, 4, 1), "?") == 0))
	{
		sendchars("Output string to LCD on Embedded system.\n\r");
		sendchars("   lcd clear        cleaing LCD.\n\r");
		sendchars("   lcd << st        print st to LCD n.\n\r");
		sendchars("   lcd ?            show help.\n\r");
	}
	else
	{
		sendchars("The syntax of the command is incorrect.\n\r");
		sendchars("Enter lcd ? to show help.\n\r");
	}
}

void ProcCmdHelp()
{
	sendchars("Available commands:\n\r");
	sendchars(" \t mssv\n\r");
	sendchars(" \t now\n\r");
	sendchars(" \t song\n\r");
}

void ProcCmdSong(char* sCmd, char* sTmp)
{  /*
	int dur = 0, freq = 0, accum = 0, sample = 0, notes = 0, freq_mult = 42950;
	const int NOTE_LENGTH = 2000000;

	PINSEL1 &= ~(0x03<<20);
	PINSEL1 |= (0x02<<20);
	
	while (notes != 14)			// phat ra 14 note
	{
		++dur;
		if(dur == NOTE_LENGTH)		// delay (do dai 1 note)
		{
			freq = Keys[arrFreq[notes]];
			dur = 0;
		}
		
		accum += freq_mult * freq;

		sample = sinetable256[accum>>24];
		DACR = ((sample) << 6) & 0xFFC0;		
		++notes;
	}	*/
  T0MR0         = 120;                       /* 1msec = 12000-1 at 12.0 MHz */
  T0MCR         = 3;                           /* Interrupt and Reset on MR0  */
  T0TCR         = 1;                           /* Timer0 Enable               */
  VICVectAddr4  = (unsigned long)T0_IRQHandler;/* Set Interrupt Vector        */
  VICVectCntl4  = 15;                          /* use it for Timer0 Interrupt */
  VICIntEnable  = (1  << 4);                   /* Enable Timer0 Interrupt     */
  PINSEL1       &= ~(0x03<<20);                      /* AD0.0 pin function select   */
  PINSEL1       |= (0x02<<20);                      /* AD0.0 pin function select   */
	sendchars("Playing... !\n\r");
	
}

int index =0;  // vi tri cua not nhac trong bai hat		 
int freq = 0; // vi tri phim piano 
int dur = 0;  // thoi gian quyet dinh thay doi not nhac
 
int  accum=0; // vi tri trong bang sin -> tin hieu nhac truyen ra loa
// he so tan so
#define freq_mult 42950

/* Timer0 IRQ: Executed periodically                                          */
__irq void T0_IRQHandler (void) {
  unsigned char sample;
  dur++;
  if(dur == 20000)	   // Ngat thi ngat	100.000
  
  {
  	freq = Keys[arrFreq[index++]]; 
	dur =0;
  }
  //freq ++;
  // tan so thuc su = he so tan so x tan so
  accum += freq_mult * freq;
  // muc sin ung voi muc tan so
  sample = sine_table256[accum >> 24];
  DACR = ((sample)<<6)&0xFFC0;
  T0IR        = 1;                      /* Clear interrupt flag               */
  VICVectAddr = 0;                      /* Acknowledge Interrupt              */

  if(index==32)
  {
  	sendchars("Play song complete!\n\r");
  	T0TCR = 0;
  }
}