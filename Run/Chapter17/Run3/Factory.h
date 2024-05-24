#pragma once
#include <vector>
#include "GameObject.h"
#include "SFML/Graphics.hpp"

using namespace sf;
using namespace std;

class InputDispatcher;

class Factory
{
private:
	RenderWindow* m_Window;

	const int PLAYER_TEX_LEFT = 0;
	const int PLAYER_TEX_TOP = 0;
	const int PLAYER_TEX_WIDTH = 80;
	const int PLAYER_TEX_HEIGHT = 96;

	const float CAM_VIEW_WIDTH = 300.f;

	const float CAM_SCREEN_RATIO_LEFT = 0.f;
	const float CAM_SCREEN_RATIO_TOP = 0.f;
	const float CAM_SCREEN_RATIO_WIDTH = 1.f;
	const float CAM_SCREEN_RATIO_HEIGHT = 1.f;

	const int CAM_TEX_LEFT = 610;
	const int CAM_TEX_TOP = 36;
	const int CAM_TEX_WIDTH = 40;
	const int CAM_TEX_HEIGHT = 30;

	const float MAP_CAM_SCREEN_RATIO_LEFT = 0.3f;
	const float MAP_CAM_SCREEN_RATIO_TOP = 0.84f;
	const float MAP_CAM_SCREEN_RATIO_WIDTH = 0.4f;
	const float MAP_CAM_SCREEN_RATIO_HEIGHT = 0.15f;

	const float MAP_CAM_VIEW_WIDTH = 800.f;
	const float MAP_CAM_VIEW_HEIGHT = MAP_CAM_VIEW_WIDTH / 2;

	const int MAP_CAM_TEX_LEFT = 665;
	const int MAP_CAM_TEX_TOP = 0;
	const int MAP_CAM_TEX_WIDTH = 100;
	const int MAP_CAM_TEX_HEIGHT = 70;

	const int PLATFORM_TEX_LEFT = 607;
	const int PLATFORM_TEX_TOP = 0;
	const int PLATFORM_TEX_WIDTH = 10;
	const int PLATFORM_TEX_HEIGHT = 10;

	const int TOP_MENU_TEX_LEFT = 770;
	const int TOP_MENU_TEX_TOP = 0;
	const int TOP_MENU_TEX_WIDTH = 100;
	const int TOP_MENU_TEX_HEIGHT = 100;

	const int RAIN_TEX_LEFT = 0;
	const int RAIN_TEX_TOP = 100;
	const int RAIN_TEX_WIDTH = 100;
	const int RAIN_TEX_HEIGHT = 100;


public:
	Factory(RenderWindow* window);

	void loadLevel(
		vector <GameObject>& gameObjects,
		VertexArray& canvas,
		InputDispatcher& inputDispatcher);

	//Make private soon
	Texture* m_Texture;
};
