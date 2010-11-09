
// ConfServer.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CConfServerApp:
// See ConfServer.cpp for the implementation of this class
//

class CConfServerApp : public CWinAppEx
{
public:
	CConfServerApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CConfServerApp theApp;