#ifndef IMANAGER_H
#define IMANAGER_H

/* This will be the generic Manager Interface to be used in all the Managers to
 * organize the execution priority of the managers */

class IManager {
public:
	IManager(){};
	virtual ~IManager();

	/* This function will take the time from the last frame */
	virtual void update(float dTime) = 0;

};

#endif
