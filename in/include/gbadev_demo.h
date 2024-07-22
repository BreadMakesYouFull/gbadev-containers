/*********************************************************************
 * gbadev_demo.h - Demo game
 * Move a sprite around the screen to change the background pixel colour.
 *
 * UP/DOWN    - red
 * LEFT/RIGHT - green
 * A/B - blue
 *
 * Ends when the START button is pressed
 *********************************************************************/
#ifndef GBADEV_DEMO_H
#define GBADEV_DEMO_H

#include "gbadev_gamestate.h"

namespace gbadev
{
/**
 * Demo game
 *
 * Move a sprite around the screen to change the background pixel colour.
 *
 * UP/DOWN    - red
 * LEFT/RIGHT - green
 * A/B - blue
 *
 * Ends when the START button is pressed
 *
 * @arg gameState - previous game state
 * @return next game state: back to splash screen
 */
GameState demo (GameState &gameState);
} // namespace gbadev

#endif
