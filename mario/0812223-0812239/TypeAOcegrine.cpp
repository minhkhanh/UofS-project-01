#include "StdAfx.h"
#include "TypeAOcegrine.h"

TypeAOcegrine::TypeAOcegrine(void)
{
}

TypeAOcegrine::TypeAOcegrine(Sprite *sprImage, TypeAMap *pCurrMap)
{
	m_pSprite = sprImage;
	m_iIsJump = 0;
	m_iIsFall = 1;
	m_pMapTypeA = pCurrMap;
}

TypeAOcegrine::~TypeAOcegrine(void)
{
}

int TypeAOcegrine::GetBottom()
{
	return m_iTop + m_pSprite->Height;
}

int TypeAOcegrine::GetRight()
{
	return m_iLeft + m_pSprite->Width;
}

int TypeAOcegrine::GetLeftCollision(int iScope)
{
	int iTiles = 0x0;
	int iBottom = GetBottom();
	int j = m_iLeft-iScope;

	for (int i = m_iTop; i < iBottom; i += 1)
	{
		iTiles |= m_pMapTypeA->GetTile(j, i);
	}

	return iTiles;
}

int TypeAOcegrine::GetRightCollision(int iScope)
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

int TypeAOcegrine::GetBottomCollision(int iScope)
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

int TypeAOcegrine::GetTopCollision(int iScope)
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

int TypeAOcegrine::GetInnerCollision()
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

void TypeAOcegrine::SetJump(int iJumpStep)
{
	m_iIsJump = iJumpStep * MOVE_PIXELS;
}

int TypeAOcegrine::GetOnScreenPosition()
{
	int x = Functions::GetScreenCenterX();

	if (m_iLeft < x-MOVE_PIXELS/2)
		return -1;
	else if (m_iLeft > x+MOVE_PIXELS/2)
		return 1;
	else
		return 0;
}

void TypeAOcegrine::MoveLeft(int &iCurrScreenX)
{
	if (m_pSprite->GetSide() == true)
		m_pSprite->TurnBack();

	if (m_iIsJump == 0 && m_iIsFall == 0)
	{
		m_pSprite->PreviousFrame();
		if (m_pSprite->m_currentFrame < 10)
			m_pSprite->m_currentFrame = 13;
	}

	if (GetOnScreenPosition() != 0)	// đi qua trái khi nhân vật không nằm giữa màn hình
	{
		for (int i = MOVE_PIXELS; i > 0; --i)
			if (!(GetLeftCollision(i) & (HARD_TILE | LEFT_SIDE_TILE)))
			{
				Functions::Move(m_iLeft, 0, -i);
				break;
			}
	}
	else										// nhân vật đang nằm giữa màn hình
	{
		if (m_pMapTypeA->GetOnMapPosition() >= 0)		// khung màn hình ko nằm ở vị trí bắt đầu
		{
			for (int i = MOVE_PIXELS; i > 0; --i)
				if (!(GetLeftCollision(i) & HARD_TILE))
				{
					Functions::Move(iCurrScreenX, 0, -i);
					if (iCurrScreenX < 0)				// di chuyển màn hình quá lố
					{
						Functions::Move(m_iLeft, 0, iCurrScreenX);	// di chuyển nhân vật
						iCurrScreenX = 0;							// trả màn hình về vị trí bắt đầu
					}
					break;
				}
		}
		else										// khung màn hình ở vị trí bắt đầu
		{
			for (int i = MOVE_PIXELS; i > 0; --i)
				if (!(GetLeftCollision(i) & HARD_TILE))
				{
					Functions::Move(m_iLeft, 0, -i);
					break;
				}
		}
	}

	if (m_iIsJump == 0 && m_iIsFall == 0)			// khi không đang nhảy lên và không đang rơi xuống
	{
		if (!(GetBottomCollision(1) & HARD_TILE))
			m_iIsFall = 1;
	}
}

void TypeAOcegrine::MoveRight(int &iCurrScreenX)
{
	if (m_pSprite->GetSide() == false)
		m_pSprite->TurnBack();

	if (m_iIsJump == 0 && m_iIsFall == 0)
	{
		m_pSprite->NextFrame();
		if (m_pSprite->m_currentFrame > 3)
			m_pSprite->m_currentFrame = 0;
	}

	if (GetOnScreenPosition() != 0)	// khi nhân vật không nằm giữa màn hình, di chuyển nhân vật
	{
		for (int i = MOVE_PIXELS; i > 0; --i)
			if (!(GetRightCollision(i) & (HARD_TILE | RIGHT_SIDE_TILE)))
			{
				Functions::Move(m_iLeft, 0, i);
				break;
			}
	}
	else										// nhân vật đang nằm giữa màn hình
	{
		if (m_pMapTypeA->GetOnMapPosition() <= 0)			// di chuyển màn hình sang phải
		{
			for (int i = MOVE_PIXELS; i > 0; --i)
				if (!(GetRightCollision(i) & HARD_TILE))
				{
					Functions::Move(iCurrScreenX, 0, i);
					if (iCurrScreenX + SCREEN_WIDTH > m_pMapTypeA->GetMapWidth())
					{
						Functions::Move(iCurrScreenX, 0, iCurrScreenX+SCREEN_WIDTH-m_pMapTypeA->GetMapWidth());
						iCurrScreenX = m_pMapTypeA->GetMapWidth() - SCREEN_WIDTH - 1;
					}
					break;
				}
		}
		else									// di chuyển nhân vật
		{
			for (int i = MOVE_PIXELS; i > 0; --i)
				if (!(GetRightCollision(i) & HARD_TILE))
				{
					Functions::Move(m_iLeft, 0, i);
					break;
				}
		}
	}

	if (m_iIsJump == 0 && m_iIsFall == 0)
	{
		if (!(GetBottomCollision(1) & HARD_TILE))
			m_iIsFall = 1;
	}
}

