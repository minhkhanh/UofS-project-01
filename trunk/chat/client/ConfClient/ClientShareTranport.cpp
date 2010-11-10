// ClientShareTranport.cpp : implementation file
//

#include "stdafx.h"
#include "ClientConf.h"
#include "ClientShareTranport.h"

int CClientShareTranport::m_iCountInstance;
// CClientShareTranport

IMPLEMENT_DYNCREATE(CClientShareTranport, CWinThread)

CClientShareTranport::CClientShareTranport()
{
	++CClientShareTranport::m_iCountInstance;
	m_iPercent = 0;
}

CClientShareTranport::~CClientShareTranport()
{
	--CClientShareTranport::m_iCountInstance;
	closesocket(m_Socket);
}

BOOL CClientShareTranport::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CClientShareTranport::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CClientShareTranport, CWinThread)
END_MESSAGE_MAP()

CClientShareTranport * CClientShareTranport::Create(CString stAddress, int iPort, CString stPath )
{
	if (CClientShareTranport::m_iCountInstance >= MAX_FILE_DOWN)
	{
		return NULL;
	}
	CClientShareTranport * ccST;
	ccST = (CClientShareTranport *) AfxBeginThread(RUNTIME_CLASS(CClientShareTranport), THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	ccST->m_ServerAddr.sin_family = AF_INET;
	ccST->m_ServerAddr.sin_port = htons(iPort);
	char * st = (char *)malloc(stAddress.GetLength()+1);
	wcstombs(st, stAddress.GetString(), stAddress.GetLength());
	*(st + stAddress.GetLength()) = 0;
	ccST->m_ServerAddr.sin_addr.s_addr = inet_addr(st);
	ccST->m_Socket = socket(AF_INET,SOCK_STREAM,0);
	ccST->m_PathFile = stPath;
	return ccST;
}

int CClientShareTranport::Run()
{
	if (connect(m_Socket,(sockaddr*)&m_ServerAddr,sizeof(m_ServerAddr)) != SOCKET_ERROR)
	{
		CFile file;
		if(file.Open(m_PathFile,CFile::modeCreate | CFile ::modeWrite,NULL))
		{
			LONG64 leng = 0;
			recv(m_Socket,(char*)&leng,sizeof(LONG64),0);
			LONG64 count = 0;
			char buffer[BUFFER_LEN];
			file.Seek(0, CFile::begin);
			while(count < leng)
			{
				int len = recv(m_Socket, buffer, BUFFER_LEN,0);
				if (len==0)
				{
					file.Close();
					ExitThread(0);
				}
				file.Write(buffer, len);
				count += len;
				m_iPercent = (char)(float)(count*100/leng);
			}
			file.Close();
			closesocket(m_Socket);
			ExitThread(1);
		}
		closesocket(m_Socket);
		ExitThread(0);
	}
	ExitThread(0);
}

void CClientShareTranport::HardDelete( CClientShareTranport ** t )
{
	TerminateThread((*t)->m_hThread, 0);
	delete (*t);
	*t = NULL;
}

CString CClientShareTranport::GetPercent()
{
	CString t;
	t.Format(_T("%d"), m_iPercent);
	return t;
}

int CClientShareTranport::GetExitCode()
{
	DWORD i;
	GetExitCodeThread(this->m_hThread, &i);
	return i;
}


// CClientShareTranport message handlers
