//////////////////////////////////////////////////////////////////////////
//
//  File:   ThanksState.h
//
//  Desc:   Game state that shows a thanks message for playing the game.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "ThanksState.h"
#include "StateMachine.h"
#include "MainMenuState.h"
#include <cassert>


// Default constructor 
ThanksState::ThanksState() : State(), m_pScreen(0), m_pBackgroundImage(0) {}


// Destructor
ThanksState::~ThanksState() {}


ThanksState* ThanksState::Instance()
{

	static ThanksState m_ThanksState; // singleton...

	return (&m_ThanksState);

}


void ThanksState::Init(sf::RenderWindow* screen)
{

	LoadResources(screen);

	m_DelayForNextState = 5.0f;

}


void ThanksState::Execute(StateMachine* pStateMachine)
{

	// Check if we must show the thanks message or change the state.
	if(m_DelayForNextState > 0.0f)
	{

		m_DelayForNextState -= m_pScreen->GetFrameTime();

		m_pScreen->Draw(*m_pBackgroundImage);

	}

	else
		pStateMachine->ChangeState(MainMenuState::Instance());

}


void ThanksState::Clear()
{

	DestroyResources();

}


void ThanksState::LoadResources(sf::RenderWindow* screen)
{

	assert(screen && "ThanksState::LoadResources(): trying to initialize to a NULL RenderWindow");

	m_pScreen = screen;

	m_ImgManager.Load("../../resources/images/testImage.png");
	
	m_pBackgroundImage = new sf::Sprite();

	assert(m_pBackgroundImage && "ThanksState::LoadResources(sf::RenderWindow* screen): the sprite is NULL");

	m_pBackgroundImage->SetImage(m_ImgManager["../../resources/images/testImage.png"]);
	m_pBackgroundImage->Resize(float(m_pScreen->GetWidth()), float(m_pScreen->GetHeight()));
	m_pBackgroundImage->SetPosition(0.0f, 0.0f);

}


void ThanksState::DestroyResources()
{

	m_ImgManager.Destroy("../../resources/images/testImage.png");

	if(m_pBackgroundImage != 0)
	{

		delete m_pBackgroundImage;
		m_pBackgroundImage = 0;

	}

}



