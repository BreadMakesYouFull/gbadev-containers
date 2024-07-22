/*********************************************************************
 *gbadev_gameloop.h - Game loop and predicates
 *********************************************************************/
#ifndef GBADEV_GAMELOOP_H
#define GBADEV_GAMELOOP_H

#include "gbadev_gamestate.h"

namespace gbadev
{

/**
 * Functional while loop
 *
 * Not technically a pure function, because uses a vanilla while.
 * This is to avoid recursion (memory) limit.
 *
 * @tparam Predicate - Conditional for each loop.
 * @tparam Function - Operation for each loop.
 * @tparam Accumulator - Value to operate on.
 * @tparam Expected - Value to match predicate against.
 * @arg predicate - The while loop will run until ``predicate == expected``..
 * @arg function - This will be run until the ``predicate == expected``.
 * @arg accumulator - Counts loop, tracks state, passed to function and
 * predicate each loop.
 * @arg expected - halt when this value does not match predicate
 * @return final value of accumulator.
 */
template <typename Predicate, typename Function, typename Accumulator,
          typename Expected = bool>
Accumulator
whileF (Predicate predicate, Function function, Accumulator &accumulator,
        Expected expected = true)
{
  while (predicate (accumulator) == expected)
    {
      accumulator = function (accumulator);
    }
  return accumulator;
}

/**
 * Predicate that always returns ``true``
 *
 * For use with ``whileF`` when you do not want to end the loop.
 *
 * @tparam Accumulator - Value to operate on (unused)
 * @arg accumulator - Ignored in favour of always returning ``true``
 * @return always true
 */
template <typename Accumulator>
bool
predicateAlways (__attribute__ ((unused)) Accumulator accumulator)
{
  return true;
}

/**
 * Predicate that returns ``true`` if START pressed
 * @arg gameState - gameState to inspect.
 * @return ``true`` if START pressed.
 */
bool predicateStartPressed (GameState gameState);

/**
 * Predicate that returns ``true`` if A pressed
 * @arg gameState - gameState to inspect.
 * @return ``true`` if A pressed.
 */
bool predicateAPressed (GameState gameState);

/**
 * Predicate that returns ``true`` if START of A pressed
 * @arg gameState - gameState to inspect.
 * @return ``true`` if START or A pressed.
 */
bool predicateStartOrAPressed (GameState gameState);

/**
 * Predicate that returns ``true`` if any key pressed
 * @arg gameState - gameState to inspect.
 * @return ``true`` if START or A pressed.
 */
bool predicateAnyPressed (GameState gameState);

/**
 * Main game loop
 *
 * Hands responsibility to the internal game loops for each menu / game,
 * via the game index.
 * Uses the previous game state to create the next one with any changes.
 *
 * @arg gameState - previous game state
 * @return next game state.
 */
GameState mainGameLoop (GameState &gameState);

} // namespace gbadev

#endif
