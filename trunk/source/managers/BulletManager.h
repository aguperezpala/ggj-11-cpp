/*
 * BulletManager.h
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#ifndef BULLETMANAGER_H_
#define BULLETMANAGER_H_

#include <SFML/System/Vector2.hpp>
#include <list>
// own libs
#include "GameEntity.h"
#include "debug_helper.h"
#include "IManager.h"

class BulletManager : public IManager
{
public:

	/* This class automatically will drop all the entities that are out of
	 * the screen and it will call the */
	static BulletManager *getInstance();

	/* Adds an entity to be processed (for collision detections and
	 * moved over the level.
	 * REQUIRES:
	 * 		ent			!= NULL
	 * 		vectMvmnt 	vector of movement normalized with the velocity
	 * NOTE: the vector will be multiply with the elapsed time of each frame  */
	void addNewBullet(GameEntity *ent, const sf::Vector2f &vectMvmnt);

	/* Remove entity from the Manager (must exist) */
	void removeBullet(GameEntity *ent);

	/* update the logic of the manager */
	void update(float dTime);


protected:
	BulletManager();
	virtual ~BulletManager();

	inline bool existEntity(GameEntity *ent)
	{
		std::list<std::pair<GameEntity *, sf::Vector2f> >::iterator it;

		if(!ent)
			return false;

			for(it = mBullets.begin(); it != mBullets.end(); ++it) {
				if((*it).first == ent)
					return true;
			}

			return false;
	}

private:
	static BulletManager *mInstance;
	// the map of the objects to track
	std::list<std::pair<GameEntity *, sf::Vector2f> > mBullets;
};

#endif /* BULLETMANAGER_H_ */
