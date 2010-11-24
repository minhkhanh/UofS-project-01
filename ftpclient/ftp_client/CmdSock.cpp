#include "StdAfx.h"
#include "CmdSock.h"

CmdSock::CmdSock(void)
{
	m_sock = INVALID_SOCKET;
	//m_bValid = true;
}

CmdSock::~CmdSock(void)
{
}

void CmdSock::USER( CString * pcsMess )
{
	CString cstrMess = _T("USER ");
	cstrMess += *pcsMess;
	cstrMess += _T("\r\n");

	send(m_sock, (char*)cstrMess.GetBuffer(), cstrMess.GetLength()*sizeof(TCHAR), 0);
}

void CmdSock::PASS( CString * pcsMess )
{
	CString cstrMess = _T("PASS ");
	cstrMess += *pcsMess;
	cstrMess += _T("\r\n");

	send(m_sock, (char*)cstrMess.GetBuffer(), cstrMess.GetLength()*sizeof(TCHAR), 0);
}

void CmdSock::LIST( CString * pcsMess, int iPassive )
{
	if (iPassive == BST_CHECKED)
		PASV();
	else
	{

	}

	CString csMess = _T("LIST");
	if (pcsMess != NULL)		// list thu muc hien tai
	{
		csMess += _T(' ');
		csMess += *pcsMess;
	}
	csMess += _T("\r\n");

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);

	m_csLastestCmd = MyTools::FC_LIST;
}

void CmdSock::PASV()
{
	CString csMess = _T("PASV\r\n");

	int err = send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);
	if (err != 0)
		return;
}

void CmdSock::QUIT()
{
	CString csMess = _T("QUIT\r\n");

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);
}

void CmdSock::CWD( CString * pcsDir )
{
	//CString csMess = _T("CWD ");
	//csMess += *pcsDir;
	//csMess += _T("\r\n");

	CString csMess;
	csMess.Format(_T("CWD %s\r\n"), *pcsDir);

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);

	m_csLastestCmd = MyTools::FC_CWD;
}