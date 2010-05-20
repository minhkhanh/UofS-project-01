#include "StdAfx.h"
#include "Functions.h"

Functions::Functions(void)
{
}

Functions::~Functions(void)
{
}

CPoint Functions::Pixel2Cell(CPoint pixel)
{
	return CPoint(pixel.x / BASE_WIDTH, pixel.y / BASE_HEIGHT);
}

CPoint Functions::Pixel2Cell(int pixX, int pixY)
{
	return CPoint(pixX / BASE_WIDTH, pixY / BASE_HEIGHT);
}

CPoint Functions::Cell2Pixel(CPoint cell)
{
	return CPoint(cell.x * BASE_WIDTH, cell.y * BASE_HEIGHT);
}

CPoint Functions::Cell2Pixel(int cellX, int cellY)
{
	return CPoint(cellX * BASE_WIDTH, cellY * BASE_HEIGHT);
}