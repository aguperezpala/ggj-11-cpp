/*
 * Environment.h
 * This class is an abstaction of a Environment, this is, the maps to be
 * showed, the duration of the environment and the logic of how to be
 * shown.
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#ifndef ENVIRONMENT_H_
#define ENVIRONMENT_H_

#include <string>
#include <vector>
// own libs
#include "GameEntity.h"


/* this struct does not handle memory (allocate nor free) */
struct Environment {
	// the name of the Environment if we want to force the EnvironmentManager
	// to show this environment.
	std::string name;
	// The maps which represents the environment.
	const std::vector<GameEntity *> maps;
	// if we will show the maps randomly or sequentialy
	bool randomSelection;
	// the time duration that the environment will be shown
	float time;

	Environment(const std::string &n, const std::vector<GameEntity *> &m,
			bool r, float t) : name(n), maps(m),randomSelection(r), time(t)
	{}

};


#endif /* ENVIRONMENT_H_ */
