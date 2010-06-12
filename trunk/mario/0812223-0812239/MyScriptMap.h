#pragma once

#include "Functions.h"

class MyScriptMap
{
private:
	vector< TCHAR* > m_vScript;
	int m_iCurScript;
	int m_iCurWord;
	int m_iX;
	int m_iY;
	int m_iNumWord;
	int m_iCurLen;
	bool m_bIsEndLine;
	void ResetShowText();
	void FindNextWord();
public:
	MyScriptMap(TCHAR *strScriptPath);
	void NextScript();
	void PreviousScript();
	bool IsEndLine();
	//bool NextCharacter();
	void ShowText(int X, int Y, CDC *pDC);
	void ShowText(int X, int Y, Graphics *pGraphics);
	void Reset();
	virtual ~MyScriptMap(void);
};
