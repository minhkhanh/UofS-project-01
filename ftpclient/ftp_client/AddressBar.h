#pragma once


// AddressBar

class AddressBar : public CEdit
{
	DECLARE_DYNAMIC(AddressBar)

public:
	AddressBar();
	virtual ~AddressBar();

protected:
	DECLARE_MESSAGE_MAP()
};


