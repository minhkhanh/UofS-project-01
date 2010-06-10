#pragma once

#include "Functions.h"

#include "TypeAObject.h"

#define JUMP_STEP		100 / MOVE_PIXELS

class TypeAOcegrine: public TypeAObject
{
private:
	int m_iIsJump;			// biến đếm nhảy
	int m_iIsCrouch;		// đang hụp

public:
	TypeAOcegrine(void);
	TypeAOcegrine(Sprite *sprImage, TypeAMap *pCurrMap);
	~TypeAOcegrine(void);

	// lấy bottom, chiều cao
	int GetBottom();
	int GetHeight();

	// hàm đặt giá trị số bước nhảy
	void SetJump(int iJumpStep);

	// hàm đi sang trái, sang phải, nhảy, hụp
	void MoveLeft();
	void MoveRight();
	void Jump();
	void CrouchToggle();

	// các hàm xử lý trên không trung
	int OnAirHandle(int &iCoinCount);
	int OnJump(int &iCoinCount);
	int OnFall();

	//int Get

	// hàm xử lý đụng độ bên trong
	int InnerCollisionHandle(int &iLiveCount, int &iCoinCount);

	// hàm chuẩn bị cho nhân vật trước khi bắt đầu 1 map
	void Prepare(TypeAMap *pTypeAMap);

	// lấy frame tiếp theo trong động tác đi
	void PreviousMoveFrame();
	void NextMoveFrame();
};
