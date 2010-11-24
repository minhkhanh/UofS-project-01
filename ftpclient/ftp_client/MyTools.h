#pragma once

#include <vector>
using namespace std;

class MyTools
{
public:
	MyTools(void);
	~MyTools(void);

	// ftp commands:
	static TCHAR* FC_LIST;
	static TCHAR* FC_CWD;

	// command-reply
	static TCHAR* CR_230;
	static TCHAR* CR_227;
	static TCHAR* CR_250;

	// ham cat chuoi, co ho tro cat tu dau chuoi va cat tu cuoi chuoi
	static CString PeelMessage(CString* pcsMess, int iDirect = 1, TCHAR sToken[] = _T(" "));
	static void GetIPnPort(CString * pcsCmd, CString * pcsIP, int * iPort);
	//static 
};
