#include "StdAfx.h"
#include "GameStateIntro.h"

#include "MyScriptMap.h"
#include "MainGame.h"

GameStateIntro::GameStateIntro(MainGame *mg, TCHAR szText[], LPCTSTR szBGR)
{
	m_pMainGame = mg;
	m_iGameStateDef = cDef::STATE_INTRO;
	m_pScriptText = new MyScriptMap(szText);
	m_pBGR = new MyBitmap(szBGR);
}

GameStateIntro::~GameStateIntro(void)
{

}

void GameStateIntro::MessageEnter( int message )
{
	m_iStep = 0;
	GameSound::Play(INTRO_THEME_SOUND);

	bNeedRedraw = true;
	m_pScriptText->Reset();
	HDC old = m_pMainGame->m_pGraphics->GetHDC();

	CDC *pMemDC = m_pMainGame->GetMemDC();
	CDC *pDC = m_pMainGame->GetMainDC();

	m_pBGR->DrawTransparent(pDC, 0, 0, RGB(113,113,113));
	//pDC->StretchBlt(0, 0, cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, pMemDC, 0, 0 , cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, SRCCOPY);
	m_pMainGame->m_pGraphics->ReleaseHDC(old);
}

void GameStateIntro::MessageUpdate( int message, int keys )
{
	if (keys & GameKeys::Left)
	{
		m_pScriptText->PreviousScript();
		bNeedRedraw = true;
		m_iStep = 0;
		m_pMainGame->KeyRelease(GameKeys::Left);
	}

	if (keys & GameKeys::Right)
	{
		m_pScriptText->NextScript();
		bNeedRedraw = true;
		m_iStep = 0;
		m_pMainGame->KeyRelease(GameKeys::Right);
	}

	if (keys & GameKeys::Enter)
	{
		m_pMainGame->mBiz_SwitchState(cDef::STATE_MENU);
		//m_pMainGame->KeyRelease(GameKeys::Enter);
	}
}

void GameStateIntro::MessagePaint( int message, CDC *pDC )
{
	++m_iStep;
	if ((m_iStep % 3) != 0) return;
	m_pMainGame->m_pMemGraphics->Clear(Color(255,25,55,255));
	if (bNeedRedraw) 
	{
		HDC old = m_pMainGame->m_pGraphics->GetHDC();
		m_pBGR->DrawTransparent(&(m_pMainGame->m_MemDC), 0, 0, RGB(113,113,113));
		pDC->StretchBlt(0, 0, cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, &(m_pMainGame->m_MemDC), 0, 0 , cDef::SCREEN_WIDTH, cDef::SCREEN_HEIGHT, SRCCOPY);
		m_pMainGame->m_pGraphics->ReleaseHDC(old);
	}
	m_pMainGame->m_pMemGraphics->Clear(Color(0,0,0,0));
	m_pScriptText->ShowText(10, 10, m_pMainGame->m_pMemGraphics);
	if (m_pScriptText->IsEndLine())
	{
		//m_pScriptText->NextScript() ;
		bNeedRedraw = true;
	}
	else bNeedRedraw = false;
	m_pMainGame->m_pGraphics->DrawImage(m_pMainGame->m_pImageGraphics, 0, 0);
}

void GameStateIntro::MessageExit( int message, CDC *pDC )
{
	GameSound::Play(INTRO_THEME_SOUND, 0);

	m_pMainGame->mBiz_iCurrentState = cDef::STATE_MENU;
}

