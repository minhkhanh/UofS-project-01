#include <LPC23xx.H> 
#include "MyDefine.h"

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
	if (strlen(source)>iStart+iNum)
	{
		FillChars(des, MAX_SIZE);
		return des;
	}
	for( ; i<iNum; ++i)
		des[i] = source[i];
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
			LED_On(1 << led);
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
			LED_Off(1 << led);
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
		if ((led>0 && sCmd[8]!='0')||(led=0 && sCmd[8]=='0' && sCmd[9]==0))
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

