#ifndef STATE_H
#define STATE_H


//////////////////////////////////////////////////////////////////////////
//
//  Name:   State.h
//
//  Desc:   Abstract class that represent a game's state
//
//  Author: Bertoa Nicolas - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include <SFML/Graphics.hpp>


//
// Forward declarations
//
class StateMachine;


class State
{

public:

	virtual ~State() {}

	//this will execute when the state is entered
	virtual void Init(sf::RenderWindow* screen)=0;

	//this is the states normal update function
	virtual void Execute(StateMachine* pStateMachine)=0;

	//this will execute when the state is exited. 
	virtual void Clear()=0;

};


#endif // STATE_H
