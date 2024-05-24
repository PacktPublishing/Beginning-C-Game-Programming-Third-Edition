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

	//For the shaders and parallax background
	Shader m_Shader;
	bool m_ShowShader = false;
	bool m_BackgrounsAreFlipped = false;
	Clock m_ShaderClock;

	Vector2f m_PlayersPreviousPosition;
	Texture m_BackgroundTexture;
	Sprite m_BackgroundSprite;
	Sprite m_BackgroundSprite2;


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
