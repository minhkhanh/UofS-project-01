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
	iNumCol = 0;
	iSortCol = 0;
	iNumItem = 0;
	iBack = 0;
	iForward = 0;
	flagLoadBackForward = 0;
	iCopy = 0;
	DeleteVector(vBack);
	DeleteVector(vForward);
}

CMyListCtrl::~CMyListCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyListCtrl, CListCtrl)
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK,  &CMyListCtrl::OnLvnColumnclick)
	ON_NOTIFY_REFLECT(LVN_ITEMACTIVATE, &CMyListCtrl::OnLvnItemActivate)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, &CMyListCtrl::OnLvnDeleteitem)
	ON_NOTIFY_REFLECT(LVN_BEGINLABELEDIT, &CMyListCtrl::OnLvnBeginlabeledit)
	ON_NOTIFY_REFLECT(LVN_ENDLABELEDIT, &CMyListCtrl::OnLvnEndlabeledit)
END_MESSAGE_MAP()

void CMyListCtrl::InitListViewClient()
{
	//init column
	InsertColumn(0, _T("Modified"), LVCFMT_LEFT, 80);
	InsertColumn(0, _T("Size"), LVCFMT_LEFT, 80);
	InsertColumn(0, _T("Type"), LVCFMT_LEFT, 50);
	InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
	SetExtendedStyle(LVS_EX_FULLROWSELECT);
	ModifyStyle(0, LVS_SINGLESEL);
	ModifyStyle(0, LVS_EDITLABELS);

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
	int i = pNMLV->iSubItem + 1;
	if (i==iSortCol)
	{
		ListView_SortItems(m_hWnd, &CompareFuncDec, 0L);
		iSortCol = -i;
	}
	else if (i!=iSortCol)
	{
		ListView_SortItems(m_hWnd, &CompareFuncInc, 0L);
		iSortCol = -i;
	}
	*pResult = 0;
}

void CMyListCtrl::OnLvnItemActivate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE lpnmitem = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	TCHAR szTemp[MAX_PATH];
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT|LVIF_PARAM;
	lvItem.iItem = lpnmitem->iItem;
	lvItem.iSubItem = 0;
	lvItem.pszText = szTemp;
	lvItem.cchTextMax = MAX_PATH;
	if (!ListView_GetItem(m_hWnd, &lvItem)) return;
	if ( ((String *)lvItem.lParam)->GetFlags() & IS_DISK )
	{
		this->LoadDir(((String *)lvItem.lParam)->GetData());
	}
	else if ( ((String *)lvItem.lParam)->GetFlags() & IS_FOLDER )
	{
		TCHAR szBuff[MAX_PATH];
		_stprintf(szBuff, _T("%s%s\\"), szCurrPath, szTemp);
		this->LoadDir(szBuff);
	}
	else
	{
		TCHAR szBuff[MAX_PATH];
		_stprintf(szBuff, _T("%s%s"), szCurrPath, szTemp);
		ShellExecute(NULL, _T("open"), szBuff, NULL, szCurrPath, SW_SHOWNORMAL);
	}
	// TODO: Add your control notification handler code here
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
	lvItem.iItem = this->GetItemCount();
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
	pData->Create(sfi.szDisplayName, iNumItem++, iStatus);
	lvItem.lParam = (LPARAM)pData;
	lvItem.iItem = this->GetItemCount();
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
	pData->Create(sfi.szDisplayName, iNumItem++, iStatus);
	lvItem.lParam = (LPARAM)pData;
	lvItem.iItem = this->GetItemCount();
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
	m_eAddressBar->SetText(_T("My Computer"));
	ListView_SortItems(m_hWnd, &CompareFuncDec, 0L);
	iSortCol = 0 + 1;
}

void CMyListCtrl::GoHome()
{
	LoadListDisk();
}

