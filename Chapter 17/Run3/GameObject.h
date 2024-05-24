#pragma once
#include "SFML/Graphics.hpp"
#include "Component.h"
#include <vector>

using namespace sf;
using namespace std;

class GameObject
{
private:
	vector <shared_ptr<Component>>  m_Components;

public:
	void addComponent(shared_ptr<Component> newComponent);
	void update(float elapsedTime);
	void draw(VertexArray& canvas);
};