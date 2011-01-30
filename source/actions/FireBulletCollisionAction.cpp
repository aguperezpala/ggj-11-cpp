/*
 * FireBulletCollisionAction.cpp
 *
 *  Created on: 30/01/2011
 *      Author: agustin
 */

#include "FireBulletCollisionAction.h"
#include <SFML/System/Vector2.hpp>



FireBulletCollisionAction::FireBulletCollisionAction()
{
	// TODO Auto-generated constructor stub

}

FireBulletCollisionAction::~FireBulletCollisionAction()
{
	// TODO Auto-generated destructor stub
}


///////////////////////////////////////////////////////////////////////////////
void FireBulletCollisionAction::handleCollision(GameEntity *source, GameEntity *target)
{
	sf::Vector2f firePosition;

	ASSERT(source);
	ASSERT(target);

	// what we have to do: 1) unavailable the entities.
	source->SetActivation(false);
	target->SetActivation(false);

	firePosition = target->GetPosition();

	// we call the FXManager and say to load an bullet explosion animation in
	// the fire position

	// Probably we want to do some performance improvments for the CollisionManager.
}
