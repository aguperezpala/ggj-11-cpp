//////////////////////////////////////////////////////////////////////////
//
// File: LevelState.h
//
// Desc: This states represents the only level of the game
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "LevelState.h"
#include "LevelFactory.h"
#include "GameEntity.h"
#include "Environment.h"
#include "EnvironmentManager.h"
#include "ScrollingManager.h"
#include <cassert>


// Default constructor
LevelState::LevelState() : State(), m_pScreen(0), m_pPlayer(0), m_pEnvironment(0), m_pMap1(0), m_pMap2(0), m_pEnvironmentManager(0) {}


// Singleton
LevelState* LevelState::Instance()
{

	static LevelState m_LevelState;

	return &m_LevelState;

}


// Destructor
LevelState::~LevelState() {}


void LevelState::Init(sf::RenderWindow *pScreen)
{

	assert(pScreen && "LevelState::Init(sf::RenderWindow *pScreen): RenderWindow is NULL");

	m_pScreen = pScreen;

	LevelFactory levelFactory(&m_ImgManager);

	m_PlayerAnimations = levelFactory.GetPlayerAnimations();
	m_AffectablesAnimation = levelFactory.GetAffectablesAnimation();
	m_AffectorsAnimation = levelFactory.GetAffectorsAnimation();
	m_MapAnimation = levelFactory.GetMapAnimation();

	InitPlayer();
	//InitCannon();
	InitEnvironmentManager();
	InitScrollingManager();
	
}


void LevelState::Execute(StateMachine* pStateMachine)
{

	assert(m_pScreen && "LevelState::Execute(StateMachine* pStateMachine): RenderWindow is NULL");
	assert(m_pPlayer && "LevelState::Execute(StateMachine* pStateMachine): GameEntity is NULL");

	m_pScreen->Draw(*m_pMap1);
	m_pScreen->Draw(*m_pMap2);
	m_pScreen->Draw(*m_pPlayer);
	
	CheckInput();

	ScrollingManager::getInstance()->update(m_pScreen->GetFrameTime());
	m_pEnvironmentManager->update(m_pScreen->GetFrameTime());
	m_pPlayer->Update();

}


void LevelState::Clear()
{

	if(m_pPlayer)
	{

		delete m_pPlayer;
		m_pPlayer = 0;

	}

	if(m_pEnvironment)
	{

		delete m_pEnvironment;
		m_pEnvironment = 0;

	}

	if(m_pMap1)
	{

		delete m_pMap1;
		m_pMap1 = 0;

	}


	if(m_pMap2)
	{

		delete m_pMap2;
		m_pMap2 = 0;

	}

	if(m_pEnvironmentManager)
	{

		delete m_pEnvironmentManager;
		m_pEnvironmentManager = 0;

	}

}


void LevelState::InitPlayer()
{

	m_pPlayer = new GameEntity();
	m_pPlayer->SetAnim(m_PlayerAnimations["straight"]);
	m_pPlayer->Play();
	m_pPlayer->SetLoop(true);
	m_pPlayer->SetX(220.0f);
	m_pPlayer->SetY(300.0f);

}


//void LevelState::


void LevelState::InitEnvironmentManager()
{

	InitEnvironment();

	m_pEnvironmentManager = new EnvironmentManager(m_pScreen->GetHeight(), m_pScreen->GetWidth());
	m_pEnvironmentManager->pushEnvironment(m_pEnvironment);

	m_pEnvironmentManager->setActive(true);

}


void LevelState::InitEnvironment()
{

	// Create and add both maps.
	m_pMap1 = new GameEntity(m_MapAnimation["map1"]);
	m_pMap2 = new GameEntity(m_MapAnimation["map2"]);
	m_MapsVector.push_back(m_pMap1);
	m_MapsVector.push_back(m_pMap2);

	m_pMap1->SetActivation(true);
	m_pMap2->SetActivation(true);

	// Create environment
	m_pEnvironment = new Environment("environment1", m_MapsVector, false, 5555555.0f);
	
}


void LevelState::InitScrollingManager()
{

	ScrollingManager::getInstance()->setActive(true);
	ScrollingManager::getInstance()->setVelocity(-100.0f);

}


void LevelState::CheckInput()
{

	if(m_pScreen->GetInput().IsKeyDown(sf::Key::Up) && m_pPlayer->GetPosition().y > 125.0f)
	{

		// Set position and animation
		m_pPlayer->Move(0.0f, -100.0f * m_pScreen->GetFrameTime());
		m_pPlayer->SetAnim(m_PlayerAnimations["up"]);
		m_pPlayer->Play();
		m_pPlayer->SetLoop(true);

	}

	else if(m_pScreen->GetInput().IsKeyDown(sf::Key::Down) && m_pPlayer->GetPosition().y + m_pPlayer->GetHeight() < 566.0f)
	{

		// Set position and animation
		m_pPlayer->Move(0.0f, 100.0f * m_pScreen->GetFrameTime());
		m_pPlayer->SetAnim(m_PlayerAnimations["down"]);
		m_pPlayer->Play();
		m_pPlayer->SetLoop(true);

	}

	else
	{

		// Set position and animation
		m_pPlayer->SetAnim(m_PlayerAnimations["straight"]);
		m_pPlayer->Play();
		m_pPlayer->SetLoop(true);

	}

}
