#ifndef LOADING_STATE_H
#define LOADING_STATE_H


//////////////////////////////////////////////////////////////////////////
//
//  File:   LoadingState.h
//
//  Desc:   Game state that shows a loading message before the level.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "State.h"
#include "ImageManager.h"


class LoadingState : public State
{

public:

	virtual ~LoadingState();
	static LoadingState* Instance();

	//this will execute when the state is entered
	virtual void Init(sf::RenderWindow* screen);

	//this is the states normal update function
	virtual void Execute(StateMachine* pStateMachine);

	//this will execute when the state is exited. 
	virtual void Clear();


private:

	LoadingState();

	virtual void LoadResources(sf::RenderWindow* screen);
	virtual void DestroyResources();

	sf::RenderWindow* m_pScreen; 
	sf::Sprite* m_pBackgroundImage;

	ImageManager m_ImgManager;

	float m_DelayForNextState; // Time to wait to change the current state

};


#endif // LOADING_STATE_H
