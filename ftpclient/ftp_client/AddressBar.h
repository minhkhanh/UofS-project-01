#pragma once


// AddressBar

class CAddressBar : public CEdit
{
	DECLARE_DYNAMIC(CAddressBar)

public:
	CAddressBar();
	virtual ~CAddressBar();
	void SetText(LPCTSTR sText);

protected:
	DECLARE_MESSAGE_MAP()
};


