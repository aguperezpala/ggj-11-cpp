#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H


//////////////////////////////////////////////////////////////////////////
//
// File: StateMachine.h
//
// Desc: StateMachine class manages the game states. The user can change 
//       and update the current state
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include <SFML/Graphics.hpp>


//
// Forward declarations
//
class GameManager;
class State;


class StateMachine
{

public:

	StateMachine(sf::RenderWindow* screen);

	virtual ~StateMachine();

	void ChangeState(State* pNewState);

	void Update();


private:

	State* m_pCurrentState;

	sf::RenderWindow* m_pScreen;

};


#endif // STATE_MACHINE_H