void CMyListCtrl::LoadDir( TCHAR * pPath )
{
	if (!flagLoadBackForward)
	{
		this->AddToBackList(pPath, 0);
		DeleteVector(vForward);
	}
	iNumItem = 0;
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR szDir[MAX_PATH];
	TCHAR szTemp[MAX_PATH];
	TCHAR szPath[MAX_PATH];
	int iDir = 0, iFile = 0;
	_tcscpy(szCurrPath, pPath);
	m_eAddressBar->SetText(szCurrPath);
	int iDem = 0;
	_tcscpy(szDir, pPath);
	ListView_DeleteAllItems(m_hWnd);
	if (szDir[_tcslen(szDir)-1] != '\\')
		_stprintf(szDir, _T("%s\\*"),szDir);
	else
		_stprintf(szDir, _T("%s*"),szDir);
	_tcscpy(szPath, szDir);
	szPath[_tcslen(szPath)-1] = 0;
	hFind = FindFirstFile(szDir, &ffd);
	do
	{
		_tcscmp(ffd.cFileName,_T("."));
		if ((_tcscmp(ffd.cFileName,_T("."))!=0) && (_tcscmp(ffd.cFileName,_T(".."))!=0) )
		{
			SHFILEINFO sfi;
			_stprintf(szTemp, _T("%s%s\\"), szPath, ffd.cFileName);
			SHGetFileInfo(szTemp, NULL, &sfi, sizeof(SHFILEINFO), SHGFI_ICON|SHGFI_SMALLICON|SHGFI_USEFILEATTRIBUTES|SHGFI_DISPLAYNAME);
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				++iDir;
				this->AddItem(ffd, sfi, 1, IS_FOLDER);
			}
			else
			{
				this->AddItem(ffd, sfi, 0);
				++iFile;
			}
		}
	}
	while (FindNextFile(hFind, &ffd) != 0);
	FindClose(hFind);
	TCHAR szText[MAX_PATH];
	_stprintf(szText, _T("Có %d folder con và %d files."), iDir, iFile);
	//mStatusBar.SetText(0, szText);
	ListView_SortItems(m_hWnd, &CompareFuncInc, 0L);
	iSortCol = 0 + 1;
}

void CMyListCtrl::SetAddressBar( CAddressBar * p )
{
	m_eAddressBar = p;
}

void CMyListCtrl::GoUp()
{
	if (_tcslen(szCurrPath)==0) return;
	TCHAR szTemp[MAX_PATH];
	_tcscpy(szTemp, szCurrPath);
	szTemp[_tcslen(szTemp)-1] = 0;
	while ((_tcslen(szTemp)>0)&&(szTemp[_tcslen(szTemp)-1]!='\\'))
	{
		szTemp[_tcslen(szTemp)-1] = 0;
	}
	if (_tcslen(szTemp)==0) 
	{
		this->LoadListDisk();
		return;
	}
	this->LoadDir(szTemp);

}

void CMyListCtrl::GoBack()
{
	if (vBack.size()<2) return;
	this->AddToForwardList((vBack[vBack.size()-1])->GetData(), (vBack[vBack.size()-1])->GetFlags());
	flagLoadBackForward = 1;
	if ((vBack[vBack.size()-2])->GetFlags() & IS_COMPUTER)
		this->LoadListDisk();
	else this->LoadDir((vBack[vBack.size()-2])->GetData());
	flagLoadBackForward = 0;
	delete (String *)vBack[vBack.size()-1];
	vBack.erase(vBack.end()-1);
}

void CMyListCtrl::GoForward()
{
	if (vForward.size()<1) return;
	this->AddToBackList((vForward[vForward.size()-1])->GetData(), (vForward[vForward.size()-1])->GetFlags());
	flagLoadBackForward = 1;
	if ((vForward[vForward.size()-1])->GetFlags() & IS_COMPUTER)
		this->LoadListDisk();
	else this->LoadDir((vForward[vForward.size()-1])->GetData());
	flagLoadBackForward = 0;
	delete (String *)vForward[vForward.size()-1];
	vForward.erase(vForward.end()-1);
}

void CMyListCtrl::GoCreateFolder()
{
	TCHAR szBuff[MAX_PATH];
	_stprintf(szBuff, _T("%sNew Folder"), szCurrPath);
	if (_tcslen(szCurrPath)<=0) return;
	if (!_tmkdir(szBuff)) 
	{
		LVITEM lvItem;
		int iTemp;
		lvItem.mask = LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM;
		lvItem.pszText = _T("New Folder");
		lvItem.iImage = 1;
		lvItem.iSubItem = 0;
		String * pData = new String;
		pData->Create(iNumItem++, IS_FOLDER);
		lvItem.lParam = (LPARAM)pData;
		lvItem.iItem = this->GetItemCount();
		iTemp = ListView_InsertItem(m_hWnd, &lvItem);
		TRACE1(_T("bien iTemp %d"), iTemp);
		SendMessage(LVM_EDITLABEL, iTemp, 0);
	}
}

void CMyListCtrl::OnLvnDeleteitem( NMHDR *pNMHDR, LRESULT *pResult )
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	LVITEM lvItem;
	lvItem.iItem = pNMLV->iItem;
	lvItem.mask = LVIF_PARAM;
	lvItem.iSubItem = 0;
	ListView_GetItem(m_hWnd, &lvItem);
	delete (String *)lvItem.lParam;
	*pResult = 0;
}

