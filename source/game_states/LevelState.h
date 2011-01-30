#ifndef LEVEL_H
#define LEVEL_H


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
#include "State.h"
#include "ImageManager.h"
#include "anim.hpp"
#include <list>
#include "FireBulletCollisionAction.h"


using namespace sftools;


//
// Forward declarations
//
class StateMachine;
class GameEntity;
class Environment;
class EnvironmentManager;
class LogicManager;


class LevelState : public State
{

public:

	virtual ~LevelState();
	static LevelState* Instance();

	void Init(sf::RenderWindow* pScreen);
	void Execute(StateMachine* pStateMachine);
	void Clear();


private:

	LevelState();

	void InitPlayer();
	void InitCannon();
	void InitBullets();
	void InitExplosions();
	void InitEnvironmentManager();
	void InitEnvironment();
	void InitScrollingManager();
	void InitLogicManager();
	void InitCollisionManager();
	void InitFXManager();
	void InitPanels();

	void CheckInput(StateMachine* pStateMachine);
	void CheckKeyboard(StateMachine* pStateMachine);
	void CheckMouse();
	void CheckCannonRotation();

	void DrawAffectables();
	void DrawAffectors();
	void DrawBullets();
	void DrawExplosions();

	void UpdateAffectables();
	void UpdateAffectors();
	
	void DestroyImgManagerData();

	void InitFont();
	void InitText();
	
	sf::RenderWindow* m_pScreen;

	ImageManager m_ImgManager;

	std::map<std::string, Anim> m_PlayerAnimations;
	std::map<std::string, Anim> m_AffectablesAnimation;
	std::map<std::string, Anim> m_AffectorsAnimation;
	std::map<std::string, Anim> m_MapAnimation;
	std::map<std::string, Anim> m_BulletAnimation;
	std::map<std::string, Anim> m_ExplosionAnimation;
	std::map<std::string, Anim> m_PanelsAnimation;

	GameEntity* m_pPlayer;

	Environment* m_pEnvironment;

	std::vector<GameEntity*> m_MapsVector;
	GameEntity* m_pMap1;
	GameEntity* m_pMap2;

	EnvironmentManager* m_pEnvironmentManager;

	GameEntity* m_pCannon;

	LogicManager* m_pLogicManager;

	std::vector<GameEntity*> m_Affectables;
	std::vector<GameEntity*> m_Affectors;
	std::list<GameEntity*> m_AffectorsList;

	std::vector<GameEntity*> m_Bullets;
	std::list<GameEntity*> m_BulletsList;

	std::vector<GameEntity*> m_Explosions;

	float m_DeltaTime;    // Delta time to wait before perform a shoot.
	float m_CurrentDelta; // Current time to wait before perform a shoot.

	FireBulletCollisionAction m_FireBullet;

	sf::Font* m_pFont;
	sf::String* m_pCronometroText;
	sf::String* m_pVelocimetroText;
	sf::String* m_pExtinguishedText;

	GameEntity* m_pCronometro;
	GameEntity* m_pVelocimetro;
	GameEntity* m_pExtinguished;

};


#endif // LEVEL_H