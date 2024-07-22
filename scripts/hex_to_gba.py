#!/usr/bin/env python
"""hex to gba

Take a hex code "XXXXXX" (remove hash)
and return gba 15 bit colour as r g b int "[0-31] [0-31] [0-31]"
"""

import os
import sys
assert len(sys.argv) > 1, "Please specify hex code"
col = sys.argv[1]
print(
    "{} {} {}".format(
        int(int(col[0:2], 16) / 255 * 31), 
        int(int(col[2:4], 16) / 255 * 31),
        int(int(col[4:], 16) / 255 * 31)
    )
)
