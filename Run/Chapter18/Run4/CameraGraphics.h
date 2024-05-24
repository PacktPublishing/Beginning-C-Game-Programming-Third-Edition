#pragma once
#include "SFML/Graphics.hpp"
#include "Graphics.h"

using namespace sf;

class CameraGraphics :
	public Graphics
{
private:
	RenderWindow* m_Window;

	View m_View;
	int m_VertexStartIndex = -999;
	Texture* m_Texture = nullptr;
	FloatRect* m_Position = nullptr;

	bool m_IsMiniMap = false;

	// For zooming the mini map
	const float MIN_WIDTH = 640.0f;
	const float MAX_WIDTH = 2000.0f;

	// For the Time UI
	Text m_Text;
	Font m_Font;
	int m_TimeAtEndOfGame = 0;
	float m_Time = 0;

public:
	CameraGraphics(RenderWindow* window,
		Texture* texture,
		Vector2f viewSize,
		FloatRect viewport);

	float* getTimeConnection();


	// From Component : Graphics
	void assemble(VertexArray& canvas,
		shared_ptr<Update> genericUpdate,
		IntRect texCoords) override;

	void draw(VertexArray& canvas) override;
};
