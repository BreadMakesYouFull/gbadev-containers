/*********************************************************************
 * gbadev_music.h - Play game music
 *********************************************************************/
#ifndef GBADEV_MUSIC_H
#define GBADEV_MUSIC_H

#include "bn_optional.h"
#include "bn_sound_handle.h"

#include "gbadev_gamestate.h"

namespace gbadev
{

/**
 * Play game soundtrack
 *
 * Iterate through wav files
 *
 * @arg gameState - current game state
 * @return gameState - current game state
 */
GameState play_music (GameState &gameState);

/**
 * Play a sound handle if not already playing.
 *
 * Selected randomly
 *
 * @arg sound_handle - to play if asigned and not already playing.
 */
void play_music_random (bn::optional<bn::sound_handle> &sound_handle);

} // namespace gbadev

#endif
