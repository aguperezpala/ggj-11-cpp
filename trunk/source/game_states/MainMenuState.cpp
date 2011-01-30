//////////////////////////////////////////////////////////////////////////
//
//  File: MainMenuState.cpp
//
//  Desc: State that represents the main menu of the game.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "MainMenuState.h"
#include "ControlsState.h"
#include "CreditsState.h"
#include "GameExplanationState.h"
#include "LoadingState.h"
#include "StateMachine.h"
#include <cassert>
	

const double MainMenuState::TIME_TO_WAIT = 0.2f;


// Default constructor
MainMenuState::MainMenuState() : InformationState() {}


// Destructor
MainMenuState::~MainMenuState() {}


MainMenuState* MainMenuState::Instance()
{

	static MainMenuState m_MainMenuState; // singleton...

	return (&m_MainMenuState);

}


void MainMenuState::Init(sf::RenderWindow* screen)
{
	
	InformationState::Init(screen);

	m_CurrentOption = MENUOPTION_NEWGAME;

	m_currentDelayOption = 0.0f;

}


void MainMenuState::UpdateInputs(StateMachine* pStateMachine)
{

	// Check if the player can change the current option or not.
	if(m_currentDelayOption > 0.0f)
		m_currentDelayOption -= m_pScreen->GetFrameTime();

	else
		CheckInputs(pStateMachine);

}


void MainMenuState::CheckInputs(StateMachine* pStateMachine)
{

	bool IsOptionChanged = false;

	// The player pushed the Up key
	if (m_pScreen->GetInput().IsKeyDown(sf::Key::Up))
	{

		IsOptionChanged = true;

		switch(m_CurrentOption)
		{

		case(MENUOPTION_NEWGAME):
			m_CurrentOption = MENUOPTION_EXIT;
			break;

		case(MENUOPTION_CONTROLS):
			m_CurrentOption = MENUOPTION_NEWGAME;
			break;

		case(MENUOPTION_GAMEEXPLANATION):
			m_CurrentOption = MENUOPTION_CONTROLS;
			break;

		case(MENUOPTION_CREDITS):
			m_CurrentOption = MENUOPTION_GAMEEXPLANATION;
			break;

		case(MENUOPTION_EXIT):
			m_CurrentOption = MENUOPTION_CREDITS;
			break;

		default:
			break;

		}

	}

	// The player pushed the Down key
	if (m_pScreen->GetInput().IsKeyDown(sf::Key::Down))
	{

		IsOptionChanged = true;

		switch(m_CurrentOption)
		{

		case(MENUOPTION_NEWGAME):
			m_CurrentOption = MENUOPTION_CONTROLS;
			break;

		case(MENUOPTION_CONTROLS):
			m_CurrentOption = MENUOPTION_GAMEEXPLANATION;
			break;

		case(MENUOPTION_GAMEEXPLANATION):
			m_CurrentOption = MENUOPTION_CREDITS;
			break;

		case(MENUOPTION_CREDITS):
			m_CurrentOption = MENUOPTION_EXIT;
			break;

		case(MENUOPTION_EXIT):
			m_CurrentOption = MENUOPTION_NEWGAME;
			break;

		default:
			break;

		}

	}

	// The player pushed the Return key
	if (m_pScreen->GetInput().IsKeyDown(sf::Key::Return))
	{

		IsOptionChanged = true;

		switch(m_CurrentOption)
		{

		case(MENUOPTION_NEWGAME):
			pStateMachine->ChangeState(LoadingState::Instance());
			break;

		case(MENUOPTION_CONTROLS):
			pStateMachine->ChangeState(ControlsState::Instance());
			break;

		case(MENUOPTION_GAMEEXPLANATION):
			pStateMachine->ChangeState(GameExplanationState::Instance());
			break;

		case(MENUOPTION_CREDITS):
			pStateMachine->ChangeState(CreditsState::Instance());
			break;

		case(MENUOPTION_EXIT):
			m_pScreen->Close();
			break;

		default:
			break;

		}

	}

	// If the option changed, then we need to wait for a new one
	m_currentDelayOption = TIME_TO_WAIT;

}


void MainMenuState::DrawTitle()
{

	/*assert(m_pText && "MainMenuState::DrawTitle(): trying to use to a NULL text");

	m_pText->SetText("The Last Fireman");
	m_pText->SetStyle(sf::String::Bold);
	m_pText->SetColor(sf::Color::Red);
	float xCoord = float(m_pScreen->GetWidth())/2.0f  - m_pText->GetRect().GetWidth()/2.0f;
	float yCoord = float(m_pScreen->GetHeight())*0.2f;
	m_pText->SetPosition(xCoord, yCoord);
	m_pScreen->Draw(*m_pText);*/

}


void MainMenuState::DrawContent()
{

	assert(m_pText && "MainMenuState::DrawMenuOptions(): trying to use to a NULL text");

	// Default style
	m_pText->SetStyle(sf::String::Regular);
	m_pText->SetColor(sf::Color::White);

	// Menu Options
	m_pText->SetText("New Game");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.6f, float(m_pScreen->GetHeight())*0.4f);
	if(m_CurrentOption == MENUOPTION_NEWGAME)
	{

		m_pText->SetStyle(sf::String::Bold);
		m_pText->SetColor(sf::Color::Black);

	}
	m_pScreen->Draw(*m_pText);
	m_pText->SetStyle(sf::String::Regular);
	m_pText->SetColor(sf::Color::White);


	m_pText->SetText("Controls");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.6f, float(m_pScreen->GetHeight())*0.4f + 50.0f);
	if(m_CurrentOption == MENUOPTION_CONTROLS)
	{

		m_pText->SetStyle(sf::String::Bold);
		m_pText->SetColor(sf::Color::Black);

	}
	m_pScreen->Draw(*m_pText);
	m_pText->SetStyle(sf::String::Regular);
	m_pText->SetColor(sf::Color::White);


	m_pText->SetText("Game Explanation");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.6f, float(m_pScreen->GetHeight())*0.4f + 100.0f);
	if(m_CurrentOption == MENUOPTION_GAMEEXPLANATION)
	{

		m_pText->SetStyle(sf::String::Bold);
		m_pText->SetColor(sf::Color::Black);

	}
	m_pScreen->Draw(*m_pText);
	m_pText->SetStyle(sf::String::Regular);
	m_pText->SetColor(sf::Color::White);


	m_pText->SetText("Credits");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.6f, float(m_pScreen->GetHeight())*0.4f + 150.0f);
	if(m_CurrentOption == MENUOPTION_CREDITS)
	{

		m_pText->SetStyle(sf::String::Bold);
		m_pText->SetColor(sf::Color::Black);

	}
	m_pScreen->Draw(*m_pText);
	m_pText->SetStyle(sf::String::Regular);
	m_pText->SetColor(sf::Color::White);


	m_pText->SetText("Exit");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.6f, float(m_pScreen->GetHeight())*0.4f + 200.0f);
	if(m_CurrentOption == MENUOPTION_EXIT)
	{

		m_pText->SetStyle(sf::String::Bold);
		m_pText->SetColor(sf::Color::Black);

	}
	m_pScreen->Draw(*m_pText);
	m_pText->SetStyle(sf::String::Regular);
	m_pText->SetColor(sf::Color::White);

}
