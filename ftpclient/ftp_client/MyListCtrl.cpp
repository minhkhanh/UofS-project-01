// MyListCtrl.cpp : implementation file
//

#include "stdafx.h"
#include "ftp_client.h"
#include "MyListCtrl.h"
#include "DiskManager.h"


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

void CMyListCtrl::AddToBackList(TCHAR *pData, int flag)
{
	if (iBack>MAX_BACK_FARWARD) 
	{
		delete (String *)vBack[0];
		vBack.erase(vBack.begin());
	}
	else ++iBack;
	String * pTemp = new String;
	pTemp->Create(pData, flag);
	vBack.push_back(pTemp);
}

void CMyListCtrl::AddToForwardList(TCHAR *pData, int flag)
{
	if (iForward>MAX_BACK_FARWARD) 
	{
		delete (String *)vForward[0];
		vForward.erase(vForward.begin());
	}
	else ++iForward;
	String * pTemp = new String;
	pTemp->Create(pData, flag);
	vForward.push_back(pTemp);
}

void CMyListCtrl::AddDisk(SHFILEINFO &sfi, TCHAR szPath[], int iStatus)	//chi dung load disk
{
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvItem.pszText = sfi.szDisplayName;
	lvItem.iImage = sfi.iIcon;
	lvItem.iSubItem = 0;
	String * pData = new String;
	pData->Create(szPath, iStatus);
	lvItem.lParam = (LPARAM)pData;
	int nItem = ListView_InsertItem(m_hWnd, &lvItem);
	//for (int i = 1; i<iNumCol; ++i) this->AddSubItem(
}

void CMyListCtrl::AddItem(WIN32_FIND_DATA ffd, SHFILEINFO &sfi, int iStatus)
{
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvItem.pszText = sfi.szDisplayName;
	lvItem.iImage = sfi.iIcon;
	lvItem.iSubItem = 0;
	String * pData = new String;
	pData->Create(iNumItem++, iStatus);
	lvItem.lParam = (LPARAM)pData;
	int nItem = ListView_InsertItem(m_hWnd, &lvItem);
	if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		TCHAR szTemp[MAX_NUM];
		double dSize;
		TCHAR szUnits[3];
		DDWORD2Size(ffd.nFileSizeHigh, ffd.nFileSizeLow, dSize, szUnits);
		_stprintf(szTemp, _T("%.2f %s"), dSize, szUnits);
		this->AddSubItem(szTemp, nItem, LV_SIZE);
		//if (ffd.ftLastWriteTime!=NULL)
		{
			TCHAR szTemp1[MAX_PATH];
			SYSTEMTIME stUTC, stLocal;
			FileTimeToSystemTime(&ffd.ftLastWriteTime, &stUTC);
			SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);
			_stprintf(szTemp1, _T("%02d/%02d/%d %02d:%02d"), stLocal.wMonth, stLocal.wDay, stLocal.wYear, stLocal.wHour, stLocal.wMinute);
			this->AddSubItem(szTemp1, nItem, LV_DATACREATE);
		}
	}
}

void CMyListCtrl::AddSubItem(TCHAR *szText, int iParentItem, int iSub)
{
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	lvItem.iItem = iParentItem;
	lvItem.pszText = szText;
	lvItem.cchTextMax = MAX_PATH;
	lvItem.iSubItem = iSub;
	ListView_SetItem(m_hWnd, &lvItem);
}

void CMyListCtrl::AddItem(WIN32_FIND_DATA ffd, SHFILEINFO &sfi, int iImage, int iStatus)
{
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
	lvItem.pszText = sfi.szDisplayName;
	lvItem.iImage = iImage;
	lvItem.iSubItem = 0;
	String * pData = new String;
	pData->Create(iNumItem++, iStatus);
	lvItem.lParam = (LPARAM)pData;
	int nItem = ListView_InsertItem(m_hWnd, &lvItem);
	if (!(ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		TCHAR szTemp[MAX_NUM];
		double dSize;
		TCHAR szUnits[3];
		DDWORD2Size(ffd.nFileSizeHigh, ffd.nFileSizeLow, dSize, szUnits);
		_stprintf(szTemp, _T("%.2f %s"), dSize, szUnits);
		this->AddSubItem(szTemp, nItem, LV_SIZE);
	}
}

bool CMyListCtrl::CheckName(TCHAR szText[]) //chưa xây dựng xong
{
	return true;
}

void CMyListCtrl::LoadListDisk()
{
	if (!flagLoadBackForward)
	{
		this->AddToBackList(_T(""), IS_COMPUTER);
		DeleteVector(vForward);
	}
	ListView_DeleteAllItems(m_hWnd);
	_tcscpy(szCurrPath, _T(""));
	iNumItem = 0;
	DiskManager mDisk;
	mDisk.UpdateStatus();
	for (int i=0; i<mDisk.GetNumDisk(); ++i)
	{
		DiskInfo dInfo = mDisk.GetDiskInfo(i);
		SHFILEINFO sfi;
		SHGetFileInfo(dInfo.sPath, NULL, &sfi, sizeof(SHFILEINFO), SHGFI_ICON|SHGFI_SMALLICON|SHGFI_USEFILEATTRIBUTES|SHGFI_DISPLAYNAME);
		this->AddDisk(sfi, dInfo.sPath, IS_DISK);
	}
	//TCHAR szText[MAX_PATH];
	//swprintf(szText, MAX_PATH, _T("Máy tính có %d ổ đĩa logic."), mDisk.GetNumDisk());
	//mStatusBar.SetText(0, szText);
	ListView_SortItems(m_hWnd, &CompareFuncDec, 0L);
	iSortCol = 0;
}

void CMyListCtrl::GoHome()
{
	LoadListDisk();
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


void DDWORD2Size(DWORD Number, DWORD lowNum, double & Size, TCHAR Units[3])
{
	const int KB = 1024;
	const int MB = KB*KB;
	const int GB = KB*MB;
	double DIV;
	double d1, d2;
	d1 = Number;
	d2 = d1 * (MAXDWORD+1);
	d2 += lowNum;
	if (d2>GB)
	{
		DIV = double(GB);
		_tcscpy(Units,_T("GB"));
	}
	else if (d2>MB)
	{
		DIV = double(MB);
		_tcscpy(Units,_T("MB"));
	}
	else
	{
		DIV = double(KB);
		_tcscpy(Units,_T("KB"));
	}
	Size = d2 / DIV;
}
void DDWORD2Size( __int64 Number, double & Size, TCHAR Units[3])
{
	const int KB = 1024;
	const int MB = KB*KB;
	const int GB = KB*MB;
	double DIV;
	if (Number>GB)
	{
		DIV = double(GB);
		_tcscpy(Units,_T("GB"));
	}
	else if (Number>MB)
	{
		DIV = double(MB);
		_tcscpy(Units,_T("MB"));
	}
	else
	{
		DIV = double(KB);
		_tcscpy(Units,_T("KB"));
	}
	Size = Number / DIV;
}

void DeleteVector(vector<String *> &v)
{
	for (int i=0; i<v.size(); ++i)
	{
		delete (String *)v[i];
	}
	v.clear();
}