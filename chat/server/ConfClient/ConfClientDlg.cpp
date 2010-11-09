
// ConfClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ConfClient.h"
#include "ConfClientDlg.h"
#include "PrivateChatDlg.h"

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


// CConfClientDlg dialog




CConfClientDlg::CConfClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConfClientDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CConfClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_LIST_FILES, m_lvFiles);
	DDX_Control(pDX, IDC_LIST_USERS, m_lvUsers);
	DDX_Control(pDX, IDC_EDIT_PUBLICCONTENT, m_ebPublicContent);
	DDX_Control(pDX, IDC_EDIT_MESSAGE, m_ebMessage);
	DDX_Control(pDX, IDC_IPADDRESS1, m_ipaddrServer);
	DDX_Control(pDX, IDC_BUTTON_CONNECT, m_btnConnect);
	DDX_Control(pDX, IDC_BUTTON_SENDMESS, m_btnSendMess);
	DDX_Control(pDX, IDC_BUTTON_GETFILE, m_btnDownload);
}

BEGIN_MESSAGE_MAP(CConfClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_CONNECT, &CConfClientDlg::OnClicked_BtnConnect)
	ON_MESSAGE(WM_SOCKET, SockMsg)
	ON_BN_CLICKED(IDC_BUTTON_SENDMESS, &CConfClientDlg::OnClicked_BtnSend)
	ON_BN_CLICKED(IDC_BUTTON_SELECTUSER, &CConfClientDlg::OnClicked_BtnSelectUser)
	ON_NOTIFY(LVN_ITEMACTIVATE, IDC_LIST_USERS, &CConfClientDlg::OnLvnItemActivateListUsers)
	ON_BN_CLICKED(IDC_BUTTON_ATTACHFILE, &CConfClientDlg::OnClicked_BtnUpload)
	ON_BN_CLICKED(IDC_BUTTON_GETFILE, &CConfClientDlg::OnBnClickedButtonGetfile)
END_MESSAGE_MAP()


// CConfClientDlg message handlers

BOOL CConfClientDlg::OnInitDialog()
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
	//InitFileLv();
	InitSocket();
	InitStuff();

	return FALSE;  // return TRUE  unless you set the focus to a control
}

void CConfClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CConfClientDlg::OnPaint()
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
HCURSOR CConfClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CConfClientDlg::InitFileLv()
{
	m_lvFiles.InsertColumn(0, L"File name", LVCFMT_LEFT, 200);		// hien thi ten file
	m_lvFiles.InsertColumn(1, L"% Up", LVCFMT_LEFT, 60);			// hien thi % upload
	m_lvFiles.InsertColumn(2, L"% Down", LVCFMT_LEFT, 60);			// hien thi % download
}

void CConfClientDlg::OnClicked_BtnConnect()
{
	// TODO: Add your control notification handler code here

	if (m_bConnected == true)		// truong hop dang connect
	{
		int iBtn = AfxMessageBox(L"Are you sure?", MB_YESNO | MB_ICONQUESTION);	// hien messbox nhac nho

		if (iBtn == IDYES)
		{
			ControlSwitch(false);
			m_comm.End();

			RemoveAllPrivDlg();
		}
		return;
	}

	CString cstrUsername;
	m_item(IDC_EDIT_USERNAME)->GetWindowText(cstrUsername);
	cstrUsername = cstrUsername.Trim();
	if (cstrUsername == "")		// username bi rong
	{
		AfxMessageBox(L"Please type an username");
		return;
	}

	m_sockThisClient = socket(AF_INET, SOCK_STREAM, 0);
	if (m_sockThisClient == INVALID_SOCKET)
	{
		AfxMessageBox(L"socket() failed!");
		return;
	}

	IN_ADDR ia;

	DWORD dwServIpAddr;
	m_ipaddrServer.GetAddress(dwServIpAddr);
	ia.S_un.S_addr = ntohl(dwServIpAddr);

	sockaddr_in addrServer;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(CHAT_PORT);
	addrServer.sin_addr.s_addr = inet_addr(inet_ntoa(ia));

	if (addrServer.sin_addr.s_addr == INADDR_NONE)
	{
		AfxMessageBox(L"Server address unknown!");
		return;
	}

	int err = connect(m_sockThisClient, (struct sockaddr*)&addrServer, sizeof(addrServer));
	if (err == SOCKET_ERROR)
	{
		AfxMessageBox(L"connect() failed");
		return;
	}

	m_comm.SetInfo(m_sockThisClient,  cstrUsername);

	err = WSAAsyncSelect(m_sockThisClient, m_hWnd, WM_SOCKET, FD_READ | FD_CLOSE);
	if (err == SOCKET_ERROR)
		AfxMessageBox(L"WSAAsyncSelect() error");

	m_comm.SendLogInReq();		// send yeu cau dang nhap
}

