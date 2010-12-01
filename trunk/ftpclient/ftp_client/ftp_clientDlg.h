
// ftp_clientDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "MyTools.h"
#include "afxwin.h"
#include "MyListCtrl.h"
#include "AddressBar.h"
#include "Resource.h"
#include "NewFolderDlg.h"

//static UINT MyThread(LPVOID param);

struct ThreadStruct
{
	SOCKET s;
	CString f;
};


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
	LRESULT DataSockMsgBinary(WPARAM wParam, LPARAM lParam);

	void ProcessCmd();
	void Handle230();
	void Handle227();
	void Handle250();
	void Handle200();
	void Handle331();
	void Handle220();
	void Handle226();
	void Handle257();
	void Handle150();
	void Handle550();
	void Handle425();

	void ProcessData();
	void HandleLIST();
	void HandleRETR();
	void HandleSTOR();
	void HandleNameList();
	void OnFtpModeResponse();
	
	void PrintMessage(CString * pcsMess);

	void InitSock();
	void InitStuff();
	void InitListViews();

	bool CheckLogging();

	bool m_bControlSwitch;
	void ControlSwitch();

	bool m_bIsConnecting;

	void NetPathToHost(CString * pcsPath);
	CString HostPathToNet(CString csHostDir);

	void CalcSavedDirLevel(CString * pcsPath, TCHAR tcLevelType);

	int MkDirAndCWD(CString * pcsNetDir);

	void BackToWrkDir();

	int CreateSocket(SOCKET& sock);
	int ConnectSocket(SOCKET& sock, DWORD dwIP, int iPort);
	int ConnectSocket(SOCKET& sock, CString * pcsIP, int iPort);
	int BindActiveSock();
	int ListenOnActiveSock();
	int SetSelectMode(SOCKET& sock, int iHandler, int iEvents);
	int CloseActiveSocks();
	int AcceptServer();
	void CloseDataConnections();

	int SetFtpMode();

	static DWORD WINAPI MyThread(LPVOID param);

	void PopFileAndDELE();
	void PopFolderAndRMD();

	void QUIT();
	void PASV();
	void PORT();
	void USER();
	void PASS();
	void CWD(CString* pcsDir);
	void LIST(CString* pcsDir = NULL);
	void TYPE(TCHAR tc);
	void RETR(CString * pcsName);
	void DELE(CString * pcsFile);
	void RMD(CString * pcsDir);
	void PWD();
	void MKD(CString * pcsDirName);
	void STOR(CString * pcsFileName);	

private:
	SOCKET m_sockCmd;		// for port 21
	SOCKET m_sockActiveClient;		// lang nghe trong mode active
	SOCKET m_sockServer;	// giao tiep data voi server trong mode active
	SOCKET m_sockData;		// giao tiep data voi server trong mode passive

	CString m_csLastCmd;
	CString m_csTodoCmd;

	CString m_csCmdBuff;
	CString m_csDataBuff;

	vector<char*> m_vBinBuff;
	vector<int> m_vBinBuffLen;

	queue<CString> m_qFiles;
	queue<CString> m_qFolders;
	stack<CString> m_stkFolders;

	TCHAR m_tcType;
	CString m_csWorkingDir;
	CString m_csSavedDir;
	int m_iSavedDirLevel;
	
	FTPMode m_eFtpMode;

	CString m_csServIPnPort;

private:
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

public:
	void FreeDataBuff();
	void FreeContainers();

	afx_msg void OnDestroy();
	afx_msg void OnLvnItemActivateList2(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedRadio1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnClicked_BtnRefresh();

	void DemoUpload();
	afx_msg void OnClicked_BtnUpload();

	afx_msg void OnLvnItemActivateListClient(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnClicked_BtnDelete();
	afx_msg void OnClicked_BtnDownload();
	
	afx_msg void OnBnClickedButton11();
	afx_msg void OnBnClickedButton10();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnClicked_BtnNewFolder();
};
