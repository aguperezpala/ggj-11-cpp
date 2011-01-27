#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H


//////////////////////////////////////////////////////////////////////////
//
//  File: MainMenuState.h
//
//  Desc: State that represents the main menu of the game.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "InformationState.h"


class MainMenuState : public InformationState
{

public:

	virtual ~MainMenuState();
	static MainMenuState* Instance();

	//this will execute when the state is entered
	virtual void Init(sf::RenderWindow* screen);

	
protected:

	enum MenuOption
	{

		MENUOPTION_DEFAULT,
		MENUOPTION_ERROR,
		MENUOPTION_NEWGAME,
		MENUOPTION_CONTROLS,
		MENUOPTION_GAMEEXPLANATION,
		MENUOPTION_CREDITS,
		MENUOPTION_EXIT

	};

	void UpdateInputs(StateMachine* pStateMachine);
	
	void DrawTitle();
	void DrawContent();


private:

	MainMenuState();

	void CheckInputs(StateMachine* pStateMachine);
	
	MenuOption m_CurrentOption;				    // Current option that will be highlighted

	double m_currentDelayOption;		        // Current time elapsed from the last change of option
	static const double TIME_TO_WAIT;		    // Time to wait before the player can change the menu option.

};


#endif // MAINMENUSTATE_H
