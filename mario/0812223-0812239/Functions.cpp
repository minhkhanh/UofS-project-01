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

void Functions::Move(int &iVal, int iStep, int iPixel)
{
	iVal += iStep*MOVE_PIXELS + iPixel;
}

int Functions::GetScreenCenterX()
{
	return SCREEN_WIDTH / 2;
}

wchar_t * Functions::UTF8_to_WChar(const char *string){
	long b=0,
		c=0;
	if ((unsigned char)string[0]==BOM8A && (unsigned char)string[1]==BOM8B && (unsigned char)string[2]==BOM8C)
		string+=3;
	for (const char *a=string;*a;a++)
		if (((unsigned char)*a)<128 || (*a&192)==192)
			c++;
	wchar_t *res=new wchar_t[c+1];
	res[c]=0;
	for (unsigned char *a=(unsigned char*)string;*a;a++){
		if (!(*a&128))
			//Byte represents an ASCII character. Direct copy will do.
			res[b]=*a;
		else if ((*a&192)==128)
			//Byte is the middle of an encoded character. Ignore.
			continue;
		else if ((*a&224)==192)
			//Byte represents the start of an encoded character in the range
			//U+0080 to U+07FF
			res[b]=((*a&31)<<6)|a[1]&63;
		else if ((*a&240)==224)
			//Byte represents the start of an encoded character in the range
			//U+07FF to U+FFFF
			res[b]=((*a&15)<<12)|((a[1]&63)<<6)|a[2]&63;
		else if ((*a&248)==240){
			//Byte represents the start of an encoded character beyond the
			//U+FFFF limit of 16-bit integers
			res[b]='?';
		}
		b++;
	}
	return res;
}

int Functions::GetBits( int a, int x, int y )
{
	return ((a >> x) & ~((-1) << (y-x+1)));
}

void Functions::SetBits( int &a, int x, int y, int v )
{
	int tmp = (v << x) & ~((-1) << (y+1));					// 0000 yyyy 0000 , ex.
	int tmp2 = (~((-1) << (x+1))) | ((-1) << (y+1));		// 1111 0000 1111 , ex.
	a &= tmp2;												// xxxx 0000 xxxx , ex.
	a |= tmp;												// xxxx yyyy xxxx
}

bool Functions::GetBit( int a, int x )
{
	return ((a >> x) & 1);
}

void Functions::SetBit( int &a, int x, bool v )
{
	if (v == 0)
		a &= ~(1 << x);
	else if (v == 1)
		a |= 1 << x;
}