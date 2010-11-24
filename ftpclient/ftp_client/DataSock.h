#pragma once

#include "MySock.h"

class DataSock: public MySock
{
private:
	//SOCKET m_sock;
	//sockaddr_in m_sockaddrServer;

public:
	DataSock(void);
	~DataSock(void);

	//int SetServInfo(char * sIP, int iPort);
};
