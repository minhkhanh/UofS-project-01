
// ftp_clientDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "CmdSock.h"
#include "DataSock.h"
#include "MyTools.h"
#include "afxwin.h"
#include "MyListCtrl.h"
#include "AddressBar.h"


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
	LRESULT DataSockMsg2(WPARAM wParam, LPARAM lParam);

	void ProcessCmd(CString * pcsCmd);
	void Handle230(CString * pcsCmd);
	void Handle227(CString * pcsCmd);
	void Handle250(CString * pcsCmd);
	void Handle200(CString * pcsCmd);
	void Handle331(CString * pcsCmd);
	void Handle220(CString * pcsCmd);
	void Handle226(CString * pcsCmd);
	void Handle257(CString * pcsCmd);

	void ProcessData(CString * pcsData);
	void HandleLIST(CString * pcsData);

	void Upload();
	void Download();
	
	void PrintMessage(CString * pcsMess);

	void InitSock();
	void InitStuff();
	void InitListViews();

	bool CheckLogging();

	bool m_bControlSwitch;
	void ControlSwitch();

private:
	SOCKET m_sockTmp;
	CString m_csRemotePath;
	CString m_csDataBuff2;
	CString m_csDataBuff;
	CmdSock m_cmdsock;
	DataSock m_datasock;
	DataSock m_datasock2;
	//SOCKET m_sockActServer;
	MySock m_sockActClient;
	CIPAddressCtrl m_ipaddrServer;
	CEdit m_ebMessage;
	// list view file ben phia client
	CMyListCtrl m_lvClient;
	//
	CAddressBar m_eAddressBar;
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
	CString m_csCmdBuff;
public:
	afx_msg void OnDestroy();

public:
	afx_msg void OnLvnItemActivateList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnClicked_BtnRefresh();
	afx_msg void OnClicked_BtnUpload();
	afx_msg void OnLvnItemActivateListClient(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton7();
};
