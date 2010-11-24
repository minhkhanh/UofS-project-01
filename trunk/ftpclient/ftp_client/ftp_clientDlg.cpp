
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
	DDX_Control(pDX, IDC_EDIT3, m_ebMessage);
	DDX_Control(pDX, IDC_LIST1, m_lvClient);
	DDX_Control(pDX, IDC_LIST2, m_lvServer);
	DDX_Control(pDX, IDC_EDIT2, m_ebUser);
	DDX_Control(pDX, IDC_EDIT1, m_ebPassword);
	DDX_Control(pDX, IDC_RADIO1, m_optActive);
	DDX_Control(pDX, IDC_RADIO2, m_optPassive);
	DDX_Control(pDX, IDC_BUTTON4, m_btnLog);
}

BEGIN_MESSAGE_MAP(Cftp_clientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON4, &Cftp_clientDlg::OnClicked_BtnLog)
	ON_MESSAGE(WM_SOCKET_CMD, CmdSockMsg)
	ON_MESSAGE(WM_SOCKET_DATA, DataSockMsg)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST2, &Cftp_clientDlg::OnLvnItemActivateList2)
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

	InitSock();
	InitListViews();
	InitStuff();

	if (m_datasock.CreateSock() != 0)
	{
		AfxMessageBox(_T("data socket init failed!"));;
		//return;
	}

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

	//s.
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


void Cftp_clientDlg::OnClicked_BtnLog()
{
	// TODO: Add your control notification handler code here

	if (CheckLogging() == false)
		return;

	if (m_cmdsock.IsConnecting() == true)
		m_cmdsock.QUIT();

	if (m_cmdsock.CreateSock() != 0)
	{
		AfxMessageBox(_T("command socket init failed!"));;
		return;
	}

	DWORD dwServIpAddr;
	m_ipaddrServer.GetAddress(dwServIpAddr);

	if (m_cmdsock.Connect(dwServIpAddr, FTP_SERVER_CMD_PORT) != 0)
	{
		AfxMessageBox(_T("connect failed!"));
		return;
	}

	if (m_cmdsock.SetSelectMode(m_hWnd, WM_SOCKET_CMD, FD_READ | FD_CLOSE) != 0)
	{
		AfxMessageBox(_T("set select mode error!"));
		return;
	}

	// cmd socket ket noi thanh cong

	//TCHAR
	CString cstrTmp;
	m_ebUser.GetWindowText(cstrTmp);
	m_cmdsock.USER(&cstrTmp);
	m_ebPassword.GetWindowText(cstrTmp);
	m_cmdsock.PASS(&cstrTmp);

	//sockaddr_in addrCmd;
	//int iSize;
	//getsockname(m_sockCmd, (sockaddr*)&addrCmd, &iSize);
	//int iPort = 0;
	//iPort = ntohs(addrCmd.sin_port);
	//iSize += iPort;

	
	//ULONG k = htonl(.S_un.S_addr);
	//cstrTmp = inet_ntoa(addrCmd.sin_addr);
}

void Cftp_clientDlg::ProcessCmd( CString * pcsCmd )
{
	CString csCode = MyTools::PeelMessage(pcsCmd);

	if (csCode.CompareNoCase(MyTools::CR_230) == 0)			// User logged in, proceed.
		Handle230(pcsCmd);
	else if (csCode.CompareNoCase(MyTools::CR_227) == 0)	// Entering Passive Mode (h1,h2,h3,h4,p1,p2).
		Handle227(pcsCmd);
	else if (csCode.CompareNoCase(MyTools::CR_250) == 0)	// Requested file action okay, completed.
		Handle250(pcsCmd);
}

LRESULT Cftp_clientDlg::CmdSockMsg(WPARAM wParam, LPARAM lParam)
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
			TCHAR sRecvBuff[CMDBUFF_MAXLEN];

			int iLength = recv(wParam, (char*)sRecvBuff, CMDBUFF_MAXLEN*sizeof(TCHAR), 0);
			//strRecvBuff[iLength] = '\0';
			CString csRecv(sRecvBuff, iLength);

			PrintMessage(&csRecv);
			//AfxMessageBox(csRecv);

			ProcessCmd(&csRecv);
		}
		break;
	case FD_CLOSE:
		{

		}
		break;
	}

	return 0;
}

