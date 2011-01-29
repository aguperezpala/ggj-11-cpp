/*
 * EnvironmentManager.h
 *
 * This class will show the map and all the possible things that could be appear
 * in the scene that have no effect in the logic of the game (probably nothing XD).
 *
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#ifndef ENVIRONMENTMANAGER_H_
#define ENVIRONMENTMANAGER_H_


#include <vector>
#include <list>
// own libs
#include "debug_helper.h"
#include "IManager.h"
#include "ScrollingManager.h"
#include "Environment.h"
//#include "GameEntity.h"


class EnvironmentManager : public IManager
{

public:
	/* The environment take the size of the screen to check if the images of
	 * the maps have the same size of the screen
	 */
	EnvironmentManager(float screenHeight = 0, float screenWidth = 0);
	virtual ~EnvironmentManager();

	/* Add a new environment to be used. The order that the environment are added
	 * will be reproduced when an environment ends its "reproduction time".
	 * REQUIRES:
	 * 		env != NULL and all the maps should be bigger than the size of the
	 * 			   screen and it should have more than one map
	 */
	void pushEnvironment(const Environment *env);

	/* Removes an environment
	 * REQUIRES:
	 * 		env != NULL and the env is in the Manager
	 * NOTE: if the environment it is reproducing then we dont know what will
	 * happen :), so do not try to remove anything.
	 */
	void removeEnvironment(const Environment *env);

	/* Set/get the stat of the Manager */
	void setActive(bool state);
	bool getActive(void) const {return mActive;};

	/* The main function used to update the environment logic. Requires the
	 * time elapsed from the last frame */
	void update(float dTime);

	/* Force to play some environment by the name. The actually Environment
	 * is pushed front and it will be executed after finish this environment.
	 * REQUIRES:
	 * 		name	the name of the environment should be exist in the manager
	 */
	void forceSetEnvironment(const std::string &name);

	/* Force to jump to the next environment */
	void forceJumpEnvironment(void);

private:
	/* Helper function */
	inline bool existEnvironment(const Environment *env)
	{
		if(!env)
			return false;

		for(std::list<const Environment*>::iterator it = mEnvironments.begin();
				it != mEnvironments.end(); ++it)
			if((*it) == env)
				return true;

		return false;
	}

	/* Function to check if a GameEntity it is out of the Screen */
	inline bool isEntityInScreen(const GameEntity* ent)
	{
		if(((ent->GetPosition().x + ent->GetWidth()) < 0.0f) ||
				(ent->GetPosition().x  > mScreenX) ||
				((ent->GetPosition().y + ent->GetHeight()) < 0.0f) ||
				(ent->GetPosition().y  > mScreenY))
			return false;
		return true;
	}

	/* Insert one entity from the mMapsOutScrolling into the ScrollingManager
	 * using the logic of the actual Environment. It will take the X,Y coords
	 * to set the GameEntity */
	void insertOnScrollingMap(float x, float y);

	/* Function used to extract all the GameEntities (maps) from the
	 * ScrollingManager (in case that the Map is not belongs to the actual Env
	 * then we only put of from the Scrolling and from the MapsOnScrolling, but
	 * if the Map belongs to the Env, then we push_back to the MapOutScrolling
	 * vector). In both cases this function will add a new one map to the
	 * ScrollingManager
	 */
	void handleOutOfScreensMaps(void);

	/* Set a new Environment configuration */
	void setNewEnvironment(const Environment *env);


private:
	// the queue of all environments
	std::list<const Environment*> mEnvironments;
	// this is the pointer to the Environment that it is actually used
	const Environment *mActualEnvironmnet;
	// the index of the vector of maps
	int mMapIndex;
	// vector used to track wich Maps are in the ScrollingManager
	std::vector<GameEntity *> mMapsOnScrolling;
	// vector used for the maps that arent in the ScrollingManager
	std::vector<GameEntity *> mMapsOutScrolling;
	// the time elapsed from the start of the beginning of the actual environment
	float mElapsedTime;
	// flag to set the state of the Manager
	bool mActive;
	// screen sizes
	float mScreenX;
	float mScreenY;

};

#endif /* ENVIRONMENTMANAGER_H_ */
