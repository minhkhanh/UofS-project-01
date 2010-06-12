#pragma once

#include "MMSystem.h"

#include "Functions.h"

class GameSound
{
public:
	GameSound(void);
	~GameSound(void);

	//static void Open(LPWSTR lpszDeviceName, LPWSTR lpszDeviceType);
	//static void Close(LPWSTR lpszDeviceString);

	static void Coin(int iFlag);
	static void Jump(int iFlag);
	static void TypeATheme(int iFlag);
	static void MenuTheme(int iFlag);
	static void IntroTheme(int iFlag);
	static void EnterMainGame(int iFlag);
};
