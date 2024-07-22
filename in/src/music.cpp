#include "gbadev_music.h"

#include "bn_random.h"

#include "bn_sound_items.h"

namespace gbadev
{

GameState
play_music (GameState &gameState)
{

  // Two approaches for playing next .wav...
  // Play Next track if sound handle exists and is inactive:
  // if (gameState.music && !gameState.music->active())
  // OR
  // Slightly overlap ticks to reduce chance for gaps.
  // if (gameState.music && (gameState.TICKS % ((60 * 5 )-2)) == 0)

  if (gameState.musicEnabled
      && (!gameState.music.has_value () || !gameState.music->active ()))
    {
      // ...play music
      ++gameState.musicSample;
      if (gameState.musicSample < 0)
        {
          gameState.musicSample = 0;
        }
      if (gameState.musicSample > 20)
        {
          gameState.musicSample = 0;
        }
      switch (gameState.musicSample)
        {
        case 0:
          gameState.music = bn::sound_items::music0000.play (1.0);
          break;
        case 1:
          gameState.music = bn::sound_items::music0001.play (1.0);
          break;
        case 2:
          gameState.music = bn::sound_items::music0002.play (1.0);
          break;
        case 3:
          gameState.music = bn::sound_items::music0003.play (1.0);
          break;
        case 4:
          gameState.music = bn::sound_items::music0004.play (1.0);
          break;
        case 5:
          gameState.music = bn::sound_items::music0005.play (1.0);
          break;
        case 6:
          gameState.music = bn::sound_items::music0006.play (1.0);
          break;
        case 7:
          gameState.music = bn::sound_items::music0007.play (1.0);
          break;
        case 8:
          gameState.music = bn::sound_items::music0008.play (1.0);
          break;
        case 9:
          gameState.music = bn::sound_items::music0009.play (1.0);
          break;
        case 10:
          gameState.music = bn::sound_items::music0010.play (1.0);
          break;
        case 11:
          gameState.music = bn::sound_items::music0011.play (1.0);
          break;
        case 12:
          gameState.music = bn::sound_items::music0012.play (1.0);
          break;
        case 13:
          gameState.music = bn::sound_items::music0013.play (1.0);
          break;
        case 14:
          gameState.music = bn::sound_items::music0014.play (1.0);
          break;
        case 15:
          gameState.music = bn::sound_items::music0015.play (1.0);
          break;
        case 16:
          gameState.music = bn::sound_items::music0016.play (1.0);
          break;
        case 17:
          gameState.music = bn::sound_items::music0017.play (1.0);
          break;
        case 18:
          gameState.music = bn::sound_items::music0018.play (1.0);
          break;
        case 19:
          gameState.music = bn::sound_items::music0019.play (1.0);
          break;
        case 20:
          gameState.music = bn::sound_items::music0020.play (1.0);
          break;
        default:
          gameState.music = bn::sound_items::music0001.play (1.0);
          break;
        }
    }
  return gameState;
}

void
play_music_random (bn::optional<bn::sound_handle> &sound_handle)
{
  // If sound handle assigned and sound not already playing...
  if (sound_handle && !sound_handle->active ())
    {
      // ...play music.
      bn::random random;
      int sample = random.get_int (4);
      switch (sample)
        {
        case 0:
          sound_handle = bn::sound_items::music0000.play (1.0);
          break;
        case 1:
          sound_handle = bn::sound_items::music0001.play (1.0);
          break;
        case 2:
          sound_handle = bn::sound_items::music0002.play (1.0);
          break;
        case 3:
          sound_handle = bn::sound_items::music0003.play (1.0);
          break;
        case 4:
          sound_handle = bn::sound_items::music0004.play (1.0);
          break;
        case 5:
          sound_handle = bn::sound_items::music0005.play (1.0);
          break;
        case 6:
          sound_handle = bn::sound_items::music0006.play (1.0);
          break;
        case 7:
          sound_handle = bn::sound_items::music0007.play (1.0);
          break;
        case 8:
          sound_handle = bn::sound_items::music0008.play (1.0);
          break;
        case 9:
          sound_handle = bn::sound_items::music0009.play (1.0);
          break;
        case 10:
          sound_handle = bn::sound_items::music0010.play (1.0);
          break;
        case 11:
          sound_handle = bn::sound_items::music0011.play (1.0);
          break;
        case 12:
          sound_handle = bn::sound_items::music0012.play (1.0);
          break;
        case 13:
          sound_handle = bn::sound_items::music0013.play (1.0);
          break;
        case 14:
          sound_handle = bn::sound_items::music0014.play (1.0);
          break;
        case 15:
          sound_handle = bn::sound_items::music0015.play (1.0);
          break;
        case 16:
          sound_handle = bn::sound_items::music0016.play (1.0);
          break;
        case 17:
          sound_handle = bn::sound_items::music0017.play (1.0);
          break;
        case 18:
          sound_handle = bn::sound_items::music0018.play (1.0);
          break;
        case 19:
          sound_handle = bn::sound_items::music0019.play (1.0);
          break;
        case 20:
          sound_handle = bn::sound_items::music0020.play (1.0);
          break;
        default:
          sound_handle = bn::sound_items::music0001.play (1.0);
          break;
        }
    }
}

} // namespace gbadev
