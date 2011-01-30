/*
 * ScrollingManager.cpp
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#include "ScrollingManager.h"


ScrollingManager *ScrollingManager::mInstance = 0;

///////////////////////////////////////////////////////////////////////////////
ScrollingManager *ScrollingManager::getInstance()
{
	if(!mInstance){
		mInstance = new ScrollingManager();
	}

	return mInstance;
}


///////////////////////////////////////////////////////////////////////////////
void ScrollingManager::insertEntity(GameEntity *ent)
{
	// preconditions
	ASSERT(ent != 0);
	ASSERT(!existGameEntity(ent->GetId()));

	mScrollableEntities[ent->GetId()] = ent;
}


///////////////////////////////////////////////////////////////////////////////
void ScrollingManager::removeEntity(int entityID)
{
	ASSERT(existGameEntity(entityID));

	mScrollableEntities.erase(entityID);

}
void ScrollingManager::removeEntity(GameEntity *ent)
{
	ASSERT(ent);
	ASSERT(existGameEntity(ent->GetId()));

	removeEntity(ent->GetId());
}

///////////////////////////////////////////////////////////////////////////////
void ScrollingManager::removeAllEntities(void)
{
	mScrollableEntities.clear();
}

///////////////////////////////////////////////////////////////////////////////
void ScrollingManager::setActive(bool active)
{
	mActive = active;
}


///////////////////////////////////////////////////////////////////////////////
void ScrollingManager::update(float dTime)
{
	if(!mActive) {
		LOG("We are calling update but the Active flag it is false, this is ok?");
		return;
	}

	// here is the real core of this manager :)
	float realUpdateVelocity = dTime * mVelocity;
	std::map<int, GameEntity*>::iterator it;

	for(it = mScrollableEntities.begin(); it != mScrollableEntities.end(); ++it){
		(*it).second->Move(realUpdateVelocity, 0);
	}
}


///////////////////////////////////////////////////////////////////////////////
void ScrollingManager::setVelocity(float pixels)
{
	mVelocity = pixels;
}

///////////////////////////////////////////////////////////////////////////////
ScrollingManager::ScrollingManager()
{
	// TODO Auto-generated constructor stub

}

///////////////////////////////////////////////////////////////////////////////
ScrollingManager::~ScrollingManager()
{
	// TODO Auto-generated destructor stub
}
