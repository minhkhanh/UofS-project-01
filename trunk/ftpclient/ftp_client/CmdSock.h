#pragma once

#include "MySock.h"
#include "DataSock.h"

class CmdSock: public MySock
{
private:
	CString m_csLastestCmd;
	CString m_csToDoCmd;
	//FTPMode m_eMode;
	
public:
	CmdSock(void);
	~CmdSock(void);

	//FTPMode& Mode() { return m_eMode; }
	CString& ToDoCmd() { return m_csToDoCmd; }
	CString& LastestCmd() { return m_csLastestCmd; }

	void SetMode(int iPassiveFlag, DataSock* pMyDataSock, HWND hWnd, int iHandler);

	void USER(CString * pcsMess);
	void PASS(CString * pcsMess);
	void LIST(CString * pcsMess = NULL);
	void PASV();
	void PORT(DataSock* pMyDataSock, HWND hWnd, int iHandler);
	void QUIT();
	void CWD(CString * pcsDir);
	void PWD();
};
