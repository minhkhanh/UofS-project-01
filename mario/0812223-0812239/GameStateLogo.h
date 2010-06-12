#pragma once

#include "Functions.h"

#include "GameState.h"

class MainGame;

class GameStateLogo: public GameState
{
public:
	GameStateLogo(MainGame *_mg);
	~GameStateLogo(void);

public:
	MyBitmap *imgBG;		// Lưu trữ ảnh background
	MyBitmap * m_pTenGame;
	Sprite *sprMenuIcon;	// Demo Sprite

	int m_iX;

	// Nạp chồng hàm xử lý các sự kiện tương ứng
	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);
};
