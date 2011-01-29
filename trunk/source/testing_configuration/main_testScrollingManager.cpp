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
#include "../entities/GameEntity.h"
#include "ScrollingManager.h"
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
	if (!img.LoadFromFile("../../resources/images/truck/canon.png"))
		return EXIT_FAILURE;

	Anim anim = GetAnimFromImage(img, 146.0f, 146.0f, 18);

	GameEntity gameEntity(anim, 0.03f);
	gameEntity.SetPosition(900.0f, 500.0f);

	ScrollingManager::getInstance()->insertEntity(&gameEntity);
	ScrollingManager::getInstance()->setVelocity(-200.0f);
	ScrollingManager::getInstance()->setActive(true);

	unsigned int Seed = 10;
	sf::Randomizer::SetSeed(Seed);

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


		UpdateEntity(gameEntity);


		int Random = sf::Randomizer::Random(-600, 600);
		ScrollingManager::getInstance()->setVelocity(float(Random));
		ScrollingManager::getInstance()->update(window.GetFrameTime());

			// Draw everything.
		window.Clear(); 
		window.Draw(gameEntity);
		window.Display();

	}

	return 0;

}