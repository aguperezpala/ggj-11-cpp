/*
 * CannonHelper.h
 *
 *  Created on: 29/01/2011
 *      Author: agustin
 */

#ifndef CANNONHELPER_H_
#define CANNONHELPER_H_

#include <cmath>
#include <climits>
#include <SFML/System/Vector2.hpp>

// here are the num of sprites used to representate the 365 degrees
// The sprite must start in the 0 X Axis and rotate in the opposite clock direction.
#ifndef M_PI
#define M_PI                3.14159265358979f

#endif
#define CH_NUM_SPRITES		36
#define CH_DELTA_ANGLE		(2*M_PI/CH_NUM_SPRITES)

namespace CannonHelper {

/* Function to retrieve the number of the sprite of the cannon based on the
 * MousePosition and CannonPosition. Returns the index of the animation.
 * The cannonPos is the position of cannon axis linked to the truck */
int getAnimationIndex(const sf::Vector2<int> &mPos, const sf::Vector2<float> &cPos);


/* Functio used to get the vector direction between the cannon and the mousePosition
 * The vector returned it is normalized to 1 */
sf::Vector2f getVectoriDirection(const sf::Vector2<float> &cannonPos,
		const sf::Vector2<int> &mousePos);

/* Function to obtain the position of the extreme of the cannon, used to get
 * the position where it gonna exit the water ball. This will take the position
 * of the axis, the index of the animation used, and the length of the Cannon
 * (this is the size of the sprite minus the size to the axis)  */
sf::Vector2<float> getCannonHole(const sf::Vector2<float> &cannonPos, int spriteIndex, float size);



};

#endif /* CANNONHELPER_H_ */
