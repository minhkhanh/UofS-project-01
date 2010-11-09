#pragma once
#include <afxmt.h>
#include "ServerShareTranportThread.h"
#include <vector>
#include "GarbageCollectorThread.h"
using namespace std;
#define MAX_SHARE 10
#define MAX_FILE_SHARE 5
//#include <vector>

// CServerShareThread

class CServerShareThread : public CWinThread
{
	DECLARE_DYNCREATE(CServerShareThread)

protected:
	CServerShareThread();           // protected constructor used by dynamic creation
	virtual ~CServerShareThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	static void HardDelete(CServerShareThread ** t);
	static CServerShareThread * CreateCServerShareThread(int iPort, CString stFilePath);
	static int m_iCountInstance;
	int GetTimeEdle();
private:
	SOCKET m_SocketListen;
	CFile * m_File;
	int * m_iCountEdle;
	CSemaphore * m_SemaphoreFile;
	CSemaphore * m_SemaphoreShare;
	CSemaphore * m_SemaphoreListThread;
	vector<CServerShareTranportThread *> * m_ListTranportThread;
	CGarbageCollectorThread * m_GarbageCollectorThread;
protected:
	DECLARE_MESSAGE_MAP()
};


