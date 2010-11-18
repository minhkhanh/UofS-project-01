
// ftp_client.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// Cftp_clientApp:
// See ftp_client.cpp for the implementation of this class
//

class Cftp_clientApp : public CWinAppEx
{
public:
	Cftp_clientApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern Cftp_clientApp theApp;