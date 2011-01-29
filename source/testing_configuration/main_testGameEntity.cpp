//////////////////////////////////////////////////////////////////////////
//
// File: main_testGameEntity.cpp
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



void UpdateEntity(GameEntity& entity, const sf::Input& input)
{
	entity.Update();

	if (input.IsKeyDown(sf::Key::Up))
		entity.Play(); // In case of not currently playing.

	else
		entity.Pause();

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
	{
	
		std::cerr << "Error : cannot load character.png.\n";
		return EXIT_FAILURE;

	}
	

	Anim anim = GetAnimFromImage(img, 146.0f, 146.0f, 18);

	GameEntity gameEntity(anim, 0.03f);
	gameEntity.SetPosition(500.0f, 500.0f);

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

		// Make all updates.
		UpdateEntity(gameEntity, window.GetInput());

		// Draw everything.
		window.Clear(); 
		window.Draw(gameEntity);
		window.Display();

	}

	return 0;

}