
// ConfClientDlg.h : header file
//

#pragma once

#include "afxwin.h"
#include "afxcmn.h"

#include "ClientComm.h"
#include "ClientShareService.h"

#define WM_SOCKET WM_USER + 1
#define CHAT_PORT 3000		// chat channel port


class CPrivateChatDlg;

// CConfClientDlg dialog
class CClientConfDlg : public CDialog
{
// Construction
public:
	CClientConfDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CONFCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

	friend class CPrivateChatDlg;
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
private:
	// chuoi con tro den cac dialog 
	vector<CPrivateChatDlg*> m_vpPrivDlg;

	// socket:
	SOCKET m_sockThisClient;
	SOCKET m_sockServer;

	CClientShareService *m_serviceClient;

	// bien comm giao tiep giua client va server
	ClientComm m_comm;

	// trang thai connect cua client
	bool m_bConnected;
	// chua do dai cua buffer cho message sap nhan
	int m_iBuffLength;

	// the hien cac file cung voi trang thai hien tai (da upload hay dang upload bao nhieu %)
	CListCtrl m_lvFiles;
	// list view username dang ket noi server
	CListCtrl m_lvUsers;
	// khung chua noi dung chat public
	CEdit m_ebPublicContent;
	// khung chua message do nguoi dung go vao
	CEdit m_ebMessage;
	// khung ip address
	CIPAddressCtrl m_ipaddrServer;

	CString m_cstrCurrFileUp;

	// ham khoi tao list view file
	void InitFileLv();
	// ham khoi tao socket
	void InitSocket();
	// ham khoi tao linh tinh
	void InitStuff();

	// ham xu ly message nhan duoc
	void ProcessMessage(CString *cstrMess);

	void ProcessPubChatMess(CString *cstrPubChatMess);
	void ProcessUserLoggedInMess(CString *cstrMessContent);
	void ProcessUserExistedErr(CString *cstrErrMess);
	void ProcessUserListData(CString *cstrUserList);
	void ProcessUserLoggedOutMess(CString *cstrMessContent);
	void ProcessPrivChatMess(CString *cstrPubChatMess);
	void ProcessPrivChatErr(CString *cstrErrMess);
	void ProcessUploadReadyMess(CString *cstrMessContent);
	void ProcessPubFileOffer(CString *cstrMessContent);
	void ProcessPrivFileOffer(CString *cstrMessContent);
	void ProcessPrivFileAccept(CString *cstrMessContent);
	void ProcessPrivFileDownload(CString *cstrMessContent);

	// chen chuoi vao cuoi khung noi dung chat public
	void WriteToPubContent(TCHAR *strMess);

	// xoa username ra khoi list view usernames
	void RemoveUsername(CString *cstrUsername);
	// xoa private chat dialog doi voi username nay
	void RemovePrivDlg(CString *cstrUsername);
	// xoa tat ca private chat dialog
	void RemoveAllPrivDlg();

	// enable / disable cac control lien quan sau khi dang nhap / dang xuat
	void ControlSwitch(bool bval);

	// tim dialog chat private
	int FindPrivDlg(CString *cstrUsername);

	// tao va hien thi private chat dialog
	CPrivateChatDlg *GetPrivDlg(CString *cstrRemoteUser);

	//void ChangeDefBtn(CButton *btnPrev, CButton *btnNext);
public:
	// ham xu ly click nut OK
	afx_msg void OnClicked_BtnConnect();
	// ham xu ly click nut Send
	afx_msg void OnClicked_BtnSendPubMess();
	// ham xu ly su kien chon user chat private
	afx_msg void OnClicked_BtnSelectUser();

	// ham bat su kien socket
	LRESULT SockMsg(WPARAM wParam, LPARAM lParam);	
	afx_msg void OnLvnItemActivateListUsers(NMHDR *pNMHDR, LRESULT *pResult);
	CButton m_btnConnect;
	CButton m_btnSendMess;
	afx_msg void OnClicked_BtnUpload();
private:
	CButton m_btnDownload;
};