
// 0812223-0812239.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMy08122230812239App:
// See 0812223-0812239.cpp for the implementation of this class
//

class CMy08122230812239App : public CWinAppEx
{
public:
	CMy08122230812239App();

// Overrides
	public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMy08122230812239App theApp;