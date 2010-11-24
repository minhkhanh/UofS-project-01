#pragma once

#include "MyTools.h"

class MySock
{
protected:
	SOCKET m_sock;
	bool m_bIsConnecting;

public:
	MySock(void);
	~MySock(void);

	bool IsConnecting() const { return m_bIsConnecting; }
	void IsConnecting(bool val) { m_bIsConnecting = val; }

	int CreateSock();
	int Connect(DWORD dwIPAddr, int iPort);
	int Connect(char* sIP, int iPort);
	int SetSelectMode(HWND hWnd, int iHandler, int iFD);
	int CloseSocket();
};
