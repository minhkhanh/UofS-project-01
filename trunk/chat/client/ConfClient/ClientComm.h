#pragma once

#include "MessProcessor.h"

//////////////////////////////////////////////////////////////////////////
/// Lop ClientComm lien lac giua client va server,
/// chua toan bo cac ham lien lac can thiet trong qua trinh chat, gui file
//////////////////////////////////////////////////////////////////////////
class ClientComm
{
public:
	// socket client
	SOCKET sockClient;

	// ten username ben phia client
	CString cstrLocalUsername;

	ClientComm(void);
	ClientComm(SOCKET sock);
	~ClientComm(void);

	// ket thuc mot ket noi
	void End();
	// gan 2 gia tri vao
	void SetInfo(SOCKET sock, CString cstrName);

	// ham nay gui mot chuoi dang TCHAR* di
	int Send(TCHAR *strMessage);

	// ham gui public chat message danh cho client
	int SendPublicMess(CString *cstrMessBody);					// c

	// ham gui private chat message
	int SendPrivMess(CString *cstrRemoteUser, CString *cstrMessBody);		// c

	// gui di yeu cau dang nhap bang username
	int SendLogInReq();												// 

	// client gui yeu cau dc upload public
	int SendPublicUploadReq(CString *cstrFileName);

	// client gui de nghi share file private
	int SendPrivFileOffer(CString *cstrRemoteUser, CString *cstrFileName);

	// client chap nhan nhan file private share
	int SendPrivFileAccept(CString *cstrReciever);
};
