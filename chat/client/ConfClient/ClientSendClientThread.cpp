// ClientSendClientThread.cpp : implementation file
//

#include "stdafx.h"
#include "ConfClient.h"
#include "ClientSendClientThread.h"

int CClientSendClientThread::m_iCountInstance;
// CClientSendClientThread

IMPLEMENT_DYNCREATE(CClientSendClientThread, CWinThread)

CClientSendClientThread::CClientSendClientThread()
{
	++CClientSendClientThread::m_iCountInstance;
	m_iPercent = 0;
}

CClientSendClientThread::~CClientSendClientThread()
{
	--CClientSendClientThread::m_iCountInstance;
	closesocket(m_Socket);
}

BOOL CClientSendClientThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CClientSendClientThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CClientSendClientThread, CWinThread)
END_MESSAGE_MAP()

void CClientSendClientThread::HardDelete( CClientSendClientThread ** t )
{
	TerminateThread((*t)->m_hThread, 0);
	delete *t;
	*t = NULL;
}

CString CClientSendClientThread::GetPercent()
{
	CString t;
	t.Format(_T("%d"), m_iPercent);
	return t;
}

int CClientSendClientThread::GetExitCode()
{
	DWORD i;
	GetExitCodeThread(this->m_hThread, &i);
	return i;
}

CClientSendClientThread * CClientSendClientThread::CreateCClientSendClientThread( CString stFile, int iPort )
{
	if (CClientSendClientThread::m_iCountInstance >= MAX_FILE_SEND)
	{
		return NULL;
	}
	CClientSendClientThread * t;
	t = (CClientSendClientThread*) AfxBeginThread(RUNTIME_CLASS(CClientSendClientThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	t->m_stFilePath = stFile;
	t->m_iPort = iPort;
	TRACE2("cho send file %s tai port: %d \n", stFile, iPort);
	return t;
}

int CClientSendClientThread::Run()
{
	CFile m_File;
	if (!m_File.Open(m_stFilePath, CFile::modeRead))
	{
		ExitThread(0);
	}
	sockaddr_in m_ServerAddr;
	m_ServerAddr.sin_family = AF_INET;
	m_ServerAddr.sin_port = htons(m_iPort);
	m_ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	m_Socket = socket(AF_INET,SOCK_STREAM,0);
	if (bind(m_Socket,(sockaddr*)&m_ServerAddr,sizeof(m_ServerAddr))==SOCKET_ERROR)
	{
		m_File.Close();
		ExitThread(0);
	}
	if (listen(m_Socket, 1 ) == SOCKET_ERROR) 
	{
		closesocket(m_Socket);
		return 1;
	}
	SOCKET soc;
	soc = accept(m_Socket,NULL,NULL);
	if (soc == INVALID_SOCKET )
	{
		closesocket(m_Socket);
		m_File.Close();
		ExitThread(0);
	}
	closesocket(m_Socket);
	LONG64 llFileLength = m_File.GetLength();
	send(soc,(char*)&llFileLength,sizeof(LONG64),0);
	LONG64 llCurSend = 0;
	m_File.Seek(llCurSend, CFile::begin);
	while (llCurSend < llFileLength)
	{
		char buffer[BUFFER_LEN] = {0};
		UINT len = m_File.Read(buffer, sizeof(buffer));
		int i = 0; 
		while (i < len)
		{
			int j = send(soc, buffer + i, len - i, 0);
			if (j <= 0)
			{
				m_File.Close();
				closesocket(soc);
				ExitThread(0);
			}
			i += j;
		}
		llCurSend += len;
		m_iPercent = (char)(float)(llCurSend*100/llFileLength);
	}
	closesocket(soc);
	ExitThread(1);
}


// CClientSendClientThread message handlers
