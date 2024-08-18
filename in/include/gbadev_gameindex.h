/*********************************************************************
 * gbadev_gameindex.h - Game Index
 *
 * Store an int for all splash/menu/game/scene/chapter/level(s)
 * These are then linked to function pointers in the ``GAMEINDEX``
 *
 *********************************************************************/
#ifndef GBADEV_GAMEINDEX_H
#define GBADEV_GAMEINDEX_H

#include "bn_array.h"

#include "gbadev_demo.h"
#include "gbadev_gamestate.h"
#include "gbadev_menus.h"

namespace gbadev
{

//  28 Addresses reserved for splash, menu, info, settings or other.
static const int SPLASH = 101;
static const int MENU = 102;
static const int SELECT = 103;
static const int SETTINGS = 104;
static const int INFO = 105;
static const int FONTTEST = 106;
static const int SLIDESHOW = 107;
static const int EXPLORE = 108;
// 100 Addresses reserved for games
// Note: only demo game and font test implemented in this example.
static const int GAME = 1;
static const int GAME0001 = 1;
static const int GAME0002 = 2;
static const int GAME0003 = 3;
static const int GAME0004 = 4;
static const int GAME0005 = 5;
static const int GAME0006 = 6;
static const int GAME0007 = 7;
static const int GAME0008 = 8;
static const int GAME0009 = 9;
static const int GAME0010 = 10;
static const int GAME0011 = 11;
static const int GAME0012 = 12;
static const int GAME0013 = 13;
static const int GAME0014 = 14;
static const int GAME0015 = 15;
static const int GAME0016 = 16;
static const int GAME0017 = 17;
static const int GAME0018 = 18;
static const int GAME0019 = 19;
static const int GAME0020 = 20;
static const int GAME0021 = 21;
static const int GAME0022 = 22;
static const int GAME0023 = 23;
static const int GAME0024 = 24;
static const int GAME0025 = 25;
static const int GAME0026 = 26;
static const int GAME0027 = 27;
static const int GAME0028 = 28;
static const int GAME0029 = 29;
static const int GAME0030 = 30;
static const int GAME0031 = 31;
static const int GAME0032 = 32;
static const int GAME0033 = 33;
static const int GAME0034 = 34;
static const int GAME0035 = 35;
static const int GAME0036 = 36;
static const int GAME0037 = 37;
static const int GAME0038 = 38;
static const int GAME0039 = 39;
static const int GAME0040 = 40;
static const int GAME0041 = 41;
static const int GAME0042 = 42;
static const int GAME0043 = 43;
static const int GAME0044 = 44;
static const int GAME0045 = 45;
static const int GAME0046 = 46;
static const int GAME0047 = 47;
static const int GAME0048 = 48;
static const int GAME0049 = 49;
static const int GAME0050 = 50;
static const int GAME0051 = 51;
static const int GAME0052 = 52;
static const int GAME0053 = 53;
static const int GAME0054 = 54;
static const int GAME0055 = 55;
static const int GAME0056 = 56;
static const int GAME0057 = 57;
static const int GAME0058 = 58;
static const int GAME0059 = 59;
static const int GAME0060 = 60;
static const int GAME0061 = 61;
static const int GAME0062 = 62;
static const int GAME0063 = 63;
static const int GAME0064 = 64;
static const int GAME0065 = 65;
static const int GAME0066 = 66;
static const int GAME0067 = 67;
static const int GAME0068 = 68;
static const int GAME0069 = 69;
static const int GAME0070 = 70;
static const int GAME0071 = 71;
static const int GAME0072 = 72;
static const int GAME0073 = 73;
static const int GAME0074 = 74;
static const int GAME0075 = 75;
static const int GAME0076 = 76;
static const int GAME0077 = 77;
static const int GAME0078 = 78;
static const int GAME0079 = 79;
static const int GAME0080 = 80;
static const int GAME0081 = 81;
static const int GAME0082 = 82;
static const int GAME0083 = 83;
static const int GAME0084 = 84;
static const int GAME0085 = 85;
static const int GAME0086 = 86;
static const int GAME0087 = 87;
static const int GAME0088 = 88;
static const int GAME0089 = 89;
static const int GAME0090 = 90;
static const int GAME0091 = 91;
static const int GAME0092 = 92;
static const int GAME0093 = 93;
static const int GAME0094 = 94;
static const int GAME0095 = 95;
static const int GAME0096 = 96;
static const int GAME0097 = 97;
static const int GAME0098 = 98;
static const int GAME0099 = 99;
static const int GAME0100 = 100;
static const int COMPLETE = 100;

/** Pointer to function that runs a game loop on game state.
 * @arg Current game state
 * @return Next game state
 * */
typedef GameState (*GameLoop) (GameState &);

// Forward declaration of mappings
GameState splash (GameState &gameState);
GameState menu (GameState &gameState);
GameState demo (GameState &gameState);
GameState select (GameState &gameState);
GameState settings (GameState &gameState);
GameState info (GameState &gameState);
GameState fontTest (GameState &gameState);
GameState slideshow (GameState &gameState);
GameState explore (GameState &gameState);

/** Game index lookup array.
 *
 * Maps game/chapter/level/screen IDs to a function pointer
 *
 * */
static const bn::array<GameLoop, 128> GAMEINDEX = [] {
  bn::array<GameLoop, 128> gameloops{};
  gameloops[SPLASH] = splash;
  gameloops[MENU] = mainMenu;
  gameloops[GAME] = demo;
  gameloops[SELECT] = select;
  gameloops[SETTINGS] = settings;
  gameloops[INFO] = info;
  gameloops[FONTTEST] = fontTest;
  gameloops[SLIDESHOW] = slideshow;
  gameloops[EXPLORE] = explore;
  return gameloops;
}();

} // namespace gbadev

#endif
