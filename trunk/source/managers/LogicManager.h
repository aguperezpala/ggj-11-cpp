#ifndef LOGIC_MANAGER_H
#define LOGIC_MANAGER_H


//////////////////////////////////////////////////////////////////////////
//
// File: LogicManager.h
//
// Desc: This class has the responsability to position entities like 
//       houses, fires or traps.
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include <vector>


//
// Forward declarations
//
class GameEntity;


class LogicManager
{

public:

	LogicManager(float windowHeight, float windowWidth);
	virtual ~LogicManager();

	void TweakTimeOuts(float offset);

	void AddAffectable(GameEntity* pEntity);
	void AddAffector(GameEntity* pEntity);

	void Update(float frameTime);


private:
	
	void UpdateAffected();

	void TryToPlaceAffectable(float frameTime); 
	void TryToPlaceAffector(float frameTime);

	float m_TimeOutToPlaceAffectable; // Time to wait before place a new affectable in the game.
	float m_CurrentAffectableTimeOut;

	float m_TimeOutToPlaceAffector;  // Time to wait before place a new affector in the game.
	float m_CurrentAffectorTimeOut;


	std::vector<GameEntity*> m_AffectableEntities; // Entities that will be affected by the affector entities.
	std::vector<bool> m_IsAffected; // This stores the state of the affectables items.
	std::vector<GameEntity*> m_AffectorEntities;   // Entities that will affect the affectable entities.

	float m_WindowHeight;
	float m_WindowWidth;

};


#endif // LOGIC_MANAGER_H