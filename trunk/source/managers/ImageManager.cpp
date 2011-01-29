//////////////////////////////////////////////////////////////////////////
//
// File: ImageManager.cpp
//
// Desc: ImageManager class manages the resources like images. The user can
//       add the file path and it can get the resource using the file path.
//
// Author: Marco Antognini - hiura@romandie.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "ImageManager.h"


/*!
 \brief Load a resource before adding it.
 \details Use ResourceManager::Add in its definition,
		  and may throw a std::runtime_error if an
          error occurs.
 \note This function doesn't catch a 
       possible std::invalid_argument thrown 
	   by ResourceManager::Add.
 \param info : The data needed to build the ResourceType.
*/
const std::string& ImageManager::Load(const std::string& info) 
{
		
	// Load in a temporary object the image, and
	// then "send" it to this.
	sf::Image i;

	if (!i.LoadFromFile(info))
		throw std::runtime_error("Unable to load the file " + info);

	Add(info, i);

	return info;
		
}
