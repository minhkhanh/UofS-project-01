#pragma once

#define MAX_FILE_UP 5
#define BUFFER_LEN 1024

// CClientUploadThread

class CClientUploadThread : public CWinThread
{
	DECLARE_DYNCREATE(CClientUploadThread)

protected:
	CClientUploadThread();           // protected constructor used by dynamic creation
	virtual ~CClientUploadThread();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	virtual int Run();
	static void HardDelete(CClientUploadThread ** t);
	static CClientUploadThread * CreateCClientUploadThread(CString stFile, CString stAdd, int iPort);
	static int m_iCountInstance;
	CString GetPercent();
	int GetExitCode();
private:
	SOCKET m_Socket;
	CString m_stFilePath;
	CString m_stAddress;
	int m_iPort;
	char m_iPercent;


protected:
	DECLARE_MESSAGE_MAP()
};


