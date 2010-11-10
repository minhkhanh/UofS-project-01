// GarbageCollectorThread.cpp : implementation file
//

#include "stdafx.h"
#include "ServerConf.h"
#include "GarbageCollectorThread.h"


// CGarbageCollectorThread

IMPLEMENT_DYNCREATE(CGarbageCollectorThread, CWinThread)

CGarbageCollectorThread::CGarbageCollectorThread()
{
}

CGarbageCollectorThread::~CGarbageCollectorThread()
{
}

BOOL CGarbageCollectorThread::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CGarbageCollectorThread::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CGarbageCollectorThread, CWinThread)
END_MESSAGE_MAP()

int CGarbageCollectorThread::Run()
{
	while (TRUE)
	{
		m_SemaphoreListThread->Lock();
		for (int i=0; i<m_ListTranportThread->size(); )
		{
			if (m_ListTranportThread->operator [](i) == NULL)
			{
				m_ListTranportThread->erase(m_ListTranportThread->begin()+i);
				m_SemaphoreShare->Unlock();
				continue;
			}
			LPDWORD lpOut = new DWORD;
			GetExitCodeThread(m_ListTranportThread->operator [](i)->m_hThread, lpOut);
			if (*lpOut != STILL_ACTIVE)
			{
				CServerShareTranportThread::HardDelete(&m_ListTranportThread->operator [](i));
				m_ListTranportThread->erase(m_ListTranportThread->begin()+i);
				m_SemaphoreShare->Unlock();
				continue;
			}
			++i;
		}
		if (m_ListTranportThread->size()>0)
		{
			*m_iCountIdle = 0;
		} 
		else
		{
			*m_iCountIdle += 1;
		}
		m_SemaphoreListThread->Unlock();
		Sleep(200);
	}
}

void CGarbageCollectorThread::HardDelete(CGarbageCollectorThread ** t)
{
	TerminateThread((*t)->m_hThread, 0);
	delete *t;
	*t = NULL;
}

CGarbageCollectorThread * CGarbageCollectorThread::CreateCGarbageCollectorThread( vector<CServerShareTranportThread *> * m_List, CSemaphore * m_SemaShare, CSemaphore * m_SemaThread, int * iCount)
{
	CGarbageCollectorThread * cGCT = (CGarbageCollectorThread *)AfxBeginThread(RUNTIME_CLASS(CGarbageCollectorThread), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	cGCT->m_ListTranportThread = m_List;
	cGCT->m_SemaphoreShare = m_SemaShare;
	cGCT->m_SemaphoreListThread = m_SemaThread;
	cGCT->m_bAutoDelete = TRUE;
	cGCT->m_iCountIdle = iCount;
	return cGCT;
}


// CGarbageCollectorThread message handlers
