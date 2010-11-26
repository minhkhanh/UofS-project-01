// AddressBar.cpp : implementation file
//

#include "stdafx.h"
#include "ftp_client.h"
#include "AddressBar.h"


// AddressBar

IMPLEMENT_DYNAMIC(CAddressBar, CEdit)

CAddressBar::CAddressBar()
{

}

CAddressBar::~CAddressBar()
{
}


BEGIN_MESSAGE_MAP(CAddressBar, CEdit)
END_MESSAGE_MAP()

void CAddressBar::SetText( LPCTSTR sText )
{
	SendMessage(WM_SETTEXT, 0, (LPARAM)sText);
}



// AddressBar message handlers


