#include "StdAfx.h"
#include "GameState.h"

GameState::GameState(void): m_iGameStateDef(-1)
{
}

GameState::~GameState(void)
{
}

void GameState::StateHandler(int message, CDC *pDC, int keys)
{
	if (message == cDef::MESSAGE_ENTER)
		MessageEnter(message);
	else if (message == cDef::MESSAGE_UPDATE)
		MessageUpdate(message, keys);
	else if (message == cDef::MESSAGE_PAINT)
		MessagePaint(message, pDC);
	else if (message == cDef::MESSAGE_EXIT)
		MessageExit(message, pDC);
}

int GameState::GetGameStateDef()
{
	return m_iGameStateDef;
}