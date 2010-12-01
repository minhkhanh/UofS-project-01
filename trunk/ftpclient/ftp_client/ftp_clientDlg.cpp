
// ftp_clientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ftp_client.h"
#include "ftp_clientDlg.h"
#include "ServerDownloadThread.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMyListCtrl * mListView;
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
	DDX_Control(pDX, IDC_EDIT4, m_eAddressBar);
}

BEGIN_MESSAGE_MAP(Cftp_clientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON4, &Cftp_clientDlg::OnClicked_BtnLog)
	ON_MESSAGE(WM_SOCKET_CMD, CmdSockMsg)
	ON_MESSAGE(WM_SOCKET_DATA, DataSockMsg)
	ON_MESSAGE(WM_SOCKET_DATA_BINARY, DataSockMsgBinary)
	ON_WM_DESTROY()
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST2, &Cftp_clientDlg::OnLvnItemActivateList2)
	ON_BN_CLICKED(IDC_RADIO1, &Cftp_clientDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &Cftp_clientDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_BUTTON5, &Cftp_clientDlg::OnClicked_BtnRefresh)
	ON_BN_CLICKED(IDC_BUTTON1, &Cftp_clientDlg::OnClicked_BtnUpload)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_CLIENT, &Cftp_clientDlg::OnLvnItemActivateListClient)
	ON_BN_CLICKED(IDC_BUTTON2, &Cftp_clientDlg::OnClicked_BtnDelete)
	ON_BN_CLICKED(IDC_BUTTON6, &Cftp_clientDlg::OnClicked_BtnDownload)
	ON_BN_CLICKED(IDC_BUTTON11, &Cftp_clientDlg::OnBnClickedButton11)
	ON_BN_CLICKED(IDC_BUTTON10, &Cftp_clientDlg::OnBnClickedButton10)
	ON_BN_CLICKED(IDC_BUTTON9, &Cftp_clientDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON8, &Cftp_clientDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON7, &Cftp_clientDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON3, &Cftp_clientDlg::OnClicked_BtnNewFolder)
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
	mListView = & m_lvClient;
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	InitSock();
	InitListViews();
	InitStuff();
	mListView->GoHome();

	//if (m_datasock.CreateSock() != 0)
	//{
	//	AfxMessageBox(_T("data socket init failed!"));;
	//	//return;
	//}

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
	mListView->ShowWindow(SW_SHOW);
	m_lvClient.ShowWindow(SW_SHOW);
	mListView->GoHome();
	if (CheckLogging() == false)
		return;

	if (m_bIsConnecting == true)
		QUIT();

	if (CreateSocket(m_sockCmd) != 0)
		return;

	DWORD dwServIpAddr;
	m_ipaddrServer.GetAddress(dwServIpAddr);

	if (ConnectSocket(m_sockCmd, dwServIpAddr, FTP_SERVER_CMD_PORT) != 0)
		return;

	if (SetSelectMode(m_sockCmd, WM_SOCKET_CMD, FD_READ | FD_CLOSE) != 0)
		return;

	m_csTodoCmd = _T("user");
	m_bIsConnecting = true;
}

void Cftp_clientDlg::ProcessCmd()
{
	CString csCode = MyTools::PeelMessage(&m_csCmdBuff);

	if (csCode.CompareNoCase(MyTools::CR_230) == 0)			// User logged in, proceed.
		Handle230();
	else if (csCode.CompareNoCase(MyTools::CR_227) == 0)	// Entering Passive Mode (h1,h2,h3,h4,p1,p2).
		Handle227();
	else if (csCode.CompareNoCase(MyTools::CR_250) == 0)	// Requested file action okay, completed.
		Handle250();
	else if (csCode.CompareNoCase(MyTools::CR_200) == 0)	// Command okay.
		Handle200();
	else if (csCode.CompareNoCase(MyTools::CR_331) == 0)	// Username okay. Need password.
		Handle331();
	else if (csCode.CompareNoCase(_T("220")) == 0)			// Server ready for new user.
		Handle220();
	else if (csCode.CompareNoCase(MyTools::CR_226) == 0)	// Closing data connection.	Requested file action successful (for example, file	transfer or file abort).
		Handle226();
	else if (csCode.CompareNoCase(MyTools::CR_150) == 0)	// File status okay; about to open data connection.
		Handle150();
	else if (csCode.CompareNoCase(_T("257")) == 0)			// Path name created
		Handle257();
	else if (csCode.CompareNoCase(_T("550")) == 0)			//
		Handle550();
	else if (csCode.CompareNoCase(_T("425")) == 0)			//
		Handle425();

	m_csCmdBuff.Empty();
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
			if (iLength > 0)
			{
				m_csCmdBuff += CString(sRecvBuff, iLength);
			
			}

			PrintMessage(&m_csCmdBuff);
			ProcessCmd();			
			//m_csCmdBuff.Empty();
		}
		break;
	case FD_CLOSE:
		{

		}
		break;
	}

	return 0;
}

//int Khoi = 0;
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
			if (iLength > 0)
				m_csDataBuff += CString(sRecvBuff, iLength);
		}
		break;
	case FD_CLOSE:
		{
			//closesocket(wParam);
		}
		break;
	case FD_ACCEPT:
		{
			AcceptServer();
		}
		break;
	}

	return 0;
}

void Cftp_clientDlg::PrintMessage( CString * pcsMess )
{
	if (m_ebMessage.GetLineCount() % 50 == 0)
	{
		m_ebMessage.SetSel(0, -1);
	}
	else
		m_ebMessage.SetSel(-1, -1);

	m_ebMessage.ReplaceSel(*pcsMess);
}

