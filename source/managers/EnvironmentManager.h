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
	 * will be reproduced when an environment ends its "reproduction time"
	 * REQUIRES:
	 * 		env != NULL and all the maps should have the same size
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
	void getActive(void) const {return mActive;};

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
		if(!ent)
			return false;

		for(std::list<const Environment*>::iterator it = mEnvironments.begin();
				it != mEnvironments.end(); ++it)
			if((*it) == env)
				return true;

		return false;
	}

private:
	// the queue of all environments
	std::list<const Environment*> mEnvironments;
	// this is the pointer to the Environment that it is actually used
	const Environment *mActualEnvironmnet;
	// the time elapsed from the start of the beginning of the actual environment
	float mElapsedTime;
	// flag to set the state of the Manager
	bool mActive;
	// screen sizes
	float mScreenX;
	float mScreenY;

};

#endif /* ENVIRONMENTMANAGER_H_ */
