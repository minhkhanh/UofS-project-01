// ServerShareThread.cpp : implementation file
//

#include "stdafx.h"
#include "ConfServer.h"
#include "ServerShareThread.h"

int CServerShareThread::m_iCountInstance;
// CServerShareThread

IMPLEMENT_DYNCREATE(CServerShareThread, CWinThread)

CServerShareThread::CServerShareThread()
{
	++CServerShareThread::m_iCountInstance;
}

CServerShareThread::~CServerShareThread()
{
	--CServerShareThread::m_iCountInstance;
	for (int i=0; i<m_ListTranportThread->size(); ++i)
	{
		TerminateThread(m_ListTranportThread->operator [](i)->m_hThread, 0);
	}
	if (m_SemaphoreFile != NULL) delete m_SemaphoreFile;
	if (m_SemaphoreShare != NULL) delete m_SemaphoreShare;
	if (m_SemaphoreListThread != NULL) delete m_SemaphoreListThread;
	if (m_iCountEdle != NULL) delete m_iCountEdle;
	CGarbageCollectorThread::HardDelete(&m_GarbageCollectorThread);
	if (m_File != NULL) delete m_File;
	closesocket(m_SocketListen);
}

BOOL CServerShareThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	m_SemaphoreShare = new CSemaphore(MAX_SHARE, MAX_SHARE);
	m_SemaphoreListThread = new CSemaphore(1, 1);
	m_SemaphoreFile = new CSemaphore(1, 1);
	m_ListTranportThread = new vector<CServerShareTranportThread *>();
	m_iCountEdle = new int;
	*m_iCountEdle = 0;
	m_GarbageCollectorThread = CGarbageCollectorThread::CreateCGarbageCollectorThread(m_ListTranportThread, m_SemaphoreShare, m_SemaphoreListThread, m_iCountEdle);
	m_GarbageCollectorThread->ResumeThread();
	return TRUE;
}

int CServerShareThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CServerShareThread, CWinThread)
END_MESSAGE_MAP()

int CServerShareThread::Run()
{
	listen(m_SocketListen, 5);
	while (TRUE)
	{
		SOCKET soc;
		m_SemaphoreShare->Lock();
		soc = accept(m_SocketListen,NULL,NULL);
		CServerShareTranportThread * cSSTT = CServerShareTranportThread::CreateServerShareTranportThread(&soc, m_File, m_SemaphoreFile);
		m_SemaphoreListThread->Lock();
		m_ListTranportThread->push_back(cSSTT);
		m_SemaphoreListThread->Unlock();
		cSSTT->ResumeThread();
	}
	return CWinThread::Run();
}

CServerShareThread * CServerShareThread::CreateCServerShareThread(int iPort, CString stFilePath )
{
	if (CServerShareThread::m_iCountInstance >= MAX_FILE_SHARE)
	{
		return NULL;
	}
	CServerShareThread * tSST;
	tSST = (CServerShareThread *) AfxBeginThread(RUNTIME_CLASS(CServerShareThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED, NULL);
	tSST->m_bAutoDelete = TRUE;
	tSST->m_File = new CFile;
	if (! tSST->m_File->Open(stFilePath, CFile::modeRead))
	{
		return NULL;
	}
	tSST->m_SocketListen = socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in ServerAddr;
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(iPort);
	ServerAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(tSST->m_SocketListen,(sockaddr*)&ServerAddr,sizeof(ServerAddr))==SOCKET_ERROR)
	{
		tSST->m_File->Close();
		return NULL;
	}
	TRACE2("cho down file %s tai port: %d \n", stFilePath, iPort);
	return tSST;
}

void CServerShareThread::HardDelete(CServerShareThread ** t)
{
	TerminateThread((*t)->m_hThread, 0);
	delete *t;
	*t = NULL;
}

int CServerShareThread::GetTimeEdle()
{
	return *m_iCountEdle;
}


// CServerShareThread message handlers