void Cftp_clientDlg::InitListViews()
{
	m_lvClient.InitListViewClient();
	m_lvClient.SetAddressBar(&m_eAddressBar);		

	m_lvServer.InsertColumn(0, _T("Modified"), LVCFMT_LEFT, 80);
	m_lvServer.InsertColumn(0, _T("Size (B)"), LVCFMT_LEFT, 80);
	m_lvServer.InsertColumn(0, _T("Type"), LVCFMT_LEFT, 50);
	m_lvServer.InsertColumn(0, _T("Name"), LVCFMT_LEFT, 100);
	m_lvServer.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	m_lvServer.ModifyStyle(0, LVS_SINGLESEL);
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
	m_bControlSwitch = true;
	m_ebUser.SetWindowText(_T("s"));
	m_ebPassword.SetWindowText(_T("s"));
	m_ipaddrServer.SetWindowText(_T("127.0.0.1"));
	m_optActive.SetCheck(BST_CHECKED);
	m_bIsConnecting = false;
	m_tcType = _T('A');

	m_bSTORReady = false;
}

// User logged in, proceed. [Uni]
void Cftp_clientDlg::Handle230()
{
	m_csTodoCmd = _T("list");
	CWD(&CString(_T("/")));
}

// Entering Passive Mode (h1,h2,h3,h4,p1,p2).
void Cftp_clientDlg::Handle227()
{
	m_eFtpMode = FTPMode::Passive;

	MyTools::PeelMessage(&m_csCmdBuff, 1, _T("("));
	CString csIPnPort = m_csServIPnPort = MyTools::PeelMessage(&m_csCmdBuff, 1, _T(")"));

	//CString csIP;
	//int iPort;
	//MyTools::GetCmdIPnPort(&csIPnPort, &csIP, &iPort);

	if (CreateSocket(m_sockData) != 0)
		return;

	//else if (m_tcType == _T('I'))
	//	iHandler = WM_SOCKET_DATA_BINARY;

	//if (ConnectSocket(m_sockData, &csIP, iPort) != 0)
	//	return;

	//if (m_tcType == _T('A'))
	//	if (SetSelectMode(m_sockData, WM_SOCKET_DATA, FD_READ | FD_CLOSE) != 0)
	//		return;

	OnFtpModeResponse();
}

void Cftp_clientDlg::HandleLIST()
{
	m_lvServer.DeleteAllItems();

	int iStart = 0;
	CString csLine = m_csDataBuff.Tokenize(_T("\r\n"), iStart);
	CString csTitle, csType, csSize, csDate;
	while (csLine.IsEmpty() == false)
	{		
		MyTools::ExtractFileDetails(&csLine, &csTitle, &csType, &csSize, &csDate);

		int iItem = m_lvServer.GetItemCount();
		m_lvServer.InsertItem(iItem, csTitle);
		m_lvServer.SetItemText(iItem, 1, csType);
		m_lvServer.SetItemText(iItem, 2, csSize);
		m_lvServer.SetItemText(iItem, 3, csDate);
		
		csLine = m_csDataBuff.Tokenize(_T("\r\n"), iStart);

		csTitle.Empty();
		csType.Empty();
		csSize.Empty();
		csDate.Empty();
	}

	//CloseConnections();
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
	
	CString csFileType = m_lvServer.GetItemText(pNMIA->iItem, 2);
	if (csFileType != _T("<DIR>"))
	{
		//!!! thao tac khi double click file o day
		return;
	}

	//CString csPath = m_lvServer.GetItemText(pNMIA->iItem, 0);
	m_csTodoCmd = _T("list");
	CWD(&(m_lvServer.GetItemText(pNMIA->iItem, 0)));
	//m_cmdsock.ToDoCmd() = MyTools::FC_LIST;
	//m_cmdsock.CWD(&csPath);

	*pResult = 0;
}

// Requested file action okay, completed.
void Cftp_clientDlg::Handle250()
{
	if (m_csLastCmd.CompareNoCase(_T("cwd")) == 0)		// directory changed
	{
		PWD();
	}
	else if (m_csLastCmd.CompareNoCase(_T("dele")) == 0)		// delete successful
	{
		if (m_qFiles.size() != 0)			// chua delete het file
		{
			PopFileAndDELE();
		}
		else if (m_stkFolders.size() != 0)	// da delete het file, chuyen sang delete cac folder rong
		{
			PopFolderAndRMD();
		}
		else
			BackToWrkDir();
	}
	else if (m_csLastCmd.CompareNoCase(_T("rmd")) == 0)
	{
		if (m_stkFolders.size() != 0)	// tiep tuc delete cac folder rong
		{
			PopFolderAndRMD();
		}
		else		// ket thuc delete thu muc
		{
			BackToWrkDir();
		}
	}
}
void Cftp_clientDlg::OnBnClickedRadio1()
{
	m_optPassive.SetCheck(BST_UNCHECKED);
}

void Cftp_clientDlg::OnBnClickedRadio2()
{
	m_optActive.SetCheck(BST_UNCHECKED);
}

// Command okay.
void Cftp_clientDlg::Handle200()
{
	if (m_csLastCmd.CompareNoCase(_T("port")) == 0)		// PORT successfully
	{
		m_eFtpMode = FTPMode::Active;
		OnFtpModeResponse();
	}
	else if (m_csLastCmd.CompareNoCase(_T("type")) == 0)	// TYPE set to ...
	{
		if (m_tcType >= 97)
			m_tcType -= 32;		// !!!important: get upper case

		SetFtpMode();
	}
}

