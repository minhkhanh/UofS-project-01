#pragma once

#define WM_SOCKET_CMD	WM_USER + 1
#define WM_SOCKET_DATA	WM_USER + 2
#define WM_SOCKET_DATA_BINARY	WM_USER + 3

#define  FTP_SERVER_CMD_PORT	21

#define CMDBUFF_MAXLEN	512
#define DATABUFF_MAXLEN	1024

//#include <tchar.h>
#include <direct.h>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

enum FTPMode
{
	Active,
	Passive,
	None
};

class MyTools
{
public:
	MyTools(void);
	~MyTools(void);

	static int DATAPORT;

	// ftp commands:
	static TCHAR* FC_LIST;
	static TCHAR* FC_CWD;
	static TCHAR* FC_PORT;
	static TCHAR* FC_PASV;
	static TCHAR* FC_USER;
	static TCHAR* FC_PASS;
	static TCHAR* FC_PWD;
	static TCHAR* FC_TYPE;
	static TCHAR* FC_STOR;
	static TCHAR* FC_DELE;
	static TCHAR* FC_RETR;

	// command-reply
	static TCHAR* CR_230;
	static TCHAR* CR_227;
	static TCHAR* CR_250;
	static TCHAR* CR_200;
	static TCHAR* CR_331;
	static TCHAR* CR_220;
	static TCHAR* CR_226;
	static TCHAR* CR_257;
	static TCHAR* CR_150;

	// ham cat chuoi, co ho tro cat tu dau chuoi va cat tu cuoi chuoi
	static CString PeelMessage(CString* pcsMess, int iDirect = 1, TCHAR sToken[] = _T(" "));
	static void GetCmdIPnPort(CString * pcsCmd, CString * pcsIP, int * pPort);
	static void GetSockIPnPort(SOCKET sock, CString * pcsIP, int * pPort);
	static void ExtractFileDetails(CString * pcsLine, CString * pcsTitle, CString * pcsType, CString * pcsSize, CString * pcsDate);
	//static 
};
