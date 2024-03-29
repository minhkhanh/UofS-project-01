#include "StdAfx.h"
#include "TypeAMap.h"

#include "MainGame.h"
#include "GameStateTypeA.h"
#include "TypeAMonster.h"
#include "TypeAOcegrine.h"

TypeAMap::TypeAMap(void)
{
}

TypeAMap::TypeAMap(char *strMapPath, int idImg, GameStateTypeA* stateTypeA)
{
	m_strMapPath = _strdup(strMapPath);
	m_idBackground = idImg;
	m_pStateTypeA = stateTypeA;
}

TypeAMap::~TypeAMap(void)
{
}

void TypeAMap::LoadMap()
{
	FILE   *f;
	if ((f = fopen(m_strMapPath, "rt")) == NULL)
		exit(0);

	char pTemp[INPUT_MAX_LEN];
	int indexCell = 0;
	m_iMapWidth = m_iMapHeight = 0;
	while (fgets(pTemp, INPUT_MAX_LEN, f))
	{
		++m_iMapHeight;		// tính độ cao map

		vector<int> vMapRow;
		m_iMapWidth = strlen(pTemp);
		for (int i = 0; i < m_iMapWidth; ++i)
		{
			if (pTemp[i] >= 'A' && pTemp[i] <= 95) 
				vMapRow.push_back(pTemp[i]-65);
			else
			{
				if	(pTemp[i] >= 'a' && pTemp[i] <= 'z')		// bổ sung quái vật
				{
					int iCellX = indexCell % m_iMapWidth;
					int iCellY = indexCell / m_iMapWidth;
					// (lúc này m_iMapWidth vẫn là đơn vị ô)

					CPoint pointPixel = Functions::Cell2Pixel(iCellX, iCellY);

					if (pTemp[i] == 'a')
						m_vMonster.push_back(new TypeAMonster(new Sprite(0,0,24,32,1,8,2, new MyBitmap((LPCTSTR)IDIMG_MONSTER07), 1), this, pointPixel.x, pointPixel.y-8, MOVE_LEFT));
					else if (pTemp[i] == 'e')
						m_vMonster.push_back(new TypeAMonster(new Sprite(0,0,24,32,1,8,2, new MyBitmap((LPCTSTR)IDIMG_MONSTER08), 1), this, pointPixel.x, pointPixel.y-8, MOVE_UP));
				}

				vMapRow.push_back(31);	// 31: ko có gì
			}

			++indexCell;
		}

		m_vData.push_back(vMapRow);
	}

	fclose(f);

	// load ảnh nền
	m_pBackground = new MyBitmap((LPCTSTR)m_idBackground);

	// chuyển từ đơn vị ô [cDef::BASE_WIDTH x cDef::BASE_HEIGHT] sang đơn vị pixel
	m_iMapWidth *= cDef::BASE_WIDTH;
	m_iMapHeight *= cDef::BASE_HEIGHT;
}

void TypeAMap::PaintMap(CDC* pDC)
{
	m_pBackground->DrawTransparent(pDC, 0, 0, RGB(255,255,255));

	for (int i = 0; i < cDef::SCREEN_HEIGHT; i += cDef::BASE_HEIGHT)
		for (int j = 0; j < cDef::SCREEN_WIDTH + cDef::BASE_WIDTH; j += cDef::BASE_WIDTH)
		{
			TypeAOcegrine *pOcegrine = m_pStateTypeA->m_pOcegrine;

			int iCurrScreenX = pOcegrine->GetCurrScreenX();

			int jj = j + iCurrScreenX;
			if (jj < 0 || jj >= m_iMapWidth)
				continue;

			CPoint cell = Functions::Pixel2Cell(jj, i);
			int iVal = m_vData[cell.y][cell.x];//Functions::GetBits(m_vData[cell.y][cell.x], 0, 4);//GetData(cell.y, cell.x);

			if (iVal >= 0 && iVal <= 30)		// nếu ô đang xét là tile của map
			{
				Sprite *pTiles = m_pStateTypeA->m_pTiles;

				pTiles->SetPositionFrame(iVal);
				pTiles->Render(j-(iCurrScreenX % cDef::BASE_WIDTH), i, pDC);
			}
		}
}

int TypeAMap::GetTile(int j, int i)
{
	int result = 0x0;

	if (i < 0)
		return cDef::HEAVEN_TILE;		// trên khung màn hình
	if (i >= m_iMapHeight)
		return cDef::HELL_TILE;		// dướj khung màn hình

	if (j < 0)
		return cDef::LEFT_SIDE_TILE;		// biên trái
	if (j >= m_iMapWidth)
		return cDef::RIGHT_SIDE_TILE;		// biên phải

	CPoint cell = Functions::Pixel2Cell(j, i);

	int iTile = m_vData[cell.y][cell.x];//Functions::GetBits(m_vData[cell.y][cell.x], 0, 4);
	//if (Functions::GetBit(m_vData[cell.y][cell.x], 12))
	//{
	//	iTile |= MONSTER_TILE;
	//}

	if ((iTile >= 0 && iTile <= 6)
		|| (iTile >= 15 && iTile <= 17)
		|| (iTile >= 24 && iTile <= 27))
		result |= cDef::HARD_TILE;		// đây là các chướng ngại ko thể đi xuyên qua

	if (iTile == 10)
	{
		result |= cDef::ITEM_TILE;		// hộp vật phẩm (hộp dấu ?)
		result |= cDef::HARD_TILE;		// hộp này cứng
	}

	if (iTile == 13 || iTile == 14
		|| iTile == 19 || iTile == 20
		|| iTile == 21 || iTile == 22
		|| iTile == 29 || iTile == 30)
		result |= cDef::GATE_TILE;		// cổng qua màn

	if (iTile == 11 || iTile == 18)
		result |= cDef::DANGEROUS_TILE;		// chướng ngại gây nguy hiểm chết người

	if (iTile == 7 || iTile == 8 || iTile == 9)
		result |= cDef::COIN_TILE;			// đồng xu

	return result;
}

