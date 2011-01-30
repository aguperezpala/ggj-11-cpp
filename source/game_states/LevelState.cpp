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
#include "CollisionManager.h"
#include "ThanksState.h"
#include "BulletManager.h"
#include "FXManager.h"
#include <cassert>
#include <iostream>
#include <sstream>


// Default constructor
LevelState::LevelState() : State(), m_pScreen(0), m_pPlayer(0), m_pEnvironment(0), m_pMap1(0), m_pMap2(0), m_pEnvironmentManager(0), 
						   m_pCannon(0), m_pLogicManager(0), m_DeltaTime(0.2f), m_CurrentDelta(0.0f) {}


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
	m_BulletAnimation = levelFactory.GetBulletAnimation();
	m_ExplosionAnimation = levelFactory.GetExplosionAnimation();
	m_PanelsAnimation = levelFactory.GetPanelsAnimation();

	InitPlayer();
	InitCannon();
	InitBullets();
	InitExplosions();
	InitEnvironmentManager();
	InitScrollingManager();
	InitLogicManager();
	InitCollisionManager();
	InitFXManager();
	BulletManager::getInstance()->setWindowsSize(m_pScreen->GetWidth(), m_pScreen->GetHeight());
	InitFont();
	InitText();
	InitPanels();
	InitSounds();

	m_ExtinctionsSucceded = 0;
	m_TotalTime = 60.0f;
		
}


void LevelState::Execute(StateMachine* pStateMachine)
{

	assert(m_pScreen && "LevelState::Execute(StateMachine* pStateMachine): RenderWindow is NULL");
	assert(m_pPlayer && "LevelState::Execute(StateMachine* pStateMachine): GameEntity is NULL");

	m_pScreen->Draw(*m_pMap1);
	m_pScreen->Draw(*m_pMap2);
	DrawAffectables();
	DrawAffectors();
	DrawExplosions();
	m_pScreen->Draw(*m_pPlayer);
	DrawBullets();
	m_pScreen->Draw(*m_pCannon);
	UpdatePanels();
	
	ScrollingManager::getInstance()->update(m_pScreen->GetFrameTime());
	m_pLogicManager->Update(m_pScreen->GetFrameTime());
	m_pEnvironmentManager->update(m_pScreen->GetFrameTime());
	UpdateBullets();
	UpdateExplosions();
	UpdateAffectables();
	UpdateAffectors();
	m_pPlayer->Update();
	m_pCannon->Update();
	CollisionManager::getInstance()->update(m_pScreen->GetFrameTime());
	BulletManager::getInstance()->update(m_pScreen->GetFrameTime());
	FXManager::getInstance()->update(m_pScreen->GetFrameTime());
	
	// Set the same coordinates as player
	m_pCannon->SetX(m_pPlayer->GetPosition().x+52.0f);
	m_pCannon->SetY(m_pPlayer->GetPosition().y-3.0f);
	
	// Check if the player loosed
	if(m_TotalTime <= 0.0f)
	{
	
		pStateMachine->ChangeState(ThanksState::Instance());
		m_AmbientMusic.Stop();

	}

	else
	{
	
		m_TotalTime -= m_pScreen->GetFrameTime() * 1.5f;
		CheckInput(pStateMachine);

	}

	

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
	m_AffectorsList.clear();

	for(unsigned int i=0; i<m_Bullets.size(); i++)
	{

		delete m_Bullets[i];
		m_Bullets[i] = 0;

	}
	m_Bullets.clear();
	m_BulletsList.clear();

	for(unsigned int i=0; i<m_Explosions.size(); i++)
	{

		delete m_Explosions[i];
		m_Explosions[i] = 0;

	}
	m_Explosions.clear();

	if(m_pFont)
	{

		delete m_pFont;
		m_pFont = 0;

	}

	if(m_pCronometroText)
	{

		delete m_pCronometroText;
		m_pCronometroText = 0;

	}

	if(m_pVelocimetroText)
	{

		delete m_pVelocimetroText;
		m_pVelocimetroText = 0;

	}

	if(m_pExtinguishedText)
	{

		delete m_pExtinguishedText;
		m_pExtinguishedText = 0;

	}

	if(m_pCronometro)
	{

		delete m_pCronometro;
		m_pCronometro = 0;

	}

	if(m_pVelocimetro)
	{

		delete m_pVelocimetro;
		m_pVelocimetro = 0;
		
	}

	if(m_pExtinguished)
	{

		delete m_pExtinguished;
		m_pExtinguished = 0; 

	}

	CollisionManager::getInstance()->RemoveAll();

	if(m_pCronometroPanel)
	{

		delete m_pCronometroPanel;
		m_pCronometroPanel = 0;

	}

	if(m_pVelocimetroPanel)
	{

		delete m_pVelocimetroPanel;
		m_pVelocimetroPanel = 0;

	}
	
	if(m_pExtinguishedPanel)
	{

		delete m_pExtinguishedPanel;
		m_pExtinguishedPanel = 0;

	}

	PanelManager::getInstance()->RemoveAll();
	FXManager::getInstance()->RemoveAll();

}


