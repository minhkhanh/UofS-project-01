#pragma once

#include "MyTools.h"

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
	static CServerDownloadThread * CreateCServerDownloadThread(CString stFilePath, SOCKET soc, CString csIPnPort, FTPMode eMode);
	virtual int Run();
	static void HardDelete(CServerDownloadThread ** t);
	int GetExitCode();
	CString GetFilePath();
	bool IsPublicShare();
	CString GetSender();
	void SetSender(CString st);
	CString GetReceiver();
	void SetReceiver(CString st);

private:
	CString m_stSender;
	CString m_stReceiver;
	bool m_bIsPublicShare;
	CString m_stFilePath;
	int m_iPort;
	SOCKET m_Socket;

	FTPMode m_eMode;
	CString m_csServIPnPort;

protected:
	DECLARE_MESSAGE_MAP()
};


