#pragma once

#include "Functions.h"

#include "GameState.h"

class TypeAMap;
class MainGame;
class TypeAOcegrine;
class TypeAMonster;
class Sprite;

#define MAX_MAP_NUM			5
#define TYPE_A_SLEEP_TIME	30

class GameStateTypeA : public GameState
{
public:
	GameStateTypeA(MainGame *_mg);
	virtual ~GameStateTypeA(void);

	TypeAOcegrine *m_pOcegrine;					// nhân vật nam chính
	vector<TypeAMonster*> m_vMonster;			// mảng quái

	Sprite *sprTiles;							// tile địa hình

	vector<TypeAMap*> m_vMap;		// mảng các map

	int m_iCurrMap;					// chỉ số map hiện tại
	int m_iCurrScreenX;				// cho biết vị trí bắt đầu của khung map hiện tại

	void MessageEnter(int message);
	void MessageUpdate(int message, int keys);
	void MessagePaint(int message, CDC *pDC);
	void MessageExit(int message, CDC *pDC);

	// load màn mới khi qua màn hoặc load lại màn cũ khi nhân vật chính tử nạn
	void PrepareMap(int iMap);

	// xử lý đụng độ bên trong
	void InnerCollisionHandle();

	// hàm cho biết khung màn hình đang ở đâu so với map
	int GetOnMapPosition();

	// hàm lấy giá trị biến m_iCurrScreenX
	int GetCurrScreenX();
};
