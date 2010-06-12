#include "StdAfx.h"
#include "GameStateHowToPlay.h"

#include "MainGame.h"

GameStateHowToPlay::GameStateHowToPlay(MainGame *mg)
{
	m_pMainGame = mg;
	m_iGameStateDef = cDef::STATE_HOWTOPLAY;

	m_vBackGround.push_back(new MyBitmap((LPCTSTR)IDIMG_HOWTOPLAY));
	m_vBackGround.push_back(new MyBitmap((LPCTSTR)IDIMG_HOWTOPLAY_MASK1));
	m_vBackGround.push_back(new MyBitmap((LPCTSTR)IDIMG_HOWTOPLAY_MASK2));
	m_vBackGround.push_back(new MyBitmap((LPCTSTR)IDIMG_HOWTOPLAY_MASK3));
}

GameStateHowToPlay::~GameStateHowToPlay(void)
{
}

void GameStateHowToPlay::MessageEnter(int message)
{
	m_pMainGame->m_iSleepTime = 100;
	m_vBackGround[0]->DrawTransparent(m_pMainGame->m_pDC, 0, 0, RGB(113,113,113));
}

void GameStateHowToPlay::MessageUpdate(int message, int keys)
{
	if (keys & GameKeys::Enter)
	{
		m_vBackGround[3]->DrawTransparent(&(m_pMainGame->m_MemDC), 0, 0, RGB(113,113,113));
		m_pMainGame->m_pDC->StretchBlt(0,0,cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, &(m_pMainGame->m_MemDC), 0,0,cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, SRCCOPY);
		m_pMainGame->KeyRelease(GameKeys::Enter);

		GameSound::Explosion(1);

		m_pMainGame->mBiz_SwitchState(cDef::STATE_MENU);
		m_pMainGame->KeyRelease(GameKeys::Enter);
	}

	if ((keys & GameKeys::Left) || (keys & GameKeys::Down))
	{
		m_vBackGround[1]->DrawTransparent(&(m_pMainGame->m_MemDC), 0, 0, RGB(113,113,113));
		m_pMainGame->m_pDC->StretchBlt(0,0,cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, &(m_pMainGame->m_MemDC), 0,0,cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, SRCCOPY);

		m_pMainGame->KeyRelease(GameKeys::Left);
		m_pMainGame->KeyRelease(GameKeys::Down);

		GameSound::Coin(1);
	}

	if ((keys & GameKeys::Right) || (keys & GameKeys::Up))
	{
		m_vBackGround[2]->DrawTransparent(&(m_pMainGame->m_MemDC), 0, 0, RGB(113,113,113));
		m_pMainGame->m_pDC->StretchBlt(0,0,cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, &(m_pMainGame->m_MemDC), 0,0,cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, SRCCOPY);

		m_pMainGame->KeyRelease(GameKeys::Right);
		m_pMainGame->KeyRelease(GameKeys::Up);

		GameSound::Coin(1);
	}
}

void GameStateHowToPlay::MessagePaint(int message, CDC *pDC)
{

}

void GameStateHowToPlay::MessageExit(int message, CDC *pDC)
{
	m_pMainGame->mBiz_iCurrentState = cDef::STATE_MENU;
}