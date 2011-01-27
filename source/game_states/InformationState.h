#ifndef INFORMATION_STATE_H
#define INFORMATION_STATE_H


//////////////////////////////////////////////////////////////////////////
//
// File: InformationState.h
//
// Desc: Abstract state that provides functionality to states that
//       will need to show information on the screen like main menu, 
//       controls, game explanation, etc.
//
// Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "State.h"
#include "managers/ImageManager.h"


class InformationState : public State
{

public:

	InformationState();

	virtual ~InformationState();

	//this will execute when the state is entered
	virtual void Init(sf::RenderWindow* screen);

	//this is the states normal update function
	virtual void Execute(StateMachine* pStateMachine);

	//this will execute when the state is exited. 
	virtual void Clear();


protected:

	virtual void LoadResources(sf::RenderWindow* screen);
	virtual void DestroyResources();

	void InitFont();
	void InitText();

	virtual void UpdateInputs(StateMachine* pStateMachine)=0;

	void Draw();
	void DrawText();
	virtual void DrawTitle()=0;
	virtual void DrawContent()=0;

	sf::RenderWindow* m_pScreen;
	sf::Sprite* m_pBackgroundImage;

	ImageManager imgManager;

	sf::Font* m_pFont;
	sf::String* m_pText;

};



#endif // INFORMATION_STATE_H