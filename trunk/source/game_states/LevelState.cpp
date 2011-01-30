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
#include "StateMachine.h"
#include "ScrollingManager.h"
#include "CannonHelper.h"
#include "LogicManager.h"
#include "MainMenuState.h"
#include <cassert>
#include <iostream>
#include <sstream>


// Default constructor
LevelState::LevelState() : State(), m_pScreen(0), m_pPlayer(0), m_pEnvironment(0), m_pMap1(0), m_pMap2(0), m_pEnvironmentManager(0), 
						   m_pCannon(0), m_pLogicManager(0) {}


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
	InitCannon();
	InitEnvironmentManager();
	InitScrollingManager();
	InitLogicManager();
	
}


void LevelState::Execute(StateMachine* pStateMachine)
{

	assert(m_pScreen && "LevelState::Execute(StateMachine* pStateMachine): RenderWindow is NULL");
	assert(m_pPlayer && "LevelState::Execute(StateMachine* pStateMachine): GameEntity is NULL");

	m_pScreen->Draw(*m_pMap1);
	m_pScreen->Draw(*m_pMap2);
	DrawAffectables();
	DrawAffectors();
	m_pScreen->Draw(*m_pPlayer);
	m_pScreen->Draw(*m_pCannon);
	
	ScrollingManager::getInstance()->update(m_pScreen->GetFrameTime());
	m_pLogicManager->Update(m_pScreen->GetFrameTime());
	m_pEnvironmentManager->update(m_pScreen->GetFrameTime());
	UpdateAffectables();
	UpdateAffectors();
	m_pPlayer->Update();
	m_pCannon->Update();
	
	// Set the same coordinates as player
	m_pCannon->SetX(m_pPlayer->GetPosition().x+40.0f);
	m_pCannon->SetY(m_pPlayer->GetPosition().y);

	CheckInput(pStateMachine);

}


void LevelState::Clear()
{

	ScrollingManager::getInstance()->removeAllEntities();

	DestroyImgManagerData();
	
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

	m_MapsVector.clear();

	if(m_pEnvironmentManager)
	{

		delete m_pEnvironmentManager;
		m_pEnvironmentManager = 0;

	}

	if(m_pCannon)
	{

		delete m_pCannon;
		m_pCannon = 0;

	}

	if(m_pLogicManager)
	{

		delete m_pLogicManager;
		m_pLogicManager = 0;

	}

	for(unsigned int i=0; i<m_Affectables.size(); i++)
	{

		delete m_Affectables[i];
		m_Affectables[i] = 0;

	}

	for(unsigned int i=0; i<m_Affectors.size(); i++)
	{

		delete m_Affectors[i];
		m_Affectors[i] = 0;

	}

	m_Affectables.clear();
	m_Affectors.clear();

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


void LevelState::InitCannon()
{

	m_pCannon = new GameEntity(m_PlayerAnimations["weapon"]);
	m_pCannon->Stop();
	m_pCannon->SetLoop(false);
	m_pCannon->SetActivation(true);

	// Set the same coordinates as player
	m_pCannon->SetX(m_pPlayer->GetPosition().x);
	m_pCannon->SetY(m_pPlayer->GetPosition().y);

}


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
	ScrollingManager::getInstance()->setVelocity(-250.0f);

}


void LevelState::InitLogicManager()
{

	m_pLogicManager = new LogicManager(m_pScreen->GetWidth(), m_pScreen->GetHeight());


	std::stringstream ss;
	for(int i=1; i<4; i++)
	{

		for(int j=0; j<4; j++)
		{

			ss.str("");
			ss << i;

			std::string name = "house" + ss.str();
			GameEntity* dummy = new GameEntity(m_AffectablesAnimation[name.c_str()]);
			dummy->Play();
			dummy->SetLoop(true);
			m_Affectables.push_back(dummy);
			m_pLogicManager->AddAffectable(dummy);

		}

	}

	
	for(unsigned int i=0; i<4; i++)
	{

		GameEntity* dummy = new GameEntity(m_AffectorsAnimation["fire"]);
		dummy->Play();
		dummy->SetLoop(true);
		m_Affectors.push_back(dummy);
		m_pLogicManager->AddAffector(dummy);

	}
	
}


void LevelState::CheckInput(StateMachine* pStateMachine)
{

	CheckMouse();

	CheckKeyboard(pStateMachine);

}


