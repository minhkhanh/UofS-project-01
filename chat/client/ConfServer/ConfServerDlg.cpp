
// ConfServerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfServer.h"
#include "ConfServerDlg.h"

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


// CConfServerDlg dialog




CConfServerDlg::CConfServerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfServerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConfServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_lvUsers);
	DDX_Control(pDX, IDC_EDIT_PUBLICCONTENT, m_ebPublicContent);
	DDX_Control(pDX, IDC_LIST_FILES, m_lvFiles);
}

BEGIN_MESSAGE_MAP(CConfServerDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SOCKET, SockMsg)
	ON_BN_CLICKED(IDC_BUTTON_RUN, &CConfServerDlg::OnClicked_BtnRun)
END_MESSAGE_MAP()


// CConfServerDlg message handlers

BOOL CConfServerDlg::OnInitDialog()
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

	InitSocket();
	InitStuff();

	OnClicked_BtnRun();		// cho chay server ngay khi khoi dong

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CConfServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CConfServerDlg::OnPaint()
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
HCURSOR CConfServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

LRESULT CConfServerDlg::SockMsg( WPARAM wParam, LPARAM lParam )
{
	if (WSAGETSELECTERROR(lParam))
	{
		// Display the error and close the socket
		closesocket(wParam);
	}
	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
		{
			if (m_iBuffLength == -1)
			{
				recv(wParam, (char*)&m_iBuffLength, sizeof(int), 0);
			}
			else
			{
				CString cstrMess = L"";
				TCHAR* strBuff = new TCHAR[m_iBuffLength];

				recv(wParam, (char*)strBuff, m_iBuffLength*sizeof(TCHAR), 0);

				cstrMess = strBuff;
				cstrMess.Insert(m_iBuffLength, L'\0');

				this->ProcessMessage(wParam, &cstrMess);

				m_iBuffLength = -1;		// reset buffer length for flag
			}
		}
		break;
	case FD_CLOSE:		// co socket vua close connect
		{
			int idx = FindComm(wParam);		// tim socket trong vector

			CString cstrNotify = L"just logged out";
			CString tmpMess = CString(L"\r\n[") + m_vComm[idx].cstrLocalUsername.GetBuffer() + L" " + cstrNotify + L"]";
			WriteToPubContent(tmpMess.GetBuffer());

			RemoveUsername(&m_vComm[idx].cstrLocalUsername);
			CString cstrUsername = m_vComm[idx].cstrLocalUsername;
			EndComm(idx);

			AnnounceUserLoggedOut(&cstrUsername, &cstrNotify);
		}
		break;
	case FD_ACCEPT:
		{
			sockaddr_in sockaddrClient;
			int iSize = (sizeof(sockaddrClient));
			SOCKET sockClient = accept(m_sockServer, (sockaddr*)&sockaddrClient, &iSize);

			m_vComm.push_back(Communicator(sockClient));
		}

		break;
	}

	return 0;
}

void CConfServerDlg::OnClicked_BtnRun()
{
	// TODO: Add your control notification handler code here

	if (m_bRunning == true)		// server dang Run
	{
		StopServer();
		ControlSwitch(false);

		return;
	}

	if ((m_sockServer = socket(AF_INET, SOCK_STREAM, 0)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"socket() failed.");
		return;
	}

	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(CHAT_PORT);
	addrServer.sin_addr.s_addr = htonl(INADDR_ANY);

	if (bind(m_sockServer, (SOCKADDR *)&addrServer, sizeof(addrServer)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"bind() error");
		return;
	}

	if (listen(m_sockServer, 5) == SOCKET_ERROR)
	{
		AfxMessageBox(L"listen() error");
		return;
	}

	int err = WSAAsyncSelect(m_sockServer, m_hWnd, WM_SOCKET, FD_READ | FD_ACCEPT | FD_CLOSE);
	if (err == SOCKET_ERROR)
	{
		AfxMessageBox(L"WSAAsyncSelect() error");
		return;
	}

	ControlSwitch(true);
}

