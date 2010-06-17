#include "StdAfx.h"
#include "GameStateSettings.h"

#include "MainGame.h"

GameStateSettings::GameStateSettings(MainGame *mg): m_iCurrItem(0)
{
	m_pMainGame = mg;

	m_iGameStateDef = cDef::STATE_SETTINGS;
	m_pBackGroundBMP = new MyBitmap((LPCTSTR)IDIMG_GAME_SETTINGS);

	m_vSettingText.push_back(L"SOUND ON");
	m_vSettingText.push_back(L"SOUND OFF");
}

GameStateSettings::~GameStateSettings(void)
{
}

void GameStateSettings::MessageEnter(int message)
{
	m_pMainGame->m_iSleepTime = 50;
	m_pBackGroundBMP->DrawTransparent(m_pMainGame->m_pDC, 0, 0, RGB(113,113,113));
	TextSettingOut();
}

void GameStateSettings::MessageUpdate(int message, int keys)
{
	if ((keys & GameKeys::Up) && m_iCurrItem > 0)
	{
		--m_iCurrItem;

		GameSound::Play(COIN_SOUND);

		TextSettingOut();

		m_pMainGame->KeyRelease(GameKeys::Up);
	}

	if ((keys & GameKeys::Down) && m_iCurrItem < MAX_SETTINGS_ITEM-1)
	{
		++m_iCurrItem;

		GameSound::Play(COIN_SOUND);

		//m_pBackGroundBMP->DrawTransparent(m_pMainGame->m_pDC, 0, 0, RGB(113,113,113));

		TextSettingOut();
		m_pMainGame->KeyRelease(GameKeys::Down);
	}

	if (keys & GameKeys::Enter)
	{
		if (m_iCurrItem == SOUND_OFF)
		{
			GameSound::TurnOffVolume();
			GameSound::MenuTheme(0);
		}
		else if (m_iCurrItem == SOUND_ON)
		{
			GameSound::TurnOnVolume();
			GameSound::MenuTheme(1);
		}

		m_pMainGame->mBiz_SwitchState(cDef::STATE_MENU);
	}
}

void GameStateSettings::MessagePaint(int message, CDC *pDC)
{
}

void GameStateSettings::MessageExit(int message, CDC *pDC)
{
	m_pMainGame->mBiz_iCurrentState = cDef::STATE_MENU;
}

void GameStateSettings::TextSettingOut()
{
	int iOldBkMode = m_pMainGame->m_pDC->SetBkMode(TRANSPARENT);
	CFont font;
	font.CreatePointFont(200, L"Courier");
	CFont *pOldFont = m_pMainGame->m_pDC->SelectObject(&font);

	CBrush brushRed, brushGray;
	brushGray.CreateHatchBrush(HS_DIAGCROSS, RGB(113,113,113));
	brushRed.CreateSolidBrush(RGB(0,0,0));
	//brushGray.CreateSolidBrush(RGB(113,113,113));

	//CBrush *brushOld = m_pMainGame->m_pDC->SelectObject(&brushRed);

	int iOldTxtClr = m_pMainGame->m_pDC->SetTextColor(RGB(0,255,0));

	RECT rect;
	rect.top = 200;
	rect.left = 10;
	rect.right = cDef::SCREEN_WIDTH - 10;
	rect.bottom = 250;

	for (int i = 0; i < MAX_SETTINGS_ITEM; ++i)
	{
		rect.top += (i * 50);
		rect.bottom += (i * 50);

		if (i == m_iCurrItem)
		{
			m_pMainGame->m_pDC->SelectObject(&brushRed);
			m_pMainGame->m_pDC->SetTextColor(RGB(0,255,0));
		}
		else
		{
			m_pMainGame->m_pDC->SelectObject(&brushGray);
			m_pMainGame->m_pDC->SetTextColor(RGB(113,113,113));
		}
		m_pMainGame->m_pDC->Rectangle(&rect);

		m_pMainGame->m_pDC->DrawText(m_vSettingText[i], &rect, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}

	//int iOldTxtClr = m_pMainGame->m_pDC->SetTextColor(RGB(255,255,255));
	//m_pMainGame->m_pDC->DrawText(m_vMenuText[m_iCurrMenuItem], -1, &rect, DT_RIGHT);

	m_pMainGame->m_pDC->SelectObject(pOldFont);
	m_pMainGame->m_pDC->SetBkMode(iOldBkMode);
	//m_pMainGame->m_pDC->SetBrus
	m_pMainGame->m_pDC->SetTextColor(iOldTxtClr);
}