LRESULT Cftp_clientDlg::DataSockMsgBinary( WPARAM wParam, LPARAM lParam )
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
			char sRecvBuff[DATABUFF_MAXLEN];
			int iLength = recv(wParam, sRecvBuff, DATABUFF_MAXLEN, 0);
			if (iLength > 0)
			{
				char* p = new char[iLength];
				memcpy(p, sRecvBuff, iLength);
				m_vBinBuff.push_back(p);
				m_vBinBuffLen.push_back(iLength);
			}
		}
		break;
	case FD_CLOSE:
		{
			//ProcessData(&m_csDataBuff2);
			//AfxMessageBox(m_csDataBuff2);
			//m_csDataBuff2.Empty();
		}
		break;
	case FD_ACCEPT:
		{
			AcceptServer();

			if (m_csTodoCmd.CompareNoCase(_T("stor")) == 0)
			{
				//m_bSTORReady = true;
				HandleSTOR();
			}
		}
		break;
	}

	return 0;
}

// User name okay, need password.
void Cftp_clientDlg::Handle331()
{
	PASS();
}

// Service ready for new user.
void Cftp_clientDlg::Handle220()
{
	if (m_csTodoCmd.CompareNoCase(_T("user")) == 0)
	{
		USER();
	}
}

void Cftp_clientDlg::ProcessData()
{
	if (m_csLastCmd.CompareNoCase(_T("list")) == 0 && m_csTodoCmd.CompareNoCase(_T("list")) == 0)
		HandleLIST();
	else if (m_csLastCmd.CompareNoCase(_T("retr")) == 0)
		HandleRETR();
	else if (m_csLastCmd.CompareNoCase(_T("list")) == 0 && m_csTodoCmd.CompareNoCase(_T("retr")) == 0)
	{
		HandleNameList();

		if (m_qFolders.size() != 0)		// tao san het cac thu muc va thu muc con
		{
			CString csNetAbsPath = m_qFolders.front();
			m_qFolders.pop();
			
			if (MkDirAndCWD(&csNetAbsPath) != 0)
			{
				//AfxMessageBox(_T("Mk"))
				return;
			}
		}
		else if (m_qFiles.size() != 0)
		{
			TYPE(_T('i'));		// bat dau download file
		}
		else
		{
			BackToWrkDir();
		}
	}
	else if (m_csTodoCmd.CompareNoCase(_T("dele")) == 0)
	{
		HandleNameList();

		if (m_qFolders.size() != 0)					// tiep tuc duyet file
		{
			CString csNetAbsPath = m_qFolders.front();
			m_qFolders.pop();

			m_stkFolders.push(csNetAbsPath);		// luu lai de sau nay RMD	

			CWD(&csNetAbsPath);
		}
		else if (m_qFiles.size() != 0)				// bat dau delete file
		{
			PopFileAndDELE();
		}
		else										// bat dau delete thu muc rong con lai
		{
			PopFolderAndRMD();
		}
	}
	else if (m_csLastCmd.CompareNoCase(_T("stor")) == 0)
	{
		if (m_qFiles.size() != 0)
			SetFtpMode();
		else
			OnClicked_BtnRefresh();
	}

	FreeDataBuff();
}

void Cftp_clientDlg::Handle226()
{
	ProcessData();

	//if (m_csLastCmd.CompareNoCase(_T("list")) != 0)
	//{
	//	m_cmdsock.ToDoCmd() = MyTools::FC_LIST;
	//	m_cmdsock.TYPE(_T('a'));				// tra ve type A de LIST
	//}
}

void Cftp_clientDlg::OnClicked_BtnRefresh()
{
	m_lvClient.Update();
	m_csTodoCmd = _T("list");
	CWD(&m_csWorkingDir);
}

