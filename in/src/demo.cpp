#include "gbadev_demo.h"

#include "bn_bg_palettes.h"
#include "bn_core.h"
#include "bn_keypad.h"
#include "bn_sprite_ptr.h"
#include "bn_sprite_text_generator.h"
#include "bn_vector.h"

#include "bn_sprite_items_sprite0001.h"

#include "gbadev_gameindex.h"
#include "gbadev_music.h"
#include "gbadev_sideeffect.h"
#include "gbadev_spritefont.h"

namespace gbadev
{

GameState
demo (GameState &gameState)
{
  // Set transparent color black
  bn::bg_palettes::set_transparent_color (bn::color (0, 0, 0));

  // Sprite offset from center to bottom left corner
  const signed int x_offset = -120 + 16;
  const signed int y_offset = 80 - 16;

  // Create sprite
  bn::sprite_ptr sprite
      = bn::sprite_items::sprite0001.create_sprite (x_offset, y_offset);
  signed int x = 0;
  signed int y = 0;
  signed int z = 0;

  // Display help text
  bn::sprite_text_generator text_generator (gbadev::spriteFont);
  bn::vector<bn::sprite_ptr, 128> text_sprites;
  text_generator.set_center_alignment ();
  text_generator.generate (0, -64, "Colour / sprite demo", text_sprites);
  text_generator.generate (0, -32, "RED : LEFT / RIGHT", text_sprites);
  text_generator.generate (0, -16, "GREEN : UP / DOWN", text_sprites);
  text_generator.generate (0, 0, "BLUE : A / B", text_sprites);
  text_generator.generate (0, 32, "START : continue",
                           text_sprites);

  // Coordinates on screen / butano are:
  //
  // /-----> +x
  // |
  // |
  // V +y
  //
  // E.g (0,0) is top left once offset from center is applied.
  //
  // But we'll track our sprite in this example as:
  //
  // ^ +y
  // |
  // |
  // \-----> +x
  //
  // E.g (0,0) is bottmom left... and then set y as negative on the sprite when
  // moving.

  // loop till start key pressed
  int r = 0;
  int g = 0;
  int b = 0;
  while (!bn::keypad::start_pressed ())
    {
      // Play music if enabled
      gameState = music (gameState);
      if (bn::keypad::any_held ())
        {
          // Track keys held
          if (bn::keypad::left_held ())
            {
              --x;
            }
          else if (bn::keypad::right_held ())
            {
              ++x;
            }
          if (bn::keypad::up_held ())
            {
              ++y;
            }
          else if (bn::keypad::down_held ())
            {
              --y;
            }
          if (bn::keypad::b_held ())
            {
              --z;
            }
          else if (bn::keypad::a_held ())
            {
              ++z;
            }
          // Normalize x, y, z relative to sprite size
          if (x < 0)
            {
              x = 0;
            };
          if (x > 240 - 32)
            {
              x = 240 - 32;
            }
          if (y < 0)
            {
              y = 0;
            };
          if (y > 160 - 32)
            {
              y = 160 - 32;
            }
          if (z < 0)
            {
              z = 0;
            };
          if (z > 160)
            {
              z = 160;
            }
          // Set background transparent color based on position
          r = (x * 31) / 240;
          if (r < 0)
            {
              r = 0;
            };
          if (r > 31)
            {
              r = 31;
            }
          g = (y * 31) / 160;
          if (g < 0)
            {
              g = 0;
            };
          if (g > 31)
            {
              g = 31;
            }
          b = (z * 31) / 160;
          if (b < 0)
            {
              b = 0;
            };
          if (b > 31)
            {
              b = 31;
            }
          bn::bg_palettes::set_transparent_color (bn::color (r, g, b));
          // change sprite position
          sprite.set_x (x + x_offset);
          sprite.set_y (-y + y_offset);
        }
      bn::core::update ();
    }
  // Return to splash screen after start pressed
  GameState newGameState (std::move (gameState));
  newGameState.index = FONTTEST;
  return newGameState;
}

} // namespace gbadev
