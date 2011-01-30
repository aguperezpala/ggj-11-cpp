/*
 * ObstacleManager.cpp
 *
 *  Created on: 30/01/2011
 *      Author: agustin
 */

#include "ObstacleManager.h"




/* Function used to handle the out of screen entities */
void ObstacleManager::checkAndHandleOutEntities(void)
{
	std::vector<GameEntity *> toRemove;

	if(mObstaclesCollisionList.size() == 0)
		return;

	// we only will check all the entities that are in the collisionManager.
	// this are the only ones that are possible in screen
	for(std::list<GameEntity*>::iterator it = mObstaclesCollisionList.begin();
			it != mObstaclesCollisionList.end(); ++it) {
		if(!isEntityInScreen(*it) || !(*it)->IsActive()) {
			// we get it out from the collision list (so this will be reflected
			// in the CollisionManager, and we add it to the obstacle map
			mObstacles[(*it)->GetId()] = *it;
			toRemove.push_back((*it));
			//mObstaclesCollisionList.remove(*it);

			// we remove it from the ScrollingManager
			ScrollingManager::getInstance()->removeEntity((*it)->GetId());
		}
	}

	if(toRemove.size() != 0) {
		for(std::vector<GameEntity *>::iterator it = toRemove.begin();
				toRemove.end() != it; ++it) {
			mObstaclesCollisionList.remove((*it));
		}
	}

}

/* Function to generate the obstacles in the screen following some logic */
void ObstacleManager::generateObstacles(void)
{
	// first we check if we have available objets
	if(mObstacles.size() == 0)
		return;

	// get randomize the number of objects at the same time
	int numObjects = sf::Randomizer::Random(0,mRegions.size()-1);
	int i = 0, counter = 0;

	//get the regions
	std::vector<int> reg;
	counter = numObjects;
	while(counter > 0) {
		reg.push_back(sf::Randomizer::Random(0, mRegions.size()-1));
		counter--;
	}
	std::unique(reg.begin(), reg.end());

	// now get the objects that not exceed the minimum size
	std::vector<int> aux;
	for (int i = 0; i < numObjects; i++)
		aux.push_back(sf::Randomizer::Random(0, mObstacles.size()-1));

	std::sort(aux.begin(), aux.end());
	//get the objects
	i = 0; counter = 0;
	std::vector<GameEntity *> ents;
	for(std::map<int, GameEntity *>::iterator it = mObstacles.begin();
			it != mObstacles.end() && counter < aux.size(); ++it) {
		if(i == aux[counter]) {
			ents.push_back((*it).second);
			counter++;
		}

		i++;
	}

	// put that objects in the screen, in the scrolling manager and in the
	// collision manager
	i = 0;
	for(std::vector<GameEntity *>::iterator it = ents.begin(); it != ents.end();
			++it, i++) {
		(*it)->SetActivation(true);

		// put in the scrollling manager
		ScrollingManager::getInstance()->insertEntity((*it));

		// put in the CollisionManager
		mObstaclesCollisionList.push_back((*it));

		// extract from the available obstacles
		mObstacles.erase((*it)->GetId());

		// set the position (one of the regions)
		(*it)->SetPosition(mScreenWidth, mRegions[reg[i]]);
	}

}

void ObstacleManager::inactiveDummyCollision(void)
{
	for( int i = 0; i < mInactiveBatchs.size(); i++)
	{
		mObstaclesCollisionList.remove(mInactiveBatchs[i]);
		// put it in the available objects
		mObstacles[mInactiveBatchs[i]->GetId()] = mInactiveBatchs[i];
	}
	mInactiveBatchs.clear();
}





ObstacleManager::ObstacleManager(float screenWidth, float screenHeight,GameEntity *player)
		: mFactor(4.0f), mMinFreeLenght(0), mScreenWidth(screenWidth),
		  mScreenHeight(screenHeight),	mActivate(false)
{
	ASSERT(player);
	mPlayerList.push_back(player);

	// add to the CollisionManager
	CollisionManager::getInstance()->addCollisionLogic(&mPlayerList,
														&mObstaclesCollisionList,
														this);
}

ObstacleManager::~ObstacleManager()
{
	// TODO Auto-generated destructor stub
}

/* Function to add a region where it will be able to insert obstacles */
void ObstacleManager::insertObstacleRegion(float rect)
{
	mRegions.push_back(rect);
}

/* Set the minimun size that it have to be free to pass the truck */
void ObstacleManager::setMinFreeLength(float l)
{
	mMinFreeLenght = l;
}

/* Insert a GameEntity that would be considered an obstacle, the size
 * of the object it is important. If the length of the objetc (height) it
 * is bigger than the minimum free space, this blows up :) */
void ObstacleManager::insertObstacle(GameEntity *obstacle)
{
	ASSERT(obstacle);
	ASSERT(mObstacles.find(obstacle->GetId()) == mObstacles.end());

	mObstacles[obstacle->GetId()] = obstacle;
}

void ObstacleManager::removeObstacle(GameEntity *obstacle)
{
	ASSERT(obstacle);
	ASSERT(mObstacles.find(obstacle->GetId()) != mObstacles.end());

	mObstacles.erase(obstacle->GetId());
}
void ObstacleManager::removeAll(void)
{
	mRegions.clear();
	mObstaclesCollisionList.clear();
	mPlayerList.clear();
	mObstacles.clear();
}

/* update the entitys, This manager will work with the CollisionManager and
 * the ScrollingManager and it will activate/desactivate the entities if
 * there are no more in screen
 * This function have the logic of where to render and how fast put the
 * obstacles */
void ObstacleManager::update(float dTime)
{
	static float elapsedTime = 0;

	if(!mActivate)
		return;

	// inactivate Collision
	inactiveDummyCollision();


	// we have to check if the entities still in the screen and extract
	// and set as inactive to the collision manager.
	checkAndHandleOutEntities();

	// now the logic to put new obstacles in the screen in a delta time
	elapsedTime -= dTime;
	if(elapsedTime < 0){
		generateObstacles();
		elapsedTime = sf::Randomizer::Random(1, int(mFactor));
	}

}


/* Handle the collisions */
void ObstacleManager::handleCollision(GameEntity *source, GameEntity *target)
{
	// here we have to show the hit animation of the player..
	float newVelocity = ScrollingManager::getInstance()->getVelocity();
	newVelocity *= 0.1f;

	if(newVelocity >= 250.0f)
		ScrollingManager::getInstance()->setVelocity(newVelocity);

	// set here the new anim to the car


	// we can safety extract the target from the collision manager
	//mObstaclesCollisionList.remove(target);
	mInactiveBatchs.push_back(target);


}







