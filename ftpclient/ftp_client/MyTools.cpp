#include "StdAfx.h"
#include "MyTools.h"

int MyTools::DATAPORT = 30000;

TCHAR* MyTools::FC_LIST = _T("list");
TCHAR* MyTools::FC_CWD = _T("cwd");
TCHAR* MyTools::FC_PORT = _T("port");
TCHAR* MyTools::FC_PASV = _T("pasv");
TCHAR* MyTools::FC_USER = _T("user");
TCHAR* MyTools::FC_PWD = _T("pwd");
TCHAR* MyTools::FC_TYPE = _T("type");
TCHAR* MyTools::FC_STOR = _T("stor");
TCHAR* MyTools::FC_DELE = _T("dele");
TCHAR* MyTools::FC_RETR = _T("retr");
TCHAR* MyTools::FC_PASS = _T("pass");

TCHAR* MyTools::CR_230 = _T("230");
TCHAR* MyTools::CR_227 = _T("227");
TCHAR* MyTools::CR_250 = _T("250");
TCHAR* MyTools::CR_200 = _T("200");
TCHAR* MyTools::CR_331 = _T("331");
TCHAR* MyTools::CR_220 = _T("220");
TCHAR* MyTools::CR_226 = _T("226");
TCHAR* MyTools::CR_257 = _T("257");
TCHAR* MyTools::CR_150 = _T("150");

MyTools::MyTools(void)
{
}

MyTools::~MyTools(void)
{
}

CString MyTools::PeelMessage( CString* pcsMess, int iDirect, TCHAR sToken[] )
{
	//int iPos = 0;
	//CString csOut = pcsMess->Tokenize(sToken, iPos);	// tach chuoi theo khoang trang

	//if (iPos == -1 || iPos == pcsMess->GetLength() + 1)	// duyet het chuoi hoac chuoi ko co ki tu gioi han
	//	csOut = "";
	//else
	//	pcsMess->Delete(0, iPos);	// loai bo phan mess leader trong message

	//return csOut;

	CString csOut;
	int iPos = -1;
	if (iDirect > 0)
	{
		iPos = pcsMess->Find(sToken, 0);
		if (iPos > 0)
		{
			csOut = pcsMess->Left(iPos);
			pcsMess->Delete(0, iPos+1);
		}
	}
	else if (iDirect < 0)
	{
		iPos = pcsMess->ReverseFind(sToken[0]);		//!!! ham ReverseFind() chi tim duoc 1 ki tu
		if (iPos > 0)
		{
			csOut = pcsMess->Right(pcsMess->GetLength() - iPos - 1);
			pcsMess->Delete(iPos, pcsMess->GetLength() - iPos);
		}
	}

	return csOut;
}

void MyTools::GetCmdIPnPort( CString * pcsCmd, CString * pcsIP, int * pPort )
{
	int count = 0;
	int i = 0;

	if (pcsIP != NULL)
	{
		pcsIP->Empty();

		for ( ; i < pcsCmd->GetLength(); ++i)
		{
			if ((*pcsCmd)[i] != _T(','))
				*pcsIP += (*pcsCmd)[i];
			else
			{
				if (++count == 4)
				{
					++i;
					break;
				}
				*pcsIP += _T('.');
			}
		}
	}

	if (pPort != NULL)
	{
		*pPort = 0;
		CString csTmp;
		int iTmp = 256;
		for ( ; i < pcsCmd->GetLength(); ++i)
		{
			if ((*pcsCmd)[i] != _T(','))
				csTmp += (*pcsCmd)[i];
			else
			{
				*pPort += _tcstoi64(csTmp.GetBuffer(), NULL, 10 ) * iTmp;
				csTmp.Empty();

				iTmp -= 255;
			}			
		}

		*pPort += _tcstoi64(csTmp.GetBuffer(), NULL, 10 );
	}
}

void MyTools::GetSockIPnPort( SOCKET sock, CString * pcsIP, int * pPort )
{
	sockaddr_in addrSock;	
	int iSize = sizeof(addrSock);
	getsockname(sock, (sockaddr*)&addrSock, &iSize);

	if (pcsIP != NULL)
	{
		pcsIP->Empty();
		*pcsIP = inet_ntoa(addrSock.sin_addr);
	}

	if (pPort != NULL)
	{
		*pPort = ntohs(addrSock.sin_port);
	}
}

void MyTools::ExtractFileDetails( CString * pcsLine, CString * pcsTitle, CString * pcsType, CString * pcsSize, CString * pcsDate )
{
	int iCount = 0;
	int iSizePos = -1, iDatePos = -1, iNamePos = -1;
	for (int i = 1; i < pcsLine->GetLength(); ++i)
	{
		if ((*pcsLine)[i] != _T(' ') && (*pcsLine)[i-1] == _T(' '))
		{
			++iCount;
			if (iCount == 4)
				iSizePos = i;

			if (iCount == 5)
				iDatePos = i;

			if (iCount == 8)
			{
				iNamePos = i;
				break;
			}
		}
	}

	CString csFileName = pcsLine->Right(pcsLine->GetLength() - iNamePos);
	//CString csFileTitle, csFileType, csSize;
	if ((*pcsLine)[0] == _T('d'))
	{
		*pcsTitle = csFileName;
		*pcsType = _T("");
		*pcsSize = _T("<DIR>");
	}
	else if ((*pcsLine)[0] == _T('-'))// || csLine[0] == _T('l'))
	{
		int iDotPos = csFileName.ReverseFind(_T('.'));
		if (iDotPos == -1)
		{
			*pcsTitle = csFileName;
			*pcsType = _T("");
		}
		else
		{
			*pcsTitle = csFileName.Left(iDotPos);
			*pcsType = csFileName.Right(csFileName.GetLength()-iDotPos-1);
		}

		*pcsSize = pcsLine->Mid(iSizePos, iDatePos-iSizePos);
	}

	*pcsDate = pcsLine->Mid(iDatePos, iNamePos-iDatePos);
}