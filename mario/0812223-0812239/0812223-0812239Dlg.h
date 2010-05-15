
// 0812223-0812239Dlg.h : header file
//

#pragma once

#include "MainGame.h"
#include "Thread.h"

// CMy08122230812239Dlg dialog
class CMy08122230812239Dlg : public CDialog, kbcafe::thread
{
// Construction
public:
	CMy08122230812239Dlg(CWnd* pParent = NULL);	// standard constructor

	virtual void run();

	MainGame *mg;

// Dialog Data
	enum { IDD = IDD_MY08122230812239_DIALOG };

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
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};