void LevelState::InitPlayer()
{

	m_pPlayer = new GameEntity();
	m_pPlayer->SetFrameTime(0.3f);
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
	m_pCannon->SetX(m_pPlayer->GetPosition().x+52.0f);
	m_pCannon->SetY(m_pPlayer->GetPosition().y-3.0f);

}


void LevelState::InitBullets()
{

	for(int i=0; i<20; i++)
	{

		GameEntity* entity;
		if(i%3==0)
			entity = new GameEntity(m_BulletAnimation["bullet"], 0.2f);
		else if(i%3==1)
			entity = new GameEntity(m_BulletAnimation["bullet2"], 0.2f);
		else
			entity = new GameEntity(m_BulletAnimation["bullet3"], 0.2f);

		entity->Play();
		entity->SetLoop(true);
		m_Bullets.push_back(entity);
		m_BulletsList.push_back(entity);

	}

}


void LevelState::InitExplosions()
{

	for(int i=0; i<20; i++)
	{

		//GameEntity* entity = 0;
		//if(i%2 == 1)
			GameEntity* entity = new GameEntity(m_ExplosionAnimation["explosion"], 0.05f);
		//else
			//entity = new GameEntity(m_ExplosionAnimation["explosion2"], 0.05f);

		m_Explosions.push_back(entity);

	}

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
	for(int i=0; i<3; i++)
	{

		for(int j=1; j<5; j++)
		{

			ss.str("");
			ss << j;

			std::string name = "house" + ss.str();
			GameEntity* dummy = new GameEntity(m_AffectablesAnimation[name.c_str()]);
			dummy->Play();
			dummy->SetLoop(true);
			m_Affectables.push_back(dummy);
			m_pLogicManager->AddAffectable(dummy);

		}

	}

	
	for(unsigned int i=0; i<2; i++)
	{

		for(int j=1; j<3; j++)
		{

			ss.str("");
			ss << j;

			std::string name = "fire" + ss.str();
			GameEntity* dummy = new GameEntity(m_AffectorsAnimation[name.c_str()], 0.3f);
			dummy->Play();
			dummy->SetLoop(true);
			m_Affectors.push_back(dummy);
			m_AffectorsList.push_back(dummy);
			m_pLogicManager->AddAffector(dummy);

		}

	}
	
}


void LevelState::InitCollisionManager()
{

	CollisionManager::getInstance()->setActive(true);
	CollisionManager::getInstance()->addCollisionLogic(&m_BulletsList, &m_AffectorsList, &m_FireBullet);

}


void LevelState::InitFXManager()
{

	FXManager::getInstance()->InsertAnimations("water", m_Explosions);

}


void LevelState::InitPanels()
{

	m_pCronometro = new GameEntity(m_PanelsAnimation["cronometro"]);
	sf::Vector2<float> position(0.0f, 200.0f);
	m_pCronometroPanel = new PanelManager::Panel(m_pCronometroText, m_pCronometro, position);

	m_pVelocimetro = new GameEntity(m_PanelsAnimation["velocimetro"]);
	position.y = 320.0f;
	m_pVelocimetroPanel = new PanelManager::Panel(m_pVelocimetroText, m_pVelocimetro, position);
	
	m_pExtinguished = new GameEntity(m_PanelsAnimation["extinguished"]);
	position.y = 400.0f;
	m_pExtinguishedPanel = new PanelManager::Panel(m_pExtinguishedText, m_pExtinguished, position);
	

	PanelManager::getInstance()->insertPanel(m_pCronometroPanel);
	PanelManager::getInstance()->insertPanel(m_pVelocimetroPanel);
	PanelManager::getInstance()->insertPanel(m_pExtinguishedPanel);

}


void LevelState::InitSounds()
{

	bool correctLoading = m_HornBuffer.LoadFromFile("../../resources/sounds/horn.wav");
	assert(correctLoading);
	m_HornSound.SetBuffer(m_HornBuffer);

	correctLoading = m_ShotBuffer.LoadFromFile("../../resources/sounds/shot.wav");
	assert(correctLoading);
	m_ShotSound.SetBuffer(m_ShotBuffer);

	m_AmbientMusic.OpenFromFile("../../resources/sounds/music.ogg");
	m_AmbientMusic.SetLoop(true);
	m_AmbientMusic.SetVolume(70.0f);
	m_AmbientMusic.Play();

}


