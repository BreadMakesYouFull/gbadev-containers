# gbadev containers template

A demo homebrew, utilizing the butano/devprokit frameworks.

See [the main project README.md](../README.md) and for license information.

Features:

* splash screen
* menu
* game (demo)
* select (level/game/screen)
* sram save
* settings
* info

## Menu

```
[ splash ] -{ START / A }-> [--- menu ---]
                            | {UP/DOWN}  |
                            | * play     | -{A}-> [ demo     ]
                            | select     | -{A}-> [ select   ]
                            | settings   | -{A}-> [ settings ]
                            | info       | -{A}-> [ info     ]
                            --------------
```

## Game (demo)

[ demo ]
   |->{ LEFT / RIGHT }->[sprite up/down, change red]
   |->{ UP / DOWN    }->[sprite left/right, change green]
   |->{ A / B        }->[change blue]
   |->{ start        }->[ menu ]

## Select (game/level/chapter/scene)

```

[-- select ---]
|  {UP/DOWN}  |
| * back      | -{A}-> [ menu  ]
| * demo      | -{A}-> [ demo  ]
| * ...       |
--------------

```

## Info

```
[--- info  ---]
| about       | -{A/START}-> [ menu ]
| ...         | 
---------------
```

## Settings

```
[--- info  ---]
|  {UP/DOWN}  | 
| * back      | -{A}->  [ menu  ]
|  option     | -{A} -> [ change state ]
|  ...        | 
---------------
```

## Game loop state/data

### Data on the GBA

* int32 is the main datatype for the GBA, due to it's cpu.
* Maximum Integer Value : 2147483647
* Minimum Integer Value : -2147483647
* Butano adds support for a limited float representation
* Use butano types over standard STL
* Generally: declare in .h or .c, define in .c
* Further reading: https://gbadev.net/getting-started.html#tutorials & https://gbadev.net/tonc/first.html

### Game loop design pattern

The game loop can be kept considerably simple if we store as little state as needed, and try to separate "side effects" from "pure" functions.

See ``resource/gameloop_mockup.py`` or ``resource/gameloop_mockup.c`` for a prototype that mocks the user pressing "A" once per tick, and the win state being they have pressed "A" 10 times. This could be taken further by utilizing monads.

The example project only implements this for some gameloops, but the principle could be pushed much further!
