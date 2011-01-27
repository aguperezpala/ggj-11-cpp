#ifndef THANKSSTATE_H
#define THANKSSTATE_H


//////////////////////////////////////////////////////////////////////////
//
//  File:   ThanksState.h
//
//  Desc:   Game state that shows a thanks message for playing the game.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "State.h"
#include "managers/ImageManager.h"


class ThanksState : public State
{
	
public:

	virtual ~ThanksState();
	static ThanksState* Instance();

	//this will execute when the state is entered
	virtual void Init(sf::RenderWindow* screen);

	//this is the states normal update function
	virtual void Execute(StateMachine* pStateMachine);

	//this will execute when the state is exited. 
	virtual void Clear();


private:

	ThanksState();

	virtual void LoadResources(sf::RenderWindow* screen);
	virtual void DestroyResources();
	
	sf::RenderWindow* m_pScreen; 
	sf::Sprite* m_pBackgroundImage;

	ImageManager m_ImgManager;

	float m_DelayForNextState; // Time to wait to change the current state

};


#endif // THANKSSTATE_H
