#pragma once

#define BUFFER_LEN 1024
#define MAX_FILE_DOWN 10

// CClientShareTranport

class CClientShareTranport : public CWinThread
{
	DECLARE_DYNCREATE(CClientShareTranport)

protected:
	CClientShareTranport();           // protected constructor used by dynamic creation
	virtual ~CClientShareTranport();

public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();
	static CClientShareTranport * Create(CString stAddress, int iPort, CString stPath);
	static int m_iCountInstance;
	virtual int Run();
	static void HardDelete(CClientShareTranport ** t);
	CString GetPercent();
	int GetExitCode();
private:
	SOCKET m_Socket;
	sockaddr_in m_ServerAddr;
	CString m_PathFile;
	char m_iPercent;

protected:
	DECLARE_MESSAGE_MAP()
};