LRESULT CConfClientDlg::SockMsg(WPARAM wParam, LPARAM lParam)
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
			if (m_iBuffLength == -1)		// chua nhan dc size truoc
			{
				recv(wParam, (char*)&m_iBuffLength, sizeof(int), 0);	// nhan message size truoc
			}
			else
			{
				// bat dau nhan message:

				CString cstrMess;
				TCHAR* strBuff = new TCHAR[m_iBuffLength];

				recv(wParam, (char*)strBuff, m_iBuffLength*sizeof(TCHAR), 0);	// nhan size truoc

				cstrMess = strBuff;
				cstrMess.Insert(m_iBuffLength, L'\0');

				this->ProcessMessage(&cstrMess);	// xu ly message

				m_iBuffLength = -1;		// reset buffer length for flag
			}
		}
		break;
	case FD_CLOSE:
		{
			// thong bao khi server bi dong
			AfxMessageBox(L"\r\nConnection closed!");
			ControlSwitch(false);
			m_comm.End();

			RemoveAllPrivDlg();
		}
		break;
	}

	return 0;
}

void CConfClientDlg::InitSocket()
{
	WORD wVersionRequested;
	WSADATA wsaData;

	wVersionRequested = MAKEWORD(2,2);

	int err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0)
		AfxMessageBox(L"WSAStartup() failed");
}
void CConfClientDlg::OnClicked_BtnSend()
{
	// TODO: Add your control notification handler code here

	CString tmpMess;

	m_ebMessage.GetWindowText(tmpMess);
	m_comm.SendPublicMess_C(&tmpMess);

	m_ebMessage.SetWindowText(L"");
	m_ebMessage.SetFocus();
}

void CConfClientDlg::ControlSwitch( bool bval )
{
	m_bConnected = bval;

	m_item(IDC_EDIT_CONTENT)->EnableWindow(bval);
	m_item(IDC_EDIT_MESSAGE)->EnableWindow(bval);

	m_item(IDC_LIST_USERS)->EnableWindow(bval);
	m_item(IDC_LIST_FILES)->EnableWindow(bval);

	m_item(IDC_BUTTON_SENDMESS)->EnableWindow(bval);
	m_item(IDC_BUTTON_SELECTUSER)->EnableWindow(bval);
	m_item(IDC_BUTTON_ATTACHFILE)->EnableWindow(bval);
	m_item(IDC_BUTTON_GETFILE)->EnableWindow(bval);

	m_item(IDC_IPADDRESS1)->EnableWindow(!bval);
	m_item(IDC_EDIT_USERNAME)->EnableWindow(!bval);

	if (bval == false)
	{
		m_lvFiles.DeleteAllItems();
		m_lvUsers.DeleteAllItems();
		m_ebPublicContent.SetWindowText(L"");
		m_ebMessage.SetWindowText(L"");

		m_item(IDC_BUTTON_CONNECT)->SetWindowText(L"Log in");
		m_item(IDC_EDIT_USERNAME)->SetFocus();
	}
	else
	{
		m_item(IDC_BUTTON_CONNECT)->SetWindowText(L"Log out");

		m_ebMessage.SetFocus();
	}
}

void CConfClientDlg::InitStuff()
{
	ControlSwitch(false);
	
	m_iBuffLength = -1;

	m_ipaddrServer.SetWindowText(L"127.0.0.1");
	m_lvUsers.InsertColumn(0, L"Usernames", LVCFMT_LEFT, 70);
	m_lvUsers.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	InitStaticMemberClient();

	m_serviceClient = CClientShareService::Create(&m_lvFiles);

	m_serviceClient->InitListViewColumn();
}

void CConfClientDlg::ProcessMessage( CString *cstrMess )
{
	CString cstrMessCode = MessProcessor::PeelMess(cstrMess);	// lay ra mess code

	if (cstrMessCode == L"")
		return;

	if (cstrMessCode == MessProcessor::MC_PUBLIC_CHAT)	// message chat public
		ProcessPubChatMess(cstrMess);
	else if (cstrMessCode == MessProcessor::MC_USER_LOGGED_IN)	// username dc server chap nhan
		ProcessUserLoggedInMess(cstrMess);
	else if (cstrMessCode == MessProcessor::EC_USERNAME_EXISTED)	// username bi trung!
		ProcessUserExistedErr(cstrMess);
	else if (cstrMessCode == MessProcessor::MC_USERNAME_LIST)	// nhan duoc danh sach username hien tai
		ProcessUserListData(cstrMess);
	else if (cstrMessCode == MessProcessor::MC_USER_LOGGEDOUT)	// thong bao co user thoat ra
		ProcessUserLoggedOutMess(cstrMess);
	else if (cstrMessCode == MessProcessor::MC_PRIVATE_CHAT)	// private chat
		ProcessPrivChatMess(cstrMess);
	else if (cstrMessCode == MessProcessor::EC_USERNAME_LOGGEDOUT)	// thong bao user da dang xuat khi dang chat private
		ProcessPrivChatErr(cstrMess);
	else if (cstrMessCode == MessProcessor::MC_UPLOAD_READY)
		ProcessUploadReadyMess(cstrMess);
	else if (cstrMessCode == MessProcessor::MC_SHARED_FILEINFO)
		ProcessSharedFileInfo(cstrMess);
}

