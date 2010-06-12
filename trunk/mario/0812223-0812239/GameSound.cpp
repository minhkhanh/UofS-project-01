#include "StdAfx.h"
#include "GameSound.h"

GameSound::GameSound(void)
{
}

GameSound::~GameSound(void)
{
}

void GameSound::Coin(int iFlag)
{
	mciSendString(L"stop coin", NULL, 0, 0);
	mciSendString(L"close coin", NULL, 0, 0);

	if (iFlag == 1)
	{
		mciSendString(L"open Resource\\Music\\coin.wav type mpegvideo alias coin", NULL, 0, 0);
		mciSendString(L"play coin wait", NULL, 0, 0);
	}

//	PlaySound(L"Resource\\Music\\coin.wav", NULL, SND_FILENAME);
}

void GameSound::Jump(int iFlag)
{
	mciSendString(L"stop jump", NULL, 0, 0);
	mciSendString(L"close jump", NULL, 0, 0);

	if (iFlag == 1)
	{
		mciSendString(L"open Resource\\Music\\step.wav type waveaudio alias jump", NULL, 0, 0);
		mciSendString(L"play jump", NULL, 0, 0);
	}
}

void GameSound::TypeATheme(int iFlag)
{
	mciSendString(L"stop typeAtheme", NULL, 0, 0);
	mciSendString(L"close typeAtheme", NULL, 0, 0);

	if (iFlag == 1)
	{
		mciSendString(L"open Resource\\Music\\SuperMario64MainTheme.wav type mpegvideo alias typeAtheme", NULL, 0, 0);
		mciSendString(L"play typeAtheme repeat", NULL, 0, 0);
	}
}

void GameSound::MenuTheme( int iFlag )
{
	mciSendString(L"stop menutheme", NULL, 0, 0);
	mciSendString(L"close menutheme", NULL, 0, 0);

	if (iFlag == 1)
	{
		mciSendString(L"open Resource\\Music\\menu.wav type mpegvideo alias menutheme", NULL, 0, 0);
		mciSendString(L"play menutheme from 0 repeat", NULL, 0, 0);
	}
}

void GameSound::IntroTheme( int iFlag )
{
	mciSendString(L"stop pushing", NULL, 0, 0);
	mciSendString(L"close pushing", NULL, 0, 0);

	if (iFlag == 1)
	{
		mciSendString(L"open Resource\\Music\\pushing.wav type mpegvideo alias pushing", NULL, 0, 0);
		mciSendString(L"play pushing from 0 repeat", NULL, 0, 0);
	}
}

void GameSound::EnterMainGame( int iFlag )
{
	mciSendString(L"stop beginlevel", NULL, 0, 0);
	mciSendString(L"close beginlevel", NULL, 0, 0);

	if (iFlag == 1)
	{
		mciSendString(L"open Resource\\Music\\beginlevel.wav type mpegvideo alias beginlevel", NULL, 0, 0);
		mciSendString(L"play beginlevel from 0 wait", NULL, 0, 0);
	}
}

void GameSound::Explosion( int iFlag )
{
	mciSendString(L"stop explosion", NULL, 0, 0);
	mciSendString(L"close explosion", NULL, 0, 0);

	if (iFlag == 1)
	{
		mciSendString(L"open Resource\\Music\\explosion.wav type mpegvideo alias explosion", NULL, 0, 0);
		mciSendString(L"play explosion from 0 wait", NULL, 0, 0);
	}
}