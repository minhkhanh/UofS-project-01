#include <LPC23xx.H> 
#include "LCD.h"
#include "MyDefine.h"

int iPos = 0;
char cKey = 0;
int ko = 0;
int mot = 1;
int hai = 2;
int ba = 3;
int bon = 4;
char sCmd[MAX_SIZE] = {0};
char sTemp[MAX_SIZE] = {0};

void Process()
{
	if (strcmp(GetString(sTemp, sCmd, ko, bon), "mssv") == 0)
	{
		ProcCmdMSSV();
	}
	else if (strcmp(GetString(sTemp, sCmd, 0, 3), "now") == 0)
	{
		ProcCmdNow(sCmd, sTemp);
	}
	else if (strcmp(GetString(sTemp, sCmd, 0, 5), "reset") == 0)
	{
		ProcCmdReset(sCmd, sTemp);
	}
	else if (strcmp(GetString(sTemp, sCmd, 0, 3), "led") == 0)
	{
		ProcCmdLed(sCmd, sTemp);
	}
	else if (strcmp(GetString(sTemp, sCmd, 0, 3), "lcd") == 0)
	{
		ProcCmdLcd(sCmd, sTemp);
	}
	else if (strcmp(GetString(sTemp, sCmd, 0, 4), "song") == 0)
	{
		ProcCmdSong(sTemp, sCmd);
	}
	else if (strcmp(GetString(sTemp, sCmd, 0, 4), "help") == 0)
	{
		ProcCmdHelp();
	}
	else
	{
		sendchars("Command not recognized!");
		ProcCmdHelp();
	}
}

int main()
{	
	init_serial();
	lcd_init();
	LED_Init();
	lcd_clear();
	sendchars("Board startup complete!\n\r");

	while (1)
	{
		cKey = getkey();

		if (cKey  >= 65 && cKey <= 90)		//chuan hoa thanh ki tu thuong
			cKey += 32;		

		//if ((iPos>0)&&(cKey == 32)&&(sCmd[iPos-1] == 32)) continue;	   //bo 2 khoang trang lien nhau

		if (cKey != 13)
		{
			sCmd[iPos] = cKey;
			iPos++;
		}
		else
		{
			sCmd[iPos] = 0;
			iPos = 0;
			Process();
		}
	}
}

