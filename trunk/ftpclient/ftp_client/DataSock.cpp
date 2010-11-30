#include "StdAfx.h"
#include "DataSock.h"

DataSock::DataSock(void)
{
	m_sockActive = INVALID_SOCKET;
}

DataSock::~DataSock(void)
{
}

int DataSock::Send(char* sBuff, int iLen)
{
	//if (m_csItemToStore.IsEmpty() == true)
	//	return -1;

	int i;
	if (m_eMode == FTPMode::Active)
	{
		i = send(m_sockActive, sBuff, iLen, 0);
	}
	else if (m_eMode == FTPMode::Passive)
	{
		send(m_sock, sBuff, iLen, 0);
	}

	return 0;
}

int DataSock::Accept()
{
	if (m_eMode != FTPMode::Active)
		return -1;

	sockaddr_in sockaddrClient;
	int iSize = sizeof(sockaddrClient);
	m_sockActive = accept(m_sock, (sockaddr*)&sockaddrClient, &iSize);
	if (m_sockActive == INVALID_SOCKET)
	{
		AfxMessageBox(_T("DataSock::Accept() failed."));
		return WSAGetLastError();
	}

	return 0;
}

int DataSock::Bind()
{
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(MyTools::DATAPORT);
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(m_sock, (SOCKADDR *)&addrServer, sizeof(addrServer)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("MySock::Bind() error"));
		return WSAGetLastError();
	}

	return 0;
}

int DataSock::Listen()
{
	if (listen(m_sock, MAX_BKLG) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("MySock::Listen() error"));
		m_bIsConnecting = false;
		m_eMode = FTPMode::None;
		return WSAGetLastError();
	}

	m_bIsConnecting = true;
	m_eMode = FTPMode::Active;
	return 0;
}

int DataSock::BindAndListen()
{
	if (Bind() == 0)
	{
		if (Listen() == 0)
		{
			m_eMode = FTPMode::Active;
			m_bIsConnecting = true;
			return 0;
		}
	}

	m_bIsConnecting = false;
	m_eMode = FTPMode::None;
	return WSAGetLastError();
}

int DataSock::CloseActiveSock()
{
	if (m_sockActive != INVALID_SOCKET)
		if (closesocket(m_sockActive) != 0)
		{
			AfxMessageBox(_T("MySock::CloseActiveSocket() failed!"));
			return WSAGetLastError();
		}

	return 0;
}