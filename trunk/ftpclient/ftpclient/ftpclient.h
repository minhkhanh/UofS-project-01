
// ftpclient.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CftpclientApp:
// See ftpclient.cpp for the implementation of this class
//

class CftpclientApp : public CWinAppEx
{
public:
	CftpclientApp();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CftpclientApp theApp;