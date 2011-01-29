/*
 * CollisionManager.h
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#ifndef COLLISIONMANAGER_H_
#define COLLISIONMANAGER_H_


#include <list>
#include "IManager.h"
#include "GameEntity.h"
#include "debug_helper.h"
#include "CollisionAction.h"

class CollisionManager : public IManager
{
	struct CollisionMapper {
		std::list<GameEntity*> *sources;
		std::list<GameEntity*> *targets;
		CollisionAction *action;

		CollisionMapper(std::list<GameEntity *> *s,
					   std::list<GameEntity *> *t,
					   CollisionAction *a):sources(s), targets(t), action(a){};
	};

public:

	static CollisionManager *getInstance();

	/* Add the lists to perform the collision in all the frames. The first
	 * one it will be considered the source and the second the targets.
	 * It is necessary to pass a CollisionAction to be taken if a collision
	 * occur.
	 * NOTE: Do not delete any of this objects after insert it in the Manager
	 * or until remove it from the Manager.
	 * NOTE2: It is possible to remove elements from the list to avoid to
	 * check all of them in some frames. Although the entities that aren't
	 * active it will not be checked.
	 */
	void addCollisionLogic(std::list<GameEntity *> *sources,
						   std::list<GameEntity *> *targets,
						   CollisionAction *action);

	/* Removes the collision logic. You have to specify the three parameters
	 * to delete the CollisionLogic
	 */
	void removeCollisionLogic(std::list<GameEntity *> *sources,
						   std::list<GameEntity *> *targets,
						   CollisionAction *action);

	/* this is the function used to check the Collisions, in all the frames. */
	void update(float dTime);

	/* This function is used to remove a GameEntity from some of the targets
	 * lists, (it will find in every lists an it will remove it from the first
	 * one it matchs.
	 */
	void removeOneTarget(GameEntity *target);
	void removeOneSource(GameEntity *source);

	/* Stop/Start Checking collisions */
	void SetActive(bool active) {mActive = false;};
	bool getActive(void) const {return mActive;}

protected:
	CollisionManager();
	virtual ~CollisionManager();


private:
	static CollisionManager *mInstance;
	// we will save the pairs of list of entities to be checked and the associated
	// action to be taken if an collision is performed
	std::list<CollisionMapper> mMapper;
	bool mActive;
};

#endif /* COLLISIONMANAGER_H_ */
