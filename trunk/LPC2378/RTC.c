 #include "lpc23xx.h"
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
void RTCGet(int &hour, int &min, int &sec)
{
	sec = RTC_SEC;
	min = RTC_MIN;
	hour = RTC_HOUR;
}