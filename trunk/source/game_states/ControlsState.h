#ifndef CONTROLSSTATE_H
#define CONTROLSSTATE_H


//////////////////////////////////////////////////////////////////////////
//
//  File:   ControlsState.h
//
//  Desc:   Game state that shows the player's controls.
//
//  Author: Nicolas Bertoa - nicobertoa@gmail.com
//
//////////////////////////////////////////////////////////////////////////


//
// Headers
//
#include "InformationState.h"


class ControlsState : public InformationState
{

public:

	virtual ~ControlsState();
	static ControlsState* Instance();

	
protected:

	void UpdateInputs(StateMachine* pStateMachine);
	
	void DrawTitle();
	void DrawContent();


private:

	ControlsState();
	
};


#endif // CONTROLSSTATE_H
