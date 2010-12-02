#include "lpc23xx.h"
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
