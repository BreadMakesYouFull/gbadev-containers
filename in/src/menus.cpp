// Butano libs
#include "bn_bg_palettes.h"
#include "bn_blending.h"
#include "bn_core.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_optional.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sound_handle.h"
#include "bn_sprite_ptr.h"
#include "bn_string.h"
#include "bn_vector.h"

// Assets
#include "bn_regular_bg_items_bigbg.h"
#include "bn_regular_bg_items_menu.h"
#include "bn_regular_bg_items_menu_select_bg.h"
#include "bn_regular_bg_items_splash1.h"
#include "bn_regular_bg_items_splash2.h"
#include "bn_regular_bg_items_whale.h"
#include "bn_regular_bg_items_whale16.h"
#include "bn_sound_items.h"

// Project files
#include "gbadev_gameindex.h"
#include "gbadev_gameloop.h"
#include "gbadev_gamestate.h"
#include "gbadev_music.h"
#include "gbadev_sideeffect.h"
#include "gbadev_spritefont.h"

namespace gbadev
{

GameState
splash (GameState &gameState)
{
  // Draw BG
  gameState.bgc = bn::color (7, 18, 31);
  bn::bg_palettes::set_transparent_color (gameState.bgc);
  gameState.bg2 = bn::regular_bg_items::whale.create_bg (5, 42);
  gameState.bg1 = bn::regular_bg_items::splash1.create_bg (0, 0);
  gameState.bg1->set_blending_enabled (true);
  bn::blending::set_transparency_alpha (0.4);
  // Draw Text
  bn::string_view text[] = { "GBADEV containers demo", "", "press START to continue" };
  gameState.text = text;
  gameState.textY = -32;
  drawText (gameState);
  // Loop
  whileF (
      predicateStartOrAPressed,
      [] (GameState &deltaGameState) -> GameState {
        deltaGameState = music (deltaGameState);
        keys (deltaGameState);
        if (deltaGameState.ticks % 4 == 0){
	  deltaGameState.bg2->set_x (deltaGameState.bg2->x () + 2);
          deltaGameState.bg2->set_y (deltaGameState.bg2->y () + 1);
	}
        if (deltaGameState.ticks % 5 == 0)
          {
            deltaGameState.bg1->set_y (deltaGameState.bg1->y () + 1);
          };
        tick (deltaGameState);
        return deltaGameState;
      },
      gameState, false);
  // Set next game state
  gameState.index = MENU;
  return gameState;
}

GameState
mainMenu (GameState &gameState)
{
  // Draw BG
  gameState.bgc = bn::color (0, 0, 31);
  bn::bg_palettes::set_transparent_color (gameState.bgc);
  gameState.bg1 = bn::regular_bg_items::menu.create_bg (0, 0);
  gameState.bg1->set_blending_enabled (true);
  bn::blending::set_transparency_alpha (0.75);
  gameState.bg3 = bn::regular_bg_items::splash2.create_bg (0, 42);
  // Menu Select BG
  gameState.bg2 = bn::regular_bg_items::menu_select_bg.create_bg (0, 0);
  // Draw Text
  bn::string_view text[] = { "play", "select", "settings", "info" };
  gameState.text = text;
  drawText (gameState);
  // Loop
  gameState = whileF (
      predicateStartOrAPressed,
      [] (GameState &deltaGameState) -> GameState {
        if (deltaGameState.ticks % 5 == 0)
        {
          deltaGameState.bg1->set_y (deltaGameState.bg1->y () + 1);
        };
        deltaGameState = music (deltaGameState);
        menuSelect (deltaGameState);
        tick (deltaGameState);
        return deltaGameState;
      },
      gameState, false);
  // Get selection
  const int selection = gameState.down - gameState.up;
  switch (selection)
    {
    case 0:
      gameState.index = GAME;
      break;
    case 1:
      gameState.index = SELECT;
      break;
    case 2:
      gameState.index = SETTINGS;
      break;
    case 3:
      gameState.index = INFO;
      break;
    default:
      gameState.index = SPLASH;
      break;
    }
  return gameState;
}

GameState
select (GameState &gameState)
{
  // Draw BG
  gameState.bgc = bn::color (10, 6, 7);
  bn::bg_palettes::set_transparent_color (gameState.bgc);
  gameState.bg1 = bn::regular_bg_items::menu.create_bg (0, 0);
  gameState.bg1->set_blending_enabled (true);
  bn::blending::set_transparency_alpha (0.75);
  // Menu Select BG
  gameState.bg2 = bn::regular_bg_items::menu_select_bg.create_bg (0, 0);
  // Draw Text
  bn::string_view text[] = {
    "< back",
    "Sprite test",
    "Font test",
    "GBADEV slides",
    "Explore"
  };
  gameState.text = text;
  drawText (gameState);
  // Loop
  gameState = whileF (
      predicateStartOrAPressed,
      [] (GameState &deltaGameState) -> GameState {
        deltaGameState = music (deltaGameState);
        menuSelect (deltaGameState);
        tick (deltaGameState);
        return deltaGameState;
      },
      gameState, false);
  // Get selection
  const int selection = gameState.down - gameState.up;
  switch (selection)
    {
    case 0:
      gameState.index = MENU;
      break;
    case 1:
      gameState.index = GAME;
      break;
    case 2:
      gameState.index = FONTTEST;
      break;
    case 3:
      gameState.index = SLIDESHOW;
      break;
    case 4:
      gameState.index = EXPLORE;
      break;
    default:
      gameState.index = SELECT;
      break;
    }
  return gameState;
}

GameState
fontTest (GameState &gameState)
{
  // Draw BG
  gameState.bgc = bn::color (31, 0, 31);
  bn::bg_palettes::set_transparent_color (gameState.bgc);
  // Draw Text
  constexpr bn::string_view text[] = { "",
                                       "Font text",
				       "",
                                       "0123456789",
                                       "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
                                       "abcdefghijklmnopqrstuvwxyz",
                                       "!\"#$%&'()*+,-./\\",
                                       ":;<=>?@[]^_`{|}~",
				       "",
                                       "press START to continue" };
  gameState.text = text;
  gameState.textX = 0;
  gameState.textY = -(bn::display::height () / 2);
  drawText (gameState);
  // Loop
  whileF (
      predicateStartPressed,
      [] (GameState &deltaGameState) -> GameState {
        deltaGameState = music (deltaGameState);
        keys (deltaGameState);
        tick (deltaGameState);
        return deltaGameState;
      },
      gameState, false);
  // Set next game state
  gameState.index = SLIDESHOW;
  return gameState;
}

GameState
settings (GameState &gameState)
{
  // Draw BG
  gameState.bgc = bn::color (31, 16, 0);
  bn::bg_palettes::set_transparent_color (gameState.bgc);
  gameState.bg1 = bn::regular_bg_items::menu.create_bg (0, 0);
  gameState.bg1->set_blending_enabled (true);
  bn::blending::set_transparency_alpha (0.75);
  // Menu Select BG
  gameState.bg2 = bn::regular_bg_items::menu_select_bg.create_bg (0, 0);
  // Draw Text
  bn::string_view text[]
      = { "< back", gameState.musicEnabled == 1 ? "Sound ON" : "Sound OFF" };
  gameState.text = text;
  drawText (gameState);
  // Loop
  gameState = whileF (
      predicateStartOrAPressed,
      [] (GameState &deltaGameState) -> GameState {
        deltaGameState = music (deltaGameState);
        menuSelect (deltaGameState);
        tick (deltaGameState);
        return deltaGameState;
      },
      gameState, false);
  // Get selection
  const int selection = gameState.down - gameState.up;
  switch (selection)
    {
    case 0:
      gameState.index = MENU;
      break;
    case 1:
      if (gameState.music.has_value ())
        {
          gameState.music->stop ();
          gameState.music.reset ();
          gameState.musicEnabled = 0;
        }
      else
        {
          gameState.musicEnabled = 1;
          gameState.musicSample = 0;
        }
      gameState.index = SETTINGS;
      gameState.saveChange = 1;
      break;
    default:
      gameState.index = SETTINGS;
      break;
    }
  return gameState;
}

GameState
info (GameState &gameState)
{
  // Draw BG
  gameState.bgc = bn::color (0, 31, 0);
  bn::bg_palettes::set_transparent_color (gameState.bgc);
  gameState.bg1 = bn::regular_bg_items::menu.create_bg (0, 0);
  gameState.bg1->set_blending_enabled (true);
  bn::blending::set_transparency_alpha (0.75);
  gameState.textX = 0;
  gameState.textY = -(bn::display::height () / 2);
  // Draw Text
  bn::string_view text[] = { "",
                             "GBADEV demo",
                             "",
                             "By - BreadMakesYouFull",
                             "For - GBA Jam 2004",
                             "Engine - butano",
                             "Toolchain - devkitpro",
                             "Via - podman / make / mgba",
                             "Font - besciii (Damian Vila)" };
  gameState.text = text;
  drawText (gameState);
  // Loop
  whileF (
      predicateStartOrAPressed,
      [] (GameState &deltaGameState) -> GameState {
        deltaGameState = music (deltaGameState);
        keys (deltaGameState);
        tick (deltaGameState);
        return deltaGameState;
      },
      gameState, false);
  // Set next game state
  gameState.index = MENU;
  return gameState;
}

GameState
explore (GameState &gameState)
{
  // Draw BG
  gameState.bgc = bn::color (0, 0, 0);
  bn::bg_palettes::set_transparent_color (gameState.bgc);
  gameState.bg1 = bn::regular_bg_items::bigbg.create_bg (0, 0);
  gameState.bg2 = bn::regular_bg_items::whale16.create_bg (5, 42);
  // Draw Text
  bn::string_view text[] = { "Feel free to explore", "press START to exit" };
  gameState.text = text;
  gameState.textY = -64;
  drawText (gameState);
  // Loop
  whileF (
      predicateStartPressed,
      [] (GameState &deltaGameState) -> GameState {
        deltaGameState = music (deltaGameState);
        keys (deltaGameState);
        if (bn::keypad::left_held())  { deltaGameState.bg1->set_x ( deltaGameState.bg1->x() + 2); }
        if (bn::keypad::right_held())  { deltaGameState.bg1->set_x ( deltaGameState.bg1->x() - 2); }
        if (bn::keypad::up_held())  { deltaGameState.bg1->set_y ( deltaGameState.bg1->y() + 2); }
        if (bn::keypad::down_held())  { deltaGameState.bg1->set_y ( deltaGameState.bg1->y() - 2); }
        if (bn::keypad::left_held())  { deltaGameState.bg2->set_x ( deltaGameState.bg2->x() - 1); }
        if (bn::keypad::right_held())  { deltaGameState.bg2->set_x ( deltaGameState.bg2->x() + 1); }
        if (bn::keypad::up_held())  { deltaGameState.bg2->set_y ( deltaGameState.bg2->y() - 1); }
        if (bn::keypad::down_held())  { deltaGameState.bg2->set_y ( deltaGameState.bg2->y() + 1); }
        tick (deltaGameState);
        return deltaGameState;
      },
      gameState, false);
  // Set next game state
  gameState.index = MENU;
  return gameState;
}

} // namespace gbadev
