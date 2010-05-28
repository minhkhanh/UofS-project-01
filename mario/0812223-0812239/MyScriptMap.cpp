#include "StdAfx.h"
#include "MyScriptMap.h"

MyScriptMap::MyScriptMap(TCHAR *strScriptPath)
{
	FILE   *f;
	if ((f = _wfopen(strScriptPath, _T("rt"))) == NULL)
		exit(0);
	TCHAR pTemp[INPUT_MAX_LEN];
	while (fgetws(pTemp, INPUT_MAX_LEN, f))
	{
		m_vScript.push_back(_wcsdup(pTemp));
	}
	m_iCurScript = 0;
	fclose(f);
}

MyScriptMap::~MyScriptMap(void)
{
	for (int i=0; i<m_vScript.size(); ++i)
	{
		delete m_vScript[i];
	}
	m_vScript.clear();
}

void MyScriptMap::NextScript()
{
	if (m_iCurScript < (m_vScript.size()-1)) ++m_iCurScript;
}

void MyScriptMap::PreviousScript()
{
	if (m_iCurScript > 0) --m_iCurScript;
}

void MyScriptMap::ShowText( int X, int Y, CDC *pDC )
{
	pDC->TextOut(X, Y, m_vScript[m_iCurScript], wcslen(m_vScript[m_iCurScript]));
}