void LevelState::CheckKeyboard(StateMachine* pStateMachine)
{

	if(m_pScreen->GetInput().IsKeyDown(sf::Key::Escape))
		pStateMachine->ChangeState(MainMenuState::Instance());

	else
	{

		if(m_pScreen->GetInput().IsKeyDown(sf::Key::Up) && m_pPlayer->GetPosition().y > 125.0f)
		{

			// Set position and animation
			m_pPlayer->Move(0.0f, -100.0f * m_pScreen->GetFrameTime());
			m_pPlayer->SetAnim(m_PlayerAnimations["up"]);
			m_pPlayer->Play();
			m_pPlayer->SetLoop(true);

		}

		else if(m_pScreen->GetInput().IsKeyDown(sf::Key::Down) && m_pPlayer->GetPosition().y + m_pPlayer->GetHeight() < 540.0f)
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

		if (m_pScreen->GetInput().IsKeyDown(sf::Key::Left))
		{

			float currentVelocity = ScrollingManager::getInstance()->getVelocity();
			float finalVelocity = currentVelocity + 4000.0f * m_pScreen->GetFrameTime();
			if (finalVelocity < -250.0f)
				ScrollingManager::getInstance()->setVelocity(finalVelocity);
			else
				ScrollingManager::getInstance()->setVelocity(-250.0f);

		}

		else if (m_pScreen->GetInput().IsKeyDown(sf::Key::Right))
		{

			float currentVelocity = ScrollingManager::getInstance()->getVelocity();
			float finalVelocity = currentVelocity - 2000.0f * m_pScreen->GetFrameTime();
			if (finalVelocity > -3500.0f )
				ScrollingManager::getInstance()->setVelocity(finalVelocity);
			else
				ScrollingManager::getInstance()->setVelocity(-3500.0f);

		}

		// Update the offset of the affordable entities generation
		float currentVelocity = ScrollingManager::getInstance()->getVelocity();
		/*if(-250.0f <= currentVelocity <= 750.0f)
			m_pLogicManager->TweakTimeOuts(2.0f);
		else if(-750.0f <= currentVelocity <= 1250.0f)
			m_pLogicManager->TweakTimeOuts(1.8f);
		else if(-1250.0f <= currentVelocity <= 1750.0f)
			m_pLogicManager->TweakTimeOuts(1.6f);
		else if(-1750.0f <= currentVelocity <= 2250.0f)
			m_pLogicManager->TweakTimeOuts(1.4f);
		else if(-2250.0f <= currentVelocity <= 2750.0f)
			m_pLogicManager->TweakTimeOuts(1.2f);
		else
			m_pLogicManager->TweakTimeOuts(1.0f);*/

	}

}


void LevelState::CheckMouse()
{

	CheckCannonRotation();

}


void LevelState::CheckCannonRotation()
{

	// Get the mouse position
	sf::Vector2<int> mousePosition;
	mousePosition.x = m_pScreen->GetInput().GetMouseX();
	mousePosition.y = m_pScreen->GetInput().GetMouseY();

	// Get the coordinates corresponding to the center of the cannon
	sf::Vector2<float> cannonCenterPos;
	cannonCenterPos.x = m_pCannon->GetPosition().x + (m_pCannon->GetWidth()/2.0f);
	cannonCenterPos.y = m_pCannon->GetPosition().y + (m_pCannon->GetHeight()/2.0f);

	// Set the new frame of the cannon
	int frame = CannonHelper::getAnimationIndex(mousePosition, cannonCenterPos);
	m_pCannon->SetFrame(frame);

}


void LevelState::DrawAffectables()
{

	for(unsigned int i=0; i<m_Affectables.size(); i++)
	{

		if(m_Affectables[i]->IsActive())
			m_pScreen->Draw(*(m_Affectables[i]));

	}

}


void LevelState::DrawAffectors()
{

	for(unsigned int i=0; i<m_Affectors.size(); i++)
	{

		if(m_Affectors[i]->IsActive())
			m_pScreen->Draw(*(m_Affectors[i]));

	}

}


void LevelState::UpdateAffectables()
{

	for(unsigned int i=0; i<m_Affectables.size(); i++)
	{

		if(m_Affectables[i]->GetPosition().x + m_Affectables[i]->GetWidth() < 0.0f)
			m_Affectables[i]->SetActivation(false);

	}

}


void LevelState::UpdateAffectors()
{

	for(unsigned int i=0; i<m_Affectors.size(); i++)
	{

		if(m_Affectors[i]->GetPosition().x + m_Affectors[i]->GetWidth() < 0.0f)
			m_Affectors[i]->SetActivation(false);
		
		else
			m_Affectors[i]->Update();

	}

}


void LevelState::DestroyImgManagerData()
{

	m_ImgManager.Destroy("../../resources/images/House/House02.png");
	m_ImgManager.Destroy("../../resources/images/House/House03.png");
	m_ImgManager.Destroy("../../resources/images/House/House04.png");
	m_ImgManager.Destroy("../../resources/images/fire/fireee.png");
	m_ImgManager.Destroy("../../resources/images/background/correjido prueba.png");
	m_ImgManager.Destroy("../../resources/images/truck/TruckFordward1.png");
	m_ImgManager.Destroy("../../resources/images/truck/TruckUp1.png");
	m_ImgManager.Destroy("../../resources/images/truck/TruckDown1.png");
	m_ImgManager.Destroy("../../resources/images/truck/cannon.png");

}
