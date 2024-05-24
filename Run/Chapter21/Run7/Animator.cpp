#include "Animator.h"

Animator::Animator(
	int leftOffset, int topOffset,
	int frameCount,
	int textureWidth,
	int textureHeight,
	int fps)
{
	m_LeftOffset = leftOffset;

	m_CurrentFrame = 0;
	m_FrameCount = frameCount;

	if (m_FrameCount == 0)
	{
		m_FrameCount = 1;
	}

	m_FrameWidth = (float)textureWidth
		/ m_FrameCount;
	m_SourceRect.left = leftOffset;
	m_SourceRect.top = topOffset;
	m_SourceRect.width = m_FrameWidth;
	m_SourceRect.height = textureHeight;
	m_FPS = fps;

	if (m_FPS == 0)
	{
		m_FPS = 1;
	}

	m_FramePeriod = 1000 / m_FPS;
	m_Clock.restart();
}


IntRect* Animator::getCurrentFrame(bool reversed)
{
	// Reversed adds 1 to the frame number 
	// when drawing the texture reversed.
	// This works because reversed 
	// (flipped horizontally) textures 
	// are drawn pixels right to left

	if (m_Clock.getElapsedTime().asMilliseconds()
		> m_FramePeriod)
	{
		m_CurrentFrame++;
		if (m_CurrentFrame >= m_FrameCount + reversed)
		{
			m_CurrentFrame = 0 + reversed;
		}

		m_Clock.restart();
	}

	m_SourceRect.left = m_LeftOffset + m_CurrentFrame
		* m_FrameWidth;

	return &m_SourceRect;
}
