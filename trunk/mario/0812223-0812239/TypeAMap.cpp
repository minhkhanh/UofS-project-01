#include "StdAfx.h"
#include "TypeAMap.h"

TypeAMap::TypeAMap(void)
{
}

TypeAMap::TypeAMap(char *strMapPath, int idImg, GameStateTypeA* stateTypeA)
{
	m_pMapPath = _strdup(strMapPath);
	m_idBackground = idImg;
	m_pStateTypeA = stateTypeA;
}

TypeAMap::~TypeAMap(void)
{
}

void TypeAMap::LoadMap()
{
	FILE   *f;
	if ((f = fopen(m_pMapPath, "rt")) == NULL)
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
			if (pTemp[i] == '?') 
				vMapRow.push_back(-1);
			else
			{
				//if	(pTemp[i] == 'a')		// bổ sung quái vật
				//{
				//	Sprite *sprMonster = new Sprite(0,0,24,32,0,3,0, new MyBitmap((LPCTSTR)IDIMG_MONSTER07));
				//	m_vMonster.push_back(new TypeAMonster(sprMonster, indexCell));
				//}

				vMapRow.push_back(pTemp[i]-65);
			}

			++indexCell;
		}

		m_vData.push_back(vMapRow);
	}

	fclose(f);

	// load ảnh nền
	m_pBackground = new MyBitmap((LPCTSTR)m_idBackground);

	// chuyển sang đơn vị pixel
	m_iMapWidth *= BASE_WIDTH;
	m_iMapHeight *= BASE_HEIGHT;
}

void TypeAMap::PaintMap()
{
	m_pBackground->DrawTransparent(&(m_pStateTypeA->mg->m_MemDC), 0, 0, RGB(255,255,255));

	for (int i = 0; i < SCREEN_HEIGHT; i += BASE_HEIGHT)
		for (int j = 0; j < SCREEN_WIDTH + BASE_WIDTH; j += BASE_WIDTH)
		{
			int jj = j + m_pStateTypeA->m_iCurrScreenX;
			if (jj < 0 || jj >= m_iMapWidth)
				continue;

			CPoint cell = Functions::Pixel2Cell(jj, i);
			int iVal = m_vData[cell.y][cell.x];
			if (iVal != 32 && iVal != -1)		// nếu ô đang xét không phải là quái và không phải rỗng
			{
				m_pStateTypeA->sprTiles->SetPositionFrame(iVal);
				m_pStateTypeA->sprTiles->Render(j-(m_pStateTypeA->m_iCurrScreenX % BASE_WIDTH), i, &(m_pStateTypeA->mg->m_MemDC));
			}
		}
}

int TypeAMap::GetTile(int j, int i)
{
	int result = 0x0;

	if (i < 0)
		return HEAVEN_TILE;		// trên khung màn hình
	if (i >= m_iMapHeight)
		return HELL_TILE;		// dướj khung màn hình

	j += m_pStateTypeA->m_iCurrScreenX;

	if (j < 0)
		return LEFT_SIDE_TILE;		// biên trái
	if (j >= m_iMapWidth)
		return RIGHT_SIDE_TILE;		// biên phải

	CPoint cell = Functions::Pixel2Cell(j, i);

	int iTile = m_vData[cell.y][cell.x];

	if ((iTile >= 0 && iTile <= 6)
		|| (iTile >= 15 && iTile <= 17)
		|| (iTile >= 24 && iTile <= 27))
		result |= HARD_TILE;		// đây là các chướng ngại ko thể đi xuyên qua

	if (iTile == 10)
	{
		result |= ITEM_TILE;		// hộp vật phẩm (hộp dấu ?)
		result |= HARD_TILE;		// hộp này cứng
	}

	if (iTile == 13 || iTile == 14
		|| iTile == 19 || iTile == 20
		|| iTile == 21 || iTile == 22)
		result |= GATE_TILE;		// cổng qua màn

	if (iTile == 11 || iTile == 18)
		result |= DANGEROUS_TILE;		// chướng ngại gây nguy hiểm chết người

	if (iTile == 7 || iTile == 8 || iTile == 9)
		result |= COIN_TILE;			// đồng xu

	return result;
}

int TypeAMap::CalcY(int iX, int iY)
{
	for (int i = iY; i < m_iMapHeight; i += BASE_HEIGHT)
	{
		if (GetTile(iX, i) == HARD_TILE)
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

int TypeAMap::GetOnMapPosition()
{
	if (m_pStateTypeA->GetCurrScreenX() == 0)
		return -1;

	if (m_pStateTypeA->GetCurrScreenX() + SCREEN_WIDTH >= GetMapWidth())
		return 1;

	return 0;
}

void TypeAMap::SetTile(int j, int i, int iTile)
{
	if (i < 0 || i >= m_iMapHeight)
		return;

	j += m_pStateTypeA->m_iCurrScreenX;

	if (j < 0 || j >= m_iMapWidth)
		return;

	CPoint cell = Functions::Pixel2Cell(j,i);
	m_vData[cell.y][cell.x] = iTile;
}