/*********************************************************************
 * gbadev_menus.h - Menu screens
 *
 * Non game screens.
 *********************************************************************/
#ifndef GBADEV_MENUS_H
#define GBADEV_MENUS_H

#include "gbadev_gamestate.h"

namespace gbadev
{

/** Splash screen */
GameState splash (GameState &gameState);
/** Main Menu */
GameState mainMenu (GameState &gameState);
/** Select a level / game / chapter */
GameState select (GameState &gameState);
/** Settings menu */
GameState settings (GameState &gameState);
/** Information */
GameState info (GameState &gameState);
/** Font test */
GameState fontTest (GameState &gameState);

} // namespace gbadev

#endif
