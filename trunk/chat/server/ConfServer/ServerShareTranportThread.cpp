// ServerShareTranportThread.cpp : implementation file
//

#include "stdafx.h"
#include "ServerConf.h"
#include "ServerShareTranportThread.h"

#define BUFFER_LEN 1024
// CServerShareTranportThread

IMPLEMENT_DYNCREATE(CServerShareTranportThread, CWinThread)

CServerShareTranportThread::CServerShareTranportThread()
{
}

CServerShareTranportThread::~CServerShareTranportThread()
{
	closesocket(*m_Socket);
}

BOOL CServerShareTranportThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CServerShareTranportThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	//HardStop();
	closesocket(*m_Socket);
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CServerShareTranportThread, CWinThread)
END_MESSAGE_MAP()

int CServerShareTranportThread::Run()
{
	LONG64 llFileLength = m_File->GetLength();
	send(*m_Socket,(char*)&llFileLength,sizeof(LONG64),0);
	LONG64 llCurSend = 0;
	while (llCurSend < llFileLength)
	{
		char buffer[BUFFER_LEN] = {0};
		m_SemaphoreFile->Lock();
		m_File->Seek(llCurSend, CFile::begin);
		UINT len = m_File->Read(buffer, sizeof(buffer));
		m_SemaphoreFile->Unlock();
		int i = 0; 
		while (i < len)
		{
			int j = send(*m_Socket, buffer + i, len - i, 0);
			if (j == 0)
			{
				m_File->Close();
				closesocket(*m_Socket);
				ExitThread(0);
			}
			i += j;
		}
		llCurSend += len;
	}
	closesocket(*m_Socket);
	ExitThread(0);
}

CServerShareTranportThread * CServerShareTranportThread::CreateServerShareTranportThread(SOCKET * soc, CFile * file, CSemaphore * sema )
{
	CServerShareTranportThread * tSSTT;
	tSSTT = (CServerShareTranportThread *) AfxBeginThread(RUNTIME_CLASS(CServerShareTranportThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	tSSTT->m_File = file;
	tSSTT->m_SemaphoreFile = sema;
	tSSTT->m_Socket = soc;
	tSSTT->m_bAutoDelete = TRUE;
	return tSSTT;
}

void CServerShareTranportThread::HardDelete(CServerShareTranportThread ** t)
{
	TerminateThread((*t)->m_hThread, 0);
	delete *t;
	*t = NULL;
}


// CServerShareTranportThread message handlers
