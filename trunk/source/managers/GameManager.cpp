//////////////////////////////////////////////////////////////////////////
//
//  Name:   GameManager.cpp
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
#include "GameManager.h"
#include <cassert>
#include <sstream>
#include "game_states/MainMenuState.h"
#include "game_states/StateMachine.h"


// Constructor
GameManager::GameManager() :  m_pStateMachine(0), m_pScreen(0), m_pFont(0), m_pFpsText(0)
{

	InitScreen();

	InitStateMachine();

	InitText();
		
}


// Destructor
GameManager::~GameManager()
{

	if(m_pStateMachine != 0)
	{

		delete m_pStateMachine;
		m_pStateMachine = 0;

	}

	if(m_pScreen != 0)
	{

		delete m_pScreen;
		m_pScreen = 0;

	}

	if(m_pFont != 0)
	{
	
		delete m_pFont;
		m_pFont = 0;

	}

	if(m_pFpsText != 0)
	{

		delete m_pFpsText;
		m_pFpsText = 0;

	}

		
}


void GameManager::Run()
{

	assert(m_pScreen && "GameManager::Run(): The RenderWindow is NULL");
	assert(m_pStateMachine && "GameManager::Run(): The StateMachine is NULL");

	// Start game loop
	while (m_pScreen->IsOpened())
	{
		// Process events
		sf::Event Event;
		while (m_pScreen->GetEvent(Event))
		{

			// Close window : exit
			if (Event.Type == sf::Event::Closed)
				m_pScreen->Close();

		}

		// Clear the screen (fill it with black color)
		m_pScreen->Clear();

		m_pStateMachine->Update();

		DrawFPS();

		// Display window contents on screen
		m_pScreen->Display();

		m_FpsManager.Update();

	}

}


void GameManager::InitScreen()
{

	m_pScreen = new sf::RenderWindow(sf::VideoMode(1024, 768, 32), "The Last Fireman", sf::Style::Fullscreen | sf::Style::Close);
	m_pScreen->ShowMouseCursor(false);

}


void GameManager::InitStateMachine()
{

	m_pStateMachine = new StateMachine(m_pScreen);
	m_pStateMachine->ChangeState(MainMenuState::Instance());

}


void GameManager::InitText()
{

	InitFont();
	
	assert(m_pFont && "GameManager::InitText(): The font is not correctly loaded");
	
	m_pFpsText = new sf::String("", *m_pFont);
	m_pFpsText->SetSize(30.0f);
	float xCoord = 10.0f;
	float yCoord = 10.0f;
	m_pFpsText->SetPosition(xCoord, yCoord);
	m_pFpsText->SetStyle(sf::String::Regular);
	m_pFpsText->SetColor(sf::Color::White);

}


void GameManager::InitFont()
{

	m_pFont = new sf::Font();
	bool correctLoading = m_pFont->LoadFromFile("../../resources/fonts/calibri.ttf");

}


void GameManager::DrawFPS()
{
	
	assert(m_pFpsText && " GameManager::DrawFPS(): The text is NULL");

	std::ostringstream oss; 
	oss << "FPS" << " " << m_FpsManager.GetFPS();
	m_pFpsText->SetText(oss.str());
	m_pScreen->Draw(*m_pFpsText);		

}
