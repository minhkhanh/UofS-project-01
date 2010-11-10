// ClientUploadThread.cpp : implementation file
//

#include "stdafx.h"
#include "ClientConf.h"
#include "ClientUploadThread.h"

int CClientUploadThread::m_iCountInstance;
// CClientUploadThread

IMPLEMENT_DYNCREATE(CClientUploadThread, CWinThread)

CClientUploadThread::CClientUploadThread()
{
	++CClientUploadThread::m_iCountInstance;
}

CClientUploadThread::~CClientUploadThread()
{
	--CClientUploadThread::m_iCountInstance;
	closesocket(m_Socket);
}

BOOL CClientUploadThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CClientUploadThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CClientUploadThread, CWinThread)
END_MESSAGE_MAP()

int CClientUploadThread::Run()
{
	CFile m_File;
	if (!m_File.Open(m_stFilePath, CFile::modeRead))
	{
		ExitThread(0);
	}
	sockaddr_in m_ServerAddr;
	m_ServerAddr.sin_family = AF_INET;
	m_ServerAddr.sin_port = htons(m_iPort);
	char * st = (char *)malloc(m_stAddress.GetLength()+1);
	wcstombs(st, m_stAddress.GetString(), m_stAddress.GetLength());
	*(st + m_stAddress.GetLength()) = 0;
	m_ServerAddr.sin_addr.s_addr = inet_addr(st);
	m_Socket = socket(AF_INET,SOCK_STREAM,0);
	//if (bind(m_Socket,(sockaddr*)&m_ServerAddr,sizeof(m_ServerAddr))==SOCKET_ERROR)
	//{
	//	m_File.Close();
	//	ExitThread(0);
	//}
	if (connect(m_Socket,(sockaddr*)&m_ServerAddr,sizeof(m_ServerAddr)) == SOCKET_ERROR)
	{
		m_File.Close();
		ExitThread(0);
	}

	LONG64 llFileLength = m_File.GetLength();
	send(m_Socket,(char*)&llFileLength,sizeof(LONG64),0);
	LONG64 llCurSend = 0;
	while (llCurSend < llFileLength)
	{
		char buffer[BUFFER_LEN] = {0};
		m_File.Seek(llCurSend, CFile::begin);
		UINT len = m_File.Read(buffer, sizeof(buffer));
		int i = 0; 
		while (i < len)
		{
			int j = send(m_Socket, buffer + i, len - i, 0);
			if (j == 0)
			{
				m_File.Close();
				closesocket(m_Socket);
				ExitThread(0);
			}
			i += j;
		}
		llCurSend += len;
		m_iPercent = (char)(float)(llCurSend*100/llFileLength);
	}
	closesocket(m_Socket);
	ExitThread(1);
}

void CClientUploadThread::HardDelete( CClientUploadThread ** t )
{
	TerminateThread((*t)->m_hThread, 0);
	delete *t;
	*t = NULL;
}

CClientUploadThread * CClientUploadThread::CreateCClientUploadThread( CString stFile, CString stAdd, int iPort )
{
	if (CClientUploadThread::m_iCountInstance >= MAX_FILE_UP)
	{
		return NULL;
	}
	CClientUploadThread * t;
	t = (CClientUploadThread*) AfxBeginThread(RUNTIME_CLASS(CClientUploadThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	t->m_stFilePath = stFile;
	t->m_stAddress = stAdd;
	t->m_iPort = iPort;
	return t;
}

CString CClientUploadThread::GetPercent()
{
	CString t;
	t.Format(_T("%d"), m_iPercent);
	return t;
}

int CClientUploadThread::GetExitCode()
{
	DWORD i;
	GetExitCodeThread(this->m_hThread, &i);
	return i;
}


// CClientUploadThread message handlers
