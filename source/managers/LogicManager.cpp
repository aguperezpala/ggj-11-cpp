//////////////////////////////////////////////////////////////////////////
//
// File: LogicManager.cpp
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
#include "LogicManager.h"
#include "GameEntity.h"
#include <cassert>
#include "ScrollingManager.h"
#include <iostream>


// Default constructor
LogicManager::LogicManager(float windowWidth, float windowHeight) : m_TimeOutToPlaceAffectable(0.5f), m_WindowHeight(windowHeight), m_WindowWidth(windowWidth)
{

	m_CurrentAffectableTimeOut = m_TimeOutToPlaceAffectable;

	// We must set a seed for the SFML's randomizer
	sf::Randomizer::SetSeed(10);

}


// Destructor
LogicManager::~LogicManager() {}


void LogicManager::TweakTimeOuts(float offset)
{

	m_TimeOutToPlaceAffectable *= offset;
	
	if(m_TimeOutToPlaceAffectable < m_CurrentAffectableTimeOut)
		m_CurrentAffectableTimeOut = m_TimeOutToPlaceAffectable;

}


void LogicManager::AddAffectable(GameEntity *pEntity)
{

	assert(pEntity && "LogicManager::AddAffectable(GameEntity *pEntity): Trying to initialize to NULL entity.");

	m_AffectableEntities.push_back(pEntity);

	ScrollingManager::getInstance()->insertEntity(pEntity);

}


void LogicManager::AddAffector(GameEntity *pEntity)
{

	assert(pEntity && "LogicManager::AddAffector(GameEntity *pEntity): Trying to initialize to NULL entity.");

	m_AffectorEntities.push_back(pEntity);

	ScrollingManager::getInstance()->insertEntity(pEntity);

}


void LogicManager::Update(float frameTime)
{

	TryToPlaceAffectable(frameTime);

}


void LogicManager::TryToPlaceAffectable(float frameTime)
{

	m_CurrentAffectableTimeOut -= frameTime;

	// Check if is time to put a new affectable entity
	if(m_CurrentAffectableTimeOut <= 0.0f)
	{

		// Check if we have an inactive entity to place
		for(unsigned int i=0; i<m_AffectableEntities.size(); i++)
		{

			// We found an inactive entity!
			if(!m_AffectableEntities[i]->IsActive())
			{

				m_AffectableEntities[i]->SetX(m_WindowWidth);

				// Get a Y coordinate to place the affectable entity based on probability.

				if(sf::Randomizer::Random(0.0f, 10.0f) < 5.0f)
					m_AffectableEntities[i]->SetY(-15.0f);
				else
					m_AffectableEntities[i]->SetY(600.0f);
				
				m_AffectableEntities[i]->SetActivation(true);

				// If we can affect the entity then we update its condition
				TryToPlaceAnAffector(m_AffectableEntities[i]);
				
				// Reset the time out
				m_CurrentAffectableTimeOut = m_TimeOutToPlaceAffectable;
				break;

			}

		}

	}

}


void LogicManager::TryToPlaceAnAffector(GameEntity* affectable)
{

	// Check if is time to put a new affectable entity
	if(sf::Randomizer::Random(0.0f, 10.0f) > 7.0f)
	{

		// Check if we have an inactive affector.
		for(unsigned int j=0; j<m_AffectorEntities.size(); j++)
		{

			// We found an inactive affector!
			if(!m_AffectorEntities[j]->IsActive())
			{
			
				m_AffectorEntities[j]->SetX(affectable->GetPosition().x+30.0f);
				m_AffectorEntities[j]->SetY(affectable->GetPosition().y);
				m_AffectorEntities[j]->SetActivation(true);

				break;

			}

		}

	}

}