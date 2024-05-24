#include "Factory.h"

#include "LevelUpdate.h"
#include "PlayerGraphics.h"
#include "PlayerUpdate.h"
#include "InputDispatcher.h"

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
	// Build a level game object
	GameObject level;
	shared_ptr<LevelUpdate> levelUpdate =
		make_shared<LevelUpdate>();
	level.addComponent(levelUpdate);
	gameObjects.push_back(level);

	// Build a player object
	GameObject player;
	shared_ptr<PlayerUpdate> playerUpdate =
		make_shared<PlayerUpdate>();
	playerUpdate->assemble(levelUpdate, nullptr);
	player.addComponent(playerUpdate);

	inputDispatcher.registerNewInputReceiver(
		playerUpdate->getInputReceiver());

	shared_ptr<PlayerGraphics> playerGraphics =
		make_shared<PlayerGraphics>();
	playerGraphics->assemble(canvas, playerUpdate,
		IntRect(PLAYER_TEX_LEFT, PLAYER_TEX_TOP,
			PLAYER_TEX_WIDTH, PLAYER_TEX_HEIGHT));
	player.addComponent(playerGraphics);

	gameObjects.push_back(player);


	// Make the LevelUpdate aware of the player
	levelUpdate->assemble(nullptr, playerUpdate);


}