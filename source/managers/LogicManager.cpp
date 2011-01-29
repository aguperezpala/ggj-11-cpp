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
LogicManager::LogicManager(float windowHeight, float windowWidth) : m_TimeOutToPlaceAffectable(1.0f), m_TimeOutToPlaceAffector(3.0f), m_WindowHeight(windowHeight), m_WindowWidth(windowWidth)
{

	m_CurrentAffectableTimeOut = m_TimeOutToPlaceAffectable;
	m_CurrentAffectorTimeOut = m_TimeOutToPlaceAffector;

	// We must set a seed for the SFML's randomizer
	sf::Randomizer::SetSeed(10);

}


// Destructor
LogicManager::~LogicManager() {}


void LogicManager::TweakTimeOuts(float offset)
{

	m_TimeOutToPlaceAffectable += offset;
	m_TimeOutToPlaceAffector += offset;

	if(m_TimeOutToPlaceAffectable < m_CurrentAffectableTimeOut)
		m_CurrentAffectableTimeOut = m_TimeOutToPlaceAffectable;

	if(m_TimeOutToPlaceAffector < m_CurrentAffectorTimeOut)
		m_CurrentAffectorTimeOut = m_TimeOutToPlaceAffector;

}


void LogicManager::AddAffectable(GameEntity *pEntity)
{

	assert(pEntity && "LogicManager::AddAffectable(GameEntity *pEntity): Trying to initialize to NULL entity.");

	m_AffectableEntities.push_back(pEntity);
	m_IsAffected.push_back(false);

}


void LogicManager::AddAffector(GameEntity *pEntity)
{

	assert(pEntity && "LogicManager::AddAffector(GameEntity *pEntity): Trying to initialize to NULL entity.");

	m_AffectorEntities.push_back(pEntity);

}


void LogicManager::Update(float frameTime)
{

	UpdateAffected();
	TryToPlaceAffectable(frameTime);
	TryToPlaceAffector(frameTime);

}


void LogicManager::UpdateAffected()
{


	for(unsigned int i=0; i<m_AffectableEntities.size(); i++)
	{

		// If the entity is not active, then it is not affected.
		if(!m_AffectableEntities[i]->IsActive())
			m_IsAffected[i] = false;

	}

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
				m_AffectableEntities[i]->SetY(sf::Randomizer::Random(0.0f, m_WindowHeight));
				
				m_AffectableEntities[i]->SetActivation(true);

				// Reset the time out
				m_CurrentAffectableTimeOut = m_TimeOutToPlaceAffectable;
				break;

			}

		}

	}

}


void LogicManager::TryToPlaceAffector(float frameTime)
{

	m_CurrentAffectorTimeOut -= frameTime;

	// Check if is time to put a new affectable entity
	if(m_CurrentAffectorTimeOut <= 0.0f)
	{

		// Check if we have an inactive affector.
		GameEntity* affector = 0;
		for(unsigned int j=0; j<m_AffectorEntities.size(); j++)
		{

			// We found an inactive affector!
			if(!m_AffectorEntities[j]->IsActive())
			{
			
				affector = m_AffectorEntities[j];
				break;

			}

		}

		// If we have an affector we must check if we can place it on an affectable.
		if(affector)
		{

			// Check if we have an active entity to place an affector on it.
			for(unsigned int i=0; i<m_AffectableEntities.size(); i++)
			{

				// We found an active and not affected entity!
				if(m_AffectableEntities[i]->IsActive() && m_IsAffected[i] == false)
				{

					affector->SetX(m_AffectableEntities[i]->GetPosition().x);
					affector->SetY(m_AffectableEntities[i]->GetPosition().y);

					affector->SetActivation(true);

					// Reset the time out
					m_CurrentAffectorTimeOut = m_TimeOutToPlaceAffector;

					// This entity is now affected
					m_IsAffected[i] = true;

					break;

				}

			}

		}

	}

}