void Cftp_clientDlg::Handle257()
{
	if (m_csLastCmd.CompareNoCase(_T("pwd")) == 0)
	{
		int iStart = 0;
		m_csWorkingDir = m_csCmdBuff.Tokenize(_T("\""), iStart);
		//m_csWorkingDir = MyTools::PeelMessage(&m_csWorkingPath, -1, _T("/"));//m_csWorkingPath.Right(m_csWorkingPath.GetLength() - m_csWorkingPath.ReverseFind(_T('/') - 1));

		if (m_csTodoCmd.CompareNoCase(_T("list")) == 0)
		{
			//OnClicked_BtnRefresh();
			if (m_tcType != _T('A'))
				TYPE(_T('A'));
			else
				SetFtpMode();
		}
		else if (m_csTodoCmd.CompareNoCase(_T("retr")) == 0)	// download folder
		{
			TYPE('a');	// for list sub files in folder
		}
		else if (m_csTodoCmd.CompareNoCase(_T("dele")) == 0)
		{
			TYPE('a');	// for list sub files in folder
		}
	}
	else if (m_csLastCmd.CompareNoCase(_T("mkd")) == 0)		// directory created
	{
		if (m_csTodoCmd.CompareNoCase(_T("mkd")) == 0)
			OnClicked_BtnRefresh();
		else if (m_csTodoCmd.CompareNoCase(_T("stor")) == 0)
		{
			if (m_qFolders.size() != 0)				// van chua mkd het thu muc
			{
				CString csFolder = HostPathToNet(m_qFolders.front());
				m_qFolders.pop();

				MKD(&csFolder);
			}
			else if (m_qFiles.size() != 0)			// da mkd het thu muc, bat dau stor file
			{
				TYPE('i');
			}
			else
				BackToWrkDir();
		}
	}
}
void Cftp_clientDlg::OnClicked_BtnUpload()
{
	//DemoUpload();
	//return;

	FreeContainers();

	POSITION pos = m_lvClient.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		TCHAR* sCurrPath = m_lvClient.GetSelectPath();
		CString csCurrPath = sCurrPath;
		delete[] sCurrPath;

		int idx = m_lvClient.GetNextSelectedItem(pos);
		String* lpData = (String*)m_lvClient.GetItemData(idx);

		CString csName = m_lvClient.GetItemText(idx, 0);

		CalcSavedDirLevel(&csCurrPath, _T('\\'));

		m_csTodoCmd = _T("stor");
		m_csSavedDir = m_csWorkingDir;

		int iFlag = lpData->GetFlags();
		if ( iFlag != IS_FOLDER && iFlag != IS_DISK)	// upload file
		{
			csName = csName + CString(_T('.')) + m_lvClient.GetItemText(idx, 1);
			m_qFiles.push(csCurrPath + csName);

			TYPE(_T('i'));
		}
		else if (iFlag == IS_FOLDER)	// upload file
		{
			m_stkFolders.push(csCurrPath + csName);

			while (m_stkFolders.size() != 0)
			{
				csCurrPath = m_stkFolders.top();
				m_qFolders.push(csCurrPath);
				m_stkFolders.pop();

				CString csTmpPath = csCurrPath;
				csTmpPath += _T("\\*");

				WIN32_FIND_DATA file;
				HANDLE hFile;

				hFile = FindFirstFile(csTmpPath.GetBuffer(), &file);
				if (hFile != INVALID_HANDLE_VALUE)					// neu co item con
					do
					{
						if ((_tcscmp(file.cFileName, _T(".")) != 0)
							&& (_tcscmp(file.cFileName,_T("..")) != 0))		// neu khong phai la 2 thu muc dac biet
						{
							CString csPath = csCurrPath;
							csPath = csPath + CString(_T('\\')) + file.cFileName;

							if ((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)	// neu item khong phai la folder
							{
								m_qFiles.push(csPath);
							}
							else
							{
								m_stkFolders.push(csPath);
							}
						}
					} while (FindNextFile(hFile, &file) != 0);		// tiep tuc tim file cho den khi nao het
			}

			CString csFolder = HostPathToNet(m_qFolders.front());
			m_qFolders.pop();
			MKD(&csFolder);
		}		
	}
	else
	{
		AfxMessageBox(_T("Please select one file/folder for uploading."));
		return;
	}
}

void Cftp_clientDlg::OnLvnItemActivateListClient(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}

// File status okay; about to open data connection.
void Cftp_clientDlg::Handle150()
{
	if (m_eFtpMode == FTPMode::Passive)
	{
		CString csIP;
		int iPort;
		MyTools::GetCmdIPnPort(&m_csServIPnPort, &csIP, &iPort);

		if (m_tcType == _T('A'))// || (m_tcType == _T('I') && m_csTodoCmd.CompareNoCase(_T("retr")) != 0))
		{
			if (ConnectSocket(m_sockData, &csIP, iPort) != 0)
				return;

			if (SetSelectMode(m_sockData, WM_SOCKET_DATA, FD_READ | FD_CLOSE) != 0)
				return;
		}
	}
	else if (m_eFtpMode == FTPMode::Active)
	{
		////if (m_tcType == _T('A'))
		//	AcceptServer();
	}

	if (m_csTodoCmd.CompareNoCase(_T("stor")) == 0)// && m_bSTORReady == true)
	{
		if (m_eFtpMode == FTPMode::Passive)
		{

		}
	}
	else if (m_csLastCmd.CompareNoCase(_T("retr")) == 0 && m_csTodoCmd.CompareNoCase(_T("retr")) == 0)
	{
		if (m_qFiles.size() != 0)
		{
			CString csFile = m_qFiles.front();
			m_qFiles.pop();
			NetPathToHost(&csFile);

			SOCKET sock = m_eFtpMode == FTPMode::Active ? m_sockActiveClient : m_sockData;
			CServerDownloadThread * t = CServerDownloadThread::CreateCServerDownloadThread(csFile, sock, m_csServIPnPort,m_eFtpMode);
		}
		else
			BackToWrkDir();
	}
}

void Cftp_clientDlg::OnClicked_BtnDelete()
{
	FreeContainers();

	POSITION pos = m_lvServer.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		if (AfxMessageBox(_T("Are you sure?"), MB_YESNO) != IDYES)
			return;

		int idx = m_lvServer.GetNextSelectedItem(pos);
		CString csSize = m_lvServer.GetItemText(idx, 2);
		CString csTitle = m_lvServer.GetItemText(idx, 0);

		CString csPath = m_csWorkingDir == _T('/') ? m_csWorkingDir : m_csWorkingDir + CString(_T('/'));

		m_csTodoCmd = _T("dele");
		m_csSavedDir = m_csWorkingDir;

		if (csSize == _T("<DIR>"))
		{
			m_stkFolders.push(csPath + csTitle);
			CWD(&csTitle);
		}
		else
		{
			CString csName = csTitle + CString(_T('.')) + m_lvServer.GetItemText(idx, 1);
			DELE(&csName);
		}		
	}
	else
	{
		AfxMessageBox(_T("Please select one file/folder for deleting."));
		return;
	}
}

