#include "StdAfx.h"
#include "Functions.h"

MCIDEVICEID g_mciDevID;

Functions::Functions(void)
{
}

Functions::~Functions(void)
{
}

CPoint Functions::Pixel2Cell(CPoint pixel)
{
	return CPoint(pixel.x / cDef::BASE_WIDTH, pixel.y / cDef::BASE_HEIGHT);
}

CPoint Functions::Pixel2Cell(int pixX, int pixY)
{
	return CPoint(pixX / cDef::BASE_WIDTH, pixY / cDef::BASE_HEIGHT);
}

CPoint Functions::Cell2Pixel(CPoint cell)
{
	return CPoint(cell.x * cDef::BASE_WIDTH, cell.y * cDef::BASE_HEIGHT);
}

CPoint Functions::Cell2Pixel(int cellX, int cellY)
{
	return CPoint(cellX * cDef::BASE_WIDTH, cellY * cDef::BASE_HEIGHT);
}

void Functions::Move(int &iVal, int iStep, int iPixel)
{
	iVal += iStep*cDef::OCEGRINE_MOVE_PIXELS + iPixel;
}

int Functions::GetScreenCenterX()
{
	return cDef::SCREEN_WIDTH / 2;
}

wchar_t * Functions::UTF8_to_WChar(const char *string){
	long b=0,
		c=0;
	if ((unsigned char)string[0]==cDef::BOM8A && (unsigned char)string[1]==cDef::BOM8B && (unsigned char)string[2]==cDef::BOM8C)
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

//bool Functions::IsWaveFile( LPWSTR lpszFileName )
//{
//	HMMIO hmmio;
//
//	// Mo file 
//	if (!(hmmio = mmioOpen(lpszFileName, 0, MMIO_READ | MMIO_ALLOCBUF)))
//		return false;
//
//	MMCKINFO mmckinfoParent;   // Group Header (special chunk)
//
//	// Dinh vi nhom wave (group header) 
//	mmckinfoParent.fccType = mmioFOURCC('W', 'A', 'V', 'E'); 
//
//	// Neu khong co nhom wave thi day la khong phai thuoc dinh dang wave
//	if (mmioDescend(hmmio, (LPMMCKINFO) &mmckinfoParent, 0, MMIO_FINDRIFF))
//		return false;
//
//	// Nguoc lai dung -> dung
//	return true;
//}
//
//bool Functions::IsMIDIFile( LPWSTR lpszFileName )
//{
//	HMMIO hmmio;
//
//	// Mo file 
//	if (!(hmmio = mmioOpen(lpszFileName, 0, MMIO_READ | MMIO_ALLOCBUF)))
//		return false;
//
//	MMCKINFO mmckinfoSubchunk;   
//
//	memset(&mmckinfoSubchunk, 0, sizeof(mmckinfoSubchunk));
//
//	// Tim nhom MThd 
//	mmckinfoSubchunk.ckid = mmioFOURCC('M', 'T', 'h', 'd'); 
//
//	// Neu khong tinm thay nhom MThd -> khong phai file Midi
//	if (mmioDescend(hmmio, &mmckinfoSubchunk, 0, MMIO_FINDCHUNK))
//		return false;
//
//	// Nguoc lai -> dung
//	return true;
//}
//
//void Functions::PlayCommandWaveMidi( LPWSTR lpszFilePath )
//{
//	MCI_OPEN_PARMS mciOpenParms;
//
//	if (Functions::IsWaveFile(lpszFilePath))
//		mciOpenParms.lpstrDeviceType = L"waveaudio";
//	else if (Functions::IsMIDIFile(lpszFilePath))
//		mciOpenParms.lpstrDeviceType = L"sequencer";
//
//	mciOpenParms.lpstrElementName = lpszFilePath;
//
//	if (mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_TYPE | MCI_OPEN_ELEMENT, (DWORD)(LPVOID)&mciOpenParms))
//		return;
//
//	g_mciDevID = mciOpenParms.wDeviceID;
//
//	MCI_PLAY_PARMS mciPlayParms;
//
//	if (mciSendCommand(g_mciDevID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&mciPlayParms))
//	{
//		mciSendCommand(g_mciDevID, MCI_CLOSE, 0, 0L);
//		return;
//	}
//}
//
//void Functions::PlayStringWaveMidi( LPWSTR lpszAlias)
//{
//	TCHAR szCommand[120];
//	wsprintf(szCommand, L"play %s type %s alias EEE", lpszAlias);
//
//	mciSendString(szCommand, NULL, 0, 0);
//	mciSendString(L"play EEE", NULL, 0, 0);
//}