#include "StdAfx.h"
#include "MyBitmap.h"

MyBitmap::MyBitmap(void)
{
}

MyBitmap::~MyBitmap(void)
{
}


MyBitmap::MyBitmap(LPCTSTR str)
{
	cb = new CBitmap();
	cb->LoadBitmap(str);
}

//**----------------------------------------------------------

//** STEP 1: Load the bitmap into a CBitmap Object

//**----------------------------------------------------------

void MyBitmap::DrawTransparent(CDC * pDC, int x, int y, COLORREF crColour)
{
	try
	{
		COLORREF crOldBack = pDC->SetBkColor(RGB(255,255,255));
		COLORREF crOldText = pDC->SetTextColor(RGB(0,0,0));
		CDC dcImage, dcTrans;

		// Create two memory dcs for the image and the mask
		dcImage.CreateCompatibleDC(pDC);
		dcTrans.CreateCompatibleDC(pDC);

		// Select the image into the appropriate dc
		CBitmap* pOldBitmapImage = dcImage.SelectObject(cb);

		// Create the mask bitmap
		CBitmap bitmapTrans;
		BITMAP bm;
		cb->GetBitmap(&bm);
		int nWidth = bm.bmWidth;
		int nHeight = bm.bmHeight;
		bitmapTrans.CreateBitmap(nWidth, nHeight, 1, 1, NULL);

		// Select the mask bitmap into the appropriate dc
		CBitmap* pOldBitmapTrans = dcTrans.SelectObject(&bitmapTrans);

		// Build mask based on transparent colour
		dcImage.SetBkColor(crColour);
		dcTrans.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCCOPY);

		// Do the work - True Mask method - cool if not actual display
		pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);
		pDC->BitBlt(x, y, nWidth, nHeight, &dcTrans, 0, 0, SRCAND);
		pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, 0, 0, SRCINVERT);

		// Restore settings
		dcImage.SelectObject(pOldBitmapImage);
		dcTrans.SelectObject(pOldBitmapTrans);
		pDC->SetBkColor(crOldBack);
		pDC->SetTextColor(crOldText);
	}
	catch(char* str)
	{
		printf("%s", str);
	}
}



void MyBitmap::DrawTransparent(CDC * pDC, int x, int y,int x1, int y1,int width,int height, COLORREF crColour)
{

	try
	{
		COLORREF crOldBack = pDC->SetBkColor(RGB(255,255,255));
		COLORREF crOldText = pDC->SetTextColor(RGB(0,0,0));
		CDC dcImage, dcTrans;

		// Create two memory dcs for the image and the mask
		dcImage.CreateCompatibleDC(pDC);
		dcTrans.CreateCompatibleDC(pDC);

		// Select the image into the appropriate dc
		CBitmap* pOldBitmapImage = dcImage.SelectObject(cb);

		// Create the mask bitmap
		CBitmap bitmapTrans;
		BITMAP bm;
		cb->GetBitmap(&bm);
		int nWidth = width;
		int nHeight = height;
		bitmapTrans.CreateBitmap(nWidth, nHeight, 1, 1, NULL);

		// Select the mask bitmap into the appropriate dc
		CBitmap* pOldBitmapTrans = dcTrans.SelectObject(&bitmapTrans);

		// Build mask based on transparent colour
		dcImage.SetBkColor(crColour);
		//dcTrans.BitBlt(0, 0, nWidth, nHeight, &dcImage, x1, y1, SRCCOPY);
		dcTrans.BitBlt(0, 0, nWidth, nHeight, &dcImage, 0, 0, SRCCOPY);  


		// Do the work - True Mask method - cool if not actual display
		pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, x1, y1, SRCINVERT);
		pDC->BitBlt(x, y, nWidth, nHeight, &dcTrans, x1, y1, SRCAND);
		pDC->BitBlt(x, y, nWidth, nHeight, &dcImage, x1, y1, SRCINVERT);

		// Restore settings
		dcImage.SelectObject(pOldBitmapImage);
		dcTrans.SelectObject(pOldBitmapTrans);
		pDC->SetBkColor(crOldBack);
		pDC->SetTextColor(crOldText);
	}
	catch(...)
	{
	}

}