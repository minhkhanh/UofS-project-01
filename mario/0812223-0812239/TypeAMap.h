#pragma once

#include "stdafx.h"
#include "GameStateTypeA.h"
#include "MyBitmap.h"
#include "cDef.h"
#include "0812223-0812239.h"
#include "Sprite.h"
#include "GameKeys.h"
#include "MainGame.h"
#include "TypeAObject.h"
#include "Functions.h"

class GameStateTypeA;
class TypeAObject;

class TypeAMap
{
public:
	TypeAMap(void);
	TypeAMap(char *strMapPath, int idImg, GameStateTypeA* stateTypeA);
	~TypeAMap(void);

	GameStateTypeA *m_pStateTypeA;

	MyBitmap *m_pBackground;
	char *m_pMapPath;
	int m_idBackground;

	vector<vector<int>> m_vMap;
	//vector<TypeAObject*> m_vMonster;

	int m_iPixelMapWidth, m_iPixelMapHeight;

	// load dữ liệu map từ file vào mảng
	void LoadMap();
	// vẽ map
	void PaintMap();
	// kiểm tra chướng ngại vật
	int WhatTile(int i, int j);
	// lấy điểm tựa đầu tiên khi chiếu từ iX xuống
	int CalcY(int iX, int iY);
};
