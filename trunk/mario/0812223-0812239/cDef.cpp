#include "StdAfx.h"
#include "cDef.h"

int cDef::STATE_LOGO	=	0x00;
int cDef::STATE_MENU	=	0x01;
int cDef::STATE_TYPE_A	=	0x02;
int cDef::STATE_INTRO	=	0x04;
int cDef::STATE_HOWTOPLAY = 0x08;

int cDef::MESSAGE_ENTER		=	0x02;
int cDef::MESSAGE_UPDATE	=	0x04;
int cDef::MESSAGE_PAINT		=	0x08;
int cDef::MESSAGE_EXIT		=	0x10;

int cDef::SCREEN_WIDTH	=	380;
int cDef::SCREEN_HEIGHT	=	480;

int cDef::BASE_WIDTH	=	24;
int cDef::BASE_HEIGHT	=	24;

int cDef::GATE_TILE			=	0x01;
int cDef::HARD_TILE			=	0x02;
int cDef::HEAVEN_TILE		=	0x04;
int cDef::HELL_TILE			=	0x08;
int cDef::LEFT_SIDE_TILE	=	0x10;
int cDef::DANGEROUS_TILE	=	0x20;
int cDef::COIN_TILE			=	0x40;
int cDef::RIGHT_SIDE_TILE	=	0x80;
int cDef::ITEM_TILE			=	0x0100;
int cDef::MONSTER_TILE		=	0x0200;

int cDef::OCEGRINE_MOVE_PIXELS = 4;

int cDef::BOM8A = 0xEF;
int cDef::BOM8B = 0xBB;
int cDef::BOM8C = 0xBF;