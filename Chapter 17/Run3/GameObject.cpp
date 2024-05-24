#include "GameObject.h"
#include "SFML/Graphics.hpp"
#include <iostream>
#include "Update.h"
#include "Graphics.h"

using namespace std;
using namespace sf;

void GameObject::addComponent(
	shared_ptr<Component> newComponent)
{
	m_Components.push_back(newComponent);
}

void GameObject::update(float elapsedTime)
{
	for (auto component : m_Components)
	{
		if (component->m_IsUpdate)
		{
			static_pointer_cast<Update>
				(component)->update(elapsedTime);
		}
	}
}

void GameObject::draw(VertexArray& canvas)
{
	for (auto component : m_Components)
	{
		if (component->m_IsGraphics)
		{
			static_pointer_cast<Graphics>
				(component)->draw(canvas);
		}
	}
}
