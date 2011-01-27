#ifndef CREDITSSTATE_H
#define CREDITSSTATE_H


//////////////////////////////////////////////////////////////////////////
//
//  File:   CreditsState.h
//
//  Desc:   State that shows the credits of the game (programmers, artists)
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "InformationState.h"


class CreditsState : public InformationState
{

public:

	~CreditsState();
	static CreditsState* Instance();

	
protected:

	void UpdateInputs(StateMachine* pStateMachine);
	
	void DrawTitle();
	void DrawContent();


private:

	CreditsState();

};


#endif // CREDITSSTATE_H
