#pragma once

#define MAX_FILE_SEND 5
#define BUFFER_LEN 1024

// CClientSendClientThread

class CClientSendClientThread : public CWinThread
{
	DECLARE_DYNCREATE(CClientSendClientThread)

protected:
	CClientSendClientThread();           // protected constructor used by dynamic creation
	virtual ~CClientSendClientThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	static void HardDelete(CClientSendClientThread ** t);
	static CClientSendClientThread * CreateCClientSendClientThread(CString stFile, int iPort);
	static int m_iCountInstance;
	CString GetPercent();
	int GetExitCode();

private:
	SOCKET m_Socket;
	CString m_stFilePath;
	int m_iPort;
	char m_iPercent;

protected:
	DECLARE_MESSAGE_MAP()
};


