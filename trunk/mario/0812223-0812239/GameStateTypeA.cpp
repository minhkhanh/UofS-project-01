#include "StdAfx.h"
#include "GameStateTypeA.h"

GameStateTypeA::GameStateTypeA(MainGame *_mg, TCHAR * pszPath)
{
	mg = _mg;
	GAME_STATE_DEF = cDef::STATE_TYPE_A;

	FILE   *f;
    if ((f = _tfopen(pszPath, _T("rt"))) == NULL)
       exit(0); 
    TCHAR szText[INPUT_MAX_LEN];
	int iTemp, iDem = 0, iCellCount = 0;
    while (fgetws(szText, INPUT_MAX_LEN, f))
	{
		// Bo ky tu \n o cuoi chuoi
		++iDem;
		//szText[wcslen(szText)-1] = '\0';
		vector<int> vTemp;
		iTemp = wcslen(szText);
		for (int i = 0; i < iTemp; ++i)
		{
			++iCellCount;
			if (szText[i]=='?') 
				vTemp.push_back(0);
			else
			{
				if	(szText[i] == 'a')		// bo sung quai vat, ak
				{
					Sprite *sprMonster = new Sprite(0,0,24,32,0,3,0, new MyBitmap((LPCTSTR)IDIMG_MONSTER07));
					m_vMonster.push_back(new TypeAMonster(sprMonster, iCellCount));
				}

				vTemp.push_back(szText[i]-65);
			}
		}

		vMap.push_back(vTemp);
	}

	fclose(f);
	iMapLogicHeight = iDem;// * BASE_HEIGHT;
	iMapLogicWidth = iTemp;// * BASE_WIDTH;

	iMainX = 5;
	iMainY = 15;

	// tao nhan vat chinh, ak
	sprOcegrine = new Sprite(0,0,18,36,1,7,0,new MyBitmap((LPCTSTR)IDIMG_OCEGRINE_SPRITE));
	m_iCurrScreenFramePos = 0;
}

GameStateTypeA::~GameStateTypeA(void)
{
}

void GameStateTypeA::MessageExit(int message, CDC *pDC)
{
	mg->mBiz_iCurrentState = cDef::STATE_LOGO;
}

void GameStateTypeA::MessageUpdate(int message, int keys)
{
	if ((keys & GameKeys::Left) == GameKeys::Left)
	{
		--iMainX;
		sprOcegrine->PreviousFrame();

		if (iMainX < 0)
			iMainX = 0;

		// xử lý đi quá lề trái cho m_iCurrScreenFramePos, ak
		--m_iCurrScreenFramePos;
		if (m_iCurrScreenFramePos < 0)
			m_iCurrScreenFramePos = 0;
	}
	else if ((keys & GameKeys::Right) == GameKeys::Right)
	{
		++iMainX;
		sprOcegrine->NextFrame();

		if (iMainX >= iMapLogicWidth)
			iMainX = iMapLogicWidth - 1;

		// xử lý đi quá lề phải cho m_iCurrScreenFramePos, ak
		++m_iCurrScreenFramePos;
		if (m_iCurrScreenFramePos + LOGIC_SCREEN_WIDTH > iMapLogicWidth)
			m_iCurrScreenFramePos = iMapLogicWidth - LOGIC_SCREEN_WIDTH - 1;
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
	sprOcegrine->Render(8*BASE_WIDTH, 10*BASE_HEIGHT, &(mg->m_MemDC));

	pDC->StretchBlt(0, 0, 380, 480, &(mg->m_MemDC), 0, 0 , 380, 480, SRCCOPY);
}

void GameStateTypeA::MessageEnter(int message)
{
	imgBG = new MyBitmap((LPCTSTR)IDIMG_BGR_TYPE_A_LEVEL_1);
	sprTiles = new Sprite(0,0,24,24,1,31,0,new MyBitmap((LPCTSTR)IDIMG_TILES_TYPE_A_LEVEL_1));
}

void GameStateTypeA::PaintMap(int iX, int iY, Sprite *sprImage, CDC *pDC)
{
	int i = iX - LOGIC_SCREEN_WIDTH/2;
	int j = iY - LOGIC_SCREEN_HEIGHT/2;

	if (i < 0)
		i = 0;
	if (j < 0)
		j = 0;

	if (i + LOGIC_SCREEN_WIDTH > iMapLogicWidth)
		i = iMapLogicWidth - LOGIC_SCREEN_WIDTH - 1;

	if (j + LOGIC_SCREEN_HEIGHT > iMapLogicHeight)
		j = iMapLogicHeight - LOGIC_SCREEN_HEIGHT;

	for (int jj = 0; jj < LOGIC_SCREEN_HEIGHT; ++jj)
		for (int ii = 0; ii < LOGIC_SCREEN_WIDTH; ++ii)
		{
			if ((vMap[j+jj][i+ii] + 65) != 'a' && vMap[j+jj][i+ii] != 0)
			{
				sprImage->SetPositionFrame(vMap[j+jj][i+ii]);
				sprImage->Render(ii*BASE_WIDTH, jj*BASE_HEIGHT, pDC);
			}
		}
}

void GameStateTypeA::RunMonster()
{
	for (unsigned i = 0; i < m_vMonster.size(); ++i)
	{
		if (m_vMonster[i]->)
	}
}