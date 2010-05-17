#include "StdAfx.h"
#include "TypeAMonster.h"

TypeAMonster::TypeAMonster(void)
{
}

TypeAMonster::TypeAMonster(Sprite *sprImage, int iPos)
{
	m_pSprite = sprImage;
	m_iPos = iPos;
	m_bIsDead = false;
	//m_bIsAppeared = false;
}

TypeAMonster::~TypeAMonster(void)
{
	if (m_pSprite != NULL)
		delete m_pSprite;
}
