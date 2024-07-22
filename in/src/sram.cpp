#include "gbadev_sram.h"

#include "bn_sram.h"
#include "bn_string.h"

namespace gbadev
{

void
saveToSram (GameState &gameState)
{
  SramData cartSramData;
  // Format tag could be used for validation (see butano example).
  bn::array<char, 32> formatTag;
  bn::istring_base formatTagIstring (formatTag._data);
  bn::ostringstream formatTagStream (formatTagIstring);
  formatTagStream.append ("GBADEV");
  cartSramData.formatTag = formatTag;
  // Schema of sram save
  cartSramData.schema = 1;
  // Game progress
  cartSramData.progress = gameState.progress;
  // Should music be playing?
  cartSramData.music = gameState.music ? 1 : 0;
  bn::sram::write (cartSramData);
  gameState.saveChange = 0;
}

} // namespace gbadev
