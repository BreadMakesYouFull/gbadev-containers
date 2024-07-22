/*********************************************************************
 * gbadev_sideeffect.h - Functions that apply side effects.
 *********************************************************************/
#ifndef GBADEV_SIDEEFFECT_H
#define GBADEV_SIDEEFFECT_H

#include "gbadev_gamestate.h"

namespace gbadev
{

/** Update butano and tick counter */
void tick (GameState &gameState);
/** Return the next game index, based on the result of the previous game loop.
 */
void nextIndex (GameState &gameState);
/** Save progress to sram */
void save (GameState &gameState);
/** Play game music */
GameState music (GameState &gameState);
/** Track menu keys, should be used on a menu instead of ``keys`` */
void menuSelect (GameState &gameState);
/** Track buttons pressed */
void keys (GameState &gameState);
/** Reset the gamestate to default values */
void reset (GameState &gameState);
/** Draw text to screen */
void drawText (GameState &gameState);

} // namespace gbadev

#endif
