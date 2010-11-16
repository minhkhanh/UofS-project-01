
// 0812239_FTPClient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CFTPClientApp:
// See 0812239_FTPClient.cpp for the implementation of this class
//

class CFTPClientApp : public CWinAppEx
{
public:
	CFTPClientApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CFTPClientApp theApp;