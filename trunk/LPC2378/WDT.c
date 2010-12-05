 #include "lpc23xx.h"
 #include "MyDefine.h"
__irq void WDTIRQTimer()
{
	char sec[9];
	itoa(WDTV >> 20, sec);
	sendchars("Board restart sau ");
	sendchars(sec);
	sendchars(" giay nua!\r\n");
	T0IR        = 1;
	VICVectAddr = 0;
}
void WDTTimerInit()
{
	T0MR0         = 11999999;                       /* 1msec = 12000-1 at 12.0 MHz */
  	T0MCR         = 3;                           /* Interrupt and Reset on MR0  */
  	T0TCR         = 1;                           /* Timer0 Enable               */
	VICVectAddr4  = (unsigned long)WDTIRQTimer;/* Set Interrupt Vector        */
  	VICVectCntl4  = 15;                          /* use it for Timer0 Interrupt */
  	VICIntEnable  = (1  << 4);                   /* Enable Timer0 Interrupt     */	
}
void WDTInit(int sec)
{
	WDTC = sec << 20;
	WDMOD = 0x03;	
	WDFEED = 0xAA;
	WDFEED = 0x55;

	WDTTimerInit();
}
void WDTFeed()
{
	WDFEED = 0xAA;
	WDFEED = 0x55;
}
