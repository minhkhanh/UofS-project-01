#include "StdAfx.h"
#include "GameStateIntro.h"

#include "MyScriptMap.h"
#include "MainGame.h"

GameStateIntro::GameStateIntro(MainGame *_mg, TCHAR szText[], LPCTSTR szBGR)
{
	mg = _mg;
	GAME_STATE_DEF = cDef::STATE_INTRO;
	m_pScriptText = new MyScriptMap(szText);
	m_pBGR = new MyBitmap(szBGR);
}

GameStateIntro::~GameStateIntro(void)
{

}

void GameStateIntro::MessageEnter( int message )
{
	bNeedRedraw = true;
	m_pScriptText->Reset();
	HDC old = mg->m_pGraphics->GetHDC();
	m_pBGR->DrawTransparent(&(mg->m_MemDC), 0, 0, RGB(255,255,255));
	mg->pDC->StretchBlt(0, 0, cDef::MAINGAME_WIDTH, cDef::MAINGAME_HEIGHT, &(mg->m_MemDC), 0, 0 , 240, 320, SRCCOPY);
	mg->m_pGraphics->ReleaseHDC(old);
}

void GameStateIntro::MessageUpdate( int message, int keys )
{
	//bNeedRedraw = false;
	if ((keys & GameKeys::Left) == GameKeys::Left)
	{
		m_pScriptText->PreviousScript();
		bNeedRedraw = true;
		keys &= ~(GameKeys::Left);
	}

	if ((keys & GameKeys::Right) == GameKeys::Right)
	{
		m_pScriptText->NextScript();
		bNeedRedraw = true;
		keys &= ~(GameKeys::Right);
	}

	if ((keys & GameKeys::Enter) == GameKeys::Enter)
	{
		mg->mBiz_SwitchState(cDef::STATE_MENU);
		mg->KeyRelease(GameKeys::Enter);
	}
}

void GameStateIntro::MessagePaint( int message, CDC *pDC )
{
	if (bNeedRedraw) 
	{
		HDC old = mg->m_pGraphics->GetHDC();
		m_pBGR->DrawTransparent(&(mg->m_MemDC), 0, 0, RGB(255,255,255));
		pDC->StretchBlt(0, 0, cDef::MAINGAME_WIDTH, cDef::MAINGAME_HEIGHT, &(mg->m_MemDC), 0, 0 , 240, 320, SRCCOPY);
		mg->m_pGraphics->ReleaseHDC(old);
	}
	mg->m_pMemGraphics->Clear(Color(0,0,0,0));
	m_pScriptText->ShowText(10, 10, mg->m_pMemGraphics);
	if (!m_pScriptText->NextCharacter())
	{
		m_pScriptText->NextScript() ;
		bNeedRedraw = true;
	}
	else bNeedRedraw = false;
	mg->m_pGraphics->DrawImage(mg->m_pImageGraphics, 0, 0);
}

void GameStateIntro::MessageExit( int message, CDC *pDC )
{
	mg->mBiz_iCurrentState = cDef::STATE_MENU;
}

