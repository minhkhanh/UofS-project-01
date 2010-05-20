#pragma once

#include "stdafx.h"
#include "GameState.h"
#include "MyBitmap.h"
#include "cDef.h"
#include "0812223-0812239.h"
#include "Sprite.h"
#include "GameKeys.h"
#include "MainGame.h"

class TypeAObject
{
public:
	TypeAObject(void);
	TypeAObject(Sprite *sprImage);
	~TypeAObject(void);

	Sprite *m_pSprite;

	// vị trí đối tượng
	int m_iTop;
	int m_iLeft;
	int GetBottom();
	int GetRight();

	// hàm lấy các kích thước của đối tượng
	int GetWidth();
	int GetHeight();

	// hàm lấy trung tâm
	int GetCenterX();

	int m_iIsDead;			// cho biết đối tượng đã chết hay còn sống
	int m_iIsJump;			// biến trạng thái nhảy
	int m_iIsFall;			// biến trạng thái rơi
};
