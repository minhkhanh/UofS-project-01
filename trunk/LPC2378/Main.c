#include <LPC23xx.H> 
#include "LCD.h"
#include "MyDefine.h"

int iPos = 0;
char cKey = 0;
char sCmd[MAX_SIZE] = {0};
char sTemp[MAX_SIZE] = {0};

void Process()
{
	if (strcmp(GetString(sTemp, sCmd, 0, 4), "mssv") == 0)
	{
		ProcCmdMSSV();
	}
	else if (strcmp(GetString(sTemp, sCmd, 0, 3), "now") == 0)
	{
		ProcCmdNow(sCmd, sTemp);
	}
	//else if (strcmp())

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
}

