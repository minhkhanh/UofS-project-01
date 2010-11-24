#include "StdAfx.h"
#include "MySock.h"

MySock::MySock(void)
{
	m_sock = INVALID_SOCKET;
	m_bIsConnecting = false;
}

MySock::~MySock(void)
{
	if (CloseSocket() != 0)
	{
		AfxMessageBox(_T("cannot destroy MySock object!"));
	}
}

int MySock::CloseSocket()
{
	if (m_sock != INVALID_SOCKET)
		if (closesocket(m_sock) != 0)
			return WSAGetLastError();

	m_bIsConnecting = false;
	return 0;
}

int MySock::CreateSock()
{
	int iErr = CloseSocket();
	if (iErr != 0)
		return iErr;

	m_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sock == INVALID_SOCKET)
	{
		m_bIsConnecting = false;
		return WSAGetLastError();
	}

	m_bIsConnecting = true;

	return 0;
}

int MySock::Connect( DWORD dwIPAddr, int iPort )
{
	IN_ADDR ia;
	ia.S_un.S_addr = ntohl(dwIPAddr);

	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(iPort);
	addrServer.sin_addr.s_addr = inet_addr(inet_ntoa(ia));

	if (addrServer.sin_addr.s_addr == INADDR_NONE)
	{
		m_bIsConnecting = false;
		return -1;
	}

	if (connect(m_sock, (struct sockaddr*)&addrServer, sizeof(addrServer))== SOCKET_ERROR)
	{
		m_bIsConnecting = false;
		return WSAGetLastError();
	}

	m_bIsConnecting = true;
	return 0;
}

int MySock::Connect(char* sIP, int iPort )
{
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(iPort);
	addrServer.sin_addr.s_addr = inet_addr(sIP);

	if (addrServer.sin_addr.s_addr == INADDR_NONE)
		return -1;

	if (connect(m_sock, (struct sockaddr*)&addrServer, sizeof(addrServer))== SOCKET_ERROR)
		return WSAGetLastError();

	return 0;
}
int MySock::SetSelectMode( HWND hWnd, int iHandler, int iFD )
{
	if (WSAAsyncSelect(m_sock, hWnd, iHandler, iFD) == SOCKET_ERROR)
		return WSAGetLastError();

	return 0;
}