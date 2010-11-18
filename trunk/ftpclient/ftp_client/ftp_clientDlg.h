
// ftp_clientDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "Comm.h"

#define WM_SOCKET	WM_USER + 1
#define  FTP_SERVER_CMD_PORT	21


// Cftp_clientDlg dialog
class Cftp_clientDlg : public CDialog
{
// Construction
public:
	Cftp_clientDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FTP_CLIENT_DIALOG };

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
	afx_msg void OnBnClickedButton4();
	LRESULT SockMsg(WPARAM wParam, LPARAM lParam);

private:
	SOCKET m_sockCmd;
	Comm m_commCmd;
	CIPAddressCtrl m_ipaddrServer;
};
