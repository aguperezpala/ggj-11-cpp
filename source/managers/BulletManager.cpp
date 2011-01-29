/*
 * BulletManager.cpp
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#include "BulletManager.h"

BulletManager *BulletManager::mInstance = 0;


BulletManager *BulletManager::getInstance()
{
	if(!mInstance) {
		mInstance = new BulletManager();
	}

	return mInstance;
}


void BulletManager::addNewBullet(GameEntity *ent, const sf::Vector2f &vectMvmnt)
{
	ASSERT(ent);
	ASSERT(!existEntity(ent));

	mBullets.push_back(std::pair<GameEntity *, sf::Vector2f>(ent, vectMvmnt));
}

/* Remove entity from the Manager (must exist) */
void BulletManager::removeBullet(GameEntity *ent)
{
	ASSERT(ent);
	ASSERT(existEntity(ent));
	std::list<std::pair<GameEntity *, sf::Vector2f> >::iterator it;

	for(it = mBullets.begin(); it != mBullets.end(); ++it) {
				if((*it).first == ent)
					mBullets.remove(*it);
	}
}

/* update the logic of the manager */
void BulletManager::update(float dTime)
{
	std::list<std::pair<GameEntity *, sf::Vector2f> >::iterator it;

	for(it = mBullets.begin(); it != mBullets.end(); ++it) {
		(*it).first->Move((*it).second.x * dTime,
				(*it).second.y * dTime);
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
