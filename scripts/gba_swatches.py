#!/usr/bin/env python
"""Palette generation for use with ``slate`` pixel editor or other applications.

Usage:
```
./gba_swatches.py output_directory
```

```
The GBA can only represent either:
* 16 x  16 colour palettes
* 1  x 256 colour palette

15bit colours are used in a 16bit byte:
[x][r][r][r][r][r][g][g][g][g][g][b][b][b][b][b]
```

Palettes provided by this script:

* gba_all.json
* gba_256.json
* gba_16.json

Useful reading:
https://www.alanzucconi.com/2015/09/30/colour-sorting/
"""

import os
import sys
assert len(sys.argv) > 1, "Please specify output directory"
assert os.path.isdir(sys.argv[1]), "Output directory does not exist"
output_directory = sys.argv[1]

import colorsys
import copy
import json

swatch = {
    "swatch": {
        "colours": []
    }
}

# All the colours the GBA can represent
# 15-bit rgb [0-31]x3 -> standard rgb hex
rgb_gba = sorted(
    (
        {
            "rgb": (
                int(r / 31 * 255),
                int(g / 31 * 255),
                int(b / 31 * 255)
            ),
            "gba": (r, g, b)
        }
        for r in range(32)
        for g in range(32)
        for b in range(32)
    ),
    key=lambda rgb_map: colorsys.rgb_to_hsv(rgb_map["rgb"][0] / 31 * 255, rgb_map["rgb"][1] / 31 * 255, rgb_map["rgb"][2] / 31 * 255)
)
colours = [
    {
        "colour": f"#{hex(c['rgb'][0])[2:]:02}{hex(c['rgb'][1])[2:]:02}{hex(c['rgb'][2])[2:]:02}",
        "name": f"gba_0_to_31({c['gba'][0]},{c['gba'][1]},{c['gba'][2]})"
    }
    for c in rgb_gba
]
gba_swatch_all = copy.deepcopy(swatch)
gba_swatch_all["swatch"]["colours"] = [{"colour": c["colour"], "name": c["name"]} for c in colours]
with open(output_directory + '/gba_all.json', 'w', encoding='utf-8') as f:
    json.dump(gba_swatch_all, f, ensure_ascii=False, indent=4)

# 256 colour palette
increment_256 = len(colours) // 256
gba_swatch_256 = copy.deepcopy(swatch)
gba_swatch_256["swatch"]["colours"] = [{"colour": colours[i*increment_256]["colour"], "name": colours[i*increment_256]["name"]} for i in range(256)]
with open(output_directory + '/gba_256.json', 'w', encoding='utf-8') as f:
    json.dump(gba_swatch_256, f, ensure_ascii=False, indent=4)

# Simple 16 colour palette
increment_16 = len(colours) // 16
gba_swatch_16 = copy.deepcopy(swatch)
gba_swatch_16["swatch"]["colours"] = [{"colour": colours[i*increment_16]["colour"], "name": colours[i*increment_16]["name"]} for i in range(16)]
with open(output_directory + '/gba_16.json', 'w', encoding='utf-8') as f:
    json.dump(gba_swatch_16, f, ensure_ascii=False, indent=4)

