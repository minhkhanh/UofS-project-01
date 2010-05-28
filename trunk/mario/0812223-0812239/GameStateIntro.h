#pragma once

#include "stdafx.h"
#include "MyScriptMap.h"
#include "GameState.h"
#include "MyBitmap.h"
#include "cDef.h"
#include "0812223-0812239.h"
#include "Sprite.h"
#include "GameKeys.h"
#include "MainGame.h"

class GameStateIntro: public GameState
{
public:
	MyScriptMap * m_pScriptText;
	GameStateIntro(MainGame *_mg, TCHAR szText[]);
	virtual ~GameStateIntro(void);

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);
};
