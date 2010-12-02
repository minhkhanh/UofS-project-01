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

