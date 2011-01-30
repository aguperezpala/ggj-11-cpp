//////////////////////////////////////////////////////////////////////////
//
//  File:   GameExplanationState.cpp
//
//  Desc:   Game state that explains how to play and the game objective
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "GameExplanationState.h"
#include "StateMachine.h"
#include "MainMenuState.h"
#include <cassert>


// Default constructor 
GameExplanationState::GameExplanationState() : InformationState() {} 


// Destructor
GameExplanationState::~GameExplanationState() {}


GameExplanationState* GameExplanationState::Instance()
{

	static GameExplanationState m_GameExplanationState; // singleton...

	return (&m_GameExplanationState);

}


void GameExplanationState::UpdateInputs(StateMachine* pStateMachine)
{

	if (m_pScreen->GetInput().IsKeyDown(sf::Key::Escape))
		pStateMachine->ChangeState(MainMenuState::Instance());

}


void GameExplanationState::DrawTitle()
{

	/*assert(m_pText && "GameExplanationState::DrawTitle(): trying to use to a NULL text");

	// Title
	m_pText->SetText("Game Explanation");
	m_pText->SetStyle(sf::String::Bold);
	m_pText->SetColor(sf::Color::Black);
	float xCoord = float(m_pScreen->GetWidth())/2.0f  - m_pText->GetRect().GetWidth()/2.0f;
	float yCoord = float(m_pScreen->GetHeight())*0.2f;
	m_pText->SetPosition(xCoord, yCoord);
	m_pScreen->Draw(*m_pText);

	// Default style
	m_pText->SetStyle(sf::String::Regular);
	m_pText->SetColor(sf::Color::White);
	m_pText->SetSize(40.0f);*/

}


void GameExplanationState::DrawContent()
{

	assert(m_pText && "GameExplanationState::DrawControls(): trying to use to a NULL text");

	m_pText->SetSize(30.0f);

	// Menu Options
	m_pText->SetText("You are the last fireman in the world and \n must extinguish all the fire in your road. \n");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.25f, float(m_pScreen->GetHeight())*0.4f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Each time you extinguish a fire, you will \n be prized with more time in your timer.");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.25f, float(m_pScreen->GetHeight())*0.4f + 60.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("When your timer reaches zero, you will lose, \n because the world cannot be saved from the entire burn.");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.25f, float(m_pScreen->GetHeight())*0.4f + 120.0f);
	m_pScreen->Draw(*m_pText);

	/*m_pText->SetText("-Don't kill black wolves.");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 80.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("In the Night:");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 120.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("-Kill black wolves.");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 160.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("-Don't kill white wolves.");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 200.0f);
	m_pScreen->Draw(*m_pText);*/

	m_pText->SetText("Press ESC to go to main menu");
	
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.3f, float(m_pScreen->GetHeight())*0.4f + 300.0f);
	m_pScreen->Draw(*m_pText);

}
