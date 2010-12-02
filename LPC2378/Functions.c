#include <LPC23xx.H> 
#include "stdlib.h"

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
void ProcCmdNow(char *sCmd, char *sTemp)
{
	char sec[3];
	char min[3];
	char hour[3];
	if (strcmp(GetString(sTemp, sCmd, 5, 3), "set") == 0)
	{
		GetString(hour, sCmd, 9, 2);
		GetString(min, sCmd, 12, 2);
		GetString(sec, sCmd, 15, 2);
		RTCSet(atoi(hour), atoi(min), atoi(sec));
	}
}