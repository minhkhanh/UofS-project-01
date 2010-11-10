#include "StdAfx.h"
#include "MessProcessor.h"

TCHAR *MessProcessor::MC_PUBLIC_CHAT = L"00";
TCHAR *MessProcessor::MC_USERNAME_REQUEST = L"01";
TCHAR *MessProcessor::EC_USERNAME_EXISTED = L"02";
TCHAR *MessProcessor::MC_USER_LOGGED_IN = L"03";
TCHAR *MessProcessor::MC_USERNAME_LIST = L"04";
TCHAR *MessProcessor::MC_USER_LOGGEDOUT = L"05";
TCHAR *MessProcessor::MC_PRIVATE_CHAT = L"06";
TCHAR *MessProcessor::EC_USERNAME_LOGGEDOUT = L"07";
TCHAR *MessProcessor::MC_DOWNLOAD_OFFER = L"08";
TCHAR *MessProcessor::EC_FILE_NOTFOUND = L"09";
TCHAR *MessProcessor::MC_UPLOAD_REQUEST = L"10";
TCHAR *MessProcessor::MC_UPLOAD_READY = L"11";
TCHAR *MessProcessor::MC_PRIVATE_FILE_OFFER = L"12";
TCHAR *MessProcessor::MC_PRIVATE_FILE_ACCEPT = L"13";

MessProcessor::MessProcessor(void)
{
}

MessProcessor::~MessProcessor(void)
{
}

CString MessProcessor::PeelMess(CString *cstrMess)
{
	int iPos = 0;
	CString cstrMessLeader = cstrMess->Tokenize(L" ", iPos);		// tach chuoi theo khoang trang
	
	if (iPos == -1 || iPos == cstrMess->GetLength() + 1)	// duyet het chuoi hoac chuoi ko co ki tu gioi han
		cstrMessLeader = "";
	else
		cstrMess->Delete(0, iPos);		// loai bo phan mess leader trong message

	return cstrMessLeader;
}

CString MessProcessor::JoinMess( TCHAR *cstrMess[], int count )
{
	// chuoi thong diep gom nhieu thanh phan ngan cach khoang trang
	CString cstrJoined;
	int i = 0;
	for ( ; i < count-1; ++i)
	{
		cstrJoined += cstrMess[i];
		cstrJoined += L' ';
	}

	cstrJoined += cstrMess[i];

	return cstrJoined;
}