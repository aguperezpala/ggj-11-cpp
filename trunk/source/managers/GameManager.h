#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H


//////////////////////////////////////////////////////////////////////////
//
//  Name:   GameManager.h
//
//  Desc:   GameManager class is responsible to coordinate the different
//          componentes of the game. It only has a function to run the game.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "managers/ImageManager.h"
#include "utilities/Fps.h"


// Forward declarations
class StateMachine;
class State;


class GameManager
{

public:

	GameManager(); 
	virtual ~GameManager(); 

	void Run();

	
private:

	//call this to update the machine
	void DrawFPS();

	StateMachine* m_pStateMachine;

	sf::RenderWindow* m_pScreen;

	Fps m_FpsManager;
	sf::Font* m_pFont;
	sf::String* m_pFpsText;

};


#endif // GAMEMANAGER_H
