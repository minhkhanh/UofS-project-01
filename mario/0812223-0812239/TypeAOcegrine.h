#pragma once

#include "Functions.h"

#include "TypeAObject.h"

#define JUMP_STEP		100 / MOVE_PIXELS

class TypeAOcegrine: public TypeAObject
{
public:
	TypeAOcegrine(void);
	TypeAOcegrine(Sprite *sprImage, TypeAMap *pCurrMap);
	~TypeAOcegrine(void);

	// các hàm lấy các giá trị: bottom, right, và chiều cao của nhân vật
	int GetBottom();
	int GetRight();
	int GetHeight();

	// các hàm lấy các giá trị xử lý đụng độ bên trái, phải, dưới, trên, trong
	int GetLeftCollision(int iScope = MOVE_PIXELS);
	int GetRightCollision(int iScope = MOVE_PIXELS);
	int GetBottomCollision(int iScope = MOVE_PIXELS);
	int GetTopCollision(int iScope = MOVE_PIXELS);
	int GetInnerCollision();

	// Hàm cho biết vị trí đối tượng so với màn hình (lấy m_iLeft so sánh với 1 khoảng nằm giữa màn hình)
	//-1: đối tượng lệch trái so với giữa màn hình	(m_iLeft < khoảng giữa)
	//0: đứng ngay giữa								(m_iLeft trong khoảng giữa)
	//1: lệch phải									(m_iLeft > khoảng giữa)
	int GetOnScreenPosition();

	// hàm đặt giá trị số bước nhảy
	void SetJump(int iJumpStep);

	// hàm đi sang trái, sang phải, nhảy
	void MoveLeft(int &iCurrScreenX);
	void MoveRight(int &iCurrScreenX);
	void Jump();
	void CrouchToggle();

	// hàm xử lý trên không trung
	int OnAirHandle(int &iCoinCount);

	// hàm xử lý đụng độ bên trong
	int InnerCollisionHandle(int &iLiveCount, int &iCoinCount, int &iCurrMap);
	
	// hàm vẽ nhân vật tại khung hình hiện tại
	void RenderSprite(CDC *pDC);

	// hàm chuẩn bị cho nhân vật trước khi bắt đầu 1 map
	void Prepare(TypeAMap *pTypeAMap);

	void PreviousMoveFrame();
	void NextMoveFrame();
};
