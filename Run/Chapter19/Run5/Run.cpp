#pragma once
#include "SFML/Graphics.hpp"

#include <vector>

#include "GameObject.h"
#include "Factory.h"
#include "InputDispatcher.h"

using namespace std;
using namespace sf;

int main()
{
	// Create a fullscreen window.
	RenderWindow window(
		VideoMode::getDesktopMode(),
		"Booster", Style::Fullscreen);

	// A VertexArray to hold all our graphics.
	VertexArray canvas(Quads, 0);

	// This can dispatch events to any object.
	InputDispatcher inputDispatcher(&window);

	// Everything will be a game object.
	// This vector will hold them all.
	vector <GameObject> gameObjects;

	// This class has all the knowledge
	// to construct game objects that do
	// many different things.
	Factory factory(&window);

	// This call will send the vector of game objects
	// the canvas to draw on and the input dispatcher
	// to the factory to set up the game.
	factory.loadLevel(gameObjects,
		canvas,
		inputDispatcher);

	// A clock for timing.
	Clock clock;

	// The color we use for the background
	const Color BACKGROUND_COLOR(100, 100, 100, 255);

	// This is the game loop.
	// We do not need to add to it.
	// Look how short and simple it is!
	while (window.isOpen())
	{
		// Measure the time taken this frame.
		float timeTakenInSeconds =
			clock.restart().asSeconds();

		// Handle the player input.
		inputDispatcher.dispatchInputEvents();

		// Clear the previous frame.
		window.clear(BACKGROUND_COLOR);

		// Update all the game objects.
		for (auto& gameObject : gameObjects)
		{
			gameObject.update(timeTakenInSeconds);
		}

		// Draw all the game objects to the canvas.
		for (auto& gameObject : gameObjects)
		{
			gameObject.draw(canvas);
		}

		// Show the new frame.
		window.display();
	}

	return 0;
}
