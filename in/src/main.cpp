/*********************************************************************
 * main.cpp - main entry point
 *********************************************************************/

#include "bn_core.h"
#include "bn_log.h"
#include "bn_sram.h"

#include "bn_sound_items.h"

#include "gbadev_gameindex.h"
#include "gbadev_gameloop.h"
#include "gbadev_gamestate.h"
#include "gbadev_sram.h"

int
main ()
{
  // Start engine
  bn::core::init ();
  BN_LOG ("Game init");
  // Init game state
  gbadev::GameState gameState;
  gameState.index = gbadev::SPLASH;
  gameState.ticks = 0; // current Game/Context ticks
  gameState.TICKS = 0; // Global ticks
  // Read save data
  gbadev::SramData cartSramData;
  bn::sram::read (cartSramData);
  // Init music
  gameState.musicEnabled = 0;
  gameState.musicEnabled = 0;
  gameState.musicSample = 0;
  // Load progress
  gameState.progress = cartSramData.progress == -1 ? 0 : cartSramData.progress;
  // Main game loop
  whileF (gbadev::predicateAlways<gbadev::GameState>, gbadev::mainGameLoop,
          gameState);
}
