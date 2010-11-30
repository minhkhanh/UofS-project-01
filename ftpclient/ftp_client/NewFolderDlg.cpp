// NewFolderDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ftp_client.h"
#include "NewFolderDlg.h"


// CNewFolderDlg dialog

IMPLEMENT_DYNAMIC(CNewFolderDlg, CDialog)

CNewFolderDlg::CNewFolderDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNewFolderDlg::IDD, pParent)
	, m_csFolderName(_T(""))
{

}

CNewFolderDlg::~CNewFolderDlg()
{
}

void CNewFolderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_csFolderName);
}


BEGIN_MESSAGE_MAP(CNewFolderDlg, CDialog)
END_MESSAGE_MAP()

// CNewFolderDlg message handlers
