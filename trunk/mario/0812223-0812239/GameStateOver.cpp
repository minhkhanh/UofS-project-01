#include "StdAfx.h"
#include "GameStateOver.h"

#include "MainGame.h"
#include "MyScriptMap.h"

GameStateOver::GameStateOver(MainGame *mg, TCHAR* szScriptPath)
{
	m_pScriptText = new MyScriptMap(szScriptPath);
	m_pMainGame = mg;
	m_iGameStateDef = cDef::STATE_GAMEOVER;

	m_pBackGroundBMP = new MyBitmap((LPCTSTR)IDIMG_GAME_OVER);
}

GameStateOver::~GameStateOver(void)
{
}

void GameStateOver::MessageEnter(int message)
{
	GameSound::Play(GAME_OVER_THEME);
	m_iStep = 0;
	m_pBackGroundBMP->DrawTransparent(m_pMainGame->m_pDC, 0, 0, RGB(113,113,113));
}

void GameStateOver::MessageUpdate(int message, int keys)
{
	if (keys & GameKeys::Enter)
	{
		m_pMainGame->mBiz_SwitchState(0);
	}

	if (keys & GameKeys::Left)
	{
		m_pScriptText->PreviousScript();
		bNeedRedraw = true;

		m_pMainGame->KeyRelease(GameKeys::Left);
	}

	if (keys & GameKeys::Right)
	{
		m_pScriptText->NextScript();
		bNeedRedraw = true;

		m_pMainGame->KeyRelease(GameKeys::Right);
	}
}

void GameStateOver::MessagePaint(int message, CDC *pDC)
{
	++m_iStep;
	if ((m_iStep % 3) != 0) return;
	m_pMainGame->m_pMemGraphics->Clear(Color(255,25,55,255));
	if (bNeedRedraw) 
	{
		HDC old = m_pMainGame->m_pGraphics->GetHDC();
		m_pBackGroundBMP->DrawTransparent(&(m_pMainGame->m_MemDC), 0, 0, RGB(113,113,113));
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

void GameStateOver::MessageExit(int message, CDC *pDC)
{
	GameSound::Play(GAME_OVER_THEME, 0);
	m_pMainGame->mBiz_iCurrentState = cDef::STATE_LOGO;
}