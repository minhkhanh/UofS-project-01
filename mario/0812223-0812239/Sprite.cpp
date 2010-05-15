#include "StdAfx.h"
#include "Sprite.h"

Sprite::Sprite(void)
{
}

Sprite::~Sprite(void)
{
}


Sprite::Sprite(int srcX, int srcY, int width, int height, int frameDirection, int frameCount, int frameDelay, MyBitmap *image)
{
	m_srcX = srcX;
	m_srcY = srcY;
	Width = width;
	Height = height;
	m_frameDirection = frameDirection;
	m_frameCount = frameCount;
	m_frameDelay = frameDelay;
	m_image = image;
	m_currentFrame = 0;
	m_loopType = 0;
	m_curDelay = 0;
	m_loopDirection = 1;
}

void Sprite::SetLoopType(int loopType)
{
	if((0 <= loopType) && (loopType <= 1))
		m_loopType = loopType;
}

void Sprite::NextFrame()
{
	if(m_curDelay >= m_frameDelay)
	{
		m_curDelay = 0;
		m_currentFrame += m_loopDirection;
		if(m_currentFrame >= m_frameCount && m_loopType == 0)
			m_currentFrame = 0;
		if(m_currentFrame >= m_frameCount && m_loopType == 1) {
			m_loopDirection *= -1;
			m_currentFrame = m_frameCount-1;
		}
		if(m_currentFrame < 0 && m_loopType == 1) {
			m_loopDirection *= -1;
			m_currentFrame = 1;
		}
	}
	else
		m_curDelay++;
}

void Sprite::PreviousFrame()
{
	m_currentFrame -= m_loopDirection;
	if(m_currentFrame < 0 && m_loopType == 0)
		m_currentFrame = m_frameCount-1;
	if(m_currentFrame >= m_frameCount && m_loopType == 1) {
		m_loopDirection *= -1;
		m_currentFrame = m_frameCount-1;
	}
	if(m_currentFrame < 0 && m_loopType == 1) {
		m_loopDirection *= -1;
		m_currentFrame = 1;
	}
}

void Sprite::SetDelay(int Delay)
{
	m_frameDelay = Delay;
}

void Sprite::Render(int X, int Y, CDC *pDC)
{
	int imageX, imageY;
	imageX = m_srcX;
	imageY = m_srcY;
	if(m_frameDirection == 0)
		imageY += (m_currentFrame*Height);
	else
		imageX += (m_currentFrame*Width);
	
	m_image->DrawTransparent(pDC,X,Y,imageX,imageY,imageX+Width,Height,RGB(255,255,255));
}

void Sprite::SetPositionFrame(int iFrame)
{
	if (iFrame<0) 
		iFrame = 0;
	else if (iFrame>=m_frameCount) 
		iFrame = m_frameCount-1;
	m_currentFrame = iFrame;
}