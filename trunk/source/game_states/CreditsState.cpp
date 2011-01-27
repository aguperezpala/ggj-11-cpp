//////////////////////////////////////////////////////////////////////////
//
//  File:   CreditsState.cpp
//
//  Desc:   State that shows the credits of the game (programmers, artists)
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "CreditsState.h"
#include "StateMachine.h"
#include "MainMenuState.h"
#include <cassert>


// Default constructor 
CreditsState::CreditsState() : InformationState() {}


// Destructor
CreditsState::~CreditsState() {}


CreditsState* CreditsState::Instance()
{

	static CreditsState m_CreditsState; // singleton...

	return (&m_CreditsState);

}


void CreditsState::UpdateInputs(StateMachine* pStateMachine)
{

	if (m_pScreen->GetInput().IsKeyDown(sf::Key::Escape))
		pStateMachine->ChangeState(MainMenuState::Instance());

}


void CreditsState::DrawTitle()
{

	m_pText->SetText("Credits");
	m_pText->SetStyle(sf::String::Bold);
	m_pText->SetColor(sf::Color::Black);
	float xCoord = float(m_pScreen->GetWidth())/2.0f  - m_pText->GetRect().GetWidth()/2.0f;
	float yCoord = float(m_pScreen->GetHeight())*0.2f;
	m_pText->SetPosition(xCoord, yCoord);
	m_pScreen->Draw(*m_pText);

}


void CreditsState::DrawContent()
{

	// Default style
	m_pText->SetStyle(sf::String::Regular);
	m_pText->SetColor(sf::Color::White);
	m_pText->SetSize(30.0f);


	// Menu Options
	m_pText->SetText("Artists:");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Guillermo Oursi - ginger3d@hotmail.com");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 40.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Damian Linossi - odapuma@hotmail.com");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 80.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Mariano Bertoa - mariano.bertoa@hotmail.com ");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 120.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Programmers:");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 160.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Nicolas Bertoa - nicobertoa@gmail.com");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 200.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Press ESC to go to main menu");
	m_pText->SetSize(50.0f);
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 300.0f);
	m_pScreen->Draw(*m_pText);

}
