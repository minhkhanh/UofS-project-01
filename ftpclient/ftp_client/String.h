#pragma once
//#include "StdAfx.h"

class String
{
private:
	TCHAR * pData;
	int iSize;
	int iFlags;
	int iIndex;
public:

	String(void)
	{
		iSize = iFlags = 0;
		pData = NULL;
	}

	void Create(int nIndex, int iFlag) //dung cho listview
	{
		iSize = 0;
		iIndex = nIndex;
		iFlags = iFlag;
		pData = NULL;
	}
	void Create(TCHAR szT[], int nIndex, int iFlag) //dung cho listview
	{
		iSize = _tcslen(szT);
		delete pData;
		pData = (TCHAR*)malloc((iSize+1)*sizeof(TCHAR));
		_tcscpy(pData, szT);
		iFlags = iFlag;
		iIndex = nIndex;
	}
	int GetIndex()
	{
		return iIndex;
	}
	void Create(int iFlag)
	{
		iSize = 0;
		iFlags = iFlag;
		pData = NULL;
	}
	void Create(TCHAR szT[]) //dung cho back forward
	{
		iSize = _tcslen(szT);
		delete pData;
		pData = (TCHAR*)malloc((iSize+1)*sizeof(TCHAR));
		_tcscpy(pData, szT);
	}
	void Create(TCHAR szT[], int iFlag) //dung cho treeview
	{
		iSize = _tcslen(szT);
		delete pData;
		pData = (TCHAR*)malloc((iSize+1)*sizeof(TCHAR));
		_tcscpy(pData, szT);
		iFlags = iFlag;
	}
	TCHAR * GetData()
	{
		return pData;
	}
	int GetFlags()
	{
		return iFlags;
	}
	void AddFlag(int iFlag)
	{
		iFlags |= iFlag;
	}
	void RemoveFlag(int iFlag)
	{
		iFlags &= (~iFlag);
	}
	virtual ~String(void)
	{
		delete pData;
	}
};

//void DDWORD2String( __int64 Number, TCHAR FmtNumber[])
//{
//	const int LBUF = 14;
//	const int LFMT = 17;
//
//	TCHAR buffer[LBUF], fmtbuffer[LFMT];
//	_i64tot(Number, buffer, 10);
//	int n=0;
//	int icount=0;
//	int l = wcslen(buffer) - 1;
//	for(int i=l;i>=0;i--)
//	{
//		if (icount==3)
//		{
//			fmtbuffer[n]=',';
//			icount=0;
//			n++;
//		}
//		fmtbuffer[n]=buffer[i];
//		icount++;
//		n++;
//	}
//	fmtbuffer[n]=0;
//	_tcscpy(FmtNumber, _tcsrev(fmtbuffer));
//}
//
//


//void DDWORD2String(DWORD Number,DWORD lowNum, TCHAR FmtNumber[])
//{
//	const int LBUF = 14;
//	const int LFMT = 17;
//
//	TCHAR buffer[LBUF], fmtbuffer[LFMT];
//	_i64tot(Number, buffer, 10);
//	int n=0;
//	int icount=0;
//	int l = wcslen(buffer) - 1;
//	for(int i=l;i>=0;i--)
//	{
//		if (icount==3)
//		{
//			fmtbuffer[n]=',';
//			icount=0;
//			n++;
//		}
//		fmtbuffer[n]=buffer[i];
//		icount++;
//		n++;
//	}
//	fmtbuffer[n]=0;
//	_tcscpy(FmtNumber, _tcsrev(fmtbuffer));
//}