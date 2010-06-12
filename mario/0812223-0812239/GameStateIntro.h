#pragma once

#include "Functions.h"

#include "GameState.h"

class MainGame;
class MyScriptMap;

class GameStateIntro: public GameState
{
private:
	MyScriptMap * m_pScriptText;
	MyBitmap * m_pBGR;
	bool bNeedRedraw;
	int m_iStep;

public:
	GameStateIntro(MainGame *_mg, TCHAR szText[], LPCTSTR szBGR);
	virtual ~GameStateIntro(void);

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);
};