LRESULT Cftp_clientDlg::DataSockMsg( WPARAM wParam, LPARAM lParam )
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
			TCHAR sRecvBuff[DATABUFF_MAXLEN];

			int iLength = recv(wParam, (char*)sRecvBuff, DATABUFF_MAXLEN*sizeof(TCHAR), 0);
			if (iLength == DATABUFF_MAXLEN*sizeof(TCHAR))
			{
				m_csRecvBuff += CString(sRecvBuff, iLength);
				if (m_csRecvBuff.Right(2) != _T("\r\n"))
					return 0;
			}
			else
				m_csRecvBuff += CString(sRecvBuff, iLength);

			//PrintMessage(&m_csRecvBuff);

			ProcessData(&m_csRecvBuff);

			m_csRecvBuff.Empty();
		}
		break;
	case FD_CLOSE:
		{

		}
		break;
	}

	return 0;
}

void Cftp_clientDlg::PrintMessage( CString * pcsMess )
{
	m_ebMessage.SetSel(0xffff,0xffff);
	m_ebMessage.ReplaceSel(*pcsMess);
}

void Cftp_clientDlg::InitListViews()
{
	m_lvClient.InsertColumn(0, _T("Modified"), LVCFMT_LEFT, 80);
	m_lvClient.InsertColumn(0, _T("Size"), LVCFMT_LEFT, 80);
	m_lvClient.InsertColumn(0, _T("Type"), LVCFMT_LEFT, 50);
	m_lvClient.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
	m_lvClient.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_lvServer.InsertColumn(0, _T("Modified"), LVCFMT_LEFT, 80);
	m_lvServer.InsertColumn(0, _T("Size"), LVCFMT_LEFT, 80);
	m_lvServer.InsertColumn(0, _T("Type"), LVCFMT_LEFT, 50);
	m_lvServer.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
	m_lvServer.SetExtendedStyle(LVS_EX_FULLROWSELECT);
}

bool Cftp_clientDlg::CheckLogging()
{
	if (m_ebUser.GetWindowTextLength() == 0)
	{
		AfxMessageBox(_T("Username must be not null!"));
		return false;
	}

	if (m_ebPassword.GetWindowTextLength() == 0)
	{
		AfxMessageBox(_T("Password must be not null!"));
		return false;
	}

	if (m_optActive.GetCheck() == false && m_optPassive.GetCheck() == false)
	{
		AfxMessageBox(_T("You must select one Mode!"));
		return false;
	}

	return true;
}

void Cftp_clientDlg::ControlSwitch()
{
	m_bControlSwitch = !m_bControlSwitch;

	//m_ebUser.EnableWindow(m_bControlSwitch);
	//m_ebPassword.EnableWindow(m_bControlSwitch);
	//m_ipaddrServer.EnableWindow(m_bControlSwitch);
	//m_optActive.EnableWindow(m_bControlSwitch);
	//m_optPassive.EnableWindow(m_bControlSwitch);

	//if (m_bControlSwitch)
	//	m_btnLog.SetWindowText(_T("Log in"));
	//else
	//	m_btnLog.SetWindowText(_T("Log out"));
}

void Cftp_clientDlg::InitStuff()
{
	m_csRemotePath = _T("/");
	m_bControlSwitch = true;
}

void Cftp_clientDlg::UpdateClientLV()
{

}

void Cftp_clientDlg::UpdateServerLV()
{

}

//void Cftp_clientDlg::HandlePORT(CString * pcsCmd)
//{
//	CString csIP;
//	int iPort;
//
//	MyTools::GetIPnPort(pcsCmd, &csIP, &iPort);
//	
//	//m_datasock.SetServInfo(csIP.GetBuffer(), iPort);
//}

