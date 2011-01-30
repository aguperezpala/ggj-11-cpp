//////////////////////////////////////////////////////////////////////////
//
//  File:   ControlsState.h
//
//  Desc:   Game state that shows the player's controls.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "ControlsState.h"
#include "StateMachine.h"
#include "MainMenuState.h"
#include <cassert>


// Default constructor 
ControlsState::ControlsState() : InformationState() {}


// Destructor
ControlsState::~ControlsState() {}


ControlsState* ControlsState::Instance()
{

	static ControlsState m_ControlsState; // singleton...

	return (&m_ControlsState);

}


void ControlsState::UpdateInputs(StateMachine* pStateMachine)
{
	
	if (m_pScreen->GetInput().IsKeyDown(sf::Key::Escape))
		pStateMachine->ChangeState(MainMenuState::Instance());

}


void ControlsState::DrawTitle()
{

	/*assert(m_pText && "ControlsState::DrawTitle(): trying to use to a NULL text");

	// Title
	m_pText->SetText("Controls");
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


void ControlsState::DrawContent()
{
	
	assert(m_pText && "ControlsState::DrawControls(): trying to use to a NULL text");

	m_pText->SetSize(30.0f);
	m_pText->SetColor(sf::Color::Blue);

	// Menu Options
	m_pText->SetText("Left/Right Arrows: Acceleration");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.5f, float(m_pScreen->GetHeight())*0.4f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Mouse: Move the fire hose");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.5f, float(m_pScreen->GetHeight())*0.4f + 40.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Left Click: Shoot a water balloon");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.5f, float(m_pScreen->GetHeight())*0.4f + 80.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Up/Down Arrow: Move the fire truck");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.5f, float(m_pScreen->GetHeight())*0.4f + 120.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Esc: Main Menu");
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.5f, float(m_pScreen->GetHeight())*0.4f + 160.0f);
	m_pScreen->Draw(*m_pText);

	m_pText->SetText("Press ESC to go to main menu");
	//m_pText->SetSize(50.0f);
	m_pText->SetPosition(float(m_pScreen->GetWidth())*0.5f, float(m_pScreen->GetHeight())*0.4f + 300.0f);
	m_pScreen->Draw(*m_pText);

}
