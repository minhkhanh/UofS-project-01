// ServerDownloadThread.cpp : implementation file
//

#include "stdafx.h"
#include "ConfServer.h"
#include "ServerDownloadThread.h"
#define BUFFER_LEN 1024

int CServerDownloadThread::m_iCountInstance;
// CServerDownloadThread

IMPLEMENT_DYNCREATE(CServerDownloadThread, CWinThread)

CServerDownloadThread::CServerDownloadThread()
{
	++CServerDownloadThread::m_iCountInstance;
}

CServerDownloadThread::~CServerDownloadThread()
{
	--CServerDownloadThread::m_iCountInstance;
}

BOOL CServerDownloadThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CServerDownloadThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CServerDownloadThread, CWinThread)
END_MESSAGE_MAP()

void CServerDownloadThread::HardDelete( CServerDownloadThread ** t )
{
	TerminateThread((*t)->m_hThread, 0);
	delete (*t);
	*t = NULL;
}

CServerDownloadThread * CServerDownloadThread::CreateCServerDownloadThread( CString stFilePath, int iPort )
{
	if (CServerDownloadThread::m_iCountInstance >= MAX_FILE_UP_TO_SERVER)
	{
		return NULL;
	}
	CServerDownloadThread * t = (CServerDownloadThread*)AfxBeginThread(RUNTIME_CLASS(CServerDownloadThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	t->m_stFilePath = stFilePath;
	t->m_iPort = iPort;
	TRACE2("cho upload file %s tai port: %d \n", stFilePath, iPort);
	return t;
}

int CServerDownloadThread::Run()
{
	CFile m_File;
	if (!m_File.Open(m_stFilePath, CFile::modeCreate|CFile::modeWrite))
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

	LONG64 leng = 0;
	recv(soc,(char*)&leng,sizeof(LONG64),0);
	LONG64 count = 0;
	char buffer[BUFFER_LEN];
	m_File.Seek(0, CFile::begin);
	while(count < leng)
	{
		int len = recv(soc, buffer, BUFFER_LEN,0);
		if (len==0)
		{
			m_File.Close();
			ExitThread(0);
		}
		m_File.Write(buffer, len);
		count += len;
	}
	m_File.Close();
	closesocket(m_Socket);
	ExitThread(1);
}

int CServerDownloadThread::GetExitCode()
{
	DWORD i;
	GetExitCodeThread(this->m_hThread, &i);
	return i;
}

CString CServerDownloadThread::GetFilePath()
{
	return m_stFilePath;
}


// CServerDownloadThread message handlers