void CConfClientDlg::WriteToPubContent( TCHAR *strMess )
{
	//////////////////////////////////////////////////////////////////////////
	/// Chen chuoi vao cuoi editbox va scroll edit box xuong
	//////////////////////////////////////////////////////////////////////////

	m_ebPublicContent.SetSel(0xffff,0xffff);
	m_ebPublicContent.ReplaceSel(strMess);
}

void CConfClientDlg::RemoveUsername( CString *cstrUsername )
{
	for (int i = 0; i < m_lvUsers.GetItemCount(); ++i)
		if (m_lvUsers.GetItemText(i, 0) == *cstrUsername)
		{
			m_lvUsers.DeleteItem(i);
			return;
		}
}
void CConfClientDlg::OnClicked_BtnSelectUser()
{
	// TODO: Add your control notification handler code here

	POSITION pos = m_lvUsers.GetFirstSelectedItemPosition();
	int iDx = -1;
	if (pos != NULL)	
		iDx = m_lvUsers.GetNextSelectedItem(pos);
	else
		return;			// ko co user nao dc chon

	GetPrivDlg(&m_lvUsers.GetItemText(iDx, 0));
}

int CConfClientDlg::FindPrivDlg( CString *cstrUsername )
{
	for (int i = 0; i < m_vpPrivDlg.size(); ++i)
	{
		if (*cstrUsername == m_vpPrivDlg[i]->m_cstrRemoteUser)
			return i;
	}

	return -1;
}

CPrivateChatDlg *CConfClientDlg::GetPrivDlg(CString *cstrRemoteUser)
{
	int iDx = FindPrivDlg(cstrRemoteUser);
	CPrivateChatDlg *dlgPrivate;

	if (iDx == -1)		// chua co dialog chat voi username nay
	{
		dlgPrivate = new CPrivateChatDlg(GetDesktopWindow());	// new mot dialog chat private	

		//dlgPrivate->set
		dlgPrivate->m_pConfClient = this;
		dlgPrivate->m_cstrRemoteUser = *cstrRemoteUser;					// gan thong tin client phia ben kia
		m_item(IDC_EDIT_USERNAME)->GetWindowText(dlgPrivate->m_cstrLocalUser);	// gan thong tin client phia ben day
		dlgPrivate->Create(CPrivateChatDlg::IDD);					// tao dialog

		m_vpPrivDlg.push_back(dlgPrivate);							// dua dialog vao vector de quan ly
		//dlgPrivate->m_iDx = m_vpPrivDlg.size()-1;					// cho dialog luu tri so mang cua no
	}
	else
		dlgPrivate = m_vpPrivDlg[iDx];

	dlgPrivate->ShowWindow(SW_SHOW);							// hien thi dialog
	dlgPrivate->m_ebMessage.SetFocus();

	return dlgPrivate;
}

void CConfClientDlg::OnLvnItemActivateListUsers(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMIA = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: Add your control notification handler code here
	OnClicked_BtnSelectUser();
	*pResult = 0;
}

void CConfClientDlg::RemovePrivDlg( CString *cstrUsername )
{
	int iDx = FindPrivDlg(cstrUsername);
	m_vpPrivDlg.erase(m_vpPrivDlg.begin() + iDx);
}

void CConfClientDlg::OnClicked_BtnUpload()
{
	// TODO: Add your control notification handler code here

	if (m_cstrCurrFileUp != "")
	{
		AfxMessageBox(L"Service busy");
		return;
	}

	CFileDialog dlgOpen(true, L"*.*", L"*.*",
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"All files|*.*||");

	if (dlgOpen.DoModal() == IDCANCEL)
		return;

	m_cstrCurrFileUp = dlgOpen.GetPathName();
	//CString cstrFileName = ;

	m_comm.SendUploadReq(&dlgOpen.GetFileName());
}

void CConfClientDlg::OnBnClickedButtonGetfile()
{
	
}

void CConfClientDlg::RemoveAllPrivDlg()
{
	for (int i = 0; i < m_vpPrivDlg.size(); ++i)
		delete m_vpPrivDlg[i];

	m_vpPrivDlg.clear();
}

