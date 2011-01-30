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
	void InitEnvironmentManager();
	void InitEnvironment();
	void InitScrollingManager();
	void InitLogicManager();

	void CheckInput(StateMachine* pStateMachine);
	void CheckKeyboard(StateMachine* pStateMachine);
	void CheckMouse();
	void CheckCannonRotation();

	void DrawAffectables();
	void DrawAffectors();

	void UpdateAffectables();
	void UpdateAffectors();

	void DestroyImgManagerData();

	sf::RenderWindow* m_pScreen;

	ImageManager m_ImgManager;

	std::map<std::string, Anim> m_PlayerAnimations;
	std::map<std::string, Anim> m_AffectablesAnimation;
	std::map<std::string, Anim> m_AffectorsAnimation;
	std::map<std::string, Anim> m_MapAnimation;

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

};


#endif // LEVEL_H