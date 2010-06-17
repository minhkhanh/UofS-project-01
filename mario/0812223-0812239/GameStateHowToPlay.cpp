#include "StdAfx.h"
#include "GameStateHowToPlay.h"

#include "MainGame.h"

GameStateHowToPlay::GameStateHowToPlay(MainGame *mg): m_iCurrPos(0)
{
	m_pMainGame = mg;
	m_iGameStateDef = cDef::STATE_HOWTOPLAY;

	m_pBackGroundBMP = new MyBitmap((LPCTSTR)IDIMG_HOWTOPLAY);
}

GameStateHowToPlay::~GameStateHowToPlay(void)
{
}

void GameStateHowToPlay::MessageEnter(int message)
{
	m_pMainGame->m_iSleepTime = 50;
	m_pBackGroundBMP->DrawTransparent(m_pMainGame->m_pDC, 0, 0, RGB(113,113,113));
}

void GameStateHowToPlay::MessageUpdate(int message, int keys)
{
	if (keys & GameKeys::Enter)
	{
		m_pBackGroundBMP->DrawTransparent(&(m_pMainGame->m_MemDC), 0, 0, RGB(113,113,113));
		m_pMainGame->m_pDC->StretchBlt(0,0,cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, &(m_pMainGame->m_MemDC), 0,0,cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, SRCCOPY);

		GameSound::Play(EXPLOSION_SOUND);

		m_pMainGame->mBiz_SwitchState(cDef::STATE_MENU);
		//m_pMainGame->KeyRelease(GameKeys::Enter);
	}
}

void GameStateHowToPlay::MessagePaint(int message, CDC *pDC)
{

}

void GameStateHowToPlay::MessageExit(int message, CDC *pDC)
{
	m_pMainGame->mBiz_iCurrentState = cDef::STATE_MENU;
}