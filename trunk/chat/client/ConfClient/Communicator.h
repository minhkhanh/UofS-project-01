#pragma once

#include "MessageProcessor.h"

//////////////////////////////////////////////////////////////////////////
/// Lop Communicator lien lac giua client va server,
/// chua toan bo cac ham lien lac can thiet trong qua trinh chat, gui file
//////////////////////////////////////////////////////////////////////////
class Communicator
{
public:
	// socket client
	SOCKET sockClient;

	// ten username ben phia client
	CString cstrLocalUsername;

	Communicator(void);
	Communicator(SOCKET sock);
	~Communicator(void);

	// ket thuc mot ket noi
	void End();
	// gan 2 gia tri vao
	void SetInfo(SOCKET sock, CString cstrName);

	// ham nay gui mot chuoi dang TCHAR* di
	int Send(TCHAR *strMessage);

	// ham gui public chat message danh cho client
	int SendPublicMess_C(CString *cstrMessBody);					// c
	// ham gui public chat message danh cho server
	int SendPublicMess_S(CString *cstrMessContent);				// s

	// ham gui private chat message
	int SendPrivMess_C(CString *cstrRemoteUser, CString *cstrMessBody);		// c
	// ham gui private chat message
	int SendPrivMess_S(CString *cstrRemoteUser, CString *cstrMessBody);		// c
	// ham gui thong bao user chat private da thoat khoi room
	int SendPrivMessErr(CString *cstrRemoteUser, CString *cstrMess);

	// gui di yeu cau dang nhap bang username
	int SendLogInReq();												// c
	// thong bao cho client biet la client da dang nhap thanh cong
	int SendLoggedInMess(CString *cstrUsername, CString *cstrMessBody);		// s
	// thong bao cho client biet mot user vua dang xuat
	int SendLoggedOutMess(CString *cstrUsername, CString *cstrMessBody);	// s
	// gui thong bao cho client dang nhap that bai
	int SendLogInErr(CString *cstrMessBody);							// s

	// gui cho client danh sach username dang co trong phong
	int SendUserLv(CListCtrl *lvUser);										// s

	// gui loi goi y download
	int SendDownOffer(CString *cstrFileName, CString *cstrFileSize);

	int SendFileNotFoundErr(CString *cstrMess);

	// gui yeu cau dc upload tu client
	int SendUploadReq(CString *cstrFileName);
	// server gui thong bao dc phep upload
	int SendUploadReadyMess(CString *cstrPort);

	int SendFileSharedInfo(CString *cstrFileName, CString *cstrFileSize, CString *cstrPort);
};
