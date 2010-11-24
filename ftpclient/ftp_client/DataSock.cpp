#include "StdAfx.h"
#include "DataSock.h"

DataSock::DataSock(void)
{
	m_sock = INVALID_SOCKET;
}

DataSock::~DataSock(void)
{
}
//
//int DataSock::SetServInfo(char * sIP, int iPort)
//{
//	m_sockaddrServer.sin_family = AF_INET;
//	m_sockaddrServer.sin_port = htons(iPort);
//	m_sockaddrServer.sin_addr.s_addr = inet_addr(sIP);
//
//	if (m_sockaddrServer.sin_addr.s_addr == INADDR_NONE)
//		return -1;
//
//	return 0;
//}