#pragma once
#include "String.h"
#include <vector>
using namespace std;
// CMyListCtrl
#define MAX_BACK_FARWARD	200
#define MAX_NUM				20
#define LV_DATACREATE		3
#define LV_SIZE				2
#define LV_TYPE				1 //chua cai dat
#define LV_NAME				0
class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

private:
	int iNumCol;
	int iSortCol;
	int iNumItem;
	int iCopy;
	int flagLoadBackForward;
	TCHAR szCurrPath[MAX_PATH];
	TCHAR szCopyPath[MAX_PATH];
	vector<String *> vBack;
	vector<String *> vForward;
	vector<String *> vCopy;
	int iBack, iForward;

private:
	void AddToBackList(TCHAR *pData, int flag);
	void AddToForwardList(TCHAR *pData, int flag);
	void AddDisk(SHFILEINFO &sfi, TCHAR szPath[], int iStatus);
	void AddItem(WIN32_FIND_DATA ffd, SHFILEINFO &sfi, int iStatus);
	void AddItem(WIN32_FIND_DATA ffd, SHFILEINFO &sfi,int iImage, int iStatus);
	void AddSubItem(TCHAR *szText, int iParentItem, int iSub);
	bool CheckName(TCHAR szText[]);

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();
	void InitListViewClient();
	void GoHome();
	int GetSortColumn();
	void LoadListDisk();

public:
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	DECLARE_MESSAGE_MAP()
};

int CALLBACK CompareFuncInc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
int CALLBACK CompareFuncDec(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

void DDWORD2Size( __int64 Number, double & Size, TCHAR Units[3]);
void DDWORD2Size(DWORD Number, DWORD lowNum, double & Size, TCHAR Units[3]);
void DeleteVector(vector<String *> &v);