/*
 * ScrollingManager.h
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#ifndef SCROLLINGMANAGER_H_
#define SCROLLINGMANAGER_H_


#include <map>
#include <list>
// own libs
#include "debug_helper.h"
#include "IManager.h"
#include "GameEntity.h"



class ScrollingManager : public IManager
{
public:
	static ScrollingManager *getInstance(void);

	/* Add a GameEntity to apply the Scrolling effect
	 * The entity must not be in the ScrollingManager
	 * REQUIRES:
	 * 		ent		!= NULL
	 */
	void insertEntity(GameEntity *ent);

	/* Removes an entity from the ScrollingManager, the entity must be in the
	 * ScrollingManager
	 * REQUIRES:
	 * 		ent 	!= NULL && be in the ScrollingManager
	 */
	void removeEntity(GameEntity *ent);
	void removeEntity(int entityID);

	/* Activate the scrolling / deactivate the scrolling (its easier do not calling
	 * the update function XD) */
	void setActive(bool active);
	bool getActiveFlag(void) const {return mActive;};

	/* This is the main function, used to update all the position of all the
	 * entities added to the ScrollingManager (only if it is active).
	 * REQUIRES:
	 * 		dTime	it is the delta time passed from the last frame
	 */
	void update(float dTime);

	/* Set/get the number of pixels that the objects gonna be moved in each
	 * update() call . */
	void setVelocity(float vel);
	float getVelocity(void) const {return mVelocity;};

	/* Increase/decrease the velocity (velocity = velocity + delta */
	void increaseVelocity(float delta) {mVelocity += delta;}

protected:
	ScrollingManager();
	virtual ~ScrollingManager();

	/* Helper function to check if an entity exists in the ScrollingManager */
	inline bool existGameEntity(int id)
	{
		return (mScrollableEntities.find(id) != mScrollableEntities.end());
	}


private:
	// Singleton instance
	static ScrollingManager *mInstance;
	// Map of ids -> GameEntities
	std::map<int, GameEntity*> mScrollableEntities;
	// Velocity used to move the entities
	float mVelocity;
	// Active flag
	bool mActive;

};

#endif /* SCROLLINGMANAGER_H_ */
