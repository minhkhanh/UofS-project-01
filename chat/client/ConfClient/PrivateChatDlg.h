#pragma once
#include "afxwin.h"
//#include "ConfClientDlg.h"


// CPrivateChatDlg dialog

class CClientConfDlg;

class CPrivateChatDlg : public CDialog
{
	DECLARE_DYNAMIC(CPrivateChatDlg)

public:
	CPrivateChatDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPrivateChatDlg();

// Dialog Data
	enum { IDD = IDD_DLG_PRIVATE };

	friend class CClientConfDlg;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	virtual BOOL OnInitDialog();
	virtual void PostNcDestroy();

	DECLARE_MESSAGE_MAP()

public:
	CString m_cstrLocalUser;
	CString m_cstrRemoteUser;
	void WriteToPrivContent(TCHAR *strMess);
	afx_msg void OnClicked_BtnSend();

	void ProcessPrivFileOffer(CString *cstrFileName);
	CString ProcessPrivFileDownload(CString cstrMessage);

private:
	//int m_iDx;
	CEdit m_ebMessage;
	CEdit m_ebPrivateContent;
	CClientConfDlg * m_pClientConf;

	CString m_cstrCurrFileUp;
public:
	afx_msg void OnClicked_BtnSendFile();
};
