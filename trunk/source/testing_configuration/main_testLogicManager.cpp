//////////////////////////////////////////////////////////////////////////
//
// File: main_testLogicManager.cpp
//
// Desc: Main file to test the LogicManager class
//
//
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "LogicManager.h"
#include "ScrollingManager.h"
#include "GameEntity.h"
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

	GameEntity gameEntity1(anim, 0.03f);
	GameEntity gameEntity2(anim, 0.03f);
	GameEntity gameEntity3(anim, 0.03f);

	ScrollingManager::getInstance()->insertEntity(&gameEntity1);
	ScrollingManager::getInstance()->insertEntity(&gameEntity2);
	ScrollingManager::getInstance()->insertEntity(&gameEntity3);
	ScrollingManager::getInstance()->setVelocity(-200.0f);
	ScrollingManager::getInstance()->setActive(true);

	LogicManager logicManager(window.GetHeight(), window.GetWidth());
	logicManager.AddAffectable(&gameEntity1);
	logicManager.AddAffectable(&gameEntity2);
	logicManager.AddAffectable(&gameEntity3);

	gameEntity1.Play();
	gameEntity1.SetLoop(true);
	gameEntity2.Play();
	gameEntity2.SetLoop(true);
	gameEntity3.Play();
	gameEntity3.SetLoop(true);

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


		ScrollingManager::getInstance()->update(window.GetFrameTime());
		logicManager.Update(window.GetFrameTime());


		// Draw everything.
		window.Clear(); 
		if(gameEntity1.IsActive())
			window.Draw(gameEntity1);
		else if(gameEntity1.GetPosition().x + gameEntity1.GetWidth() < 0.0f)
			gameEntity1.SetActivation(false);

		if(gameEntity2.IsActive())
			window.Draw(gameEntity2);
		else if(gameEntity2.GetPosition().x + gameEntity2.GetWidth() < 0.0f)
			gameEntity2.SetActivation(false);
			
		if(gameEntity3.IsActive())
			window.Draw(gameEntity3);
		else if(gameEntity3.GetPosition().x + gameEntity3.GetWidth() < 0.0f)
			gameEntity3.SetActivation(false);


		window.Display();

	}

	return 0;

}