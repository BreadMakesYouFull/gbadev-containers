#include "gbadev_slides.h"

#include "bn_bg_palettes.h"
#include "bn_blending.h"
#include "bn_color.h"
#include "bn_core.h"
#include "bn_display.h"
#include "bn_keypad.h"
#include "bn_optional.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sound_handle.h"
#include "bn_sprite_ptr.h"
#include "bn_string.h"
#include "bn_vector.h"

#include "bn_regular_bg_items_splash1.h"
#include "bn_regular_bg_items_whale.h"

#include "gbadev_gameindex.h"
#include "gbadev_gameloop.h"
#include "gbadev_gamestate.h"
#include "gbadev_sideeffect.h"

namespace gbadev
{

GameState
slideshow (GameState &gameState)
{
  bn::array<bn::span<const bn::string_view>, 128> slides;
  
  bn::string_view slide0[] = {
  "",
  "GBADEV containers",
  "",
  "",
  "",
  "",
  "",
  "",
  "D-pad: move whale",
  "    [1/15] A>"
  };
  
  bn::string_view slide1[] = {
  "",
  "Making games with OCI",
  "",
  "* How was this demo made?",
  "* What tools can I use?",
  "* Can I make a GBA game?",
  "",
  "",
  "",
  "<B  [2/15] A>"
  };
  
  bn::string_view slide2[] = {
  "",
  "OCI CONTAINERS",
  "(Open Container Initiative)",
  "Software builds that:",
  "* run cross platform",
  "* bundle dependencies",
  "* are snapshots",
  "* are extensible",
  "",
  "<B [3/15] A>"
  };
  
  bn::string_view slide3[] = {
  "",
  "",
  "IMMUTABLE SNAPSHOTS",
  "Why should I care?",
  "",
  "Less \"...it works for me\"",
  "",
  "More \"it works for us\" :)",
  "",
  "<B [4/15] A>"
  };
  
  bn::string_view slide4[] = {
  "",
  "EXTENSIBLE SNAPSHOTS",
  "base image(s) + package(s)",
  "= GBADEV environment!",
  "",
  "FROM debian",
  "FROM  devkitpro/devkitarm",
  "RUN {install packages}",
  "",
  "<B [5/15] A>"
  };
  
  bn::string_view slide5[] = {
  "",
  "DOCKER / PODMAN",
  "",
  "OCI build managers",
  "",
  "Less time debugging builds,",
  "more time writing games.",
  "",
  "",
  "<B [6/15] A>"
  };
  
  bn::string_view slide6[] = {
  "",
  "DEBIAN",
  "",
  "Stable & flexible",
  "Linux distribution.",
  "",
  "linux kernel + userspace",
  "& open source packages.",
  "",
  "<B [7/15] A>"
  };
  
  bn::string_view slide7[] = {
  "",
  "",
  "DEVKITPRO (ARM)",
  "",
  "Powerful build toolchain,",
  "with support for the GBA.",
  "",
  "",
  "",
  "<B [8/15] A>"
  };
  
  bn::string_view slide8[] = {
  "",
  "",
  "BUTANO",
  "",
  "Modern C++ game engine",
  "for the GBA.",
  "Thoroughly documented.",
  "Written in C++.",
  "",
  "<B [9/15] A>"
  };
  
  bn::string_view slide9[] = {
  "",
  "",
  "MGBA",
  "",
  "Accurate GBA emulation.",
  "Enabling homebrew.",
  "",
  "",
  "",
  "<B [10/15] A>"
  };
  
  bn::string_view slide10[] = {
  "",
  "",
  "POWERED BY OPEN SOURCE",
  "",
  "Made possible by",
  "open source developers",
  "and communities.",
  "",
  "",
  "<B [11/15] A>"
  };
  
  bn::string_view slide11[] = {
  "",
  "\"I JUST WANT TO MAKE A GAME!\"",
  "",
  "* Learn some basic C++",
  "* Read the butano docs",
  "* See butano template",
  "* ... or this project",
  "* Respect licenses",
  "* Consider open source",
  "<B [12/15] A>"
  };
  
  bn::string_view slide12[] = {
  "",
  "",
  "Learn more...",
  "Other frameworks..",
  "Other tools...",
  "",
  "gbadev.net",
  "",
  "",
  "<B [13/15] A>"
  };
  
  bn::string_view slide13[] = {
  "",
  "",
  "Use thise project:",
  "",
  "github.com",
  "/BreadMakesYouFull",
  "/gbadev-containers"
  "",
  "",
  "",
  "<B [14/15] A>"
  };
  
  bn::string_view slide14[] = {
  "",
  "Thanks for reading!",
  "",
  "",
  "",
  "",
  "",
  "",
  "- press START or A -",
  "<B [15/15]"
  "",
  };
  
  slides[0] = slide0;
  slides[1] = slide1;
  slides[2] = slide2;
  slides[3] = slide3;
  slides[4] = slide4;
  slides[5] = slide5;
  slides[6] = slide6;
  slides[7] = slide7;
  slides[8] = slide8;
  slides[9] = slide9;
  slides[10] = slide10;
  slides[11] = slide11;
  slides[12] = slide12;
  slides[13] = slide13;
  slides[14] = slide14;

  bn::array<bn::color, 128> slideBgc;
  slideBgc[0] = bn::color(7, 18, 31);
  slideBgc[1] = bn::color(11, 15, 25);
  slideBgc[2] = bn::color(17, 14, 30);
  slideBgc[3] = bn::color(5, 5, 14);
  slideBgc[4] = bn::color(9, 8, 17);
  slideBgc[5] = bn::color(17, 2, 19);
  slideBgc[6] = bn::color(26, 1, 10);
  slideBgc[7] = bn::color(1, 6, 13);
  slideBgc[8] = bn::color(31, 13, 6);
  slideBgc[9] = bn::color(11, 3, 20);
  slideBgc[10] = bn::color(11, 20, 20);
  slideBgc[11] = bn::color(4, 3, 6);
  slideBgc[12] = bn::color(0, 0, 0);
  slideBgc[13] = bn::color(21, 10, 31);
  slideBgc[14] = bn::color(0, 0, 0);


  int slideNum = 0;
  int whale_x = 60;
  int whale_y = 50;
  while(slideNum <= 14){
    gameState.bgc = slideBgc[slideNum];
    bn::bg_palettes::set_transparent_color (gameState.bgc);
    gameState.bg1 = bn::regular_bg_items::whale.create_bg (whale_x, whale_y);
    gameState.bg2 = bn::regular_bg_items::splash1.create_bg (0, 0);
    gameState.bg2->set_blending_enabled (true);
    bn::blending::set_transparency_alpha (0.4);
    gameState.textX = 0;
    gameState.textY = -(bn::display::height () / 2);
    // Draw Text
    gameState.text = slides[slideNum];
    drawText (gameState);
    // Loop
    gameState = whileF (
        predicateAnyPressed,
        [] (GameState &deltaGameState) -> GameState {
          deltaGameState = music (deltaGameState);
          keys (deltaGameState);

    // Move whale
    if (bn::keypad::left_held())  { deltaGameState.bg1->set_x ( deltaGameState.bg1->x() - 1); }
    if (bn::keypad::right_held())  { deltaGameState.bg1->set_x ( deltaGameState.bg1->x() + 1); }
    if (bn::keypad::up_held())  { deltaGameState.bg1->set_y ( deltaGameState.bg1->y() - 1); }
    if (bn::keypad::down_held())  { deltaGameState.bg1->set_y ( deltaGameState.bg1->y() + 1); }

          tick (deltaGameState);
          return deltaGameState;
        },
        gameState, false);
    whale_x = gameState.bg1->x().integer();
    whale_y = gameState.bg1->y().integer();
    // Set next game state
    if (
      gameState.a > 0
      || gameState.r > 0
      || gameState.start > 0
      ) {
      ++slideNum;
    }
    if (
      gameState.b > 0
      || gameState.l > 0
      || gameState.select > 0
      ) {
      --slideNum;
    }
    if(slideNum < 0) {
      slideNum = 0;
    }


    reset(gameState);

  }

  gameState.index = EXPLORE;
  return gameState;

}

} // namespace gbadev
