// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ftp_client.h"
#include "MyListCtrl.h"


// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{

}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
END_MESSAGE_MAP()

void CMyListCtrl::InitListViewClient()
{
	InsertColumn(0, _T("Modified"), LVCFMT_LEFT, 80);
	InsertColumn(0, _T("Size"), LVCFMT_LEFT, 80);
	InsertColumn(0, _T("Type"), LVCFMT_LEFT, 50);
	InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
	SetExtendedStyle(LVS_EX_FULLROWSELECT);
}



// CMyListCtrl message handlers


