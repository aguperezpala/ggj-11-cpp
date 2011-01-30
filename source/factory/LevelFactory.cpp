//////////////////////////////////////////////////////////////////////////
//
// File: LevelFactory.cpp
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
#include "LevelFactory.h"
#include "ImageManager.h"
#include <cassert>


// Default constructor
LevelFactory::LevelFactory(ImageManager *imgManager) : m_ImgManager(0)
{

	assert(imgManager && "LevelFactory::LevelFactory(ImageManager *imgManager): Trying to initialize to a NULL ImgManager");
	m_ImgManager = imgManager;
	
}


// Destructor
LevelFactory::~LevelFactory() {}


// Get an Anim from an Image
Anim LevelFactory::GetAnimFromImage(const sf::Image& img, float width, float height, int howMany)
{

	// Add each frame
	Anim anim;
	for (int i=0; i<howMany; i++)
		anim.PushFrame(Frame(img, sf::IntRect(width*i, 0, width * (i+1), height)));

	return anim;

}


std::map<std::string, Anim> LevelFactory::GetPlayerAnimations()
{

	std::map<std::string, Anim> animMap;

	animMap.insert(std::pair<std::string, Anim>("straight", GetPlayerStraightAnimation()));
	animMap.insert(std::pair<std::string, Anim>("up", GetPlayerUpAnimation()));
	animMap.insert(std::pair<std::string, Anim>("down", GetPlayerDownAnimation()));
	animMap.insert(std::pair<std::string, Anim>("weapon", GetPlayerWeaponAnimation()));

	return animMap;
	
}


std::map<std::string, Anim> LevelFactory::GetAffectablesAnimation()
{

	std::map<std::string, Anim> animMap;

	m_ImgManager->Load("../../resources/images/House/House02.png");
	m_ImgManager->Load("../../resources/images/House/House03.png");
	m_ImgManager->Load("../../resources/images/House/House04.png");
		
	animMap.insert(std::pair<std::string, Anim> ("house1", GetAnimFromImage((*m_ImgManager)["../../resources/images/House/House02.png"], 122.0f, 110.0f, 1)));
	animMap.insert(std::pair<std::string, Anim>("house2", GetAnimFromImage((*m_ImgManager)["../../resources/images/House/House03.png"], 122.0f, 110.0f, 1)));
	animMap.insert(std::pair<std::string, Anim>("house3", GetAnimFromImage((*m_ImgManager)["../../resources/images/House/House04.png"], 122.0f, 110.0f, 1)));
	

	return animMap;

}


std::map<std::string, Anim> LevelFactory::GetAffectorsAnimation()
{

	std::map<std::string, Anim> animMap;

	m_ImgManager->Load("../../resources/images/fire/fireee.png");
	animMap.insert(std::pair<std::string, Anim>("fire", GetAnimFromImage((*m_ImgManager)["../../resources/images/fire/fireee.png"], 82.0f, 88.0f, 2)));
	//m_ImgManager->Load("../../resources/images/fire2/2.png");
	//animMap.insert(std::pair<std::string, Anim>("fire2", GetAnimFromImage((*m_ImgManager)["../../resources/images/fire2/2.png"], 82.0f, 88.0f, 1)));

	return animMap;

}


std::map<std::string, Anim> LevelFactory::GetMapAnimation()
{

	std::map<std::string, Anim> animMap;
	m_ImgManager->Load("../../resources/images/background/correjido prueba.png");
	animMap.insert(std::pair<std::string, Anim>("map1", GetAnimFromImage((*m_ImgManager)["../../resources/images/background/correjido prueba.png"], 1024.0f, 768.0f, 1)));
	animMap.insert(std::pair<std::string, Anim>("map2", GetAnimFromImage((*m_ImgManager)["../../resources/images/background/correjido prueba.png"], 1024.0f, 768.0f, 1)));

	return animMap;

}


Anim LevelFactory::GetPlayerStraightAnimation()
{

	m_ImgManager->Load("../../resources/images/truck/TruckFordward1.png");
	return GetAnimFromImage((*m_ImgManager)["../../resources/images/truck/TruckFordward1.png"], 200.0f, 120.0f, 1);

}


Anim LevelFactory::GetPlayerUpAnimation()
{

	m_ImgManager->Load("../../resources/images/truck/TruckUp1.png");
	return GetAnimFromImage((*m_ImgManager)["../../resources/images/truck/TruckUp1.png"], 180.0f, 115.0f, 1);

}


Anim LevelFactory::GetPlayerDownAnimation()
{

	m_ImgManager->Load("../../resources/images/truck/TruckDown1.png");
	return GetAnimFromImage((*m_ImgManager)["../../resources/images/truck/TruckDown1.png"], 180.0f, 115.0f, 1);

}


Anim LevelFactory::GetPlayerWeaponAnimation()
{

	m_ImgManager->Load("../../resources/images/truck/cannon.png");
	return GetAnimFromImage((*m_ImgManager)["../../resources/images/truck/cannon.png"], 97.0f, 88.0f, 36);

}

