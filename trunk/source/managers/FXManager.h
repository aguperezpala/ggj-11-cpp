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

	void PlayAnimation(const std::string& type, sf::Vector2<float> position, bool isScrolleable);

	void update(float frameTime);

	
private:

	FXManager();

	void CheckEndOfAnimation(std::vector<GameEntity*>* animations);

	std::map<std::string, std::vector<GameEntity*> > m_AnimationsMap;

	std::vector<GameEntity*> m_PlayingScrolleable;
	std::vector<GameEntity*> m_PlayingNoScrolleable;

};


#endif // FX_MANAGER_H
