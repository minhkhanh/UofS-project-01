#include "StdAfx.h"
#include "TypeAMonster.h"

TypeAMonster::TypeAMonster(void)
{
}

TypeAMonster::TypeAMonster(Sprite *pSprite, TypeAMap *pCurrMap, int iLeft, int iTop, int iMoveDirection)
{
	m_pSprite = pSprite;
	m_pMapTypeA = pCurrMap;

	m_iLeft = iLeft;
	m_iTop = iTop;

	m_iMoveDirection = iMoveDirection;
	m_iStatus = 0;
}

TypeAMonster::~TypeAMonster(void)
{
}

void TypeAMonster::Move()
{
	if (m_iStatus != 1)
		return;

	if (m_iMoveDirection & VERTICAL)
	{
		if (m_iMoveDirection == MOVE_DOWN)
			MoveDown();
		else if (m_iMoveDirection == MOVE_UP)
			MoveUp();

		NextMoveFrame();
	}
	else if (m_iMoveDirection & HORIZON)
	{
		if (m_iMoveDirection == MOVE_RIGHT)
			MoveRight();
		else if (m_iMoveDirection == MOVE_LEFT)
			MoveLeft();

		if (!(GetBottomCollision(1) & HARD_TILE))
			m_iIsFall = 1;

		OnFall();
		InnerCollisionHandle();
	}
}

void TypeAMonster::MoveUp()
{
	int i = MONSTER_MOVE_PIXELS;
	for ( ; i > 0; --i)
		if (!(GetTopCollision(i) & (HARD_TILE | HEAVEN_TILE)))
		{
			Functions::Move(m_iTop, 0, -i);
			break;
		}

	if (i != MONSTER_MOVE_PIXELS)
	{
		m_iMoveDirection = MOVE_DOWN;
	}
}

void TypeAMonster::MoveDown()
{
	int i = MONSTER_MOVE_PIXELS;
	for ( ; i > 0; --i)
		if (!(GetBottomCollision(i) & (HARD_TILE | HELL_TILE)))
		{
			Functions::Move(m_iTop, 0, i);
			break;
		}

	if (i != MONSTER_MOVE_PIXELS)
	{
		m_iMoveDirection = MOVE_UP;
	}
}

void TypeAMonster::MoveLeft()
{
	if (m_pSprite->GetDirection() == 1)
		m_pSprite->TurnBack();

	PreviousMoveFrame();

	int i = MONSTER_MOVE_PIXELS;
	for ( ; i > 0; --i)
		if (!(GetLeftCollision(i) & (HARD_TILE | LEFT_SIDE_TILE)))
		{
			Functions::Move(m_iLeft, 0, -i);
			break;
		}

	if (i != MONSTER_MOVE_PIXELS)
	{
		m_iMoveDirection = MOVE_RIGHT;
	}
}

void TypeAMonster::MoveRight()
{
	if (m_pSprite->GetDirection() == -1)
		m_pSprite->TurnBack();

	NextMoveFrame();

	int i = MONSTER_MOVE_PIXELS;
	for ( ; i > 0; --i)
		if (!(GetRightCollision(i) & (HARD_TILE | RIGHT_SIDE_TILE)))
		{
			Functions::Move(m_iLeft, 0, i);
			break;
		}

	if (i != MONSTER_MOVE_PIXELS)
	{
		m_iMoveDirection = MOVE_LEFT;
	}
}

void TypeAMonster::PreviousMoveFrame()
{
	m_pSprite->PreviousFrame();

	if (m_pSprite->GetPositionFrame() < 4)
		m_pSprite->SetPositionFrame(6);
}

void TypeAMonster::NextMoveFrame()
{
	m_pSprite->NextFrame();

	if (m_pSprite->GetPositionFrame() > 3)
		m_pSprite->SetPositionFrame(1);
}

void TypeAMonster::Activate()
{
	m_iStatus = 1;
}

void TypeAMonster::InnerCollisionHandle()
{
	int iTiles = GetInnerCollision();

	if (iTiles & HELL_TILE)
		m_iStatus = -1;
}

int TypeAMonster::GetStatus()
{
	return m_iStatus;
}