void LevelState::CheckInput(StateMachine* pStateMachine)
{

	CheckMouse();

	CheckKeyboard(pStateMachine);

}


void LevelState::CheckKeyboard(StateMachine* pStateMachine)
{

	if(m_pScreen->GetInput().IsKeyDown(sf::Key::Escape))
	{
	
		pStateMachine->ChangeState(MainMenuState::Instance());
		m_AmbientMusic.Stop();

	}

	else
	{

		if((m_pScreen->GetInput().IsKeyDown(sf::Key::Up) || m_pScreen->GetInput().IsKeyDown(sf::Key::W)) && m_pPlayer->GetPosition().y > 125.0f)
		{

			// Set position and animation
			m_pPlayer->Move(0.0f, -100.0f * m_pScreen->GetFrameTime());
			m_pPlayer->SetAnim(m_PlayerAnimations["up"]);
			m_pPlayer->Play();
			m_pPlayer->SetLoop(true);

		}

		else if((m_pScreen->GetInput().IsKeyDown(sf::Key::Down) || m_pScreen->GetInput().IsKeyDown(sf::Key::S)) && m_pPlayer->GetPosition().y + m_pPlayer->GetHeight() < 540.0f)
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

		if (m_pScreen->GetInput().IsKeyDown(sf::Key::Left) || m_pScreen->GetInput().IsKeyDown(sf::Key::A))
		{

			float currentVelocity = ScrollingManager::getInstance()->getVelocity();
			float finalVelocity = currentVelocity + 4000.0f * m_pScreen->GetFrameTime();
			if (finalVelocity < -250.0f)
				ScrollingManager::getInstance()->setVelocity(finalVelocity);
			else
				ScrollingManager::getInstance()->setVelocity(-250.0f);

		}

		else if (m_pScreen->GetInput().IsKeyDown(sf::Key::Right) || m_pScreen->GetInput().IsKeyDown(sf::Key::D))
		{

			float currentVelocity = ScrollingManager::getInstance()->getVelocity();
			float finalVelocity = currentVelocity - 2000.0f * m_pScreen->GetFrameTime();
			if (finalVelocity > -3500.0f )
				ScrollingManager::getInstance()->setVelocity(finalVelocity);
			else
				ScrollingManager::getInstance()->setVelocity(-3500.0f);

		}


		// Update delta time to shoot
		m_CurrentDelta -= m_pScreen->GetFrameTime();

		if(m_pScreen->GetInput().IsMouseButtonDown(sf::Mouse::Left))
		{

			if(m_CurrentDelta < 0.0f)
			{

				// Search for a free bullet
				for(unsigned int i=0; i<m_Bullets.size();i++)
				{

					if(!m_Bullets[i]->IsActive())
					{

						// Activate the entity
						m_Bullets[i]->SetActivation(true);
						m_Bullets[i]->Play();
						m_Bullets[i]->SetLoop(true);

						sf::Vector2<int> mousePos;
						mousePos.x = m_pScreen->GetInput().GetMouseX();
						mousePos.y = m_pScreen->GetInput().GetMouseY();
						sf::Vector2<float> cannonCenterPos = m_pCannon->GetCenterCordinates();
	
						sf::Vector2<float> bulletDirection = CannonHelper::getVectorDirection(cannonCenterPos, mousePos);
						sf::Vector2<float> newCannonPos = CannonHelper::getCannonHole(cannonCenterPos, m_pCannon->GetCurrentFrame(), m_pCannon->GetHeight()/2.3f);
		
						// Set the source position of the bullet
						m_Bullets[i]->SetX(newCannonPos.x);
						m_Bullets[i]->SetY(newCannonPos.y);

						BulletManager::getInstance()->addNewBullet(m_Bullets[i], bulletDirection*1000.0f);

						m_ShotSound.Play();

						// Restore the delta time
						m_CurrentDelta = m_DeltaTime;
						break;
					}

				}

			}

		}

		// Update the offset of the affordable entities generation
		/*float currentVelocity = ScrollingManager::getInstance()->getVelocity();
		if(-250.0f <= currentVelocity <= 750.0f)
			m_pLogicManager->TweakTimeOuts(0.4f);
		else if(-750.0f <= currentVelocity <= 1250.0f)
			m_pLogicManager->TweakTimeOuts(0.35f);
		else if(-1250.0f <= currentVelocity <= 1750.0f)
			m_pLogicManager->TweakTimeOuts(0.3f);
		else if(-1750.0f <= currentVelocity <= 2250.0f)
			m_pLogicManager->TweakTimeOuts(0.25f);
		else if(-2250.0f <= currentVelocity <= 2750.0f)
			m_pLogicManager->TweakTimeOuts(0.2f);
		else
			m_pLogicManager->TweakTimeOuts(0.15f);*/

		if(m_pScreen->GetInput().IsKeyDown(sf::Key::Space) && m_HornSound.GetStatus() != sf::Sound::Playing)
			m_HornSound.Play();

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


void LevelState::DrawBullets()
{

	for (unsigned int i=0; i<m_Bullets.size();i++)
	{
	
		if(m_Bullets[i]->IsActive())
			m_pScreen->Draw(*(m_Bullets[i]));

	}

}


void LevelState::DrawExplosions()
{

	for (unsigned int i=0; i<m_Explosions.size();i++)
	{

		if(m_Explosions[i]->IsActive())
			m_pScreen->Draw(*(m_Explosions[i]));

	}

}


void LevelState::UpdateBullets()
{

	for(unsigned int i=0; i<m_Bullets.size(); i++)
		m_Bullets[i]->Update();

}


void LevelState::UpdateExplosions()
{

	for(unsigned int i=0; i<m_Explosions.size(); i++)
		m_Explosions[i]->Update();

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


void LevelState::UpdatePanels()
{

	PanelManager::getInstance()->update(m_pScreen);

	// Update cronometer time
	std::stringstream ss;
	ss << int(m_TotalTime);
	std::string str = ss.str();
	m_pCronometroText->SetText(str.c_str());

	ss.str("");

	// Update velocimeter 
	ss << int(ScrollingManager::getInstance()->getVelocity() / -10.0f);
	str = ss.str();
	str +=	" km";
	m_pVelocimetroText->SetText(str.c_str());

	ss.str("");

	// Update total extinctions
	ss << m_ExtinctionsSucceded;
	str = ss.str();
	m_pExtinguishedText->SetText(str.c_str());


}


void LevelState::DestroyImgManagerData()
{

	m_ImgManager.Destroy("../../resources/images/House/House01.png");
	m_ImgManager.Destroy("../../resources/images/House/House02.png");
	m_ImgManager.Destroy("../../resources/images/House/House03.png");
	m_ImgManager.Destroy("../../resources/images/House/House04.png");
	m_ImgManager.Destroy("../../resources/images/fire/fireee.png");
	m_ImgManager.Destroy("../../resources/images/fire/fireend.png");
	m_ImgManager.Destroy("../../resources/images/background/correjido prueba.png");
	m_ImgManager.Destroy("../../resources/images/proyectiles/Ballon.png");
	m_ImgManager.Destroy("../../resources/images/proyectiles/water.png");
	m_ImgManager.Destroy("../../resources/images/truck/TruckFordward.png");
	m_ImgManager.Destroy("../../resources/images/truck/TruckUp.png");
	m_ImgManager.Destroy("../../resources/images/truck/TruckDown.png");
	m_ImgManager.Destroy("../../resources/images/truck/cannon.png");
	m_ImgManager.Destroy("../../resources/images/paneles/cronometro.png");
	m_ImgManager.Destroy("../../resources/images/paneles/velocimetro.png");
	m_ImgManager.Destroy("../../resources/images/paneles/extinguished.png");
	m_ImgManager.Destroy("../../resources/images/proyectiles/water2.png");
	m_ImgManager.Destroy("../../resources/images/proyectiles/Ballonred.png");
	m_ImgManager.Destroy("../../resources/images/proyectiles/Ballongreen.png");

}


void LevelState::InitFont()
{

	m_pFont = new sf::Font();
	bool correctLoading = m_pFont->LoadFromFile("../../resources/fonts/calibri.ttf");
	assert(correctLoading && "LevelState::InitFont() Font is not correctly loaded");
	
}


void LevelState::InitText()
{

	m_pCronometroText = new sf::String("", *m_pFont);
	m_pCronometroText->SetSize(30.0f);
	m_pCronometroText->SetStyle(sf::String::Bold);
	m_pCronometroText->SetColor(sf::Color::White);

	m_pVelocimetroText = new sf::String("", *m_pFont);
	m_pVelocimetroText->SetSize(30.0f);
	m_pVelocimetroText->SetStyle(sf::String::Bold);
	m_pVelocimetroText->SetColor(sf::Color::White);

	m_pExtinguishedText = new sf::String("", *m_pFont);
	m_pExtinguishedText->SetSize(30.0f);
	m_pExtinguishedText->SetStyle(sf::String::Bold);
	m_pExtinguishedText->SetColor(sf::Color::White);

}


void LevelState::IncreaseExtinctions()
{

	m_ExtinctionsSucceded++;
	m_TotalTime += 2.0f;

}