void CConfServerDlg::ProcessMessage( SOCKET socketTarget, CString *cstrMess )
{
	CString cstrMessCode = MessProcessor::PeelMess(cstrMess);

	int iSenderIdx = this->FindComm(socketTarget);	// tim socket vua gui message

	if (cstrMessCode == L"")
		return;

	if (cstrMessCode == MessProcessor::MC_PUBLIC_CHAT)
		ProcessPubChatMess(cstrMess);
	else if (cstrMessCode == MessProcessor::MC_USERNAME_REQUEST)
		ProcessUsernameReq(cstrMess, iSenderIdx);
	else if (cstrMessCode == MessProcessor::MC_PRIVATE_CHAT)
		ProcessPrivChatMess(cstrMess, iSenderIdx);
	else if (cstrMessCode == MessProcessor::MC_DOWNLOAD_OFFER)
		ProcessDownloadReq(cstrMess, iSenderIdx);
	else if (cstrMessCode == MessProcessor::MC_UPLOAD_REQUEST)
		ProcessUploadReq(cstrMess, iSenderIdx);
}

void CConfServerDlg::AnnouncePubChatMess( CString *cstrMessContent )
{
	for (unsigned u = 0; u < m_vComm.size(); ++u)
	{
		m_vComm[u].SendPublicMess_S(cstrMessContent);
	}
}

bool CConfServerDlg::CheckUsername( CString *cstrUsername )
{
	for (int i = 0; i < m_lvUsers.GetItemCount(); ++i)
	{
		if (*cstrUsername == m_lvUsers.GetItemText(i,0))
			return false;
	}

	return true;
}

int CConfServerDlg::FindComm( SOCKET sock )
{
	for (int i = 0; i < m_vComm.size(); ++i)
	{
		if (sock == m_vComm[i].sockClient)
			return i;
	}

	return -1;
}

int CConfServerDlg::FindComm( CString *cstrUsername )
{
	for (int i = 0; i < m_vComm.size(); ++i)
	{
		if (*cstrUsername == m_vComm[i].cstrLocalUsername)
			return i;
	}

	return -1;
}
void CConfServerDlg::InitStuff()
{
	m_lvUsers.InsertColumn(0, L"Usernames", LVCFMT_LEFT, 70);
	m_lvUsers.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	ControlSwitch(false);
	m_iBuffLength = -1;

	InitStaticMemberServer();

	m_serviceShare = CServerShareService::CreateCServerShareService(this);
}

void CConfServerDlg::InitSocket()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2,2);

	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		AfxMessageBox(L"WSAStartup() error");
}

void CConfServerDlg::EndComm( int idx )
{
	m_vComm[idx].End();
	m_vComm.erase(m_vComm.begin() + idx);
}

void CConfServerDlg::AnnounceUserLoggedIn(CString *cstrUsername, CString *cstrMessBody)
{
	for (unsigned u = 0; u < m_vComm.size(); ++u)
		m_vComm[u].SendLoggedInMess(cstrUsername, cstrMessBody);
}

void CConfServerDlg::AnnounceUserLoggedOut( CString *cstrUsername, CString *cstrMessBody )
{
	for (unsigned u = 0; u < m_vComm.size(); ++u)
		m_vComm[u].SendLoggedOutMess(cstrUsername, cstrMessBody);
}

void CConfServerDlg::RemoveUsername( CString *cstrUsername )
{
	for (int i = 0; i < m_lvUsers.GetItemCount(); ++i)
		if (m_lvUsers.GetItemText(i, 0) == *cstrUsername)
		{
			m_lvUsers.DeleteItem(i);
			return;
		}
}

void CConfServerDlg::WriteToPubContent(TCHAR *strMess)
{
	m_ebPublicContent.SetSel(0xffff,0xffff);
	m_ebPublicContent.ReplaceSel(strMess);
}

void CConfServerDlg::StopServer()
{
	for (int i = 0; i < m_vComm.size(); ++i)
		m_vComm[i].End();

	m_vComm.clear();

	shutdown(m_sockServer, SD_BOTH);
	closesocket(m_sockServer);
}

