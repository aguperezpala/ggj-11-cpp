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


//
// Forward declarations
//
class StateMachine;


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

	sf::RenderWindow* m_pScreen;

	ImageManager m_ImgManager;


};



#endif // LEVEL_H