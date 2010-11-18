
// ftp_clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ftp_client.h"
#include "ftp_clientDlg.h"

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


// Cftp_clientDlg dialog




Cftp_clientDlg::Cftp_clientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Cftp_clientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Cftp_clientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddrServer);
}

BEGIN_MESSAGE_MAP(Cftp_clientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON4, &Cftp_clientDlg::OnBnClickedButton4)
	ON_MESSAGE(WM_SOCKET, SockMsg)
END_MESSAGE_MAP()


// Cftp_clientDlg message handlers

BOOL Cftp_clientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

void Cftp_clientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void Cftp_clientDlg::OnPaint()
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
HCURSOR Cftp_clientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Cftp_clientDlg::OnBnClickedButton4()
{
	// TODO: Add your control notification handler code here

	m_sockCmd = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockCmd == INVALID_SOCKET)
	{
		AfxMessageBox(_T("socket() failed!"));
		return;
	}

	IN_ADDR ia;

	DWORD dwServIpAddr;
	m_ipaddrServer.GetAddress(dwServIpAddr);
	ia.S_un.S_addr = ntohl(dwServIpAddr);

	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(FTP_SERVER_CMD_PORT);
	addrServer.sin_addr.s_addr = inet_addr(inet_ntoa(ia));

	//sockaddr_in.sin_addr

	if (addrServer.sin_addr.s_addr == INADDR_NONE)
	{
		AfxMessageBox(_T("Server address unknown!"));
		return;
	}

	int err = connect(m_sockCmd, (struct sockaddr*)&addrServer, sizeof(addrServer));
	if (err == SOCKET_ERROR)
	{
		AfxMessageBox(_T("connect() failed!"));
		return;
	}

	err = WSAAsyncSelect(m_sockCmd, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	if (err == SOCKET_ERROR)
	{
		AfxMessageBox(_T("WSAAsyncSelect() error!"));
		closesocket(m_sockCmd);
		return;
	}

	// cmd socket ket noi thanh cong
	m_commCmd.SockComm(m_sockCmd);
}

LRESULT Cftp_clientDlg::SockMsg(WPARAM wParam, LPARAM lParam)
{
	WORD WERROR = WSAGETSELECTERROR(lParam);
	if (WERROR)
	{
		closesocket(wParam);
	}

	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
		{
			TCHAR strRecvBuff[512];

			recv(wParam, (char*)strRecvBuff, 512*sizeof(TCHAR), 0);

			AfxMessageBox(strRecvBuff);
		}
		break;
	case FD_CLOSE:
		{

		}
		break;
	}

	return 0;
}