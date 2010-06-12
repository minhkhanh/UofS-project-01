#pragma once

#include "Functions.h"

#include "gamestate.h"

class GameStateHowToPlay :
	public GameState
{
private:
	vector<MyBitmap*> m_vBackGround;

public:
	GameStateHowToPlay(MainGame*);
	~GameStateHowToPlay(void);

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);
};
