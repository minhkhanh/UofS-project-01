// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ftp_client.h"
#include "MyListCtrl.h"
#include "String.h"

extern CMyListCtrl * mListView;
// CMyListCtrl

IMPLEMENT_DYNAMIC(CMyListCtrl, CListCtrl)

CMyListCtrl::CMyListCtrl()
{
	iSortCol = -1;
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
	int i = pNMLV->iSubItem;
	if (i!=iSortCol)
	{
		ListView_SortItems(m_hWnd, &CompareFuncInc, 0L);
		iSortCol = i;
	}
	else
	{
		ListView_SortItems(m_hWnd, &CompareFuncDec, 0L);
		iSortCol = -1;
	}
	*pResult = 0;
}

int CMyListCtrl::GetSortColumn()
{
	return iSortCol;
}

// CMyListCtrl message handlers



int CALLBACK CompareFuncInc( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
	TCHAR	szItemText1[MAX_PATH];	// Text (Label) cua item #1
	TCHAR	szItemText2[MAX_PATH];	// Text (Label) cua item #2

	LVITEM lvItem;

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = ((String *)lParam1)->GetIndex();
	lvItem.pszText = szItemText1;
	lvItem.cchTextMax = MAX_PATH;
	lvItem.iSubItem = mListView->GetSortColumn();
	ListView_GetItem(mListView->m_hWnd, &lvItem);

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = ((String *)lParam2)->GetIndex();
	lvItem.pszText = szItemText2;
	lvItem.cchTextMax = MAX_PATH;
	lvItem.iSubItem = mListView->GetSortColumn();
	ListView_GetItem(mListView->m_hWnd, &lvItem);

	if (((String *)lParam1)->GetFlags() & IS_FOLDER)
	{
		if (((String *)lParam2)->GetFlags()& IS_FOLDER)
		{
			return _tcscmp(szItemText1, szItemText2);
		}
		else return -1;
	}
	else
	{
		if (!(((String *)lParam2)->GetFlags()& IS_FOLDER))
		{
			return _tcscmp(szItemText1, szItemText2);
		}
		else return 1;
	}
	//return 0;
}

int CALLBACK CompareFuncDec( LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort )
{
	TCHAR	szItemText1[MAX_PATH];	// Text (Label) cua item #1
	TCHAR	szItemText2[MAX_PATH];	// Text (Label) cua item #2

	LVITEM lvItem;

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = ((String *)lParam1)->GetIndex();
	lvItem.pszText = szItemText1;
	lvItem.cchTextMax = MAX_PATH;
	lvItem.iSubItem = mListView->GetSortColumn();
	ListView_GetItem(mListView->m_hWnd, &lvItem);

	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = ((String *)lParam2)->GetIndex();
	lvItem.pszText = szItemText2;
	lvItem.cchTextMax = MAX_PATH;
	lvItem.iSubItem = mListView->GetSortColumn();
	ListView_GetItem(mListView->m_hWnd, &lvItem);

	if (((String *)lParam1)->GetFlags() & IS_FOLDER)
	{
		if (((String *)lParam2)->GetFlags()& IS_FOLDER)
		{
			return _tcscmp(szItemText2, szItemText1);
		}
		else return 1;
	}
	else
	{
		if (!(((String *)lParam2)->GetFlags()& IS_FOLDER))
		{
			return _tcscmp(szItemText2, szItemText1);
		}
		else return -1;
	}
}
