#include "StdAfx.h"
#include "TypeAObject.h"

TypeAObject::TypeAObject(void)
{
}

TypeAObject::TypeAObject(Sprite *sprImage)
{
	m_pSprite = sprImage;

	m_iIsDead = m_iIsJump = m_iIsFall = 0;
}

TypeAObject::~TypeAObject(void)
{
	if (m_pSprite != NULL)
		delete m_pSprite;
}

int TypeAObject::GetWidth()
{
	return m_pSprite->Width;
}

int TypeAObject::GetHeight()
{
	return m_pSprite->Height;
}

int TypeAObject::GetCenterX()
{
	return (2*m_iLeft +  m_pSprite->Width) / 2;
}

int TypeAObject::GetBottom()
{
	return m_iTop + m_pSprite->Height;
}

int TypeAObject::GetRight()
{
	return m_iLeft + m_pSprite->Width;
}