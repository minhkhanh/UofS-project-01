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

#define SCREEN_WIDTH		380
#define SCREEN_HEIGHT		480

class GameStateTypeA;
class TypeAMonster;

class GameStateTypeA :public GameState
{
public:
	MyBitmap *imgBG;
	Sprite *sprTiles;
	Sprite *sprOcegrine;

	int iMapLogicHeight, iMapLogicWidth, iMainX, iMainY;

	vector<vector<int>> vMap;
	vector<TypeAMonster*> m_vMonster;

	GameStateTypeA(MainGame *_mg, TCHAR * pszPath);
	virtual ~GameStateTypeA(void);

	void PaintMap(int iX, int iY, Sprite *sprImage, CDC *pDC);
	void akPaintMap();

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);



	// ak bổ sung:

	int m_iCurrScreenFrameX;	// cho biết vị trí bắt đầu của khung map hiện tại, ak
	int m_iOcegrineX, m_iOcegrineY;	// tọa độ nhân vật chính (logical)
	int m_iIsJump;					// biến trạng thái nhảy
	int m_iIsFall;					// biến trạng thái rơi

	// hàm vẽ quái thú, ak
	void akPaintMonster();
	// hàm lấy tọa độ X của điểm giữa màn hình game
	int ScreenFrameCenterX();
	// xét xem tại tọa độ cho trước trên màn hình game có vật cản hay không
	bool IsBarrier(int i, int jFrame);
	// xác định từ iX chiếu xuống có điểm tựa hay ko
	int CalcY(int iX);
};
