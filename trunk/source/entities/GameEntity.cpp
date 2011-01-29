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
GameEntity::GameEntity(float time, bool play, bool loop) : Animated(time, play, loop), m_Id(m_GlobalId), m_IsActive(false)
{

	// We must increment the global Id to avoid Id conflicts.
	m_GlobalId++;

}


// Default constructor
GameEntity::GameEntity(const Anim& anim, float time, bool play, bool loop) : Animated(anim, time, play, loop), m_Id(m_GlobalId), m_IsActive(false)
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


// Set if the entity is active or not, this will be used to decide if draw or not draw an entity.
void GameEntity::SetActivation(bool activation)
{

	m_IsActive = activation;

}


bool GameEntity::IsActive() const
{

	return m_IsActive;

}
