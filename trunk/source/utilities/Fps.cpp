//////////////////////////////////////////////////////////////////////////
//
//  Name:   Fps.cpp
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
#include "Fps.h"


// Initialize time limit to wait before recalculate Fps
const double Fps::TIME_LIMIT = 1.0f;


// Default constructor
Fps::Fps()
{
	
	m_Frame = 0;
	m_Fps = 0;
	m_Clock.Reset();

}


// Destructor
Fps::~Fps() {}


// Update the current fps
void Fps::Update()
{

	// Calculate the fps every second.
	if(m_Clock.GetElapsedTime() >= TIME_LIMIT)
	{
	
		// Update fps
		m_Fps = m_Frame;
		
		// Reset the current frame and clock.
		m_Frame = 0;
		m_Clock.Reset();

	}

	else
		m_Frame++;

}


int Fps::GetFPS() const
{

	return m_Fps;

}
