
// ConfServerDlg.h : header file
//

#pragma once

#include "afxcmn.h"
#include "afxwin.h"

#include "ServerComm.h"
#include "ServerShareService.h"
#include "resource.h"

#define WM_SOCKET WM_USER + 1	// socket message
#define CHAT_PORT	3000


// CConfServerDlg dialog
class CServerConfDlg : public CDialog
{
// Construction
public:
	CServerConfDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CONFSERVER_DIALOG };

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

private:
	// 2 thong tin ve socket cua server
	SOCKET m_sockServer;

	CServerShareService *m_serviceShare;

	// mang cac socket client
	vector<ServerComm> m_vComm;

	// trang thai cho biet server dang chay hay khong
	bool m_bRunning;
	// do dai buffer danh cho message sap nhan
	int m_iBuffLength;

	// danh sach file dang duoc share
	CListCtrl m_lvFiles;
	// danh sach cac user da ket noi den server
	CListCtrl m_lvUsers;
	// khung noi dung chat public
	CEdit m_ebPublicContent;

	// cac ham khoi tao
	void InitSocket();
	void InitStuff();

	// ham xu ly message
	void ProcessMessage(SOCKET sockTarget, CString *cstrMess);

	void ProcessPubChatMess(CString *cstrPubChatMess, int iSenderIdx = -1);
	void ProcessUsernameReq(CString *cstrUsername, int iSenderIdx = -1);
	void ProcessPrivChatMess(CString *cstrMessContent, int iSenderIdx = -1);
	void ProcessUploadReq(CString *cstrFileName, int iSenderIdx = -1);
	void ProcessPrivFileOffer(CString *cstrMessContent, int iSenderIdx = -1);
	void ProcessPrivFileAccept(CString *cstrMessContent, int iSenderIdx = -1);

	// ham gui thong diep chat public cho tat ca client
	void AnnouncePubChatMess(CString *cstrMessContent);

	// gui thong diep thong bao co user dang nhap vao server
	void AnnounceUserLoggedIn(CString *cstrUsername, CString *cstrMessBody);
	// gui thong bao co user thoat ra
	void AnnounceUserLoggedOut(CString *cstrUsername, CString *cstrMessBody);

	// tim kiem theo gia tri socket
	int FindComm(SOCKET sock);
	// tim kiem theo gia tri ten username
	int FindComm(CString *cstrUsername);
	// ket thuc mot socket
	void EndComm(int idx);

	// xoa bo username ra khoi list view users
	void RemoveUsername(CString *cstrUsername);
	// kiem tra username co tren list view username hay ko. false: co
	bool CheckUsername(CString *cstrUsername);

	// thay doi trang thai cac control khi server thay doi trang thai
	void ControlSwitch(bool bval);

	// dung server
	void StopServer();

	// gui noi dung chat vao cuoi khung chat public
	void WriteToPubContent(TCHAR *strMess);

	// kiem tra co file ko. !!! false: co
	bool CheckFile(CString *cstrFileName);

public:
	void AnnounceFileForShare( CString *cstrFileSize, CString *cstrPort, CString *cstrFileName);

	// ham bat su kien socket
	LRESULT SockMsg(WPARAM wParam, LPARAM lParam);

	// ham click nut Run
	afx_msg void OnClicked_BtnRun();	
};
