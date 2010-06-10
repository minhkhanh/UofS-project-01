#pragma once

#include "Functions.h"

class MyScriptMap
{
private:
	vector< TCHAR* > m_vScript;
	int m_iCurScript;
	int m_iCurCharacter;
	int m_iX;
	int m_iY;
	void ResetShowText();
public:
	MyScriptMap(TCHAR *strScriptPath);
	void NextScript();
	void PreviousScript();
	bool NextCharacter();
	void ShowText(int X, int Y, CDC *pDC);
	void ShowText(int X, int Y, Graphics *pGraphics);
	void Reset();
	virtual ~MyScriptMap(void);
};
