#pragma once

class MyBitmap
{
public:
	MyBitmap(void);
	MyBitmap(LPCTSTR str);
	~MyBitmap(void);

	CBitmap *cb;
	void DrawTransparent(CDC * pDC, int x, int y, COLORREF crColour);
	void DrawTransparent(CDC * pDC, int x, int y,int x1, int y1,int width,int height, COLORREF crColour);	
};
