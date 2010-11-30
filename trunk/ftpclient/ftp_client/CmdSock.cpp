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

	m_csLastestCmd = MyTools::FC_USER;
}

void CmdSock::PASS( CString * pcsMess )
{
	CString cstrMess = _T("PASS ");
	cstrMess += *pcsMess;
	cstrMess += _T("\r\n");

	send(m_sock, (char*)cstrMess.GetBuffer(), cstrMess.GetLength()*sizeof(TCHAR), 0);
}

void CmdSock::LIST( CString * pcsMess )
{
	//if (iPassive == BST_CHECKED)
	//	PASV();
	//else
	//	PORT();

	CString csMess = _T("LIST");
	if (pcsMess != NULL)		// == NULL: list thu muc hien tai
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

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);

	m_csLastestCmd = MyTools::FC_PASV;
}

void CmdSock::QUIT()
{
	CString csMess = _T("QUIT\r\n");

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);
}

void CmdSock::CWD( CString * pcsDir )
{
	CString csMess;
	csMess.Format(_T("CWD %s\r\n"), *pcsDir);

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);

	m_csLastestCmd = MyTools::FC_CWD;
}

void CmdSock::PORT( DataSock* pMyDataSock, HWND hWnd, int iHandler )
{

	CString csClientIP;
	int iPort;
	MyTools::GetSockIPnPort(m_sock, &csClientIP, &iPort);
	csClientIP.Replace(_T('.'), _T(','));

	++MyTools::DATAPORT;
	int n = MyTools::DATAPORT / 256;
	int m = MyTools::DATAPORT % 256;

	CString csPort;
	csPort.Format(_T("%d,%d"), n,m);

	CString csMess;
	csMess.Format(_T("PORT %s,%s\r\n"), csClientIP, csPort);

	pMyDataSock->CreateSock();
	pMyDataSock->BindAndListen();
	//pMyDataSock->Listen();
	pMyDataSock->SetSelectMode(hWnd, iHandler, FD_ACCEPT | FD_READ | FD_CLOSE);

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);

	m_csLastestCmd = MyTools::FC_PORT;
}

void CmdSock::SetMode( int iPassiveFlag, DataSock* pMyDataSock, HWND hWnd, int iHandler )
{
	if (iPassiveFlag == BST_CHECKED)
	{
		PASV();
		//m_csLastestCmd = MyTools::FC_PASV;
	}
	else
	{
		PORT(pMyDataSock, hWnd, iHandler);
		//m_csLastestCmd = MyTools::FC_PORT;
	}
}

void CmdSock::PWD()
{
	CString csMess;
	csMess.Format(_T("PWD\r\n"));

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);

	m_csLastestCmd = MyTools::FC_PWD;
}

void CmdSock::TYPE( TCHAR tcType )
{
	CString csMess = _T("TYPE ");
	csMess += tcType;
	csMess += _T("\r\n");

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);
	m_csLastestCmd = MyTools::FC_TYPE;
}

void CmdSock::STOR( CString * pcsName )
{
	CString csMess;
	csMess.Format(_T("STOR %s\r\n"), *pcsName);

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);
	m_csLastestCmd = MyTools::FC_STOR;
}

void CmdSock::DELE( CString * pcsName )
{
	CString csMess;
	csMess.Format(_T("DELE %s\r\n"), *pcsName);

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);
	m_csLastestCmd = MyTools::FC_DELE;
}

void CmdSock::RETR( CString * pcsName )
{
	CString csMess;
	csMess.Format(_T("RETR %s\r\n"), *pcsName);

	send(m_sock, (char*)csMess.GetBuffer(), csMess.GetLength()*sizeof(TCHAR), 0);
	m_csLastestCmd = MyTools::FC_RETR;
}