void Cftp_clientDlg::OnClicked_BtnDownload()
{
	FreeContainers();

	POSITION pos = m_lvServer.GetFirstSelectedItemPosition();
	if (pos != NULL)
	{
		int idx = m_lvServer.GetNextSelectedItem(pos);
		CString csSize = m_lvServer.GetItemText(idx, 2);
		CString csName = m_lvServer.GetItemText(idx, 0);

		m_csTodoCmd = _T("retr");

		CString csPath;
		csPath = m_csWorkingDir == _T('/') ? m_csWorkingDir : m_csWorkingDir + CString(_T('/'));

		CalcSavedDirLevel(&csPath, _T('/'));

		m_csSavedDir = m_csWorkingDir;

		if (csSize == _T("<DIR>"))
		{
			if (MkDirAndCWD(&(csPath + csName)) != 0)
				return;
		}
		else
		{
			csName = csPath + csName + CString(_T('.')) + m_lvServer.GetItemText(idx, 1);
			m_qFiles.push(csName);
			TYPE(_T('i'));
		}		
	}
	else
	{
		AfxMessageBox(_T("Please select one file/folder for downloading."));
		return;
	}
}

void Cftp_clientDlg::OnBnClickedButton11()
{
	m_lvClient.GoHome();
	// TODO: Add your control notification handler code here
}

void Cftp_clientDlg::OnBnClickedButton10()
{
	m_lvClient.GoUp();
	// TODO: Add your control notification handler code here
}

void Cftp_clientDlg::OnBnClickedButton9()
{
	m_lvClient.GoBack();
	// TODO: Add your control notification handler code here
}

void Cftp_clientDlg::OnBnClickedButton8()
{
	m_lvClient.GoForward();
	// TODO: Add your control notification handler code here
}

void Cftp_clientDlg::OnBnClickedButton7()
{
	m_lvClient.GoCreateFolder();
	// TODO: Add your control notification handler code here
}

void Cftp_clientDlg::HandleRETR()
{
	if (m_qFiles.size() != 0)
	{
		SetFtpMode();
	}
	else
	{
		BackToWrkDir();
	}
}

void Cftp_clientDlg::FreeDataBuff()
{
	for (int i = 0; i < m_vBinBuff.size(); ++i)
		delete[] m_vBinBuff[i];

	m_vBinBuff.clear();
	m_vBinBuffLen.clear();
	m_csDataBuff.Empty();
}

void Cftp_clientDlg::QUIT()
{
	char sMess[] = "QUIT\r\n";
	send(m_sockCmd, sMess, 6, 0);
}

int Cftp_clientDlg::SetSelectMode( SOCKET& sock, int iHandler, int iEvents )
{
	if (WSAAsyncSelect(sock, m_hWnd, iHandler, iEvents) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("SetSelectMode() fail!"));
		return WSAGetLastError();
	}

	return 0;
}

void Cftp_clientDlg::PASV()
{
	char sMess[] = "PASV\r\n";
	//send(m_sockCmd, sMess, 6, 0);
	send(m_sockCmd, "PASV\r\n", 6, 0);
}

void Cftp_clientDlg::PORT()
{
	if (CreateSocket(m_sockActiveClient) != 0)
		return;

	if (BindActiveSock() != 0)
		return;

	if (ListenOnActiveSock() != 0)
		return;

	//int iHandler = 0;
	if (m_tcType == _T('A'))
	{
		if (SetSelectMode(m_sockActiveClient, WM_SOCKET_DATA, FD_READ | FD_ACCEPT | FD_CLOSE) != 0)
			return;
	}
	else if (m_tcType == _T('I') && m_csTodoCmd.CompareNoCase(_T("retr")) != 0)
	{
		if (SetSelectMode(m_sockActiveClient, WM_SOCKET_DATA_BINARY, FD_READ | FD_ACCEPT | FD_CLOSE) != 0)
			return;
	}

	CString csIP;
	MyTools::GetSockIPnPort(m_sockCmd, &csIP, NULL);
	csIP.Replace(_T('.'), _T(','));

	int iPort;
	MyTools::GetSockIPnPort(m_sockActiveClient, NULL, &iPort);

	int n = iPort / 256;
	int m = iPort % 256;
	CString csPort;
	csPort.Format(_T("%d,%d"), n,m);

	char sMess[40];
	int iLen = _stprintf(sMess, "PORT %s,%s\r\n", csIP.GetBuffer(), csPort.GetBuffer());

	send(m_sockCmd, sMess, iLen, 0);

	m_csLastCmd = _T("port");
}

int Cftp_clientDlg::CreateSocket( SOCKET& sock )
{
	closesocket(sock);
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		AfxMessageBox(_T("CreateSocket() failed!"));
		return WSAGetLastError();
	}

	return 0;
}

int Cftp_clientDlg::BindActiveSock()
{
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(m_sockActiveClient, (sockaddr *)&addrServer, sizeof(addrServer)) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("BindActiveSock() failed."));
		return WSAGetLastError();
	}

	return 0;
}

int Cftp_clientDlg::ListenOnActiveSock()
{
	if (listen(m_sockActiveClient, MAX_BKLG) == SOCKET_ERROR)
	{
		AfxMessageBox(_T("ListenOnActiveSock() failed."));
		return WSAGetLastError();
	}

	return 0;
}

void Cftp_clientDlg::PASS()
{
	CString csPass;
	m_ebPassword.GetWindowText(csPass);

	char* sMess = new char[csPass.GetLength() + 10];
	int iLen = _stprintf(sMess, "PASS %s\r\n", csPass.GetBuffer());

	send(m_sockCmd, sMess, iLen, 0);

	delete[] sMess;
	m_csLastCmd = _T("pass");
}

void Cftp_clientDlg::USER()
{
	CString csUsername;
	m_ebUser.GetWindowText(csUsername);

	//int iMaxLen = csUsername.GetLength() + 10;
	char* sMess = new char[csUsername.GetLength() + 10];
	int iLen = _stprintf(sMess, "USER %s\r\n", csUsername.GetBuffer());

	send(m_sockCmd, sMess, iLen, 0);

	delete[] sMess;
	m_csLastCmd = _T("user");
}

