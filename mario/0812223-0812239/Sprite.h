#pragma once
#include "MyBitmap.h"

// lớp quản lý Animation trong Game
class Sprite
{
public:
	bool m_bSide;

	int m_frameDirection; //0 vertical, 1 horizontal
	int m_loopType; //0 loop back to begining, 1 bounce between begin and end
	int m_loopDirection;
	int m_frameCount;
	int m_currentFrame;
	int m_srcX;
	int m_srcY;
	int m_frameDelay;
	int m_curDelay;
	MyBitmap *m_image;
	int Width;
	int Height;

	Sprite(int srcX, int srcY, int Width, int Height, int frameDirection, int frameCount, int frameDelay, MyBitmap *image);
	void SetLoopType(int loopType);
	void NextFrame();
	void PreviousFrame();
	void SetPositionFrame(int iFrame);
	void SetDelay(int Delay);
	void Render(int X, int Y, CDC *pDC);

	void TurnBack();
	bool GetSide();

	int GetPositionFrame();

	void SetHeight(int iHeight);
	int GetHeight();

	void AddOffSetY(int iOffSet);

	Sprite(void);
	~Sprite(void);
};