void Cftp_clientDlg::Handle230( CString * pcsCmd )
{
	m_csRemotePath = _T("/");
	m_cmdsock.LIST(&m_csRemotePath, m_optPassive.GetCheck());
}

void Cftp_clientDlg::Handle227( CString * pcsCmd )
{
	CString csCmd(*pcsCmd);		// giu lai ban goc cua message

	MyTools::PeelMessage(&csCmd, 1, _T("("));
	CString csIPnPort = MyTools::PeelMessage(&csCmd, 1, _T(")"));

	CString csIP;
	int iPort;
	MyTools::GetIPnPort(&csIPnPort, &csIP, &iPort);

	m_datasock.CreateSock();
	m_datasock.Connect(csIP.GetBuffer(), iPort);
	m_datasock.SetSelectMode(m_hWnd, WM_SOCKET_DATA, FD_READ | FD_CLOSE);
}

void Cftp_clientDlg::ProcessData( CString * pcsData )
{
	if (m_cmdsock.LastestCmd().CompareNoCase(MyTools::FC_LIST) == 0)
		HandleLIST(pcsData);
}

void Cftp_clientDlg::HandleLIST( CString * pcsData )
{
	m_lvServer.DeleteAllItems();

	//m_lvServer.InsertItem(0, _T("[..]"));

	CString csLine = MyTools::PeelMessage(pcsData, 1, _T("\n"));
	while (csLine != _T(""))
	{
		int iCount = 0;
		int iSizePos = -1, iDatePos = -1, iNamePos = -1;
		for (int i = 1; i < csLine.GetLength(); ++i)
		{
			if (csLine[i] != _T(' ') && csLine[i-1] == _T(' '))
			{
				++iCount;
				if (iCount == 4)
					iSizePos = i;

				if (iCount == 5)
					iDatePos = i;

				if (iCount == 8)
				{
					iNamePos = i;
					break;
				}
			}
		}

		CString csFileName = csLine.Right(csLine.GetLength() - iNamePos);
		CString csFileTitle, csFileType, csSize;
		if (csLine[0] == _T('d'))
		{
			csFileTitle = csFileName;
			csFileType = _T("");
			csSize = _T("<DIR>");
		}
		else if (csLine[0] == _T('-') || csLine[0] == _T('l'))
		{
			int iDotPos = csFileName.ReverseFind(_T('.'));
			if (iDotPos == -1)
			{
				csFileTitle = csFileName;
				csFileType = _T("<UNK>");
			}
			else
			{
				csFileTitle = csFileName.Left(iDotPos);
				csFileType = csFileName.Right(csFileName.GetLength()-iDotPos-1);
			}

			csSize = csLine.Mid(iSizePos, iDatePos-iSizePos);
		}
		
		CString csDateTime = csLine.Mid(iDatePos, iNamePos-iDatePos);

		int iItem = m_lvServer.GetItemCount();
		m_lvServer.InsertItem(iItem, csFileTitle);
		m_lvServer.SetItemText(iItem, 1, csFileType);
		m_lvServer.SetItemText(iItem, 2, csSize);
		m_lvServer.SetItemText(iItem, 3, csDateTime);
		
		csLine = MyTools::PeelMessage(pcsData, 1, _T("\n"));
	}
}

void Cftp_clientDlg::InitSock()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2,2);

	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		AfxMessageBox(_T("WSAStartup() failed"));
}
void Cftp_clientDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	WSACleanup();
}

void Cftp_clientDlg::OnLvnItemActivateList2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	CString csFileType = m_lvServer.GetItemText(pNMIA->iItem, 2);
	if (csFileType != _T("<DIR>"))
	{
		//!!! thao tac voi file o day
		return;
	}

	CString csPath = m_lvServer.GetItemText(pNMIA->iItem, 0);
	m_cmdsock.CWD(&csPath);
}

void Cftp_clientDlg::Handle250( CString * pcsCmd )
{
	if (m_cmdsock.LastestCmd().CompareNoCase(MyTools::FC_CWD) == 0)
		m_cmdsock.LIST(NULL, m_optPassive.GetCheck());
}