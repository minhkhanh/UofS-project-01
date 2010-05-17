#pragma once

#include "stdafx.h"
#include "GameState.h"
#include "MyBitmap.h"
#include "cDef.h"
#include "0812223-0812239.h"
#include "Sprite.h"
#include "GameKeys.h"
#include "MainGame.h"
#include "TypeAMonster.h"

#define BASE_HEIGHT 24
#define BASE_WIDTH 24
#define LOGIC_SCREEN_WIDTH 16
#define LOGIC_SCREEN_HEIGHT 20

class TypeAMonster;

class GameStateTypeA :public GameState
{
public:
	MyBitmap *imgBG;
	Sprite *sprTiles;
	Sprite *sprOcegrine;

	int iMapLogicHeight, iMapLogicWidth, iMainX, iMainY;
	int m_iCurrScreenFramePos;	// cho biết vị trí bắt đầu của khung map hiện tại, ak

	vector<vector<int>> vMap;
	vector<TypeAMonster*> m_vMonster;

	GameStateTypeA(MainGame *_mg, TCHAR * pszPath);
	virtual ~GameStateTypeA(void);

	void PaintMap(int iX, int iY, Sprite *sprImage, CDC *pDC);
	// hàm vẽ quái thú, ak
	void RunMonster();

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);
};