void CConfClientDlg::ProcessPubChatMess( CString *cstrPubChatMess, int iSenderIdx )
{
	CString cstrUsername = MessProcessor::PeelMess(cstrPubChatMess);

	WriteToPubContent((L"\r\n" + cstrUsername + L": " + cstrPubChatMess->GetBuffer()).GetBuffer());
}

void CConfClientDlg::ProcessUserLoggedInMess( CString *cstrMessContent, int iSenderIdx )
{
	CString cstrUsername = MessProcessor::PeelMess(cstrMessContent);

	if (cstrUsername == m_comm.cstrLocalUsername)	// neu user dang nhap thanh cong chinh la client thi switch trang thai
		ControlSwitch(true);

	m_lvUsers.InsertItem(0, cstrUsername);			// dua username vao list
	WriteToPubContent((L"\r\n[" + cstrUsername + L" " + cstrMessContent->GetBuffer() + L"]").GetBuffer());		
}

void CConfClientDlg::ProcessUserExistedErr( CString *cstrErrMess, int iSenderIdx )
{
	AfxMessageBox(*cstrErrMess);
	m_comm.End();
}

void CConfClientDlg::ProcessUserListData( CString *cstrUserList, int iSenderIdx )
{
	//////////////////////////////////////////////////////////////////////////
	/// Khi user moi dang nhap thi duoc server gui cho mot danh sach cac user dang co mat
	//////////////////////////////////////////////////////////////////////////

	CString cstrUsername = MessProcessor::PeelMess(cstrUserList);

	while (cstrUsername != "")
	{
		m_lvUsers.InsertItem(m_lvUsers.GetItemCount(), cstrUsername);

		cstrUsername = MessProcessor::PeelMess(cstrUserList);
	}
}

void CConfClientDlg::ProcessUserLoggedOutMess( CString *cstrMessContent, int iSenderIdx )
{
	CString cstrUsername = MessProcessor::PeelMess(cstrMessContent);
	CString tmpMess = L"\r\n[" + cstrUsername + L" " + L"just logged out]";
	WriteToPubContent(tmpMess.GetBuffer());

	RemoveUsername(&cstrUsername);
}

void CConfClientDlg::ProcessPrivChatMess( CString *cstrPrivChatMess, int iSenderIdx )
{
	CString cstrSender = MessProcessor::PeelMess(cstrPrivChatMess);	// chuoi xac dinh client gui

	CString cstrPrivMess = CString(L"\r\n") + cstrSender + L": " + cstrPrivChatMess->GetBuffer();

	CPrivateChatDlg *dlgPrivate = GetPrivDlg(&cstrSender);	
	dlgPrivate->WriteToPrivContent(cstrPrivMess.GetBuffer());
}

void CConfClientDlg::ProcessPrivChatErr( CString *cstrErrMess, int iSenderIdx )
{
	CString cstrSender = MessProcessor::PeelMess(cstrErrMess);
	int i = FindPrivDlg(&cstrSender);
	m_vpPrivDlg[i]->WriteToPrivContent(cstrErrMess->GetBuffer());
}

void CConfClientDlg::ProcessUploadReadyMess( CString *cstrMessContent, int iSenderIdx )
{
	//CString cstrFileName = MessProcessor::PeelMess(cstrMessContent);
	CString cstrPort = MessProcessor::PeelMess(cstrMessContent);

	CString cstrIPAddr;
	m_ipaddrServer.GetWindowText(cstrIPAddr);

	int iPort = _wtoi(cstrPort.GetBuffer());

	m_serviceClient->Upload(m_cstrCurrFileUp, cstrIPAddr, iPort);

	m_cstrCurrFileUp = "";
}

void CConfClientDlg::ProcessSharedFileInfo( CString *cstrMessContent, int iSenderIdx /*= -1*/ )
{
	CString cstrFileName = MessProcessor::PeelMess(cstrMessContent);
	CString cstrFileSize = MessProcessor::PeelMess(cstrMessContent);
	CString cstrPort = MessProcessor::PeelMess(cstrMessContent);

	if (AfxMessageBox(CString(L"Server have 1 file to share: ") + cstrFileName + L" " + cstrFileSize + L".\r\nDo you want to save?") != MB_OK)
		return;

	CFileDialog dlgSave(false, L"", cstrFileName,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		L"All files|*.*||");

	if (dlgSave.DoModal() == IDCANCEL)
		return;

	CString cstrFilePath = dlgSave.GetPathName();

	CString cstrSverIPAddr;
	m_ipaddrServer.GetWindowText(cstrSverIPAddr);
	int iPort = _wtoi(cstrPort.GetBuffer());
	m_serviceClient->Download(cstrFilePath, cstrSverIPAddr, iPort);
}