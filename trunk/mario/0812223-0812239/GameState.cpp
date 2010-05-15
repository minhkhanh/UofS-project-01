#include "StdAfx.h"
#include "GameState.h"

GameState::GameState(void)
{
	GAME_STATE_DEF = -1;
}

GameState::~GameState(void)
{
}

void GameState::StateHandler(int message, CDC *pDC, int keys)
{
	if (message == cDef::MESSAGE_ENTER)
	{
		MessageEnter(message);
	}

	if (message == cDef::MESSAGE_UPDATE)
	{
		MessageUpdate(message, keys);
	}

	if (message == cDef::MESSAGE_PAINT)
	{
		MessagePaint(message, pDC);
	}
}