
// 0812223-0812239Dlg.cpp : implementation file
//

#include "stdafx.h"
#include "0812223-0812239Dlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CMy08122230812239Dlg dialog




CMy08122230812239Dlg::CMy08122230812239Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMy08122230812239Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy08122230812239Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy08122230812239Dlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_WM_KEYDOWN()
	ON_WM_KEYUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()


// CMy08122230812239Dlg message handlers

BOOL CMy08122230812239Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	mg = new MainGame();
	this->start();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMy08122230812239Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMy08122230812239Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMy08122230812239Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

CClientDC *pDC;
void CMy08122230812239Dlg::run()
{
	pDC = new CClientDC(this);

	mg->SetPDC(pDC);
	mg->GameLoop();
}
void CMy08122230812239Dlg::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	char aChar = (char)nChar;

	switch (aChar)
	{
	case 'w':
	case 'W':
		mg->KeyPressed(GameKeys::Up);
		break;
	case 's':
	case 'S':
		mg->KeyPressed(GameKeys::Down);
		break;
	case 'a':
	case 'A':
		mg->KeyPressed(GameKeys::Left);
		break;
	case 'd':
	case 'D':
		mg->KeyPressed(GameKeys::Right);
		break;
	case 'n':
	case 'N':
		mg->KeyPressed(GameKeys::Enter);
		break;
	}

	__super::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CMy08122230812239Dlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default

	char aChar = (char)nChar;

	switch (aChar)
	{
	case 'w':
	case 'W':
		mg->KeyRelease(GameKeys::Up);
		break;

	case 's':
	case 'S':
		mg->KeyRelease(GameKeys::Down);
		break;
	case 'a':
	case 'A':
		mg->KeyRelease(GameKeys::Left);
		break;

	case 'd':
	case 'D':
		mg->KeyRelease(GameKeys::Right);
		break;

	case 'n':
	case 'N':
		mg->KeyRelease(GameKeys::Enter);
		break;
	}

	__super::OnKeyUp(nChar, nRepCnt, nFlags);
}

int CMy08122230812239Dlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (__super::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}
