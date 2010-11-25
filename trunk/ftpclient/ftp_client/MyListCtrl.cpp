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
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK,  &CMyListCtrl::OnLvnColumnclick)
END_MESSAGE_MAP()

void CMyListCtrl::InitListViewClient()
{
	//init column
	InsertColumn(0, _T("Modified"), LVCFMT_LEFT, 80);
	InsertColumn(0, _T("Size"), LVCFMT_LEFT, 80);
	InsertColumn(0, _T("Type"), LVCFMT_LEFT, 50);
	InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
	SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//init imagelist
	HIMAGELIST	hSmallList;
	HIMAGELIST	hLargeList;
	Shell_GetImageLists(&hLargeList, &hSmallList);
	ListView_SetImageList(this->m_hWnd, hSmallList, LVSIL_SMALL);
	ListView_SetImageList(this->m_hWnd, hLargeList, LVSIL_NORMAL);
}

void CMyListCtrl::OnLvnColumnclick( NMHDR *pNMHDR, LRESULT *pResult )
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}



// CMyListCtrl message handlers


