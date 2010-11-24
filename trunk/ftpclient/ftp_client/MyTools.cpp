#include "StdAfx.h"
#include "MyTools.h"

TCHAR* MyTools::FC_LIST = _T("list");
TCHAR* MyTools::FC_CWD = _T("cwd");

TCHAR* MyTools::CR_230 = _T("230");
TCHAR* MyTools::CR_227 = _T("227");
TCHAR* MyTools::CR_250 = _T("250");

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

void MyTools::GetIPnPort( CString * pcsCmd, CString * pcsIP, int * iPort )
{
	pcsIP->Empty();

	int count = 0;
	int i = 0;
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

	*iPort = 0;
	CString csTmp;
	int iTmp = 256;
	for ( ; i < pcsCmd->GetLength(); ++i)
	{
		if ((*pcsCmd)[i] != _T(','))
			csTmp += (*pcsCmd)[i];
		else
		{
			*iPort += _tcstoi64(csTmp.GetBuffer(), NULL, 10 ) * iTmp;
			csTmp.Empty();

			iTmp -= 255;
		}			
	}

	*iPort += _tcstoi64(csTmp.GetBuffer(), NULL, 10 );
}