//////////////////////////////////////////////////////////////////////////
//
// File: StateMachine.cpp
//
// Desc: StateMachine class manages the game states. The user can change 
//       the current state.
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "StateMachine.h"
#include <cassert>
#include "State.h"


// Default constructor
StateMachine::StateMachine(sf::RenderWindow* screen) : m_pCurrentState(0), m_pScreen(screen)
{
	
	assert(m_pScreen && "StateMachine::StateMachine(sf::RenderWindow* screen): trying to initialize with a NULL RenderWindow");
	
}


// Destructor
StateMachine::~StateMachine()
{

	m_pCurrentState = 0;
	m_pScreen = 0;

}


// Change the current state.
void StateMachine::ChangeState(State* pNewState)
{

	assert(pNewState && "StateMachine::ChangeState(State* pNewState): trying to change to NULL state");

	// Call the exit method of the existing state
	if(m_pCurrentState != 0)
		m_pCurrentState->Clear();

	// Change state to the new state
	m_pCurrentState = pNewState;

	//call the entry method of the new state
	m_pCurrentState->Init(m_pScreen);

}


// Update the current state.
void StateMachine::Update()
{

	m_pCurrentState->Execute(this);

}

