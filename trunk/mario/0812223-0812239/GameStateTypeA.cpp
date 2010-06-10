#include "StdAfx.h"
#include "GameStateTypeA.h"

#include "TypeAMap.h"
#include "MainGame.h"
#include "TypeAOcegrine.h"

GameStateTypeA::GameStateTypeA(MainGame *_mg)
{
	mg = _mg;
	GAME_STATE_DEF = cDef::STATE_TYPE_A;

	m_pTiles = new Sprite(0,0,24,24,1,31,0,new MyBitmap((LPCTSTR)IDIMG_TILES));	// load các tile
	m_iCurrMap = 0;

	// khởi tạo tất cả các map Type A
	m_vMap.push_back(new TypeAMap("Resource\\Level1\\Map1.dat", IDIMG_BGR_TYPE_A_LEVEL_1, this));
	m_vMap.push_back(new TypeAMap("Resource\\Level2\\Map1.dat", IDIMG_BGR_TYPE_A_LEVEL_2, this));
	m_vMap.push_back(new TypeAMap("Resource\\Level3\\Map1.dat", IDIMG_BGR_TYPE_A_LEVEL_3, this));
	m_vMap.push_back(new TypeAMap("Resource\\Level4\\Map1.dat", IDIMG_BGR_TYPE_A_LEVEL_4, this));
	m_vMap.push_back(new TypeAMap("Resource\\Level5\\Map1.dat", IDIMG_BGR_TYPE_A_LEVEL_5, this));
	//---

	// tạo nhân vật nam chính
	m_pOcegrine = new TypeAOcegrine(new Sprite(0,0,18,36,1,14,2,new MyBitmap((LPCTSTR)IDIMG_OCEGRINE_SPRITE)), m_vMap[m_iCurrMap]);
}

GameStateTypeA::~GameStateTypeA(void)
{
}

void GameStateTypeA::MessageEnter(int message)
{
	mg->iSleepTime = TYPE_A_SLEEP_TIME;
	PrepareMap(m_iCurrMap);
}

void GameStateTypeA::MessageUpdate(int message, int keys)
{
	if (mg->KeyGet() & GameKeys::Left)
	{
		m_pOcegrine->MoveLeft();
	}
	
	if (mg->KeyGet() & GameKeys::Right)
	{
		m_pOcegrine->MoveRight();
	}

	if (m_pOcegrine->OnAirHandle(mg->m_iCoinCount) == 0)		// chỉ xử lý nhảy khi không đang nhảy và không đang rơi
	{
		if (mg->KeyGet() & GameKeys::Up)
		{
			m_pOcegrine->Jump();		
		}
	}

	int iMap;

	m_vMap[m_iCurrMap]->ActivateMonsters();

	if (m_vMap[m_iCurrMap]->MoveMonsters() == 1)
		iMap = m_iCurrMap;
	else
		iMap = m_pOcegrine->InnerCollisionHandle(mg->m_iLiveCount, mg->m_iCoinCount);

	if (iMap >= 0)
		PrepareMap(iMap);

	if (mg->KeyGet() & GameKeys::Down)
	{
		m_pOcegrine->CrouchToggle();
	}

	if (mg->KeyGet() & GameKeys::Enter)
	{
		mg->mBiz_SwitchState(cDef::STATE_MENU);
	}
}

void GameStateTypeA::MessagePaint(int message, CDC *pDC)
{
	m_vMap[m_iCurrMap]->PaintMap(&(mg->m_MemDC));
	m_vMap[m_iCurrMap]->ThrowMonsters(&(mg->m_MemDC));
	m_pOcegrine->RenderSprite(&(mg->m_MemDC));

	mg->DrawGameStatus();

	pDC->StretchBlt(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, &(mg->m_MemDC), 0, 0 , SCREEN_WIDTH, SCREEN_HEIGHT, SRCCOPY);
}

void GameStateTypeA::MessageExit(int message, CDC *pDC)
{
	mg->mBiz_iCurrentState = cDef::STATE_LOGO;
}

void GameStateTypeA::PrepareMap(int iMap)
{
	if (iMap >= MAX_MAP_NUM)			// chỉ số map vượt quá số lượng map cho phép
		return;

	m_vMap[m_iCurrMap]->ReleaseData();
	m_iCurrMap = iMap;					// xác định map hiện tại
	m_vMap[m_iCurrMap]->LoadMap();		// đọc thông tin map từ file, load ảnh nền, load quái, tính các số liệu liên quan

	m_pOcegrine->Prepare(m_vMap[m_iCurrMap]);
}

int GameStateTypeA::GetCurrMapIndex()
{
	return m_iCurrMap;
}

TypeAOcegrine *GameStateTypeA::GetOcegrine()
{
	return m_pOcegrine;
}