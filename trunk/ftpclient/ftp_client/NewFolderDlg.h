#pragma once
#include "afxwin.h"


// CNewFolderDlg dialog

class CNewFolderDlg : public CDialog
{
	DECLARE_DYNAMIC(CNewFolderDlg)

public:
	CNewFolderDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CNewFolderDlg();

// Dialog Data
	enum { IDD = IDD_NEWFOLDER_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
private:
	CString m_csFolderName;
	
public:
	CString GetFolderName() { return m_csFolderName; }
	
};
