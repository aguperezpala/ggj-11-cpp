/*
 * ObstacleManager.h
 *
 *  Created on: 30/01/2011
 *      Author: agustin
 */

#ifndef OBSTACLEMANAGER_H_
#define OBSTACLEMANAGER_H_

#include <map>
#include <vector>
#include <list>
#include <SFML/System.hpp>

#include "CollisionAction.h"
#include "CollisionManager.h"
#include "ScrollingManager.h"
#include "IManager.h"
#include "GameEntity.h"
#include "debug_helper.h"


class ObstacleManager : public IManager, public CollisionAction
{
public:
	// It takes the screen sizes, and the player entity to detect the collisions
	ObstacleManager(float screenWidth, float screenHeight, GameEntity *player);
	virtual ~ObstacleManager();

	/* Function to add a region (it is the y coordinate where it will be inserted
	 * the object where it will be able to insert obstacles */
	void insertObstacleRegion(float y);

	/* Set the minimun size that it have to be free to pass the truck */
	void setMinFreeLength(float l);

	/* Set the number of objets in window at the same time (factor) */
	void setObstaclesFactor(float fac) {mFactor = fac;};
	float getObstaclesFactor(void) const {return mFactor;}

	/* activate / desactivate the manager */
	void setActivate(bool b) {mActivate = b;}

	/* Insert a GameEntity that would be considered an obstacle, the size
	 * of the object it is important. If the length of the objetc (height) it
	 * is bigger than the minimum free space, this blows up :) */
	void insertObstacle(GameEntity *obstacle);
	void removeObstacle(GameEntity *obstacle);
	void removeAll(void);

	/* update the entitys, This manager will work with the CollisionManager and
	 * the ScrollingManager and it will activate/desactivate the entities if
	 * there are no more in screen
	 * This function have the logic of where to render and how fast put the
	 * obstacles */
	void update(float dTime);

	/* Handle the collisions */
	void handleCollision(GameEntity *source, GameEntity *target);


protected:

	/* Function to check if a GameEntity it is out of the Screen */
	inline bool isEntityInScreen(const GameEntity* ent)
	{
		if(((ent->GetPosition().x + ent->GetWidth()) < 0.0f) ||
				(ent->GetPosition().x  > mScreenWidth) ||
				((ent->GetPosition().y + ent->GetHeight()) < 0.0f) ||
				(ent->GetPosition().y  > mScreenHeight))
			return false;
		return true;
	}

	/* Function used to handle the out of screen entities */
	void checkAndHandleOutEntities(void);

	/* Function to generate the obstacles in the screen following some logic */
	void generateObstacles(void);

	void inactiveDummyCollision(void);


private:
	std::map<int, GameEntity *> mObstacles;
	std::vector<float> mRegions;
	std::vector<GameEntity *> mInactiveBatchs;
	// lists used for the CollisionManager
	std::list<GameEntity *> mPlayerList;
	std::list<GameEntity *> mObstaclesCollisionList;


	float mMinFreeLenght;
	float mScreenWidth;
	float mScreenHeight;
	float mFactor;
	bool mActivate;


};

#endif /* OBSTACLEMANAGER_H_ */