int TypeAOcegrine::OnAirHandle(int &iCoinCount)
{
	if (m_iIsJump > 0)		// đang nhảy
	{
		int iTiles = 0x0;
		int i = MOVE_PIXELS;
		for ( ; i > 0; --i)
		{
			int iTmp = GetTopCollision(i);
			if (!(iTmp & HARD_TILE))
			{
				Functions::Move(m_iTop, 0, -i);			// nhảy lên giảm Y
				Functions::Move(m_iIsJump, 0, -i);		// giai đoạn nhảy trôi dần qua
				break;
			}
			else
				iTiles = iTmp;
		}

		if (i != MOVE_PIXELS)			// đụng nóc
		{
			m_iIsJump = 0;				// dừng giai đoạn nhảy
			if (iTiles & ITEM_TILE)		// khi nhảy đội trúng hộp vật phẩm
			{
				++iCoinCount;			// hiện tại hộp vật phẩm chỉ chứa 1 đồng xu

				for (int j = m_iLeft; j < GetRight(); ++j)
					if (m_pMapTypeA->GetTile(j, m_iTop-1) & ITEM_TILE)
						m_pMapTypeA->SetTile(j, m_iTop-1, 0);	// đổi tile cho hộp vật phẩm sau khi bị ăn
			}
		}

		if (m_iIsJump == 0)			// giai đoạn nhảy kết thúc, chuyển sang giai đoạn rơi
			m_iIsFall = 1;

		return 1;
	}
	else
	{
		if (m_iIsFall != 0)		// đang rơi
		{
			int i = MOVE_PIXELS;
			for ( ; i > 0; --i)
				if (!(GetBottomCollision(i) & HARD_TILE))
				{
					Functions::Move(m_iTop, 0, i);
					break;
				}

			if (i != MOVE_PIXELS)
				m_iIsFall = 0;

			return 1;
		}
	}

	return 0;			// ko đang nhảy và ko đang rơi
}

void TypeAOcegrine::Jump()
{
	SetJump(JUMP_STEP);
	if (m_pSprite->GetSide() == 1)
		m_pSprite->SetPositionFrame(3);
	else
		m_pSprite->SetPositionFrame(10);

	//int i = MOVE_PIXELS;
	//for ( ; i > 0; --i)
	//	if (!(GetTopCollision(i) & HARD_TILE))
	//	{
	//		Functions::Move(m_iTop, 0, -i);
	//		break;
	//	}

	//if (i != MOVE_PIXELS)
	//{
	//	m_iIsJump = 0;			// nhảy lên đụng nóc
	//	m_iIsFall = 1;			// rơi
	//}
}

void TypeAOcegrine::RenderSprite(CDC *pDC)
{
	m_pSprite->Render(m_iLeft, m_iTop, pDC);
}

void TypeAOcegrine::Prepare(TypeAMap *pTypeAMap)
{
	m_pMapTypeA = pTypeAMap;

	m_iLeft = Functions::GetScreenCenterX();
	m_iTop = m_pMapTypeA->CalcY(m_iLeft, 0) - GetHeight();

	m_iIsFall = 1;
	m_iIsJump = 0;
}

int TypeAOcegrine::GetHeight()
{
	return m_pSprite->Height;
}

int TypeAOcegrine::InnerCollisionHandle(int &iLiveCount, int &iCoinCount, int &iCurrMap)
{
	int iTiles = GetInnerCollision();

	if (iTiles & HELL_TILE)		// nhân vật nam chính chết giữa đường, chơi lại map
	{
		Functions::Move(iLiveCount, 0, -1);		// giảm mạng
		return iCurrMap;
	}
	else if (iTiles & DANGEROUS_TILE)	// chạm phải chướng ngại nguy hiểm chết người, đi lại từ đầu
	{
		return iCurrMap;
	}
	else if (iTiles & GATE_TILE)		// chạm cổng qua màn, load màn kế tiếp
	{
		return iCurrMap + 1;
	}
	else if (iTiles & COIN_TILE)
	{
		int iBottom = GetBottom();
		int iRight = GetRight();
		for (int i = m_iTop; i < iBottom; i += 1)
			for (int j = m_iLeft; j < iRight; j += 1)
				if (m_pMapTypeA->GetTile(j, i) & COIN_TILE)
				{
					m_pMapTypeA->SetTile(j, i, -1);
					++iCoinCount;
				}
	}

	// sắp xếp câu lệnh if như trên là theo thứ tự ưu tiên: rớt xuống vực, chết > chạm quái, chết > chạm cửa, qua màn > ăn tiền

	return -1;
}