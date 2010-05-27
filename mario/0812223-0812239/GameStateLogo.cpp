#include "StdAfx.h"
#include "GameStateLogo.h"

GameStateLogo::GameStateLogo(MainGame *_mg)
{
	mg = _mg;
	GAME_STATE_DEF = cDef::STATE_LOGO;

	m_iX = 0;
}

GameStateLogo::~GameStateLogo(void)
{
}

void GameStateLogo::MessageUpdate(int message, int keys)
{
	if ((keys & GameKeys::Left) == GameKeys::Left)
	{
		sprMenuIcon->NextFrame();
		--m_iX;
	}
	
	if ((keys & GameKeys::Right) == GameKeys::Right)
	{
		sprMenuIcon->NextFrame();
		++m_iX;
	}
	
	if ((keys & GameKeys::Enter) == GameKeys::Enter)
	{
		mg->mBiz_SwitchState(cDef::STATE_MENU);
	}

}

void GameStateLogo::MessagePaint(int message, CDC *pDC)
{
	imgBG->DrawTransparent(&(mg->m_MemDC), 0, 0, RGB(255,255,255));
	sprMenuIcon->Render(m_iX, 230, &(mg->m_MemDC));

	pDC->StretchBlt(0, 0, cDef::MAINGAME_WIDTH, cDef::MAINGAME_HEIGHT, &(mg->m_MemDC), 0, 0 , 240, 320, SRCCOPY);
}

void GameStateLogo::MessageEnter(int message)
{
	imgBG = new MyBitmap((LPCTSTR)IDIMG_DEMOMENU);
	sprMenuIcon = new Sprite(0,0,42,40,1,3,0,new MyBitmap((LPCTSTR)IDIMG_COMMANDER));

	mg->iSleepTime = 100;
}

void GameStateLogo::MessageExit(int message, CDC *pDC)
{
	mg->mBiz_iCurrentState = cDef::STATE_MENU;
}