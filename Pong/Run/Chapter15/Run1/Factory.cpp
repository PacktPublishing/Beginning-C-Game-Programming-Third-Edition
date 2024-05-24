#include "Factory.h"
#include <iostream>

using namespace std;

Factory::Factory(RenderWindow* window)
{
	m_Window = window;
	m_Texture = new Texture();
	if (!m_Texture->loadFromFile("graphics/texture.png"))
	{
		cout << "Texture not loaded";
		return;
	}
}

void Factory::loadLevel(
	vector<GameObject>& gameObjects,
	VertexArray& canvas,
	InputDispatcher& inputDispatcher)
{

}