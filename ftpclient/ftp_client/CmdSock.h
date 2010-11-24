#pragma once

#include "MySock.h"

class CmdSock: public MySock
{
private:
	CString m_csLastestCmd;

public:
	CmdSock(void);
	~CmdSock(void);

	CString LastestCmd() const { return m_csLastestCmd; }
	//void LastestCmd(CString val) { m_csLastestCmd = val; }

	void USER(CString * pcsMess);
	void PASS(CString * pcsMess);
	void LIST(CString * pcsMess, int iPassive);
	void PASV();
	void QUIT();
	void CWD(CString * pcsDir);
};
