#ifndef GAMEEXPLANATIONSTATE_H
#define GAMEEXPLANATIONSTATE_H


//////////////////////////////////////////////////////////////////////////
//
//  File:   GameExplanationState.h
//
//  Desc:   Game state that explains how to play and the game objective
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "InformationState.h"


class GameExplanationState : public InformationState
{

public:

	virtual ~GameExplanationState();
	static GameExplanationState* Instance();

	
protected:

	void UpdateInputs(StateMachine* pStateMachine);

	void DrawTitle();
	void DrawContent();


private:

	GameExplanationState();

};


#endif // GAMEEXPLANATIONSTATE_H
