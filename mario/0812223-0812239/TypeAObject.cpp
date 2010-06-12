#include "StdAfx.h"
#include "TypeAObject.h"

TypeAObject::TypeAObject(void)
{
	m_iIsFall = 0;
}

TypeAObject::~TypeAObject(void)
{
}

int TypeAObject::GetBottom()
{
	return m_iTop + m_pSprite->GetHeight();
}

int TypeAObject::GetRight()
{
	return m_iLeft + m_pSprite->GetWidth();
}

int TypeAObject::GetLeftCollision(int iScope)
{
	int iTiles = 0x0;
	int iBottom = GetBottom();
	int j = m_iLeft-iScope;


	for (int i = m_iTop; i < iBottom; i += 1)
		iTiles |= m_pMapTypeA->GetTile(j, i);

	return iTiles;
}

int TypeAObject::GetRightCollision(int iScope)
{
	int iTiles = 0x0;
	int iBottom = GetBottom();
	int j = GetRight()+iScope;

	for (int i = m_iTop; i < iBottom; i += 1)
	{
		iTiles |= m_pMapTypeA->GetTile(j, i);
	}

	return iTiles;
}

int TypeAObject::GetBottomCollision(int iScope)
{
	int iTiles = 0x0;
	int iRight = GetRight();
	int i = GetBottom()+iScope;

	for (int j = m_iLeft; j < iRight; j += 1)
	{
		iTiles |= m_pMapTypeA->GetTile(j, i);
	}

	return iTiles;
}

int TypeAObject::GetTopCollision(int iScope)
{
	int iTiles = 0x0;
	int iRight = GetRight();
	int i = m_iTop-iScope;

	for (int j = m_iLeft; j < iRight; j += 1)
	{
		iTiles |= m_pMapTypeA->GetTile(j, i);
	}

	return iTiles;
}

int TypeAObject::GetInnerCollision()
{
	int iTiles = 0x0;
	int iBottom = GetBottom();
	int iRight = GetRight();

	for (int i = m_iTop; i < iBottom; i += 1)
		for (int j = m_iLeft; j < iRight; j += 1)
		{
			iTiles |= m_pMapTypeA->GetTile(j, i);
		}

		return iTiles;
}

void TypeAObject::RenderSprite(CDC *pDC)
{
	if (IsInSight())
		m_pSprite->Render(m_iLeft - m_pMapTypeA->GetCurrScreenX(), m_iTop, pDC);
}

int TypeAObject::OnFall()
{
	if (m_iIsFall != 0)
	{
		//int i = cDef::OCEGRINE_MOVE_PIXELS;
		//for ( ; i > 0; --i)
		//	if (!(GetBottomCollision(i) & cDef::HARD_TILE))
		//	{
		//		Functions::Move(m_iTop, 0, i);
		//		break;
		//	}

		int i = 1;
		for ( ; i <= cDef::OCEGRINE_MOVE_PIXELS*2; ++i)
		{
			if (GetBottomCollision(i) & cDef::HARD_TILE)
			{
				break;
			}
		}

		--i;
		m_iTop += i;

			if (i != cDef::OCEGRINE_MOVE_PIXELS*2)
				m_iIsFall = 0;

			return 1;
	}

	return 0;
}

int TypeAObject::GetLeft()
{
	return m_iLeft;
}

int TypeAObject::GetTop()
{
	return m_iTop;
}

void TypeAObject::SetLeft(int iVal)
{
	m_iLeft = iVal;
}

int TypeAObject::IsInSight()
{
	return (GetRight() >= m_pMapTypeA->GetCurrScreenX() && m_iLeft <= m_pMapTypeA->GetCurrScreenX()+cDef::SCREEN_WIDTH
		&& GetTop() >= 0 && GetBottom() <= m_pMapTypeA->GetMapHeight());
}

int TypeAObject::GetCurrScreenX()
{
	int iResult = m_iLeft - Functions::GetScreenCenterX();

	if (iResult < 0)
		return iResult = 0;

	return iResult;
}

int TypeAObject::GetWidth()
{
	return m_pSprite->GetWidth();
}

int TypeAObject::GetFall()
{
	return m_iIsFall;
}

Sprite *TypeAObject::GetSprite()
{
	return m_pSprite;
}

void TypeAObject::SetTop( int iVal )
{
	m_iTop = iVal;
}