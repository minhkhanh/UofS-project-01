#pragma once

#include "Functions.h"

#include "gamestate.h"

class GameStateHowToPlay :
	public GameState
{
private:
	MyBitmap *m_pBackGroundBMP;
	int m_iCurrPos;

public:
	GameStateHowToPlay(MainGame*);
	~GameStateHowToPlay(void);

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);
};
