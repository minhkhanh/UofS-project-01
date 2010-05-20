#pragma once

#include "stdafx.h"
#include "GameState.h"
#include "MyBitmap.h"
#include "cDef.h"
#include "0812223-0812239.h"
#include "Sprite.h"
#include "GameKeys.h"
#include "MainGame.h"
#include "TypeAObject.h"
#include "TypeAMap.h"

class GameStateTypeA;
class TypeAObject;
class TypeAMap;

class GameStateTypeA :public GameState
{
public:
	GameStateTypeA(MainGame *_mg);
	virtual ~GameStateTypeA(void);

	int MAX_MAP_NUM;
	int MOVE_PIXELS;

	TypeAObject *m_pOcegrine;

	Sprite *sprTiles;

	vector<TypeAMap*> m_vMap;
	int m_iCurrMap;

	int m_iCurrScreenX;		// cho biết vị trí bắt đầu của khung map hiện tại

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);

	// load màn mới khi qua màn hoặc load lại màn cũ khi nhân vật chính tử nạn
	void PrepareLevel(int iMap);
	// xử lý cho việc đi tới
	void OnKeyRight();
	// xử lý cho việc đi ngược về
	void OnKeyLeft();
	// xử lý khi nhảy hoặc khi rơi
	int OverheadHandler();
	// xử lý cho load map
	void ReloadHandler();
	// tăng giảm biến số khi di chuyển
	void Move(int &iVal, int sign);

	// xét các va chạm bên trái, phải, trên, dưới, trong
	int GetLeftCollision(TypeAObject *pObject);
	int GetRightCollision(TypeAObject *pObject);
	int GetTopCollision(TypeAObject *pObject);
	int GetBottomCollision(TypeAObject *pObject);
	int GetCenterCollision(TypeAObject *pObject);

	// cho biết trạng thái vị trí nhân vật chính so với màn hình
	//	-2: chạm biên trái của màn hình
	//	-1: lệch trái so với giữa màn hình
	//	0: ngay giữa màn hình
	//	1: lệch phải so với giữa màn hình
	//	2: chạm biên phải của màn hình
	int GetOcegrinePositionStatus();

	// cho biết trạng thái vị trí màn hình so với map
	//	-1: chạm biên trái của map
	//	1: chạm biên phải của map
	int GetScreenPositionStatus();

	// hàm lấy tọa độ X của điểm giữa màn hình game
	int GetScreenCenterX();
};