void Cftp_clientDlg::CWD( CString* pcsDir )
{
	char* sMess = new char[pcsDir->GetLength() + 10];
	int iLen = _stprintf(sMess, "CWD %s\r\n", pcsDir->GetBuffer());

	send(m_sockCmd, sMess, iLen, 0);

	delete[] sMess;
	m_csLastCmd = _T("cwd");
}

int Cftp_clientDlg::SetFtpMode()
{
	if (m_optPassive.GetCheck() == BST_CHECKED)
	{
		PASV();
	}
	else
	{
		PORT();
	}

	return 0;
}

void Cftp_clientDlg::LIST( CString* pcsDir /* = NULL */ )
{
	int iMaxLen = pcsDir == NULL ? 
									10 : // !!! must be greater than real needed length for _stprintf to add endl at end of string
										pcsDir->GetLength()+10;
	char* sMess = new char[iMaxLen];
	int iLen = 0;
	if (pcsDir == NULL)		// list thu muc hien tai
	{
		iLen = _stprintf(sMess, "LIST\r\n");
	}
	else
	{
		iLen = _stprintf(sMess, "LIST %s\r\n", pcsDir->GetBuffer());
	}

	send(m_sockCmd, sMess, iLen, 0);
	
	delete[] sMess;
	m_csLastCmd = _T("list");
}

int Cftp_clientDlg::CloseActiveSocks()
{
	//closesocket(m_sockServer);
	//closesocket(m_sockActiveClient);

	return 0;
}

int Cftp_clientDlg::AcceptServer()
{
	sockaddr_in sockaddrClient;
	int iSize = sizeof(sockaddrClient);
	if ((m_sockServer = accept(m_sockActiveClient, (sockaddr*)&sockaddrClient, &iSize)) == INVALID_SOCKET)
	{
		AfxMessageBox(_T("AcceptServer() failed."));
		return WSAGetLastError();
	}

	return 0;
}

void Cftp_clientDlg::TYPE( TCHAR tc )
{
	char sMess[10];
	int iLen = _stprintf(sMess, "TYPE %c\r\n", tc);

	send(m_sockCmd, sMess, iLen, 0);

	m_csLastCmd = _T("type");

	m_tcType = tc < 97 ? tc + 32 : tc;		// get lower case
}

void Cftp_clientDlg::HandleNameList()
{
	CString csTitle, csType, csSize, csDate;
	int iStart = 0;
	CString csLine = m_csDataBuff.Tokenize(_T("\r\n"), iStart);
	while (csLine.IsEmpty() == false)
	{
		MyTools::ExtractFileDetails(&csLine, &csTitle, &csType, &csSize, &csDate);

		if (csTitle != _T('.') && csTitle != _T("..") && csTitle != (_T("")))
			if (csSize == _T("<DIR>"))
			{

				m_qFolders.push(m_csWorkingDir + CString(_T('/')) + csTitle);
			}
			else
			{
				m_qFiles.push(m_csWorkingDir + CString(_T("/")) + csTitle + CString(_T('.')) + csType);
			}

		csLine = m_csDataBuff.Tokenize(_T("\r\n"), iStart);

		csTitle.Empty();
		csType.Empty();
		csSize.Empty();
		csDate.Empty();
	}
}

void Cftp_clientDlg::RETR( CString * pcsName )
{
	char* sMess = new char[pcsName->GetLength()+10];
	int iLen = _stprintf(sMess, "RETR %s\r\n", pcsName->GetBuffer());

	send(m_sockCmd, sMess, iLen, 0);

	delete[] sMess;
	m_csLastCmd = _T("retr");
}

void Cftp_clientDlg::DELE( CString * pcsFile )
{
	char* sMess = new char[pcsFile->GetLength()+10];
	int iLen = _stprintf(sMess, "DELE %s\r\n", pcsFile->GetBuffer());

	send(m_sockCmd, sMess, iLen, 0);

	delete[] sMess;
	m_csLastCmd = _T("dele");
}

void Cftp_clientDlg::RMD( CString * pcsDir )
{
	char* sMess = new char[pcsDir->GetLength()+10];
	int iLen = _stprintf(sMess, "RMD %s\r\n", pcsDir->GetBuffer());

	send(m_sockCmd, sMess, iLen, 0);

	delete[] sMess;
	m_csLastCmd = _T("rmd");
}

void Cftp_clientDlg::Handle550()
{
	if (m_csLastCmd.CompareNoCase(_T("rmd")) == 0)	// cannot remove directory
	{
		AfxMessageBox(_T("Cannot remove directory."));
	}
	else if (m_csLastCmd.CompareNoCase(_T("mkd")) == 0)	// directory already existed
	{
		AfxMessageBox(_T("Cannot create directory."));
	}
}

void Cftp_clientDlg::PWD()
{
	char sMess[10];
	int iLen = _stprintf(sMess, "PWD\r\n");

	send(m_sockCmd, sMess, iLen, 0);

	m_csLastCmd = _T("pwd");
}

int Cftp_clientDlg::MkDirAndCWD( CString * pcsNetDir )
{
	CString csHostDir = *pcsNetDir;

	NetPathToHost(&csHostDir);

	if (_tmkdir(csHostDir.GetBuffer()) != 0)
	{
		AfxMessageBox(_T("Folder creating failed!"));
		BackToWrkDir();
		return -1;
	}

	CWD(pcsNetDir);

	return 0;
}

