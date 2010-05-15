#pragma once

#include "stdafx.h"
#include "GameState.h"
#include "MyBitmap.h"
#include "cDef.h"
#include "0812223-0812239.h"
#include "Sprite.h"
#include "GameKeys.h"
#include "MainGame.h"
#include <vector>

#define BASE_HEIGHT 24
#define BASE_WIDTH 24
#define iLogicScreenWidth 16
#define iLogicScreenHeight 20
using namespace std;
class GameStateTypeA :public GameState
{
public:
	MyBitmap *imgBG;
	Sprite *sprTiles;
	vector<vector<int>> vMap;
	int iMapLogicHeight, iMapLogicWidth, iMainX, iMainY;
	GameStateTypeA(MainGame *_mg, TCHAR * pszPath);
	virtual ~GameStateTypeA(void);

	void PaintMap(int iX, int iY, Sprite *sprImage, CDC *pDC);

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
};
