// PrivateChatDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfClient.h"
#include "PrivateChatDlg.h"
#include "ConfClientDlg.h"


// CPrivateChatDlg dialog

IMPLEMENT_DYNAMIC(CPrivateChatDlg, CDialog)

CPrivateChatDlg::CPrivateChatDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPrivateChatDlg::IDD, pParent)
{
}

CPrivateChatDlg::~CPrivateChatDlg()
{
}

void CPrivateChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_ebPrivateContent);
	DDX_Control(pDX, IDC_EDIT2, m_ebMessage);
}


BEGIN_MESSAGE_MAP(CPrivateChatDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CPrivateChatDlg::OnClicked_BtnSend)
	ON_BN_CLICKED(IDC_BUTTON2, &CPrivateChatDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

void CPrivateChatDlg::WriteToPrivContent( TCHAR *strMess )
{
	m_ebPrivateContent.SetSel(0xffff,0xffff);
	m_ebPrivateContent.ReplaceSel(strMess);
}

BOOL CPrivateChatDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	this->SetWindowText(m_cstrRemoteUser);

	return FALSE;
}
// CPrivateChatDlg message handlers

void CPrivateChatDlg::OnClicked_BtnSend()
{
	// TODO: Add your control notification handler code here

	CString cstrMess;
	m_ebMessage.GetWindowText(cstrMess);
	
	CString cstrPrivMess = CString(L"\r\n") + m_cstrLocalUser + L": " + cstrMess.GetBuffer();
	WriteToPrivContent(cstrPrivMess.GetBuffer());

	m_pConfClient->m_comm.SendPrivMess_C(&m_cstrRemoteUser, &cstrMess);

	m_ebMessage.SetWindowText(L"");
	m_ebMessage.SetFocus();
}

//
//void CPrivateChatDlg::WritePrivMess( CString *cstrUsername, CString *cstrMess )
//{
//	CString cstrMess = cstrUsername->GetBuffer();
//}

void CPrivateChatDlg::PostNcDestroy()
{
	CDialog::PostNcDestroy();

	delete this;
}
void CPrivateChatDlg::OnBnClickedButton2()
{
	// TODO: Add your control notification handler code here

	// filepath + ip + port
	// goi message
}
