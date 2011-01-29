//////////////////////////////////////////////////////////////////////////
//
// File: GameEntity.cpp
//
// Desc: This file defines the GameEntity class. This is the most basic
//       entity of the game.
//
// 
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "GameEntity.h"


int GameEntity::m_GlobalId = 0;


// Default constructor
GameEntity::GameEntity(float time, bool play, bool loop) : Animated(time, play, loop), m_Id(m_GlobalId)
{

	// We must increment the global Id to avoid Id conflicts.
	m_GlobalId++;

}


// Default constructor
GameEntity::GameEntity(const Anim& anim, float time, bool play, bool loop) : Animated(anim, time, play, loop), m_Id(m_GlobalId)
{

	// We must increment the global Id to avoid Id conflicts.
	m_GlobalId++;

}


// Destructor
GameEntity::~GameEntity() {}


int GameEntity::GetId() const
{

	return m_Id;

}
