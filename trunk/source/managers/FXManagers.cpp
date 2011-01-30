//////////////////////////////////////////////////////////////////////////
//
// File: FXManager.h
//
// Desc: The FXManager class has the responsability to manage effects, like
//       explosions.
//
//
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "FXManager.h"
#include "GameEntity.h"
#include "ScrollingManager.h"


// Default constructor
FXManager::FXManager() {}


// Singleton
FXManager* FXManager::getInstance()
{

	static FXManager m_FXManager;
	return &m_FXManager;

}


// Destructor
FXManager::~FXManager() {}


void FXManager::InsertAnimations(const std::string& type, const std::vector<GameEntity*>& animations)
{

	m_AnimationsMap.insert(std::pair<std::string, std::vector<GameEntity*> > (type, animations));

}


void FXManager::PlayAnimation(const std::string& type, sf::Vector2<float> position, bool isScrolleable)
{

	std::vector<GameEntity*> animations = m_AnimationsMap[type];

	// Check if we can find an inactive animations and play it in the correct position.
	for(unsigned int i=0; i<animations.size(); i++)
	{

		if(!animations[i]->IsActive())
		{

			animations[i]->Play();
			animations[i]->SetLoop(false);
			animations[i]->SetPosition(position);
			animations[i]->SetActivation(true);

			if(isScrolleable)
			{
			
				ScrollingManager::getInstance()->insertEntity(animations[i]);
				m_PlayingScrolleable.push_back(animations[i]);

			}

			else
				m_PlayingNoScrolleable.push_back(animations[i]);
		
			break;

		}

	}

}


void FXManager::update(float frameTime)
{

	CheckEndOfAnimation(&m_PlayingNoScrolleable);
	CheckEndOfAnimation(&m_PlayingScrolleable);

}


void FXManager::CheckEndOfAnimation(std::vector<GameEntity*>* animations)
{

	for(unsigned int i=0; i<(*animations).size(); i++)
	{

		if((*animations)[i]->GetCurrentFrame() == (*animations)[i]->GetAnim()->Size()-1)
		{

			(*animations)[i]->SetActivation(false);
			animations->erase(animations->begin()+i);

		}

	}

}


void FXManager::InsertSound(const std::string &path)
{
	
	sound sn;
	assert(sn.sBuffer.LoadFromFile(path.c_str()));
	sn.sSound.SetBuffer(sn.sBuffer);

	m_SoundsMap.insert(std::pair<std::string, sound> (path, sn));

}


void FXManager::PlaySound(const std::string& path)
{



}
