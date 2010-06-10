#include "StdAfx.h"
#include "GameKeys.h"

GameKeys::GameKeys(void)
{
}

GameKeys::~GameKeys(void)
{
}

int GameKeys::Null = 0x0;
int GameKeys::Up = 0x01;
int GameKeys::Down = 0x02;
int GameKeys::Left = 0x04;
int GameKeys::Right = 0x08;
int GameKeys::Enter = 0x10;
int GameKeys::DownKeyDowning = 0x20;
int GameKeys::LeftKeyDowning = 0x40;
int GameKeys::RightKeyDowning = 0x80;
int GameKeys::UpKeyDowning = 0x100;