void Cftp_clientDlg::NetPathToHost( CString * pcsPath )
{
	int i = 0;
	int iCount = 0;
	for ( ; i < pcsPath->GetLength(); ++i)
		if ((*pcsPath)[i] == _T('/'))
		{
			++iCount;
			if (iCount == m_iSavedDirLevel)
				break;
		}
	*pcsPath = pcsPath->Right(pcsPath->GetLength() - i);

	TCHAR* sCurrPath = m_lvClient.GetSelectPath();		// luon co '\' o cuoi

	if ((*pcsPath)[0] == _T('/'))
	{
		pcsPath->Delete(0,1);		// delete because current path has one '\' at end	
	}

	pcsPath->Replace(_T("/"), _T("\\\\"));	
	if (sCurrPath != NULL)
		pcsPath->Insert(0, _T('\\'));
	pcsPath->Insert(0, sCurrPath);	

	delete sCurrPath;
}

//int Cftp_clientDlg::CountDirLevel( CString * pcsDir )
//{
//	int iPos = -1;
//	//CString csTmp = pcsDir->Tokenize(_T("/"), iStart);
//	//pcsDir->
//	int iCount = 0;
//	while ((iPos = pcsDir->Find(_T('/'), iPos+1)) != -1)
//	{
//		++iCount;
//	}
//
//	return iCount;
//}

//void Cftp_clientDlg::GetRETRDirRoot( CString * pcsDir )
//{
//	int i = 0;
//	int iCount = 0;
//	for ( ; i < pcsDir->GetLength(); ++i)
//		if ((*pcsDir)[i] == _T('/'))
//		{
//			++iCount;
//			if (iCount == m_iSavedDirLevel)
//				break;
//		}
//
//	*pcsDir = pcsDir->Right(pcsDir->GetLength() - i);
//}

void Cftp_clientDlg::OnFtpModeResponse()
{
	if (m_csTodoCmd.CompareNoCase(_T("list")) == 0)
	{
		LIST();
	}
	else if (m_csTodoCmd.CompareNoCase(_T("retr")) == 0)
	{
		if (m_tcType == _T('A'))		// list sub files/folders to download the parent folder
			LIST();
		else if (m_tcType == _T('I'))
		{
			if (m_qFiles.size() != 0)		// da tao het thu muc, bat dau download file
			{
				RETR(&m_qFiles.front());
			}
			else
			{
				BackToWrkDir();
			}
		}
	}
	else if (m_csTodoCmd.CompareNoCase(_T("dele")) == 0)
	{
		LIST();
	}
	else if (m_csTodoCmd.CompareNoCase(_T("stor")) == 0)
	{
		if (m_qFiles.size() != 0)
		{
			CString csFile = HostPathToNet(m_qFiles.front());
			STOR(&csFile);
		}
		else
			OnClicked_BtnRefresh();
	}
}

int Cftp_clientDlg::ConnectSocket( SOCKET& sock, DWORD dwIP, int iPort )
{
	IN_ADDR ia;
	ia.S_un.S_addr = ntohl(dwIP);

	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(iPort);
	addrServer.sin_addr.s_addr = inet_addr(inet_ntoa(ia));

	if (connect(sock, (sockaddr*)&addrServer, sizeof(addrServer))== SOCKET_ERROR)
	{
		m_bIsConnecting = false;
		AfxMessageBox(_T("socket connect failed!"));
		return WSAGetLastError();
	}

	return 0;
}

int Cftp_clientDlg::ConnectSocket( SOCKET& sock, CString * pcsIP, int iPort )
{
	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(iPort);
	addrServer.sin_addr.s_addr = inet_addr(pcsIP->GetBuffer());

	if (connect(sock, (sockaddr*)&addrServer, sizeof(addrServer)) == SOCKET_ERROR)
	{
		m_bIsConnecting = false;
		AfxMessageBox(_T("ConnectSocket() failed!"));
		return WSAGetLastError();
	}

	return 0;
}

void Cftp_clientDlg::CloseDataConnections()
{
	//closesocket(m_sockActiveClient);
	//closesocket(m_sockServer);
	//closesocket(m_sockData);
}

void Cftp_clientDlg::PopFileAndDELE()
{
	CString csFile = m_qFiles.front();
	m_qFiles.pop();

	DELE(&csFile);
}

void Cftp_clientDlg::PopFolderAndRMD()
{
	CString csFolder = m_stkFolders.top();
	m_stkFolders.pop();

	RMD(&csFolder);
}

void Cftp_clientDlg::OnClicked_BtnNewFolder()
{
	CNewFolderDlg dlgNewFolder;
	if (dlgNewFolder.DoModal() == IDCANCEL)
		return;

	CString csName = dlgNewFolder.GetFolderName();

	m_csTodoCmd = _T("mkd");
	MKD(&csName);
}

void Cftp_clientDlg::MKD( CString * pcsDirName )
{
	char* sMess = new char[pcsDirName->GetLength() + 10];
	int iLen = _stprintf(sMess, "MKD %s\r\n", pcsDirName->GetBuffer());

	send(m_sockCmd, sMess, iLen, 0);

	delete[] sMess;
	m_csLastCmd = _T("mkd");
}

void Cftp_clientDlg::BackToWrkDir()
{
	m_csWorkingDir = m_csSavedDir;
	OnClicked_BtnRefresh();
}

