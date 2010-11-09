#include "StdAfx.h"
#include "Communicator.h"

Communicator::Communicator(void)
{
}

Communicator::Communicator( SOCKET sock )
{
	this->sockClient = sock;
}

Communicator::~Communicator(void)
{
	//closesocket(sockClient);
}

int Communicator::Send( TCHAR *strMessage )
{
	int iCharNum = wcslen(strMessage);
	send(sockClient, (char*)&iCharNum, sizeof(int), 0);							//!!send message size di truoc, ben nhan phai co co che phan biet size message
	return send(sockClient, (char*)strMessage, iCharNum * sizeof(TCHAR), 0);	// gui message di
}

void Communicator::SetInfo( SOCKET sock , CString cstrLocalName)
{
	this->sockClient = sock;
	this->cstrLocalUsername = cstrLocalName;
}

int Communicator::SendPublicMess_S(CString *cstrMessContent )
{
	TCHAR *carrStr[] = {MessProcessor::MC_PUBLIC_CHAT, cstrMessContent->GetBuffer()};
	CString cstrMess = MessProcessor::JoinMess(carrStr, 2);

	return this->Send(cstrMess.GetBuffer());
}

int Communicator::SendPublicMess_C(CString *cstrMessBody)
{
	TCHAR *carrStr[] = {MessProcessor::MC_PUBLIC_CHAT, cstrLocalUsername.GetBuffer(), cstrMessBody->GetBuffer()};
	CString cstrMess = MessProcessor::JoinMess(carrStr, 3);

	return this->Send(cstrMess.GetBuffer());
}

int Communicator::SendLogInReq()
{
	TCHAR *carrStr[] = {MessProcessor::MC_USERNAME_REQUEST, cstrLocalUsername.GetBuffer()};
	CString cstrLoginMess = MessProcessor::JoinMess(carrStr, 2);

	return this->Send(cstrLoginMess.GetBuffer());
}

int Communicator::SendLogInErr(CString *cstrMessBody )
{
	TCHAR *arrStr[] = {MessProcessor::EC_USERNAME_EXISTED, cstrMessBody->GetBuffer()};
	CString cstrErrMess = MessProcessor::JoinMess(arrStr, 2);

	return this->Send(cstrErrMess.GetBuffer());
}

int Communicator::SendLoggedInMess(CString *cstrUsername, CString *cstrMessBody)
{
	TCHAR *arrStr[] = {MessProcessor::MC_USER_LOGGED_IN, cstrUsername->GetBuffer(), cstrMessBody->GetBuffer()};
	CString cstrMess = MessProcessor::JoinMess(arrStr, 3);

	return this->Send(cstrMess.GetBuffer());
}

int Communicator::SendLoggedOutMess(CString *cstrUsername, CString *cstrMessBody)
{
	TCHAR *carrStr[] = {MessProcessor::MC_USER_LOGGEDOUT, cstrUsername->GetBuffer(), cstrMessBody->GetBuffer()};
	CString cstrLoggedOutMess = MessProcessor::JoinMess(carrStr, 3);

	return this->Send(cstrLoggedOutMess.GetBuffer());
}

void Communicator::End()
{
	// gracefull ending
	shutdown(sockClient, SD_BOTH);
	closesocket(sockClient);
}

int Communicator::SendUserLv( CListCtrl *lvUser )
{
	CString cstrUserList = MessProcessor::MC_USERNAME_LIST;

	// tao chuoi co chua danh sach username:
	int i = 0;
	for ( ; i < lvUser->GetItemCount(); ++i)
		cstrUserList = cstrUserList + L" " + lvUser->GetItemText(i, 0);

	return this->Send(cstrUserList.GetBuffer());
}

int Communicator::SendPrivMess_C( CString *cstrRemoteUser, CString *cstrMessBody )
{
	TCHAR *arrStr[] = {MessProcessor::MC_PRIVATE_CHAT, cstrLocalUsername.GetBuffer(), cstrRemoteUser->GetBuffer(), cstrMessBody->GetBuffer()};
	CString cstrPrivMess = MessProcessor::JoinMess(arrStr, 4);

	return this->Send(cstrPrivMess.GetBuffer());
}

int Communicator::SendPrivMessErr( CString *cstrRemoteUser, CString *cstrMess )
{
	TCHAR *arrStr[] = {MessProcessor::EC_USERNAME_LOGGEDOUT, cstrRemoteUser->GetBuffer(), cstrMess->GetBuffer()};
	CString cstrErrMess = MessProcessor::JoinMess(arrStr, 3);

	return Send(cstrErrMess.GetBuffer());
}

int Communicator::SendPrivMess_S( CString *cstrRemoteUser, CString *cstrMessBody )
{
	TCHAR *arrStr[] = {MessProcessor::MC_PRIVATE_CHAT, cstrRemoteUser->GetBuffer(), cstrMessBody->GetBuffer()};
	CString cstrPrivMess = MessProcessor::JoinMess(arrStr, 3);

	return this->Send(cstrPrivMess.GetBuffer());
}

int Communicator::SendDownOffer( CString *cstrFileName, CString *cstrFileSize)
{
	TCHAR *arrStr[] = {MessProcessor::MC_DOWNLOAD_OFFER, cstrFileName->GetBuffer(), cstrFileSize->GetBuffer()};
	CString cstrDownReq = MessProcessor::JoinMess(arrStr, 2);

	return this->Send(cstrDownReq.GetBuffer());
}

int Communicator::SendFileNotFoundErr( CString *cstrMess )
{
	TCHAR *arrStr[] = {MessProcessor::EC_FILE_NOTFOUND, cstrMess->GetBuffer()};
	CString cstrErrMess = MessProcessor::JoinMess(arrStr, 2);

	return this->Send(cstrErrMess.GetBuffer());
}

int Communicator::SendUploadReadyMess(CString *cstrPort )
{
	TCHAR *arrStr[] = {MessProcessor::MC_UPLOAD_READY, cstrPort->GetBuffer()};
	CString cstrMess = MessProcessor::JoinMess(arrStr, 2);

	return this->Send(cstrMess.GetBuffer());
}

int Communicator::SendUploadReq(CString *cstrFileName)
{
	TCHAR *arrStr[] = {MessProcessor::MC_UPLOAD_REQUEST, cstrFileName->GetBuffer()};
	CString cstrMess = MessProcessor::JoinMess(arrStr, 2);

	return this->Send(cstrMess.GetBuffer());
}

int Communicator::SendFileSharedInfo( CString *cstrFileName, CString *cstrFileSize, CString *cstrPort )
{
	TCHAR *arrStr[] = {MessProcessor::MC_SHARED_FILEINFO, cstrFileName->GetBuffer(), cstrFileSize->GetBuffer(), cstrPort->GetBuffer()};
	CString cstrMess = MessProcessor::JoinMess(arrStr, 4);

	return this->Send(cstrMess.GetBuffer());
}