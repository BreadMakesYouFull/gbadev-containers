#include "gbadev_gameloop.h"

#include "gbadev_sideeffect.h"

namespace gbadev
{

bool
predicateStartPressed (GameState gameState)
{
  return (gameState.start >= 1);
}

bool
predicateAPressed (GameState gameState)
{
  return (gameState.a >= 1);
}

bool
predicateStartOrAPressed (GameState gameState)
{
  return (predicateStartPressed (gameState) || predicateAPressed (gameState));
}

bool
predicateAnyPressed (GameState gameState)
{
  const int keypresses = (
    gameState.a + 
    gameState.b + 
    gameState.l + 
    gameState.r + 
    gameState.start + 
    gameState.select + 
    gameState.left + 
    gameState.right + 
    gameState.up + 
    gameState.down
  );
  return keypresses > 0;
}

GameState
mainGameLoop (GameState &gameState)
{
  reset (gameState);
  nextIndex (gameState);
  save (gameState);
  tick (gameState);
  return gameState;
}

} // namespace gbadev
