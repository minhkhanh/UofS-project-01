 #include "lpc23xx.h"
 #include "MyDefine.h"

 void RTCInit(int hour, int min, int sec)
{
	//Diable CCR;
	RTC_CCR	 = 0;
	//Set Prescaler;
	RTC_PREINT = 0x1C8;		 //int [(PCLK/32768)] – 1			   
	RTC_PREFRAC = 0x61C0; 	//[PCLK – ((PREINT + 1)] x 32768)
	RTC_SEC = sec;
	RTC_MIN = min;
	RTC_HOUR = hour;
	//Enable CCR;
	RTC_CCR	 = 1;
}
void RTCSet(int hour, int min, int sec)
{
	RTCInit(hour, min, sec);
}
void RTCGet(char * result)
{
	itoa(RTC_HOUR, result);
	if (RTC_HOUR<10) 
	{
		result[1] = result[0];
		result[0] = '0';
	}
	itoa(RTC_MIN, result+3);
	if (RTC_MIN<10) 
	{
		result[4] = result[3];
		result[3] = '0';
	}
	itoa(RTC_SEC, result+6);
	if (RTC_SEC<10) 
	{
		result[7] = result[6];
		result[6] = '0';
	}
	result[2] = result[5] = ':';
}


