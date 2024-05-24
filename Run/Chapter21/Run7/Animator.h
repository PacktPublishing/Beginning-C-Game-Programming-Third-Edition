#pragma once
#include<SFML/Graphics.hpp>

using namespace sf;

class Animator
{
private:
	IntRect m_SourceRect;
	int m_LeftOffset;
	int m_FrameCount;
	int m_CurrentFrame;
	int m_FramePeriod;
	int m_FrameWidth;
	int m_FPS = 12;
	Clock m_Clock;

public:

	Animator(
		int leftOffset, int topOffset,
		int frameCount,
		int textureWidth,
		int textureHeight,
		int fps);

	IntRect* getCurrentFrame(bool reversed);
};
