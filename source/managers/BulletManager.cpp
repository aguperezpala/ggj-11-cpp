/*
 * BulletManager.cpp
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#include "BulletManager.h"
#include "ScrollingManager.h"

BulletManager *BulletManager::mInstance = 0;


BulletManager *BulletManager::getInstance()
{
	if(!mInstance) {
		mInstance = new BulletManager();
	}

	return mInstance;
}

void BulletManager::setWindowsSize(float screenWidth, float screenHeight)
{
	mScreenHeight = screenHeight;
	mScreenWidth = screenWidth;
}

void BulletManager::addNewBullet(GameEntity *ent, const sf::Vector2f &vectMvmnt)
{
	ASSERT(ent);
	//ASSERT(!existEntity(ent));
	if(!ent->IsActive())
		return;

	std::map<int, std::pair<GameEntity *, sf::Vector2f> >::iterator it;

	it = mBullets.find(ent->GetId());
	if(it == mBullets.end()) {
		// add new one
		mBullets[ent->GetId()] = std::pair<GameEntity *, sf::Vector2f>(ent, vectMvmnt);
	} else {
		// replace the vector of the old
		(*it).second.second = vectMvmnt;
	}
	ScrollingManager::getInstance()->insertEntity(ent);
}

/* Remove entity from the Manager (must exist) */
void BulletManager::removeBullet(GameEntity *ent)
{
	ASSERT(ent);
	ASSERT(existEntity(ent));

	ScrollingManager::getInstance()->removeEntity(ent->GetId());
	mBullets.erase(ent->GetId());
}

/* update the logic of the manager */
void BulletManager::update(float dTime)
{
	std::map<int, std::pair<GameEntity *, sf::Vector2f> >::iterator it;
	std::map<int, std::pair<GameEntity *, sf::Vector2f> > auxMap;

	for(it = mBullets.begin(); it != mBullets.end(); ++it) {
		if(!(*it).second.first->IsActive() || !isEntityInScreen((*it).second.first)){
			auxMap.insert(*it);
			continue;
		}

		(*it).second.first->Move((*it).second.second);
	}

	if(auxMap.size() > 0) {
		// we must erase all that entities that are not more in the scene
		for(it = auxMap.begin(); it != auxMap.end(); ++it) {
			(*it).second.first->SetActivation(false);
			ScrollingManager::getInstance()->removeEntity((*it).second.first->GetId());
			mBullets.erase((*it).second.first->GetId());
		}
	}

}

BulletManager::BulletManager()
{
	// TODO Auto-generated constructor stub

}

BulletManager::~BulletManager()
{
	// TODO Auto-generated destructor stub
}
