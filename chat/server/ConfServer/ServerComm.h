#pragma once

#include "MessProcessor.h"

//////////////////////////////////////////////////////////////////////////
/// Lop Communicator lien lac giua client va server,
/// chua toan bo cac ham lien lac can thiet trong qua trinh chat, gui file
//////////////////////////////////////////////////////////////////////////
class ServerComm
{
public:
	// socket client
	SOCKET sockClient;

	// ten username ben phia client
	CString cstrLocalUsername;

	ServerComm(void);
	ServerComm(SOCKET sock);
	~ServerComm(void);

	// ket thuc mot ket noi
	void End();
	// gan 2 gia tri vao
	void SetInfo(SOCKET sock, CString cstrName);

	// ham nay gui mot chuoi dang TCHAR* di
	int Send(TCHAR *strMessage);

	// ham gui public chat message danh cho server
	int SendPublicMess(CString *cstrMessContent);				// s

	// ham gui private chat message
	int SendPrivMess(CString *cstrSender, CString *cstrMessBody);		// c
	// ham gui thong bao user chat private da thoat khoi room
	int SendPrivMessErr(CString *cstrSender, CString *cstrMess);

	// thong bao cho client biet la client da dang nhap thanh cong
	int SendLoggedInMess(CString *cstrUsername, CString *cstrMessBody);		// s
	// thong bao cho client biet mot user vua dang xuat
	int SendLoggedOutMess(CString *cstrUsername, CString *cstrMessBody);	// s
	// gui thong bao cho client dang nhap that bai
	int SendLogInErr(CString *cstrMessBody);							// s

	// gui cho client danh sach username dang co trong phong
	int SendUserLv(CListCtrl *lvUser);										// s

	// server gui thong bao dc phep upload
	int SendUploadReadyMess(CString *cstrPort);

	// gui di loi de nghi download trong public share
	int SendDownloadOffer(CString *cstrFileSize, CString *cstrPort, CString *cstrFileName);

	// client gui de nghi share file private
	int SendPrivateFileOffer(CString *cstrSender, CString *cstrMessContent);

	int SendPrivFileAccept(CString *cstrSender, CString *cstrServerPort);

	int SendPrivFileDownload(CString *cstrSender, CString *cstrFileName, CString *cstrFileSize, CString *cstrPort);
};
