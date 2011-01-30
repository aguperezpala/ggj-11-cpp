/*
 * FireBulletCollisionAction.h
 *
 *  Created on: 30/01/2011
 *      Author: agustin
 */

#ifndef FIREBULLETCOLLISIONACTION_H_
#define FIREBULLETCOLLISIONACTION_H_

#include "CollisionAction.h"
#include "GameEntity.h"
#include "debug_helper.h"



class FireBulletCollisionAction : public CollisionAction
{
public:
	FireBulletCollisionAction();
	virtual ~FireBulletCollisionAction();


	/* Here it will be the core of the logic of the collision between this two
	 * kind of entities */
	void handleCollision(GameEntity *source, GameEntity *target);

private:

};

#endif /* FIREBULLETCOLLISIONACTION_H_ */
