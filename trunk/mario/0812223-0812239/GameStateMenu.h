#pragma once

#include "Functions.h"

#include "GameState.h"

class MainGame;

#define MAX_ITEM	2
#define MENU_STATUS_SIZE	15

class GameStateMenu :	public GameState
{
private:
	MyBitmap *m_pBackGround;		// Lưu trữ ảnh background
	vector<LPCTSTR> m_vMenuText;
	int m_iCurrMenuItem;

public:
	GameStateMenu(MainGame *_mg);
	virtual ~GameStateMenu(void);

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);

	void TextMenuOut();
	void DrawMenuStatusBar();
};
