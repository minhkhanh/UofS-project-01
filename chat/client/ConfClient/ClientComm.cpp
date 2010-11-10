#include "StdAfx.h"
#include "ClientComm.h"

ClientComm::ClientComm(void)
{
}

ClientComm::ClientComm( SOCKET sock )
{
	this->sockClient = sock;
}

ClientComm::~ClientComm(void)
{
	//closesocket(sockClient);
}

int ClientComm::Send( TCHAR *strMessage )
{
	int iCharNum = wcslen(strMessage);
	send(sockClient, (char*)&iCharNum, sizeof(int), 0);							//!!send message size di truoc, ben nhan phai co co che phan biet size message
	return send(sockClient, (char*)strMessage, iCharNum * sizeof(TCHAR), 0);	// gui message di
}

void ClientComm::SetInfo( SOCKET sock , CString cstrLocalName)
{
	this->sockClient = sock;
	this->cstrLocalUsername = cstrLocalName;
}

int ClientComm::SendPublicMess(CString *cstrMessBody)
{
	TCHAR *carrStr[] = {MessProcessor::MC_PUBLIC_CHAT, cstrLocalUsername.GetBuffer(), cstrMessBody->GetBuffer()};
	CString cstrMess = MessProcessor::JoinMess(carrStr, 3);

	return this->Send(cstrMess.GetBuffer());
}

int ClientComm::SendLogInReq()
{
	TCHAR *carrStr[] = {MessProcessor::MC_USERNAME_REQUEST, cstrLocalUsername.GetBuffer()};
	CString cstrLoginMess = MessProcessor::JoinMess(carrStr, 2);

	return this->Send(cstrLoginMess.GetBuffer());
}

void ClientComm::End()
{
	// gracefull ending
	shutdown(sockClient, SD_BOTH);
	closesocket(sockClient);
}

int ClientComm::SendPrivMess( CString *cstrRemoteUser, CString *cstrMessBody )
{
	TCHAR *arrStr[] = {MessProcessor::MC_PRIVATE_CHAT, cstrLocalUsername.GetBuffer(), cstrRemoteUser->GetBuffer(), cstrMessBody->GetBuffer()};
	CString cstrPrivMess = MessProcessor::JoinMess(arrStr, 4);

	return this->Send(cstrPrivMess.GetBuffer());
}

int ClientComm::SendPublicUploadReq(CString *cstrFileName)
{
	TCHAR *arrStr[] = {MessProcessor::MC_UPLOAD_REQUEST, cstrFileName->GetBuffer()};
	CString cstrMess = MessProcessor::JoinMess(arrStr, 2);

	return this->Send(cstrMess.GetBuffer());
}

int ClientComm::SendPrivFileOffer( CString *cstrRemoteUser, CString *cstrFileName )
{
	TCHAR *arrStr[] = {MessProcessor::MC_PRIVATE_FILE_OFFER, cstrLocalUsername.GetBuffer(), cstrRemoteUser->GetBuffer(), cstrFileName->GetBuffer()};
	CString cstrMess = MessProcessor::JoinMess(arrStr, 4);

	return this->Send(cstrMess.GetBuffer());
}

int ClientComm::SendPrivFileAccept(CString *cstrReciever)
{
	TCHAR *arrStr[] = {MessProcessor::MC_PRIVATE_FILE_ACCEPT, cstrLocalUsername.GetBuffer(), cstrReciever->GetBuffer()};
	CString cstrMess = MessProcessor::JoinMess(arrStr, 3);

	return this->Send(cstrMess.GetBuffer());
}