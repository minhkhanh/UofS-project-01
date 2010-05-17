#include "StdAfx.h"
#include "MainGame.h"

MainGame::MainGame(void)
{
	m_keys = 0;
	mBiz_iCurrentState = cDef::STATE_LOGO;

	iSleepTime = 100;
	m_playing = true;

	// khởi tạo tất cả các State trong game:

	m_arrGameStates.push_back((GameState*)new GameStateLogo(this));
	m_arrGameStates.push_back((GameState*)new GameStateMenu(this));
	m_arrGameStates.push_back((GameState*)new GameStateTypeA(this, _T("Resource\\Level1\\Map1.dat")));

	//--

	mBiz_bEnterNextState = true;
	mBiz_bExitCurrentState = false;
	// --
}

MainGame::~MainGame(void)
{
	m_MemDC.DeleteDC();
	m_MemBitmap.DeleteObject();
}

GameState *MainGame::GetGameState(int _gsID)
{
	GameState *_gs = NULL;
	for (unsigned i = 0; i < m_arrGameStates.size(); ++i)
	{
		_gs = m_arrGameStates[i];
		if (_gs->GAME_STATE_DEF == _gsID)
		{
			return _gs;
		}
	}

	return NULL;
}

void MainGame::mBiz_SwitchState(int stateID)
{
	//mBiz_iCurrentState = stateID;
	mBiz_bExitCurrentState = true;
}

void MainGame::mBiz_SendMessage(int message)
{
	GameState *_gs = GetGameState(mBiz_iCurrentState);
	if (_gs != NULL)
	{
		_gs->StateHandler(message, pDC, m_keys);
	}
}

void MainGame::GameLoop()
{
	while (m_playing)
	{
		// xử lý khi mới vào State
		if (mBiz_bEnterNextState)
		{
			mBiz_bEnterNextState = false;
			mBiz_SendMessage(cDef::MESSAGE_ENTER);
		}

		// xử lý logic trong 1 vòng lặp Game
		mBiz_SendMessage(cDef::MESSAGE_UPDATE);

		if (mBiz_bExitCurrentState)
		{
			mBiz_SendMessage(cDef::MESSAGE_EXIT);
			mBiz_bExitCurrentState = false;
			mBiz_bEnterNextState = true;
		}
		else
			mBiz_SendMessage(cDef::MESSAGE_PAINT);

		::Sleep(iSleepTime);
	}
}

void MainGame::KeyPressed(int iKey)
{
	m_keys |= iKey;
}

void MainGame::KeyRelease(int iKey)
{
	m_keys &= ~iKey;
}

void MainGame::SetPDC(CDC *dc)
{
	m_MemDC.DeleteDC();
	m_MemBitmap.DeleteObject();

	pDC = dc;

	// tạo MemDC:
	int nScreenWidth = ::GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = ::GetSystemMetrics(SM_CYSCREEN);

	m_MemDC.CreateCompatibleDC(pDC);
	m_MemBitmap.CreateCompatibleBitmap(pDC, nScreenWidth, nScreenHeight);
	m_pOldBitmap = m_MemDC.SelectObject(&m_MemBitmap);
}