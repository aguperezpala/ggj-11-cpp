//////////////////////////////////////////////////////////////////////////
//
// File: InformationState.cpp
//
// Desc: Abstract state that provides functionality to states that
//       will need to show information on the screen like main menu, 
//       controls, game explanation, etc.
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "InformationState.h"
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include <cassert>


// Default constructor 
InformationState::InformationState() : State(), m_pScreen(0), m_pBackgroundImage(0), m_pFont(0), m_pText(0) {} 


// Destructor
InformationState::~InformationState() {}


void InformationState::Init(sf::RenderWindow* screen)
{

	LoadResources(screen);

	InitFont();
	InitText();

}


void InformationState::Execute(StateMachine* pStateMachine)
{

	Draw();
	UpdateInputs(pStateMachine);

}


void InformationState::Clear()
{

	DestroyResources();

}


void InformationState::LoadResources(sf::RenderWindow* screen)
{

	assert(screen && "InformationState::LoadResources(): trying to initialize to a NULL RenderWindow");

	m_pScreen = screen;

	imgManager.Load("../../resources/images/background/main_screen.png");

	m_pBackgroundImage = new sf::Sprite();

	assert(m_pBackgroundImage && "InformationState::LoadResources(sf::RenderWindow* screen): Image for the menu is NULL");

	m_pBackgroundImage->SetImage(imgManager["../../resources/images/background/main_screen.png"]);
	m_pBackgroundImage->Resize(float(m_pScreen->GetWidth()), float(m_pScreen->GetHeight()));
	m_pBackgroundImage->SetPosition(0.0f, 0.0f);

}


void InformationState::DestroyResources()
{

	imgManager.Destroy("../../resources/images/background/main_screen.png");

	if(m_pFont != 0)
	{

		delete m_pFont;
		m_pFont = 0;

	}


	if(m_pText != 0)
	{

		delete m_pText;
		m_pText = 0;

	}


	if(m_pBackgroundImage != 0)
	{

		delete m_pBackgroundImage;
		m_pBackgroundImage = 0;

	}

}


void InformationState::InitFont()
{

	m_pFont = new sf::Font();
	bool correctLoading = m_pFont->LoadFromFile("../../resources/fonts/calibri.ttf");
	assert(correctLoading && "GameExplanationState::InitFont() Font is not correctly loaded");


}


void InformationState::InitText()
{

	// Init text
	m_pText = new sf::String("", *m_pFont);
	m_pText->SetSize(50.0f);
	m_pText->SetStyle(sf::String::Regular);
	m_pText->SetColor(sf::Color::White);

}


void InformationState::Draw()
{

	assert(m_pBackgroundImage && "GameExplanationState::::Draw(): trying to draw to a NULL image");

	m_pScreen->Draw(*m_pBackgroundImage);

	DrawText();

}


void InformationState::DrawText()
{

	DrawTitle();
	DrawContent();

}