void CConfServerDlg::ControlSwitch( bool bval )
{
	m_bRunning = bval;

	if (bval == true)
	{
		m_item(IDC_BUTTON_RUN)->SetWindowText(L"Stop");
		WriteToPubContent(L"\r\n[Server started]");
	}
	else
	{
		m_item(IDC_BUTTON_RUN)->SetWindowText(L"Start");
		WriteToPubContent(L"\r\n[Server stopped]");

		m_lvUsers.DeleteAllItems();
	}
}

bool CConfServerDlg::CheckFile( CString *cstrFileName )
{
	for (int i = 0; i < m_lvFiles.GetItemCount(); ++i)
	{
		if (*cstrFileName == m_lvUsers.GetItemText(i,0))
			return false;
	}

	return true;
}

void CConfServerDlg::ProcessPubChatMess( CString *cstrPubChatMess, int iSenderIdx )
{
	AnnouncePubChatMess(cstrPubChatMess);	// broadcast to clients

	CString cstrUsername = MessProcessor::PeelMess(cstrPubChatMess);

	CString tmpMess = L"\r\n" + cstrUsername + L": " + cstrPubChatMess->GetBuffer();
	WriteToPubContent(tmpMess.GetBuffer());
}

void CConfServerDlg::ProcessUsernameReq( CString *cstrUsername, int iSenderIdx )
{
	//!!!cstrMess hien tai chi con chua chuoi username

	if (CheckUsername(cstrUsername) == false)	//!!!username bi trung roi
	{
		m_vComm[iSenderIdx].SendLogInErr(&CString(L"Username existed"));
		EndComm(iSenderIdx);		// xoa communicator voi socket nay

		return;		// logging false
	}

	// logging succeed:

	m_vComm[iSenderIdx].cstrLocalUsername = *cstrUsername;

	CString cstrNotify = L"just logged in";
	AnnounceUserLoggedIn(cstrUsername, &cstrNotify);	// broadcast to clients

	m_vComm[iSenderIdx].SendUserLv(&m_lvUsers);	// gui ds username cho client
	m_lvUsers.InsertItem(m_lvUsers.GetItemCount(), *cstrUsername); // them username vao list view

	CString tmpMess = CString(L"\r\n[") + cstrUsername->GetBuffer() + L" " + cstrNotify + L"] ";
	WriteToPubContent(tmpMess.GetBuffer());
}

void CConfServerDlg::ProcessPrivChatMess( CString *cstrMessContent, int iSenderIdx )
{
	CString cstrSender = MessProcessor::PeelMess(cstrMessContent);
	CString cstrReceiver = MessProcessor::PeelMess(cstrMessContent);

	if (CheckUsername(&cstrReceiver))		// username nay thoat roi
	{
		m_vComm[iSenderIdx].SendPrivMessErr(&cstrReceiver, &CString(L"\r\n[This user logged out, your message was undelivered]"));
		return;
	}

	int i = FindComm(&cstrReceiver);
	m_vComm[i].SendPrivMess_S(&cstrSender, cstrMessContent);
}

void CConfServerDlg::ProcessDownloadReq( CString *cstrFileName, int iSenderIdx )
{
	if (CheckFile(cstrFileName))
	{
		m_vComm[iSenderIdx].SendFileNotFoundErr(&CString(L"File not found"));
		return;
	}
}

void CConfServerDlg::ProcessUploadReq( CString *cstrFileName, int iSenderIdx )
{
	int iPort = m_serviceShare->OnClientNeedShareFile(*cstrFileName);

	CString cstrPort;
	cstrPort.Format(L"%d", iPort);

	m_vComm[iSenderIdx].SendUploadReadyMess(&cstrPort);
}

void CConfServerDlg::AnnounceFileForShare(CString *cstrFileName, CString *cstrFileSize, CString *cstrPort)
{
	for (int i = 0; i < m_vComm.size(); ++i)
	{
		m_vComm[i].SendFileSharedInfo(cstrFileName, cstrFileSize, cstrPort);
	}
}