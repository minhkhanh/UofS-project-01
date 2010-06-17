#include "StdAfx.h"
#include "GameStateLogo.h"

#include "MainGame.h"

GameStateLogo::GameStateLogo(MainGame *_mg): m_iX(0)
{
	m_pMainGame = _mg;
	m_iGameStateDef = cDef::STATE_LOGO;

	m_pTenGame = new MyBitmap((LPCTSTR)IDIMG_BGR_LOGO_TEN_GAME);
	m_iX = 0;
}

GameStateLogo::~GameStateLogo(void)
{
}

void GameStateLogo::MessageUpdate(int message, int keys)
{
	if ((keys & GameKeys::Left) == GameKeys::Left)
	{
		m_pMenuIcon->NextFrame();
		--m_iX;
		m_pMainGame->KeyRelease(GameKeys::Left);
	}
	
	if ((keys & GameKeys::Right) == GameKeys::Right)
	{
		m_pMenuIcon->NextFrame();
		++m_iX;
		m_pMainGame->KeyRelease(GameKeys::Right);
	}
	
	if ((keys & GameKeys::Enter) == GameKeys::Enter)
	{
		m_pMainGame->mBiz_SwitchState(cDef::STATE_MENU);
		m_pMainGame->KeyRelease(GameKeys::Enter);
	}

}

void GameStateLogo::MessagePaint(int message, CDC *pDC)
{
	GameSound::Play(JUMP_SOUND);

	m_pBackground->DrawTransparent(&(m_pMainGame->m_MemDC), 0, 0, RGB(255, 255, 255));
	m_pTenGame->DrawTransparent(&(m_pMainGame->m_MemDC), 5, 20, RGB(255,255,255));
	m_pMenuIcon->Render(m_iX, 230, &(m_pMainGame->m_MemDC));
	m_iX += 3;
	m_pMenuIcon->NextFrame();
	if (m_iX > 240) m_pMainGame->KeyPressed(GameKeys::Enter);
	pDC->StretchBlt(0, 0, cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, &(m_pMainGame->m_MemDC), 0, 0 , 240, 320, SRCCOPY);
}

void GameStateLogo::MessageEnter(int message)
{
	m_pBackground = new MyBitmap((LPCTSTR)IDIMG_DEMOMENU);
	m_pMenuIcon = new Sprite(0,0,42,40,1,3,0,new MyBitmap((LPCTSTR)IDIMG_COMMANDER));

	m_pMainGame->m_iSleepTime = 100;
}

void GameStateLogo::MessageExit(int message, CDC *pDC)
{
	m_pMainGame->mBiz_iCurrentState = cDef::STATE_INTRO;
}
