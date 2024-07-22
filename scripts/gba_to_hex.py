#!/usr/bin/env python
"""gba to hex

Take 3 gba r g b ints "[0-31] [0-31] [0-31]"
return a hex code "XXXXXX" (hash removed)
"""

import os
import sys
assert len(sys.argv) > 3, "Please specify hex code"
r = sys.argv[1]
g = sys.argv[2]
b = sys.argv[3]
print(
    "{:02}{:02}{:02}".format(
        hex(int(int(r) / 31 * 255))[2:],
        hex(int(int(g) / 31 * 255))[2:],
        hex(int(int(b) / 31 * 255))[2:],
    )
)
