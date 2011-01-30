/*
 * PanelManager.h
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#ifndef PANELMANAGER_H_
#define PANELMANAGER_H_

#include <string>
#include <SFML/Graphics.hpp>
#include <list>

#include "GameEntity.h"


class PanelManager
{
public:
	class Panel {
	public:
		// the size of the panel it will be given by the size of the entity
		// Note that the string could not be deleted before the destruction of
		// the panel. If the var it is a null pointer then non text is shown
		Panel(sf::String *text, GameEntity *icon, const sf::Vector2f &pos);
		~Panel(void);

		/* set the position of the panel */
		void setPosition(const sf::Vector2f &p);

		void drawPanel(sf::RenderWindow *w);


	private:
		sf::String *mText;
		GameEntity *mIcon;
	};

public:
	/* the panel manager it is no responsable to free the memory allocated for
	 * the panels if there was */
	static PanelManager *getInstance();

	/* insert/removes a panel to be drawn */
	void insertPanel(Panel *p){mPanels.push_back(p);};
	void removePanel(Panel *p){mPanels.remove(p);};

	/* Draw panels */
	void update(sf::RenderWindow *w);

	void RemoveAll() { mPanels.clear(); }


protected:
	PanelManager();
	virtual ~PanelManager();

private:
	static PanelManager *mInstance;
	// the list of panels to be shown
	std::list<Panel *> mPanels;
};

#endif /* PANELMANAGER_H_ */
