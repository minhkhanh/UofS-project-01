#pragma once
#include <afxmt.h>



// CServerShareTranportThread

class CServerShareTranportThread : public CWinThread
{
	DECLARE_DYNCREATE(CServerShareTranportThread)

protected:
	CServerShareTranportThread();           // protected constructor used by dynamic creation
	virtual ~CServerShareTranportThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	static void HardDelete(CServerShareTranportThread ** t);
	CFile * m_File;
	CSemaphore * m_SemaphoreFile;
	SOCKET  m_Socket;
	static CServerShareTranportThread * CreateServerShareTranportThread(SOCKET  soc, CFile * file, CSemaphore * sema);

protected:
	DECLARE_MESSAGE_MAP()
};


