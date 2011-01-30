/*
 * CollisionManager.cpp
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#include "Collision.h"
#include "CollisionManager.h"



CollisionManager *CollisionManager::mInstance = 0;


CollisionManager *CollisionManager::getInstance()
{
	if(!mInstance) {
		mInstance = new CollisionManager();
	}

	return mInstance;
}

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
void CollisionManager::addCollisionLogic(std::list<GameEntity *> *sources,
					   std::list<GameEntity *> *targets,
					   CollisionAction *action)
{
	ASSERT(sources);
	ASSERT(targets);
	ASSERT(action);

	std::list<CollisionMapper>::iterator it;

	for(it = mMapper.begin(); it != mMapper.end(); ++it) {
		if((*it).sources == sources && (*it).targets == targets &&
				(*it).action == action)
		{
			ASSERT(false);
			return;
		}
	}

	mMapper.push_back(CollisionMapper(sources,targets,action));

}

/* Removes the collision logic. You have to specify the three parameters
 * to delete the CollisionLogic
 */
void CollisionManager::removeCollisionLogic(std::list<GameEntity *> *sources,
					   std::list<GameEntity *> *targets,
					   CollisionAction *action)
{
	std::list<CollisionMapper>::iterator it;

	for(it = mMapper.begin(); it != mMapper.end(); ++it) {
		if((*it).sources == sources && (*it).targets == targets &&
				(*it).action == action)
		{
			mMapper.erase(it);
		}
	}

}

/* this is the function used to check the Collisions, in all the frames. */
void CollisionManager::update(float dTime)
{
	if(!mActive)
		return;

	std::list<CollisionMapper>::iterator it;
	std::list<GameEntity*>::iterator eIt;
	std::list<GameEntity*>::iterator targetIt;

	for(it = mMapper.begin(); it != mMapper.end(); ++it) {
		for(eIt = (*it).sources->begin(); eIt != (*it).sources->end(); ++eIt){
			if(!(*eIt)->IsActive())
				continue;
			for(targetIt = (*it).targets->begin(); targetIt != (*it).targets->end(); ++targetIt){
				if(!(*targetIt)->IsActive())
					continue;

				if(Collision::BoundingBoxTest(*(*eIt), *(*targetIt))) {
					// there are a collision!
					LOG("COLLISION!!!");
					(*it).action->handleCollision((*eIt), *targetIt);
				}
			}

		}
	}

}

/* This function is used to remove a GameEntity from some of the targets
 * lists, (it will find in every lists an it will remove it from the first
 * one it matchs.
 */
void CollisionManager::removeOneTarget(GameEntity *target)
{
	std::list<CollisionMapper>::iterator it;
	std::list<GameEntity*>::iterator eIt;

	for(it = mMapper.begin(); it != mMapper.end(); ++it) {
		for(eIt = (*it).targets->begin(); eIt != (*it).targets->end(); ++eIt){
			if((*eIt) == target) {
				(*it).targets->remove(*eIt);
				return;
			}
		}
	}


}
void CollisionManager::removeOneSource(GameEntity *source)
{
	std::list<CollisionMapper>::iterator it;
	std::list<GameEntity*>::iterator eIt;

	for(it = mMapper.begin(); it != mMapper.end(); ++it) {
		for(eIt = (*it).sources->begin(); eIt != (*it).sources->end(); ++eIt){
			if((*eIt) == source) {
				(*it).sources->remove(*eIt);
				return;
			}
		}
	}


}


CollisionManager::CollisionManager()
{
	// TODO Auto-generated constructor stub

}

CollisionManager::~CollisionManager()
{
	// TODO Auto-generated destructor stub
}
