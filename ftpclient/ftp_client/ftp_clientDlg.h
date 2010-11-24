
// ftp_clientDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "CmdSock.h"
#include "DataSock.h"
#include "MyTools.h"
#include "afxwin.h"

#define WM_SOCKET_CMD	WM_USER + 1
#define WM_SOCKET_DATA	WM_USER + 2

#define  FTP_SERVER_CMD_PORT	21

#define CMDBUFF_MAXLEN	256
#define DATABUFF_MAXLEN	512


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
	afx_msg void OnClicked_BtnLog();
	LRESULT CmdSockMsg(WPARAM wParam, LPARAM lParam);
	LRESULT DataSockMsg(WPARAM wParam, LPARAM lParam);

	void ProcessCmd(CString * pcsCmd);
	void Handle230(CString * pcsCmd);
	void Handle227(CString * pcsCmd);
	void Handle250(CString * pcsCmd);

	void ProcessData(CString * pcsData);
	void HandleLIST(CString * pcsData);
	
	void PrintMessage(CString * pcsMess);

	void InitSock();
	void InitStuff();
	void InitListViews();

	bool CheckLogging();

	bool m_bControlSwitch;
	void ControlSwitch();

	void UpdateClientLV();
	void UpdateServerLV();

private:
	CString m_csRemotePath;
	CString m_csRecvBuff;
	CmdSock m_cmdsock;
	DataSock m_datasock;
	CIPAddressCtrl m_ipaddrServer;
	CEdit m_ebMessage;
	// list view file ben phia client
	CListCtrl m_lvClient;
	// list view file ben phia server
	CListCtrl m_lvServer;
	// edit box ten dang nhap
	CEdit m_ebUser;
	// edit box mat khau
	CEdit m_ebPassword;
	// nut chon Active Mode
	CButton m_optActive;
	// nut chon Passive Mode
	CButton m_optPassive;
	// nut dang nhat/dang xuat
	CButton m_btnLog;
public:
	afx_msg void OnDestroy();

public:
	afx_msg void OnLvnItemActivateList2(NMHDR *pNMHDR, LRESULT *pResult);
};
