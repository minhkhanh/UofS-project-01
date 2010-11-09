#pragma once
#include <vector>
#include "ServerShareTranportThread.h"
using namespace std;


// CGarbageCollectorThread

class CGarbageCollectorThread : public CWinThread
{
	DECLARE_DYNCREATE(CGarbageCollectorThread)

protected:
	CGarbageCollectorThread();           // protected constructor used by dynamic creation
	virtual ~CGarbageCollectorThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	static void HardDelete(CGarbageCollectorThread ** t);
	static CGarbageCollectorThread * CreateCGarbageCollectorThread(vector<CServerShareTranportThread *> * m_List, CSemaphore * m_SemaShare, CSemaphore * m_SemaThread, int * iCount);
private:
	vector<CServerShareTranportThread *> * m_ListTranportThread;
	CSemaphore * m_SemaphoreShare;
	CSemaphore * m_SemaphoreListThread;
	int * m_iCountIdle;

protected:
	DECLARE_MESSAGE_MAP()
};


