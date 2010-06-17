#pragma once

#include "Functions.h"

#include "gamestate.h"

#define MAX_SETTINGS_ITEM 2
#define SOUND_ON	0
#define SOUND_OFF	1

class GameStateSettings :	public GameState
{
private:
	MyBitmap *m_pBackGroundBMP;
	vector<LPCTSTR> m_vSettingText;
	int m_iCurrItem;

public:
	GameStateSettings(MainGame* mg);
	virtual ~GameStateSettings(void);

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);

	void TextSettingOut();
};
