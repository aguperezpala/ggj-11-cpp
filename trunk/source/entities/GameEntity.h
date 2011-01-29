#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H


//////////////////////////////////////////////////////////////////////////
//
// File: GameEntity.h
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
#include <SFML/Graphics.hpp>
#include <vector>
#include "animated.hpp"


using namespace sftools;


class GameEntity : public Animated
{

public:

	GameEntity(float time = 0.f, bool play = false, bool loop = true);
	GameEntity(const Anim& anim, float time = 0.f, bool play = false, bool loop = true);
	virtual ~GameEntity();

	int GetId() const;


private:

	static int m_GlobalId; // This will assign an Id to all the GameEntities and will increment its value.

	const int m_Id; // This is the Id for this GameEntity.

};



#endif // GAME_ENTITY_H