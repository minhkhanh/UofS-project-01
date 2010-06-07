#include "StdAfx.h"
#include "MyScriptMap.h"

MyScriptMap::MyScriptMap(TCHAR *strScriptPath)
{
	FILE * f;
	if ((f = _wfopen(strScriptPath, _T("rt"))) == NULL)
		exit(0);

	char pTemp[INPUT_MAX_LEN];
	//wchar_t * pTempw;
	int indexCell = 0;
	while (fgets(pTemp, INPUT_MAX_LEN, f))
	{
		m_vScript.push_back(Functions::UTF8_to_WChar(pTemp));
	}
	//pTempw = Functions::UTF8_to_WChar(pTemp);
	fclose(f);
	m_iCurScript = 0;
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

void MyScriptMap::ShowText( int X, int Y, Graphics *pGraphics )
{
	// Create a string.
	//WCHAR string[] = L"Trần Minh Khánh\n";

	// Initialize arguments.
	//FontFamily fontFamily = new FontFamily(L"Arial");
	Gdiplus::Font myFont(_T("Arial"), 16);
	PointF origin(0.0f, 0.0f);
	SolidBrush blackBrush(Color(255, 0, 255, 0));

	// Draw string.
	pGraphics->DrawString(
		 m_vScript[m_iCurScript],
		-1,
		&myFont,
		origin,
		&blackBrush);
	//pGraphics->

}