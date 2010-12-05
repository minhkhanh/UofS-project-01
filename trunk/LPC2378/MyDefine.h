#include "stdlib.h"

#define MAX_SIZE 256

extern int strlen(const char*);

int sendchar (int ch);
int strcmp(const char *s1, const char *s2);
int strcmp(const char *s1, const char *s2);
void itoa(int n, char s[]);
void FillChars(char* st, int size);
char * GetString(char * des, char * source,int iStart, int iNum);
void ProcCmdNow(char *sCmd, char *sTemp);
void ProcCmdMSSV(void);
void RTCInit(int hour, int min, int sec);
void RTCSet(int hour, int min, int sec);
void RTCGet(char * result);
int sendchar (int ch);
void sendchars(char s[]);
void init_serial (void);
int getkey (void);
void ProcCmdReset(char *sCmd, char *sTemp);
void WDTFeed(void);
void WDTInit(int sec);
void ProcCmdLed(char *sCmd, char *sTemp);
void ProcCmdLcd(char *sCmd, char *sTemp);
void lcd_clear (void);
void lcd_print (unsigned char const *string);
void lcd_init (void);
void set_cursor (unsigned char column, unsigned char line);
void LED_Init(void);
void ProcCmdSong(char* sCmd, char* sTmp);
void ProcCmdHelp();
__irq void T0_IRQHandler (void);


