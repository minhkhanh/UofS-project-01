#pragma once

#include "Functions.h"

#include "TypeAObject.h"

#define VERTICAL	0x01
#define MOVE_UP		0x03
#define MOVE_DOWN	0x05

#define HORIZON		0x08
#define MOVE_RIGHT	0x18
#define MOVE_LEFT	0x28

#define MONSTER_MOVE_PIXELS		1

class TypeAMonster: public TypeAObject
{
private:
	int m_iStatus;
	int m_iMoveDirection;

public:
	TypeAMonster(void);
	TypeAMonster(Sprite *pSprite, TypeAMap *pCurrMap, int iLeft, int iTop, int iMoveDirection);
	virtual ~TypeAMonster(void);

	void Move();
	void MoveUp();
	void MoveDown();
	void MoveLeft();
	void MoveRight();

	void PreviousMoveFrame();
	void NextMoveFrame();

	void Activate();
	int GetStatus();

	void InnerCollisionHandle();
};
