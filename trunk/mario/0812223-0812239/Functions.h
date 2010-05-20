#pragma once

#define BASE_HEIGHT						24
#define BASE_WIDTH						24

#define SCREEN_FRAME_WIDTH				16
#define SCREEN_FRAME_HEIGHT				20

#define SCREEN_WIDTH					380
#define SCREEN_HEIGHT					480

#define OTHER_TILE						0x0
#define GATE_TILE						0x01
#define HARD_TILE						0x02
#define HEAVEN_TILE						0x04
#define HELL_TILE						0x08
#define LEFT_SIDE_TILE					0x10
#define DANGEROUS_TILE					0x20
#define COIN_TILE						0x40
#define RIGHT_SIDE_TILE					0x80

class Functions
{
public:
	Functions(void);
	~Functions(void);

	static CPoint Pixel2Cell(CPoint pixel);
	static CPoint Pixel2Cell(int pixX, int pixY);

	static CPoint Cell2Pixel(CPoint cell);
	static CPoint Cell2Pixel(int cellX, int cellY);
};