int TypeAMap::CalcY(int iX, int iY)
{
	for (int i = iY; i < m_iMapHeight; i += cDef::BASE_HEIGHT)
	{
		if (GetTile(iX, i) == cDef::HARD_TILE)
			return i;
	}

	return -1;		// từ trên chiếu xuống không có điểm tựa
}

int TypeAMap::GetMapWidth()
{
	return m_iMapWidth;
}

int TypeAMap::GetMapHeight()
{
	return m_iMapHeight;
}

void TypeAMap::SetTile(int j, int i, int iTile)
{
	if (i < 0 || i >= m_iMapHeight)
		return;

	if (j < 0 || j >= m_iMapWidth)
		return;

	CPoint cell = Functions::Pixel2Cell(j,i);
	m_vData[cell.y][cell.x] = iTile;
}

int TypeAMap::MoveMonsters()
{
	for (int i = 0; i < m_vMonster.size(); ++i)
	{
		m_vMonster[i]->Move();

		int iTmp = m_vMonster[i]->InnerCollisionHandle();

		if (iTmp == 1)
			return 1;
		else if (iTmp == -1)
		{
			GameSound::Play(EXPLOSION_SOUND);		// đạp đầu quái
			m_pStateTypeA->m_pOcegrine->Jump();		// tưng lên
		}
	}

	return 0;
}

void TypeAMap::ThrowMonsters(CDC* pDC)
{
	for (int i = 0; i < m_vMonster.size(); ++i)
	{
		m_vMonster[i]->RenderSprite(pDC);
	}
}

int TypeAMap::GetCurrScreenX()
{
	return m_pStateTypeA->m_pOcegrine->GetCurrScreenX();
}

int TypeAMap::GetCurrMapIndex()
{
	return m_pStateTypeA->m_iCurrMap;
}

GameStateTypeA *TypeAMap::GetGameStateTypeA()
{
	return m_pStateTypeA;
}

void TypeAMap::ActivateMonsters()
{
	for (int i = 0; i < m_vMonster.size(); ++i)
	{
		if (m_vMonster[i]->IsInSight() && m_vMonster[i]->GetStatus() == 0)
			m_vMonster[i]->Activate();
	}
}

void TypeAMap::ReleaseData()
{
	for (unsigned u = 0; u < m_vData.size(); ++u)
		m_vData[u].clear();

	m_vData.clear();

	m_vMonster.clear();
}

//void TypeAMap::KillMonsters(TypeAOcegrine *pOcegrine)
//{
//	for (int i = 0; i < m_vMonster.size(); ++i)
//	{
//
//	}
//}

//int TypeAMap::GetData(int y, int x)
//{
//	if (y >= 0 && y < m_vData.size())
//		if (x >= 0 && x < m_vData[y].size())
//			return m_vData[y][x] & 31;
//
//	return 31;
//}

//void TypeAMap::MarkMonster( int index)
//{
//	if (m_vMonster[index]->GetStatus() != 1)
//		return;
//
//	int iLeft = m_vMonster[index]->GetLeft();
//	int iTop = m_vMonster[index]->GetTop();
//	int iBottom = m_vMonster[index]->GetBottom();
//	int iRight = m_vMonster[index]->GetRight();
//
//	for (int i = iTop; i < iBottom; i += cDef::BASE_HEIGHT)
//		for (int j = iLeft; j < iRight; j += cDef::BASE_WIDTH)
//		{
//			CPoint cellMap = Functions::Pixel2Cell(j,i);
//
//			if (cellMap.y >= 20)
//				continue;
//
//			m_vData[cellMap.y][cellMap.x] |= 4064;		// a = 1111 111a aaaa
//
//			int iVal = (index & 127) << 5;				// b = bbbb bbb0 0000
//			iVal |= 31;									// b = bbbb bbb1 1111
//
//														// a = 1111 111a aaaa
//														// b = bbbb bbb1 1111
//
//			m_vData[cellMap.y][cellMap.x] &= iVal;		// a & b
//			m_vData[cellMap.y][cellMap.x] |= 1 << 12;	// bật bit cờ
//		}
//}
//
//void TypeAMap::UnmarkMonster( int index )
//{
//	if (m_vMonster[index]->GetStatus() != 1)
//		return;
//
//	int iLeft = m_vMonster[index]->GetLeft();
//	int iTop = m_vMonster[index]->GetTop();
//	int iBottom = m_vMonster[index]->GetBottom();
//	int iRight = m_vMonster[index]->GetRight();
//
//	for (int i = iTop; i < iBottom; i += cDef::BASE_HEIGHT)
//		for (int j = iLeft; j < iRight; j += cDef::BASE_WIDTH)
//		{
//			CPoint cellMap = Functions::Pixel2Cell(j,i);
//
//			if (cellMap.y >= 0 && cellMap.y < 20)
//				Functions::SetBit(m_vData[cellMap.y][cellMap.x], 12, 0);
//		}
//}