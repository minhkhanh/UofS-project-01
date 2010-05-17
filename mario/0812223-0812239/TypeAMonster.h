#pragma once

#include "stdafx.h"
#include "GameState.h"
#include "MyBitmap.h"
#include "cDef.h"
#include "0812223-0812239.h"
#include "Sprite.h"
#include "GameKeys.h"
#include "MainGame.h"

class TypeAMonster
{
public:
	TypeAMonster(void);
	TypeAMonster(Sprite *sprImage, int iPos);
	~TypeAMonster(void);

	Sprite *m_pSprite;
	int m_iPos;
	//int m_iY;
	bool m_bIsDead;
	//bool m_bIsAppeared;
};
