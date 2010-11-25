#pragma once

#include "MyTools.h"

class MySock
{
protected:
	SOCKET m_sock;
	bool m_bIsConnecting;
	//Cftp_clientDlg * m_dlgFTPClient;

public:
	MySock(void);
	~MySock(void);

	bool& IsConnecting() { return m_bIsConnecting; }
	SOCKET& Sock() { return m_sock; }

	int CreateSock();
	int Connect(DWORD dwIPAddr, int iPort);
	int Connect(char* sIP, int iPort);
	int SetSelectMode(HWND hWnd, int iHandler, int iFD);
	int CloseSocket();

	int Bind();
	int Listen(int iBklg);
};
