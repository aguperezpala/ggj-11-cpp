/*
  resourcemanager
  Copyright (C) 2009 Marco Antognini (hiura@romandie.com)
  License : CC-BY-SA 3.0
  	You can find the full legal code at 
  	http://creativecommons.org/licenses/by-sa/3.0/
  	or in the local file cc-by-sa-3.0-legalcode.html .
  	Here is only an abstract :

  You are free :
  	to Share — to copy, distribute and transmit the work
	to Remix — to adapt the work

  Under the following conditions :
  	Attribution. You must attribute the work in the manner 
		specified by the author or licensor (but not 
		in any way that suggests that they endorse you
		or your use of the work).
	Share Alike. If you alter, transform, or build upon this 
		work, you may distribute the resulting work only 
		under the same, similar or a compatible license.

  For any reuse or distribution, you must make clear to others 
  	the license terms of this work. The best way to do this 
	is with a link to this
       	(http://creativecommons.org/licenses/by-sa/3.0/) web page.
  
  Any of the above conditions can be waived if you get 
  	permission from the copyright holder.

  Nothing in this license impairs or restricts the author's 
  	moral rights.

*/

/*!
 \file ImageManager.h
 \brief Definition and implementation of ImageManager class.
*/

#ifndef IMAGEMANAGER_HPP
#define IMAGEMANAGER_HPP


//////////////////////////////////////////////////////////////////////////
//
// File: ImageManager.h
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
#include "ResourceManager.h"
#include <string>
#include <SFML/Graphics.hpp>


class ImageManager : public ResourceManager<sf::Image, std::string, std::string> 
{

public:
		
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
	const std::string& Load(const std::string& info);
		
};


#endif // IMAGEMANAGER_HPP


