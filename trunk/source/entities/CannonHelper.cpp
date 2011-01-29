/*
 * CannonHelper.cpp
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#include "CannonHelper.h"


/* Function to retrieve the number of the sprite of the cannon based on the
 * MousePosition and CannonPosition. Returns the index of the animation.
 * The cannonPos is the position of cannon axis linked to the truck */
int CannonHelper::getAnimationIndex(const sf::Vector2<int> &mousePos,
		const sf::Vector2<float> &cannonPos)
{
	float q = std::abs(cannonPos.x - mousePos.x);
	float p = std::abs(cannonPos.y - mousePos.y);
	float angle;

	if(q == 0) {
		angle = 45;
	} else {
		angle = std::atan2(p,q);
	}

	// now get the absolute angle
	if(mousePos.y <= cannonPos.y) {
		if(mousePos.x >= cannonPos.x) {
			// do nothing, quarter one
		} else {
			// quarter 2
			angle = M_PI - angle;
		}
	} else if (mousePos.x >= cannonPos.x) {
		// quarter 4
		angle = 2*M_PI - angle;
	} else {
		// quarter 3
		angle = angle + M_PI;
	}

	// now we return the index of the cannon
	return (int) (angle/(float)CH_DELTA_ANGLE) + 1;

}

sf::Vector2f CannonHelper::getVectoriDirection(const sf::Vector2<float> &Current,
		const sf::Vector2<int> &Target)
{

	sf::Vector2f result;

	result.x = Target.x - Current.x;
	result.y = Target.y - Current.y;


	float length = std::sqrt((result.x * result.x) + (result.y * result.y));
	    if (length != 0)
	        return sf::Vector2f(result.x / length, result.y / length);
	    else
	        return result;
}



/* Function to obtain the position of the extreme of the cannon, used to get
 * the position where it gonna exit the water ball. This will take the position
 * of the axis, the index of the animation used, and the length of the Cannon
 * (this is the size of the sprite minus the size to the axis)  */
sf::Vector2<float> CannonHelper::getCannonHole(const sf::Vector2<float> &cannonPos,
		int spriteIndex, float size)
{

	sf::Vector2<float> result;
	float angle = CH_DELTA_ANGLE * (spriteIndex + 1);

	/*if(angle  < M_PI/2) {
		// quarter 1
		result.x = cannonPos.x + (std::cos(angle) * size);
		result.y = cannonPos.y - (std::sin(angle) * size);
	} else if (angle < M_PI) {
		// quearter 2
		angle = M_PI - angle;
		result.x = cannonPos.x - (std::cos(angle) * size);
		result.y = cannonPos.y - (std::sin(angle) * size);
	} else if (angle < 1.5f * M_PI) {
		//quearter 3
		angle = angle - M_PI ;
		result.x = cannonPos.x - (std::cos(angle) * size);
		result.y = cannonPos.y + (std::sin(angle) * size);
	} else {
		// quarter 4
		angle = 2*M_PI - angle;
		result.x = cannonPos.x + (std::cos(angle) * size);
		result.y = cannonPos.y + (std::sin(angle) * size);
	}
*/
	result.x = cannonPos.x + std::cos(angle) * size;
	result.y = cannonPos.y - std::sin(angle) * size;

	return result;



}



