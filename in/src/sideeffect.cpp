#include "gbadev_sideeffect.h"

#include "bn_bg_palettes.h"
#include "bn_blending.h"
#include "bn_color.h"
#include "bn_core.h"
#include "bn_display.h"
#include "bn_fixed.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_string_view.h"
#include "bn_vector.h"

#include "gbadev_spritefont.h"

#include "gbadev_gameindex.h"
#include "gbadev_music.h"
#include "gbadev_sram.h"

namespace gbadev
{

void
tick (GameState &gameState)
{
  ++gameState.ticks;
  ++gameState.TICKS;
  if (gameState.TICKS >= 99999960)
    {
      gameState.TICKS = 0;
    }
  bn::core::update ();
}

void
nextIndex (GameState &gameState)
{
  gameState = GAMEINDEX[gameState.index](gameState);
}

void
save (GameState &gameState)
{
  int progress
      = std::max (gameState.progress, std::min (gameState.index, COMPLETE));
  if (progress > gameState.progress)
    {
      gameState.progress = progress;
      saveToSram (gameState);
    }
}

GameState
music (GameState &gameState)
{
  return play_music (gameState);
}

void
keys (GameState &gameState)
{
  if (bn::keypad::up_pressed ())
    {
      ++gameState.up;
    }
  if (bn::keypad::down_pressed ())
    {
      ++gameState.down;
    }
  if (bn::keypad::left_pressed ())
    {
      ++gameState.left;
    }
  if (bn::keypad::right_pressed ())
    {
      ++gameState.right;
    }
  if (bn::keypad::b_pressed ())
    {
      ++gameState.b;
    }
  if (bn::keypad::a_pressed ())
    {
      ++gameState.a;
    }
  if (bn::keypad::l_pressed ())
    {
      ++gameState.l;
    }
  if (bn::keypad::r_pressed ())
    {
      ++gameState.r;
    }
  if (bn::keypad::select_pressed ())
    {
      ++gameState.select;
    }
  if (bn::keypad::start_pressed ())
    {
      ++gameState.start;
    }
}

void
reset (GameState &gameState)
{
  gameState.ticks = 0;
  gameState.up = 0;
  gameState.down = 0;
  gameState.left = 0;
  gameState.right = 0;
  gameState.a = 0;
  gameState.b = 0;
  gameState.l = 0;
  gameState.r = 0;
  gameState.select = 0;
  gameState.start = 0;
  gameState.bgc = bn::color (0, 0, 0);
  bn::optional<bn::regular_bg_ptr> bg1;
  gameState.bg1 = bg1;
  bn::optional<bn::regular_bg_ptr> bg2;
  gameState.bg2 = bg2;
  bn::optional<bn::regular_bg_ptr> bg3;
  gameState.bg3 = bg3;
  bn::optional<bn::regular_bg_ptr> bg4;
  gameState.bg4 = bg4;
  bn::vector<bn::sprite_ptr, 128> textSprites;
  gameState.textSprites = textSprites;
  bn::span<const bn::string_view> text;
  gameState.text = text;
  bn::blending::set_transparency_alpha (1);
  gameState.textX = 0;
  gameState.textY = 0;
}

void
drawText (GameState &gameState)
{
  // Configure text generator
  bn::sprite_text_generator textGenerator (gbadev::spriteFont);
  textGenerator.set_center_alignment ();
  bn::vector<bn::sprite_ptr, 128> textSprites;
  gameState.textSprites = textSprites;
  // Display text
  int x = 0 + gameState.textX;
  int y = 0 + gameState.textY;
  for (const bn::string_view &line : gameState.text)
    {
      textGenerator.generate (bn::fixed_t<8> (x), bn::fixed_t<8> (y), line,
                              gameState.textSprites);
      y += 16;
    }
}

void
menuSelect (GameState &gameState)
{
  const int selection = gameState.down - gameState.up;
  const int items = gameState.text.size ();
  if (bn::keypad::any_pressed ())
    {
      int move = 0;
      if (bn::keypad::a_pressed ())
        {
          ++gameState.a;
        }
      if (bn::keypad::start_pressed ())
        {
          ++gameState.a;
        }
      if (bn::keypad::up_pressed () && selection > 0)
        {
          ++gameState.up;
          move = 16;
        }
      else if (bn::keypad::down_pressed () && selection < items - 1)
        {
          ++gameState.down;
          move = -16;
        }
      for (bn::sprite_ptr &sprite : gameState.textSprites)
        {
          sprite.set_y (sprite.y () + move);
        }
    }
}

}
