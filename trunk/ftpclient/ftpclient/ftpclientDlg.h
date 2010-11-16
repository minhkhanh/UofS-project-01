
// ftpclientDlg.h : header file
//

#pragma once
#include "afxcmn.h"


// CftpclientDlg dialog
class CftpclientDlg : public CDialog
{
// Construction
public:
	CftpclientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FTPCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();

	void InitListViews();
private:
	// list view file/folder ben phia client
	CListCtrl m_lvClient;
	// list view file/folder ben phia server
	CListCtrl m_lvServer;
	// dia chi IP cua server
	CIPAddressCtrl m_ipaddrServer;
};