void CMyListCtrl::OnLvnBeginlabeledit( NMHDR *pNMHDR, LRESULT *pResult )
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	LVITEM lvI;
	lvI = pDispInfo->item;
	lvI.iSubItem = 0;
	lvI.mask = LVIF_PARAM;
	ListView_GetItem(m_hWnd, &lvI);
	if ( ((String *)lvI.lParam)->GetFlags() & IS_DISK )
	{
		SendMessage(LVM_EDITLABEL, -1, 0);
	}
	*pResult = 0;
}

void CMyListCtrl::OnLvnEndlabeledit( NMHDR *pNMHDR, LRESULT *pResult )
{
	NMLVDISPINFO *pDispInfo = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	LVITEM lvI;
	TCHAR szText[MAX_PATH];
	TCHAR szNewText[MAX_PATH];
	lvI = pDispInfo->item;
	if (lvI.pszText==NULL) return;
	lvI.iSubItem = 0;
	lvI.mask = LVIF_PARAM|LVIF_TEXT;
	_tcscpy(szNewText, lvI.pszText);
	lvI.pszText = szText;
	lvI.cchTextMax = MAX_PATH;
	ListView_GetItem(m_hWnd, &lvI);
	if ( ((String *)lvI.lParam)->GetFlags() & IS_DISK )
	{
		MessageBox(_T("Thành thật xin lỗi chương trình chỉ hỗ trợ đổi tên 1 file hoặc folder !!!"), _T("FTP Client"), MB_OK|MB_ICONERROR);
		return;
	}
	if (!CheckName(szNewText))
	{
		MessageBox(_T("Thành thật xin lỗi hình như tên bạn nhập không hợp lệ thì phải !!!"), _T("FTP Client"), MB_OK|MB_ICONERROR);
		return;
	}
	TCHAR szPath1[MAX_PATH];
	TCHAR szPath2[MAX_PATH];
	_stprintf(szPath1, _T("%s%s"), szCurrPath, szText);
	_stprintf(szPath2, _T("%s%s"), szCurrPath, szNewText);
	if (Rename(szPath1, szPath2))
	{
		this->Update();
	}

	*pResult = 0;
}

void CMyListCtrl::Update()
{
	 if (_tcslen(szCurrPath)<=0) return;

	flagLoadBackForward = 1;
	this->LoadDir(szCurrPath);
	flagLoadBackForward = 0;
}

TCHAR* CMyListCtrl::GetSelectPath()
{
	int iNum = this->GetSelectedCount();
	TCHAR * t = new TCHAR[MAX_PATH];
	if (iNum==1)
	{
		LVITEM lvI;
		lvI.mask = LVIF_PARAM;
		lvI.iItem = ListView_GetNextItem(m_hWnd, -1, LVNI_SELECTED);
		lvI.iSubItem = 0;
		ListView_GetItem(m_hWnd, &lvI);
		if ( ((String *)lvI.lParam)->GetFlags() & IS_DISK )
		{
			_tcscpy(t, ((String *)lvI.lParam)->GetData());
			return t;
		}
		else if (((String *)lvI.lParam)->GetFlags() & IS_FOLDER)
		{
			//_stprintf(t, _T("%s%s\\"), szCurrPath, ((String *)lvI.lParam)->GetData());
			_tcscpy(t, szCurrPath);
			return t;
		}
		else 
		{
			//_stprintf(t, _T("%s%s"), szCurrPath, ((String *)lvI.lParam)->GetData());
			_tcscpy(t, szCurrPath);
			return t;
		}
	}
	if (iNum!=1)
	{
		if (_tcslen(szCurrPath)>0)
		{
			_tcscpy(t, szCurrPath);
			return t;
		}
	}
	delete t;
	return NULL;
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

bool Rename(TCHAR szPathS[], TCHAR szPathD[])
{
	SHFILEOPSTRUCT shfo;
	shfo.hwnd = mListView->m_hWnd;
	shfo.lpszProgressTitle = _T("FTP Client");
	shfo.wFunc = FO_RENAME;

	int i = _tcslen(szPathS)-1;
	int l = _tcslen(szPathD)-1;
	//double null
	szPathS[i+2] = 0;
	szPathD[l+2] = 0;

	shfo.pFrom = szPathS;
	shfo.pTo = szPathD;
	shfo.fFlags = FOF_RENAMEONCOLLISION;

	if (SHFileOperation(&shfo)) 
	{
		//MessageBox(hWnd, _T("Thật ngại quá có vài điều không như ý muốn !!!"), szTitle, MB_OK|MB_ICONERROR);
		return false;
	}
	else 
	{
		return true;
		//MessageBox(hWnd, _T("Hay quá thao tác đã thành công !!!"), szTitle, MB_OK|MB_ICONEXCLAMATION);
	}
}