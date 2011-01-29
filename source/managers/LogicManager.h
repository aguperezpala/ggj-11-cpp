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

	LogicManager();
	virtual ~LogicManager();

	void AddAffectable(GameEntity* pEntity);
	void AddAffector(GameEntity* pEntity);

	void Update();


private:

	std::vector<GameEntity*> m_AffectableEntities; // Entities that will be affected by the affector entities.
	std::vector<GameEntity*> m_AffectorEntities;   // Entities that will affect the affectable entities.

};


#endif // LOGIC_MANAGER_H