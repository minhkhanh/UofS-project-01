#include "lpc23xx.h"
#include "LCD.h"
#include "stdlib.h"
//#include "string.h"

int iPos = 0;
char cKey = 0;
char sCmd[256] = {0};

void Process()
{
	if (strcmp(sCmd, "mssv") == 0)
	{
		sendchars("0812223_0812239");
	}
	else if (strcmp(sCmd, "now") == 0)
	{
		char sec[5];
		char min[5];
		char hour[5];

		RTC_Init();

		itoa(RTC_SEC, sec);
		itoa(RTC_MIN, min);
		itoa(RTC_HOUR, hour);

		sendchars(sec);
		sendchars(min);
		sendchars(hour);
	}
	else if (strcmp())

	sendchar(13);
	sendchar(10);
}

int main()
{	
	init_serial();
	sendchars("UART OK!");

	while (1)
	{
		cKey = getkey();

		if (cKey >= 65 && cKey <= 90)		//chuan hoa thanh ki tu thuong
			cKey += 32;		

		//sendchar(cKey);

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

	return 0;
}