#ifndef LEVEL_FACTORY_H
#define LEVEL_FACTORY_H


//////////////////////////////////////////////////////////////////////////
//
// File: LevelFactory.h
//
// Desc: The LevelFactory class is a typical factory. It loads the resources
//       needed by the LevelState
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include <string>
#include <map>
#include "anim.hpp"


//
// Forward declarations
//
class ImageManager;


class LevelFactory
{

public:

	LevelFactory(ImageManager* imgManager);
	virtual ~LevelFactory();

	std::map<std::string, Anim> GetPlayerAnimations();
	std::map<std::string, Anim> GetAffectablesAnimation();
	std::map<std::string, Anim> GetAffectorsAnimation();
	Anim GetMapAnimation();


private:

	ImageManager* m_ImgManager;

};



#endif // LEVEL_FACTORY_H