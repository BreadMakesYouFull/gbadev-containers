/*********************************************************************
 *gbadev_sram.h - Save state for level progress
 *********************************************************************/
#ifndef GBADEV_SRAM_H
#define GBADEV_SRAM_H

#include "bn_array.h"

#include "gbadev_gamestate.h"

namespace gbadev
{
/*! sram_data Store current level progress as sram.
 *
 * To read save data:
 * ```
 * gbadev::sram_data cart_sram_data;
 * bn::sram::read(cart_sram_data);
 * ```
 *
 * sram data will be -1 if no previous save made!
 *
 * To write save data:
 * ```
 * cart_sram_data.level;
 * bn::sram::write(cart_sram_data);
 * ```
 */
struct SramData
{
  // format_tag - Useful for validation.
  bn::array<char, 32> formatTag;
  // schema - in case we ever want to extend saves.
  int schema;
  // progress - highest unlocked level.
  int progress;
  // Music - 1=On 0=Off
  int music;
};

/*! Save game progress to sram
 *
 * @arg gameState - current game state.
 */
void saveToSram (GameState &gameState);
} // namespace gbadev

#endif
