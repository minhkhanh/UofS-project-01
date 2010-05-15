#include "StdAfx.h"
#include "GameStateTypeA.h"

GameStateTypeA::GameStateTypeA(MainGame *_mg, TCHAR * pszPath)
{
	mg = _mg;
	GAME_STATE_DEF = cDef::STATE_LOGO;
	FILE   *f;
    if ((f = _tfopen(pszPath, _T("rt"))) == NULL)
       exit(0); 
    TCHAR szText[INPUT_MAX_LEN];
	int iTemp, iDem = 0;
    while (fgetws(szText, INPUT_MAX_LEN, f))	{
		// Bo ky tu \n o cuoi chuoi
		++iDem;
		//szText[wcslen(szText)-1] = '\0';
		vector<int> vTemp;
		iTemp = wcslen(szText);
		for (int i=0; i<iTemp; ++i)
			if (szText[i]=='?') 
				vTemp.push_back(0);
			else vTemp.push_back(szText[i]-65);
		vMap.push_back(vTemp);
	}
	fclose(f);
	iMapLogicHeight = iDem;// * BASE_HEIGHT;
	iMapLogicWidth = iTemp;// * BASE_WIDTH;
	iMainX = 8;
	iMainY = 10;
}

GameStateTypeA::~GameStateTypeA(void)
{
}

void GameStateTypeA::MessageUpdate(int message, int keys)
{
	if ((keys & GameKeys::Left) == GameKeys::Left)
	{
		--iMainX;
		if (iMainX<0) iMainX = 0;
	}
	else if ((keys & GameKeys::Right) == GameKeys::Right)
	{
		++iMainX;
		if (iMainX>=iMapLogicWidth) iMainX = iMapLogicWidth -1;
	}
	else if ((keys & GameKeys::Enter) == GameKeys::Enter)
	{
		mg->mBiz_SwitchState(cDef::STATE_MENU);
	}

}

void GameStateTypeA::MessagePaint(int message, CDC *pDC)
{
	imgBG->DrawTransparent(&(mg->m_MemDC), 0, 0, RGB(255,255,255));
	PaintMap(iMainX, iMainY, sprTiles, &(mg->m_MemDC));

	pDC->StretchBlt(0, 0, 380, 480, &(mg->m_MemDC), 0, 0 , 380, 480, SRCCOPY);
}

void GameStateTypeA::MessageEnter(int message)
{
	imgBG = new MyBitmap((LPCTSTR)IDIMG_BGR_TYPE_A_LEVEL_1);
	sprTiles = new Sprite(0,0,24,24,1,31,0,new MyBitmap((LPCTSTR)IDIMG_TILES_TYPE_A_LEVEL_1));
}

void GameStateTypeA::PaintMap(int iX, int iY, Sprite *sprImage, CDC *pDC)
{
	int i = iX - iLogicScreenWidth/2;
	int j = iY - iLogicScreenHeight/2;
	if (i<0) i = 0;
	if (j<0) j = 0;
	if (i + iLogicScreenWidth > iMapLogicWidth) i = iMapLogicWidth - iLogicScreenWidth -1;
	if (j + iLogicScreenHeight > iMapLogicHeight) i = iMapLogicHeight - iLogicScreenHeight -1;
	for (int jj=0; jj<iLogicScreenHeight; ++jj)
		for (int ii=0; ii<iLogicScreenWidth; ++ii)
		{
			if (vMap[j+jj][i+ii])
			{
				sprImage->SetPositionFrame(vMap[j+jj][i+ii]);
				sprImage->Render(ii*BASE_WIDTH, jj*BASE_HEIGHT, pDC);
			}
		}
}