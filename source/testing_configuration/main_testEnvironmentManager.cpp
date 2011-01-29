//////////////////////////////////////////////////////////////////////////
//
// File: main_testScrollingManager.cpp
//
// Desc: Main entry point to test the GameEntity class functionality.
//
//
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "GameEntity.h"
#include "Environment.h"
#include "EnvironmentManager.h"
#include <iostream>


//
// Auxiliar functions
//

// Get an Anim from an Image
Anim GetAnimFromImage(const sf::Image& img, float height, float width, int howMany)
{

	// Add each frame
	Anim anim;
	for (int i=0; i<howMany; i++)
		anim.PushFrame(Frame(img, sf::IntRect(width*i, 0, width * (i+1), height)));

	return anim;

}


void UpdateEntity(GameEntity& entity)
{
	
	entity.Update();
	entity.Play(); // In case of not currently playing.
	
}


//
// Main
//
int main()
{

	sf::RenderWindow window(sf::VideoMode(1024, 768, 32), "main_testGameEntity");

	// Loading a picture with anims.
	sf::Image img;
	sf::Image img2;
	if (!img.LoadFromFile("../../resources/images/background/backgroundtex1.png"))
		return EXIT_FAILURE;
	if (!img2.LoadFromFile("../../resources/images/background/backgroundtex1.png"))
			return EXIT_FAILURE;

	EnvironmentManager envMan(768, 1024);

	Anim anim = GetAnimFromImage(img, 768.0f, 1024.0f, 1);
	Anim anim2 = GetAnimFromImage(img, 768.0f, 1024.0f, 1);

	GameEntity gameEntity(anim, 0.03f);
	gameEntity.SetPosition(9999.0f, 500.0f);
	GameEntity gameEntity2(anim, 0.03f);
	gameEntity2.SetPosition(9001.0f, 500.0f);

	unsigned int Seed = 10;
	sf::Randomizer::SetSeed(Seed);

	std::vector<GameEntity *> maps;
	maps.push_back(&gameEntity);
	maps.push_back(&gameEntity2);

	Environment env("test", maps, true, 555555.0f);

	envMan.pushEnvironment(&env);
	envMan.setActive(true);
	ScrollingManager::getInstance()->setActive(true);
	ScrollingManager::getInstance()->setVelocity(-156.0f);

	// Main loop.
	sf::Event event;
	bool running = true;
	while (running)
	{

		// Events loop.
		while (window.GetEvent(event))
		{

			// Here we just deal with close event.
			// Moving is handle by sf::Input.
			switch (event.Type)
			{

			case sf::Event::Closed:
				running = false;
				break;

			default:
				break;
			}

		}
		if(window.GetInput().IsKeyDown(sf::Key::Up)){
			ScrollingManager::getInstance()->increaseVelocity(-10);
		} else if (window.GetInput().IsKeyDown(sf::Key::Down)) {
			ScrollingManager::getInstance()->increaseVelocity(10);
		}


		ScrollingManager::getInstance()->update(window.GetFrameTime());
		envMan.update(window.GetFrameTime());

			// Draw everything.
		window.Clear(); 
		window.Draw(gameEntity);
		window.Draw(gameEntity2);
		window.Display();

	}

	return 0;

}
