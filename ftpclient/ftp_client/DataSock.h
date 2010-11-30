#pragma once

#define MAX_BKLG	5

#include "MySock.h"

class DataSock: public MySock
{
private:
	vector<CString> m_vItemNames;
	vector<CString> m_vFolderNames;

	SOCKET m_sockActive;
	//FTPMode m_eMode;
	int Bind();
	
	
public:
	DataSock(void);
	~DataSock(void);

	int BindAndListen();
	int Listen();
	int Accept();
	int CloseActiveSock();
	int Send(char* sBuff, int iLen);

	vector<CString>& FolderNames() { return m_vFolderNames; }
	vector<CString>& ItemNames() { return m_vItemNames; }
};
