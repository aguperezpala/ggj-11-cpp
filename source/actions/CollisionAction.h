/*
 * CollisionAction.h
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#ifndef COLLISIONACTION_H_
#define COLLISIONACTION_H_

#include "GameEntity.h"

/* Here we define the interface to be used to handle the collisions between the
 * objects */

class CollisionAction {
public:
	CollisionAction() {};
	virtual ~CollisionAction() = 0;

	/* This is the function to be reimplemented */
	virtual void handleCollision(GameEntity *source, GameEntity *target) = 0;
};


#endif /* COLLISIONACTION_H_ */
