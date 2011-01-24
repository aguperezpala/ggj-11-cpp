#ifndef FPS_H
#define FPS_H


//////////////////////////////////////////////////////////////////////////
//
//  Name:   Fps.h
//
//  Desc:   Fps class has functions to update and get the current 
//          frames per second.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include <SFML/Graphics.hpp>


class Fps
{

public:
	
	Fps();
	virtual ~Fps();
	
	void Update();
	int GetFPS() const;


private:

	static const double TIME_LIMIT;
	
	int m_Frame; // Current frame

	int m_Fps; // Current fps

	sf::Clock m_Clock; // The clock where we can get the milliseconds elapsed.

};


#endif // FPS_H
