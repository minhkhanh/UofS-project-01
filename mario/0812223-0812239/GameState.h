#pragma once

#ifndef _GameState_
#define _GameState

#include "cDef.h"

class MainGame;
class GameState;

class GameState
{
public:
	GameState(void);
	~GameState(void);

public:
	MainGame *mg;
	int GAME_STATE_DEF;		// hằng số định nghĩa trạng thái

	virtual void MessageEnter(int message) = 0;
	virtual void MessageUpdate(int message, int keys) = 0;
	virtual void MessagePaint(int message, CDC *pDC) = 0;

	// Handler cho các hàm xử lý tương ứng khi nhận message
	void StateHandler(int mesage, CDC *pDC, int keys);
};

#endif