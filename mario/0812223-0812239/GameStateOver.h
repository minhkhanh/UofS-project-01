#pragma once

#include "Functions.h"

#include "gamestate.h"

class MyScriptMap;

class GameStateOver :	public GameState
{
private:
	MyScriptMap * m_pScriptText;
	MyBitmap *m_pBackGroundBMP;
	bool bNeedRedraw;

	int m_iStep;

public:
	GameStateOver(MainGame *mg, TCHAR* szScriptPath);
	virtual ~GameStateOver(void);

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);
};
