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
#include "GameEntity.h"
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


void UpdateEntity(GameEntity& entity, GameEntity& entity2, const sf::Input& input, float frameTime)
{

	entity.Update();
	entity2.Update();

	if(input.IsKeyDown(sf::Key::Up))
		entity.Move(0.0f, -100.0f * frameTime);

	if (input.IsKeyDown(sf::Key::Down))
		entity.Move(0.0f, 100.0f * frameTime);

	if(input.IsKeyDown(sf::Key::Left))
		entity.Move(-100.0f * frameTime, 0.0f);

	if (input.IsKeyDown(sf::Key::Right))
		entity.Move(100.0f * frameTime, 0.0f);


	if(input.IsKeyDown(sf::Key::S))
		entity2.Play();
	else
		entity2.Pause();

	entity2.SetX(entity.GetPosition().x);
	entity2.SetY(entity.GetPosition().y);


}



//
// Main
//
int main()
{

	sf::RenderWindow window(sf::VideoMode(1024, 768, 32), "main_testGameEntity");

	// Loading a picture with anims.
	sf::Image img;
	if (!img.LoadFromFile("../../resources/images/truck/TruckFordward1.png"))
		return EXIT_FAILURE;

	Anim anim = GetAnimFromImage(img, 200.0f, 120.0f, 1);

	GameEntity gameEntity1(anim, 0.03f);
	gameEntity1.Play();
	gameEntity1.SetLoop(false);
	gameEntity1.SetX(0.0f);
	gameEntity1.SetY(0.0f);

	// Loading a picture with anims.
	sf::Image map;
	if (!map.LoadFromFile("../../resources/images/background/bk1024.png"))
		return EXIT_FAILURE;

	Anim animMap = GetAnimFromImage(map, 1024.0f, 768.0f, 1);

	GameEntity mapEntity(animMap, 0.03f);
	mapEntity.Stop();
	mapEntity.SetLoop(false);
	mapEntity.SetX(0.0f);
	mapEntity.SetY(0.0f);

	// Loading a picture with anims.
	sf::Image cannon;
	if (!cannon.LoadFromFile("../../resources/images/truck/cannon.png"))
		return EXIT_FAILURE;

	Anim animCannon = GetAnimFromImage(cannon, 180.0f, 115.0f, 18);

	GameEntity cannonEntity(animCannon, 0.03f);
	cannonEntity.Play();
	cannonEntity.SetLoop(true);
	cannonEntity.SetX(550.0f);
	cannonEntity.SetY(550.0f);
	

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

		// Draw everything.
		window.Clear(); 
		UpdateEntity(gameEntity1, cannonEntity, window.GetInput(), window.GetFrameTime());
		window.Draw(mapEntity);
		window.Draw(gameEntity1);
		window.Draw(cannonEntity);
		window.Display();

	}

	return 0;

}