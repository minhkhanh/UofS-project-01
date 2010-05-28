#include "StdAfx.h"
#include "GameStateIntro.h"

GameStateIntro::GameStateIntro(MainGame *_mg, TCHAR szText[])
{
	mg = _mg;
	GAME_STATE_DEF = cDef::STATE_INTRO;
	m_pScriptText = new MyScriptMap(szText);
}

GameStateIntro::~GameStateIntro(void)
{
}

void GameStateIntro::MessageEnter( int message )
{

}

void GameStateIntro::MessageUpdate( int message, int keys )
{
	if ((keys & GameKeys::Left) == GameKeys::Left)
	{
		m_pScriptText->PreviousScript();
		keys &= ~(GameKeys::Left);
	}

	if ((keys & GameKeys::Right) == GameKeys::Right)
	{
		m_pScriptText->NextScript();
		keys &= ~(GameKeys::Right);
	}

	if ((keys & GameKeys::Enter) == GameKeys::Enter)
	{
		mg->mBiz_SwitchState(cDef::STATE_MENU);
	}
}

void GameStateIntro::MessagePaint( int message, CDC *pDC )
{
	mg->m_MemDC.Rectangle(0,0,SCREEN_WIDTH, SCREEN_HEIGHT);
	m_pScriptText->ShowText(10, 10, &(mg->m_MemDC));
	pDC->StretchBlt(0, 0, cDef::MAINGAME_WIDTH, cDef::MAINGAME_HEIGHT, &(mg->m_MemDC), 0, 0 , 240, 320, SRCCOPY);
}

void GameStateIntro::MessageExit( int message, CDC *pDC )
{
	mg->mBiz_iCurrentState = cDef::STATE_MENU;
}