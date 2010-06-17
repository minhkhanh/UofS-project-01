#include "StdAfx.h"
#include "GameStateFinish.h"

#include "MainGame.h"
#include "MyScriptMap.h"

GameStateFinish::GameStateFinish( MainGame *mg, TCHAR* szScriptPath )
{
	m_pMainGame = mg;
	m_pScriptText = new MyScriptMap(szScriptPath);
	m_iGameStateDef = cDef::STATE_FINISH;

	m_pBackGroundBMP = new MyBitmap((LPCTSTR)IDIMG_GAME_FINISH);
}
GameStateFinish::~GameStateFinish(void)
{
}

void GameStateFinish::MessageEnter(int message)
{
	m_pMainGame->SetSleepTime(30);
	GameSound::Play(GAME_FINISH_THEME_SOUND);

	m_pBackGroundBMP->DrawTransparent(m_pMainGame->m_pDC, 0, 0, RGB(113,113,113));
}

void GameStateFinish::MessageUpdate(int message, int keys)
{
	if (keys & GameKeys::Enter)
	{
		m_pMainGame->mBiz_SwitchState(0);
	}

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
}

void GameStateFinish::MessagePaint(int message, CDC *pDC)
{
	++m_iStep;
	if ((m_iStep % 10) != 0) return;
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
		bNeedRedraw = true;
	}
	else bNeedRedraw = false;
	m_pMainGame->m_pGraphics->DrawImage(m_pMainGame->m_pImageGraphics, 0, 0);
}

void GameStateFinish::MessageExit(int message, CDC *pDC)
{
	GameSound::Play(GAME_FINISH_THEME_SOUND, 0);
	m_pMainGame->mBiz_iCurrentState = cDef::STATE_LOGO;
}