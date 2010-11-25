#pragma once

// CMyListCtrl

class CMyListCtrl : public CListCtrl
{
	DECLARE_DYNAMIC(CMyListCtrl)

private:
	int iSortCol;

public:
	CMyListCtrl();
	virtual ~CMyListCtrl();
	void InitListViewClient();
	void GoHome();
	int GetSortColumn();

public:
	afx_msg void OnLvnColumnclick(NMHDR *pNMHDR, LRESULT *pResult);

protected:
	DECLARE_MESSAGE_MAP()
};

int CALLBACK CompareFuncInc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);
int CALLBACK CompareFuncDec(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

