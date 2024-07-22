/*********************************************************************
 * gbadev_spritefont.h - 8x8 fixed sprite font
 *********************************************************************/
#ifndef GBADEV_SPRITEFONT_H
#define GBADEV_SPRITEFONT_H

#include "bn_sprite_font.h"

#include "bn_sprite_items_spritefont.h"

namespace gbadev
{

// 8x8 fixed sprite font.
constexpr bn::sprite_font spriteFont (bn::sprite_items::spritefont);

} // namespace gbadev

#endif
