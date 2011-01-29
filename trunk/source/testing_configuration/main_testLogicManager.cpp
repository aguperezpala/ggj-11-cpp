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
Anim GetAnimFromImage(const sf::Image& img, float width, float height, int howMany)
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
	if (!img.LoadFromFile("../../resources/images/truck/House02.png"))
		return EXIT_FAILURE;

	Anim anim = GetAnimFromImage(img, 122.0f, 110.0f, 1);

	GameEntity gameEntity1(anim, 0.03f);
	GameEntity gameEntity2(anim, 0.03f);
	GameEntity gameEntity3(anim, 0.03f);

	// Loading a picture with anims.
	sf::Image fire;
	if (!fire.LoadFromFile("../../resources/images/fire2/1.png"))
		return EXIT_FAILURE;

	Anim fireAnim = GetAnimFromImage(fire, 82.0f, 88.0f, 1);

	GameEntity fireEntity1(fireAnim, 0.03f);
	GameEntity fireEntity2(fireAnim, 0.03f);
	GameEntity fireEntity3(fireAnim, 0.03f);

	// Loading a picture with anims.
	sf::Image map;
	if (!map.LoadFromFile("../../resources/images/background/bk32.png"))
		return EXIT_FAILURE;

	Anim animMap = GetAnimFromImage(map, 1024.0f, 768.0f, 1);

	GameEntity mapEntity(animMap, 0.03f);
	mapEntity.Stop();
	mapEntity.SetLoop(false);
	mapEntity.SetX(0.0f);
	mapEntity.SetY(0.0f);

	ScrollingManager::getInstance()->insertEntity(&fireEntity1);
	ScrollingManager::getInstance()->insertEntity(&fireEntity2);
	ScrollingManager::getInstance()->insertEntity(&fireEntity3);

	ScrollingManager::getInstance()->insertEntity(&gameEntity1);
	ScrollingManager::getInstance()->insertEntity(&gameEntity2);
	ScrollingManager::getInstance()->insertEntity(&gameEntity3);

	ScrollingManager::getInstance()->setVelocity(-200.0f);
	ScrollingManager::getInstance()->setActive(true);

	LogicManager logicManager(window.GetHeight(), window.GetWidth());
	logicManager.AddAffectable(&gameEntity1);
	logicManager.AddAffectable(&gameEntity2);
	logicManager.AddAffectable(&gameEntity3);
	logicManager.AddAffector(&fireEntity1);
	logicManager.AddAffector(&fireEntity2);
	logicManager.AddAffector(&fireEntity3);


	gameEntity1.Play();
	gameEntity1.SetLoop(true);
	gameEntity2.Play();
	gameEntity2.SetLoop(true);
	gameEntity3.Play();
	gameEntity3.SetLoop(true);

	fireEntity1.Play();
	fireEntity1.SetLoop(true);
	fireEntity2.Play();
	fireEntity2.SetLoop(true);
	fireEntity3.Play();
	fireEntity3.SetLoop(true);

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

		window.Draw(mapEntity);

		if(gameEntity1.IsActive())
			window.Draw(gameEntity1);
		if(gameEntity1.GetPosition().x + gameEntity1.GetWidth() < 0.0f)
			gameEntity1.SetActivation(false);


		if(gameEntity2.IsActive())
			window.Draw(gameEntity2);
		if(gameEntity2.GetPosition().x + gameEntity2.GetWidth() < 0.0f)
			gameEntity2.SetActivation(false);
			
		if(gameEntity3.IsActive())
			window.Draw(gameEntity3);
		if(gameEntity3.GetPosition().x + gameEntity3.GetWidth() < 0.0f)
			gameEntity3.SetActivation(false);

		gameEntity1.Update();
		gameEntity2.Update();
		gameEntity3.Update();

		if(fireEntity1.IsActive())
			window.Draw(fireEntity1);
		if(fireEntity1.GetPosition().x + fireEntity1.GetWidth() < 0.0f)
			fireEntity1.SetActivation(false);


		if(fireEntity2.IsActive())
			window.Draw(fireEntity2);
		if(fireEntity2.GetPosition().x + fireEntity2.GetWidth() < 0.0f)
			fireEntity2.SetActivation(false);

		if(fireEntity3.IsActive())
			window.Draw(fireEntity3);
		if(fireEntity3.GetPosition().x + fireEntity3.GetWidth() < 0.0f)
			fireEntity3.SetActivation(false);

		fireEntity1.Update();
		fireEntity2.Update();
		fireEntity3.Update();

		window.Display();

	}

	return 0;

}