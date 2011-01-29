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


// Default constructor
LevelState::LevelState() : State(), m_pScreen(0) {}


// Singleton
LevelState* LevelState::Instance()
{

	static LevelState m_LevelState;

	return &m_LevelState;

}


void LevelState::Init(sf::RenderWindow *pScreen)
{



}