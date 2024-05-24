#pragma once
#include "Graphics.h"
#include "SFML/Graphics.hpp"

using namespace sf;

class PlatformGraphics : public Graphics
{
private:
	FloatRect* m_Position = nullptr;
	int m_VertexStartIndex = -1;

public:

	//From Graphics : Component
	void draw(VertexArray& canvas) override;

	void assemble(VertexArray& canvas,
		shared_ptr<Update> genericUpdate,
		IntRect texCoords) override;

};
