#pragma once

#include "MMSystem.h"

#include "Functions.h"

#define COIN_SOUND				0
#define JUMP_SOUND				1
#define EXPLOSION_SOUND			2
#define MAIN_GAME_THEME_SOUND	3
#define INTRO_THEME_SOUND		4
#define ENTER_MAIN_GAME_SOUND	5
#define MENU_THEME_SOUND		6
#define GAME_OVER_THEME			7
#define BONUS_LIVE				8

class GameSound
{
private:
	static int m_iSoundOn;

public:
	GameSound(void);
	~GameSound(void);

	//static void Open(LPWSTR lpszDeviceName, LPWSTR lpszDeviceType);
	//static void Close(LPWSTR lpszDeviceString);

	static void TurnOnVolume();
	static void TurnOffVolume();

	static void Play(int iSoundID, int iFlag = 1);

	static void Coin();
	static void Jump();
	static void Explosion();
	static void MainGameTheme(int iFlag = 1);
	static void MenuTheme(int iFlag = 1);
	static void IntroTheme(int iFlag = 1);
	static void EnterMainGame(int iFlag = 1);
	static void GameOverTheme(int iFlag = 1);
	static void BonusLive(int iFlag = 1);
};
