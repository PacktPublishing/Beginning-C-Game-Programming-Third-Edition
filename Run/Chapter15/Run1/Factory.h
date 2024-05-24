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

public:
	Factory(RenderWindow* window);

	void loadLevel(
		vector <GameObject>& gameObjects,
		VertexArray& canvas,
		InputDispatcher& inputDispatcher);

	//Make private soon
	Texture* m_Texture;
};
