//////////////////////////////////////////////////////////////////////////
//
//  File:   LoadingState.cpp
//
//  Desc:   Game state that shows a loading message before the level.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "LoadingState.h"
#include "StateMachine.h"
#include "LevelState.h"
#include <cassert>


// Default constructor 
LoadingState::LoadingState() : State(), m_pScreen(0), m_pBackgroundImage(0) {}


// Destructor
LoadingState::~LoadingState() {}


LoadingState* LoadingState::Instance()
{

	static LoadingState m_LoadingState; // singleton...

	return (&m_LoadingState);

}


void LoadingState::Init(sf::RenderWindow* screen)
{

	LoadResources(screen);

	m_DelayForNextState = 5.0f;

}


void LoadingState::Execute(StateMachine* pStateMachine)
{

	// Check if we must show the thanks message or change the state.
	if(m_DelayForNextState > 0.0f)
	{

		m_DelayForNextState -= m_pScreen->GetFrameTime();

		m_pScreen->Draw(*m_pBackgroundImage);

	}

	else
		pStateMachine->ChangeState(LevelState::Instance());

}


void LoadingState::Clear()
{

	DestroyResources();

}


void LoadingState::LoadResources(sf::RenderWindow* screen)
{

	assert(screen && "ThanksState::LoadResources(): trying to initialize to a NULL RenderWindow");

	m_pScreen = screen;

	m_ImgManager.Load("../../resources/images/background/loading.png");

	m_pBackgroundImage = new sf::Sprite();

	assert(m_pBackgroundImage && "ThanksState::LoadResources(sf::RenderWindow* screen): the sprite is NULL");

	m_pBackgroundImage->SetImage(m_ImgManager["../../resources/images/background/loading.png"]);
	m_pBackgroundImage->Resize(float(m_pScreen->GetWidth()), float(m_pScreen->GetHeight()));
	m_pBackgroundImage->SetPosition(0.0f, 0.0f);

}


void LoadingState::DestroyResources()
{

	m_ImgManager.Destroy("../../resources/images/background/loading.png");

	if(m_pBackgroundImage != 0)
	{

		delete m_pBackgroundImage;
		m_pBackgroundImage = 0;

	}

}
