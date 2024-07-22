/*********************************************************************
 * gbadev_gamestate.h - Game state
 *
 * Passed between each tick.
 * The intention being that side effects are limited to between ticks,
 * and well isolated.
 *********************************************************************/
#ifndef GBADEV_GAMESTATE_H
#define GBADEV_GAMESTATE_H

#include "bn_color.h"
#include "bn_optional.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sound_handle.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string_view.h"
#include "bn_vector.h"

#include "gbadev_spritefont.h"

namespace gbadev
{
/*! Game state
 *
 * State of the game at the current tick.
 */
typedef struct
{
  // Current game index
  int index;
  // Highest level unlocked
  int progress;
  // Save changes? 0:no 1:yes
  int saveChange;

  // ticks passed in current context
  int ticks;
  // ticks passed in total (not reset by change of game/context)
  int TICKS;
  // up keypress in current context
  int up;
  // down keypress in current context
  int down;
  // left keypress in current context
  int left;
  // right keypress in current context
  int right;
  // a keypress in current context
  int a;
  // b keypress in current context
  int b;
  // l keypress in current context
  int l;
  // r keypress in current context
  int r;
  // select keypress in current context
  int select;
  // start keypress in current context
  int start;

  // Background colour
  bn::color bgc;
  // Background 1
  bn::optional<bn::regular_bg_ptr> bg1;
  // Background 2
  bn::optional<bn::regular_bg_ptr> bg2;
  // Background 3
  bn::optional<bn::regular_bg_ptr> bg3;
  // Background 4
  bn::optional<bn::regular_bg_ptr> bg4;
  // Sound handle
  bn::optional<bn::sound_handle> music;
  // Also keep track of what we're playing
  int musicSample;
  // Is music enabled?
  int musicEnabled;
  // Text Sprites
  bn::vector<bn::sprite_ptr, 128> textSprites;
  // Text lines
  bn::span<const bn::string_view> text;
  // Text x
  int textX;
  // Text y
  int textY;

} GameState;

} // namespace gbadev

#endif
