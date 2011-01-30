#ifndef FX_MANAGER_H
#define FX_MANAGER_H


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
#include <vector>
#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


//
// Forward declarations
//
class GameEntity;


class FXManager
{

public:

	virtual ~FXManager();
	static FXManager* getInstance();

	void InsertAnimations(const std::string& type, const std::vector<GameEntity*>& animations);
	void InsertSound(const std::string& path);

	void PlayAnimation(const std::string& type, sf::Vector2<float> position, bool isScrolleable);
	void PlaySound(const std::string& path);
	
	void update(float frameTime);

	void RemoveAll() { m_AnimationsMap.clear(); m_PlayingScrolleable.clear(); m_PlayingNoScrolleable.clear(); m_SoundsMap.clear(); }

	
private:

	struct sound
	{
		
		sf::Sound sSound;
		sf::SoundBuffer sBuffer;

	};

	FXManager();

	void CheckEndOfAnimation(std::vector<GameEntity*>* animations);

	std::map<std::string, std::vector<GameEntity*> > m_AnimationsMap;
	std::map<std::string, sound> m_SoundsMap;

	std::vector<GameEntity*> m_PlayingScrolleable;
	std::vector<GameEntity*> m_PlayingNoScrolleable;

};


#endif // FX_MANAGER_H