CString Cftp_clientDlg::HostPathToNet( CString csHostDir )
{
	int i = 0;
	int iCount = 0;
	for ( ; i < csHostDir.GetLength(); ++i)
		if (csHostDir[i] == _T('\\'))
		{
			++iCount;
			if (iCount == m_iSavedDirLevel)
				break;
		}
// C:\A\b.txt
// C:\A\B
	csHostDir = csHostDir.Right(csHostDir.GetLength() - i);

	csHostDir.Replace(_T('\\'), _T('/'));
	if (m_csWorkingDir != _T('/'))
		csHostDir.Insert(0, m_csWorkingDir);

	return csHostDir;
}

void Cftp_clientDlg::STOR( CString * pcsFileName )
{
	char* sMess = new char[pcsFileName->GetLength() + 10];
	int iLen = _stprintf(sMess, "STOR %s\r\n", pcsFileName->GetBuffer());

	send(m_sockCmd, sMess, iLen, 0);

	delete[] sMess;
	m_csLastCmd = _T("stor");
}

void Cftp_clientDlg::HandleSTOR()
{
	CString csFile = m_qFiles.front();
	m_qFiles.pop();

	CFile file;
	if (file.Open(csFile, CFile::modeRead) == 0)
		return;

	ULONGLONG ullFSize = file.GetLength();
	ULONGLONG ullCurPos = 0;

	SOCKET sock = m_eFtpMode == FTPMode::Active ? m_sockServer : m_sockData;

	while (ullCurPos < ullFSize)
	{
		char sBuff[DATABUFF_MAXLEN] = {0};
		UINT len = file.Read(sBuff, DATABUFF_MAXLEN);
		int i = 0;
		while (i < len)
		{
			int j = send(sock, sBuff + i, len - i, 0);
			if (j <= 0)
			{
				break;
			}
			i += j;
		}
		ullCurPos += len;
	}

	file.Close();	
	closesocket(sock);
}

void Cftp_clientDlg::Handle425()
{
	AfxMessageBox(_T("Server cannot open data connection."));
	BackToWrkDir();
}

void Cftp_clientDlg::FreeContainers()
{
	while (m_qFiles.size() != 0)
		m_qFiles.pop();
	while (m_qFolders.size() != 0)
		m_qFolders.pop();
	while (m_stkFolders.size() != 0)
		m_qFolders.pop();
	
}

void Cftp_clientDlg::DemoUpload()
{
	FreeContainers();

	CString csCurrPath = _T("E:\\09-10");
	//CString csName;

	CalcSavedDirLevel(&csCurrPath, _T('\\'));

	m_csTodoCmd = _T("stor");

	//if (lpData->GetFlags() == 0)	// upload file
	//{
	//	csName = csName + CString(_T('.')) + m_lvClient.GetItemText(idx, 1);
	//	m_qFiles.push(csCurrPath + csName);

	//	TYPE(_T('i'));
	//}
	//else if (lpData->GetFlags() == IS_FOLDER)	// upload file
	{
		m_stkFolders.push(csCurrPath);

		while (m_stkFolders.size() != 0)
		{
			csCurrPath = m_stkFolders.top();
			m_qFolders.push(csCurrPath);
			m_stkFolders.pop();

			CString csTmpPath = csCurrPath;
			csTmpPath += _T("\\*");

			WIN32_FIND_DATA file;
			HANDLE hFile;

			hFile = FindFirstFile(csTmpPath.GetBuffer(), &file);
			if (hFile != INVALID_HANDLE_VALUE)					// neu co item con
				do
				{
					if ((_tcscmp(file.cFileName, _T(".")) != 0)
						&& (_tcscmp(file.cFileName,_T("..")) != 0))		// neu khong phai la 2 thu muc dac biet
					{
						CString csPath = csCurrPath;
						csPath = csPath + CString(_T('\\')) + file.cFileName;

						if ((file.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) == 0)	// neu item khong phai la folder
							m_qFiles.push(csPath);
						else
							m_stkFolders.push(csPath);
					}
				} while (FindNextFile(hFile, &file) != 0);		// tiep tuc tim file cho den khi nao het
		}

		CString csFolder = HostPathToNet(m_qFolders.front());
		m_qFolders.pop();
		MKD(&csFolder);
	}
}

void Cftp_clientDlg::CalcSavedDirLevel( CString * pcsPath, TCHAR tcLevelType )
{
	int iPos = -1;
	m_iSavedDirLevel = 0;
	while ((iPos = pcsPath->Find(tcLevelType, iPos+1)) != -1)
	{
		++m_iSavedDirLevel;
	}
}

DWORD WINAPI Cftp_clientDlg::MyThread(LPVOID param)
{
	ThreadStruct * a = (ThreadStruct*) param;
	
	CFile m_File;
	if (!m_File.Open(a->f, CFile::modeCreate|CFile::modeWrite))
	{
		//ExitThread(0);
		return 0;
	}

	SOCKET soc;
	sockaddr_in sockaddrClient;
	int iSize = sizeof(sockaddrClient);
	soc = accept(a->s,(sockaddr*)&sockaddrClient, &iSize);
	if (soc == INVALID_SOCKET )
	{
		int i = WSAGetLastError();
		closesocket(a->s);
		m_File.Close();
		ExitThread(0);
		//return 0;
	}

	LONG64 leng = 0;
	//recv(soc,(char*)&leng,sizeof(LONG64),0);
	LONG64 count = 0;
	char buffer[1024];
	m_File.Seek(0, CFile::begin);
	while(TRUE)//count < leng)
	{
		int len = recv(soc, buffer, 1024,0);
		if (len==0)
		{
			m_File.Close();
			closesocket(soc);
			closesocket(a->s);
			//ExitThread(1);
			return 1;
		}
		m_File.Write(buffer, len);
		count += len;
	}
	m_File.Close();
	closesocket(soc);
	closesocket(a->s);
	//ExitThread(1);
	return 1;
}