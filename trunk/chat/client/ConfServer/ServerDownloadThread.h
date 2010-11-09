#pragma once

#define MAX_FILE_UP_TO_SERVER 5

// CServerDownloadThread

class CServerDownloadThread : public CWinThread
{
	DECLARE_DYNCREATE(CServerDownloadThread)

protected:
	CServerDownloadThread();           // protected constructor used by dynamic creation
	virtual ~CServerDownloadThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	static int m_iCountInstance;
	static CServerDownloadThread * CreateCServerDownloadThread(CString stFilePath, int iPort);
	virtual int Run();
	static void HardDelete(CServerDownloadThread ** t);
	int GetExitCode();
	CString GetFilePath();

private:
	CString m_stFilePath;
	int m_iPort;
	SOCKET m_Socket;

protected:
	DECLARE_MESSAGE_MAP()
};


