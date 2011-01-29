/*
 * EnvironmentManager.cpp
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */
#include <algorithm>
#include "EnvironmentManager.h"



///////////////////////////////////////////////////////////////////////////////
void EnvironmentManager::insertOnScrollingMap(float x, float y)
{
	if(mMapsOutScrolling.empty() || !mActualEnvironmnet)
		return;

	int index = 0;
	// check the logic
	if(mActualEnvironmnet->randomSelection) {
		index = sf::Randomizer::Random(0, mMapsOutScrolling.size() - 1);
	} else {
		// get the next element
		mMapIndex = (mMapIndex + 1) % mMapsOutScrolling.size();
		index = mMapIndex;
	}

	GameEntity *ent = mMapsOutScrolling[index];
	ent->SetPosition(x,y);
	ScrollingManager::getInstance()->insertEntity(ent);
	mMapsOutScrolling.erase(find(mMapsOutScrolling.begin(), mMapsOutScrolling.end(),
			ent));
	mMapsOnScrolling.push_back(ent);
}

///////////////////////////////////////////////////////////////////////////////
void EnvironmentManager::handleOutOfScreensMaps(void)
{

	if(mMapsOnScrolling.empty()){
		// this is the initial case, we have to add 2 maps.
		insertOnScrollingMap(0,0);
		insertOnScrollingMap(mScreenX, 0);
		return;
	}

	GameEntity *ent = mMapsOnScrolling[0];
	GameEntity *nextEnt = 0;

	if(!isEntityInScreen(ent)){
		// we remove from the scrollingManager (isn't anymore in the screen)
		ScrollingManager::getInstance()->removeEntity(ent);

		// we get the next entity
		if(mMapsOnScrolling.size() < 2)
			ASSERT(false);
		GameEntity *nextEnt = mMapsOnScrolling[1];

		// now we check if the ent is in the vector of the actual env
		if(find(mActualEnvironmnet->maps.begin(), mActualEnvironmnet->maps.end(),
				ent) == mActualEnvironmnet->maps.end()){
			// the map is from another env, we only pop it out from the vector
			// and include a new one in the ScrollingManager
			mMapsOnScrolling.erase(find(mMapsOnScrolling.begin(),
					mMapsOnScrolling.end(),	ent));
			// insert new one
			insertOnScrollingMap(nextEnt->GetPosition().x + nextEnt->GetWidth() -4, 0);
			return;
		} else {
			// we have to pass the Map from the OnScrolling list to the OutScrolling
			// list
			mMapsOnScrolling.erase(find(mMapsOnScrolling.begin(),
								mMapsOnScrolling.end(),	ent));
			// we let it available again in the OutScrilling vector
			mMapsOutScrolling.push_back(ent);

			// insert new one
			insertOnScrollingMap(nextEnt->GetPosition().x + nextEnt->GetWidth() - 4, 0);


		}
	} // else we have nothing to do.
}

///////////////////////////////////////////////////////////////////////////////
void EnvironmentManager::setNewEnvironment(const Environment *env)
{
	if(!mActualEnvironmnet){
		mActualEnvironmnet = env;
	}
	mEnvironments.remove(mActualEnvironmnet);
	mEnvironments.push_back(mActualEnvironmnet);
	mActualEnvironmnet = env;
	mMapIndex = 0;
	// we must clear the OutScrolling vector but not the OnScrolling, because
	// if we do, it will never gonna be removed from the ScrollingManager
	mMapsOutScrolling.clear();
	mMapsOutScrolling.assign(env->maps.begin(), env->maps.end());
	mElapsedTime = 0;
}



///////////////////////////////////////////////////////////////////////////////
EnvironmentManager::EnvironmentManager(float y, float x) :
	mActualEnvironmnet(0), mScreenX(x), mScreenY(y), mMapIndex(0)
{
	// TODO Auto-generated constructor stub

}

///////////////////////////////////////////////////////////////////////////////
void EnvironmentManager::pushEnvironment(const Environment *env)
{
	ASSERT(env);
	ASSERT(!existEnvironment(env));
	ASSERT(env->maps.size() >= 2);

	// TODO: this is not supporting the possibility to receive maps biggers
	// than the size of the screen
	std::vector<GameEntity *>::const_iterator it;
	for(it = env->maps.begin(); it != env->maps.end(); ++it){
		if(!(*it) || ((*it)->GetHeight() != mScreenY) ||
				((*it)->GetWidth() != mScreenX)) {
			ASSERT(false);
			return;
		}
	}

	// everything ok
	mEnvironments.push_back(env);
	// if we have no actualEnvironment then we set it
	if(!mActualEnvironmnet) {
		setNewEnvironment(env);
	}
}

///////////////////////////////////////////////////////////////////////////////
void EnvironmentManager::removeEnvironment(const Environment *env)
{
	ASSERT(env);
	ASSERT(existEnvironment(env));

	// now check if the actual env is the one that we are trying to remove
	if(mActualEnvironmnet == env) {
		forceJumpEnvironment();
	}

	mEnvironments.remove(env);
}

///////////////////////////////////////////////////////////////////////////////
void EnvironmentManager::setActive(bool state)
{
	mActive = state;
}

///////////////////////////////////////////////////////////////////////////////
void EnvironmentManager::update(float dTime)
{
	if(!mActualEnvironmnet || !mActive){
		// no actual env or it is no active, so return
		return;
	}

	// check if we have to create a environment jump
	mElapsedTime += dTime;
	if(mActualEnvironmnet->time < mElapsedTime) {
		forceJumpEnvironment();
		return;
	}

	// if we are here then we have to check if we have to add the new GameEntity
	// to the ScrollingManager, and we check if we have to extract one from it
	handleOutOfScreensMaps();
}

///////////////////////////////////////////////////////////////////////////////
void EnvironmentManager::forceSetEnvironment(const std::string &name)
{
	std::list<const Environment *>::iterator it;

	for(it = mEnvironments.begin(); it != mEnvironments.end(); ++it) {
		if((*it)->name == name){
			setNewEnvironment(*it);
			return;
		}
	}

	// this it should never happens
	ASSERT(false);

}

///////////////////////////////////////////////////////////////////////////////
void EnvironmentManager::forceJumpEnvironment(void)
{
	if(mEnvironments.size() == 1)
		return;

	std::list<const Environment*>::iterator it;

	it = find(mEnvironments.begin(), mEnvironments.end(), mActualEnvironmnet);
	if((it == mEnvironments.end()) || (++it == mEnvironments.end()))
		return;

	setNewEnvironment(*it);
}

///////////////////////////////////////////////////////////////////////////////
EnvironmentManager::~EnvironmentManager()
{
	// TODO Auto-generated destructor stub
}
