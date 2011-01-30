/*
 * PanelManager.cpp
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#include "PanelManager.h"


PanelManager *PanelManager::mInstance = 0;

PanelManager::Panel::Panel(sf::String *var, GameEntity *icon,
		const sf::Vector2f &pos):mText(var), mIcon(icon)
{
	// empty
	setPosition(pos);
}

PanelManager::Panel::~Panel(void)
{
	// nothing to do
}

/* set the position of the panel */
void PanelManager::Panel::setPosition(const sf::Vector2f &p)
{
	sf::Vector2f position = p;

	if(mIcon){
		mIcon->SetPosition(position);

		if(mText){
			// set the position for the text
			position.x += mIcon->GetWidth();
			position.y += (mIcon->GetHeight() / 2.0f) - mText->GetSize()/2.0f;

			mText->SetPosition(position);
		}
	}

}

void PanelManager::Panel::drawPanel(sf::RenderWindow *w)
{
	// here it is the logic of how to render every panel
	// (every panel it will be shown equally :(
	if(mIcon) {
		w->Draw(*mIcon);
	}
	if(mText) {
		w->Draw(*mText);

	}
}



PanelManager *PanelManager::getInstance()
{
	if(!mInstance){
		mInstance = new PanelManager();
	}

	return mInstance;
}


void PanelManager::update(sf::RenderWindow *w)
{
	for(std::list<Panel *>::iterator it = mPanels.begin(); it != mPanels.end(); ++it) {
		(*it)->drawPanel(w);
	}
}


PanelManager::PanelManager()
{
	// TODO Auto-generated constructor stub

}

PanelManager::~PanelManager()
{
	// TODO Auto-generated destructor stub
}
