#!/usr/bin/env python
"""GIMP plugin - butano bmp export

* flatten image
* convert to 256 indexed colours
* set to 8bit precision
* post process to remove colourspace information
* save to gbadev project
"""

from gimpfu import *
import copy
import os
import subprocess

SAVE_DIR=os.getenv("BUTANO_GRAPHICS_PATH", "/tmp/")

def python_fu_butano_export(img, drawable, palette_colours, kind):
    # -- start undo group -- #
    pdb.gimp_image_undo_group_start(img)
    # Current image
    # Flatten the image
    pdb.gimp_image_flatten(img)
    # Set image precision to 8-bit
    if not pdb.gimp_image_get_precision(img) == PRECISION_U8_GAMMA:
        pdb.gimp_image_convert_precision(img, PRECISION_U8_GAMMA)
    # Convert to indexed colors with ``palette_colours`` colours
    if not pdb.gimp_drawable_is_indexed(pdb.gimp_image_get_active_drawable(img)):
        pdb.gimp_image_convert_indexed(img, CONVERT_DITHER_NONE, MAKE_PALETTE, palette_colours, False, False, "")
    pdb.gimp_image_undo_group_end(img)
    # -- end undo group -- # 
    # Save image
    drawable = pdb.gimp_image_get_active_drawable(img)
    try:
        if os.path.isdir(SAVE_DIR):
            i = 1
            while os.path.exists(os.path.join(SAVE_DIR, "{}{:04}.bmp".format(kind, i))):
                i += 1
            filepath = os.path.join(SAVE_DIR, "{}{:04}.bmp".format(kind, i))
            sidecar = os.path.join(SAVE_DIR, "{}{:04}.json".format(kind, i))
            pdb.file_bmp_save(img, drawable, filepath, filepath)
            print("saved to {}".format(filepath))
            with open(sidecar, "w") as f:
                f.write('{\n    "type": "' + kind + '"\n}')
                print("saved to {}".format(sidecar))
            try:
                print(
                    subprocess.check_output(
                        ["bmp_post_process", str(palette_colours), filepath, filepath]
                    )
                )
            except:
                print("bmp post process script not found! You will need to remove colourspace (check the butano docs)")
        else:
            print("could not save to {}".format(SAVE_DIR))
    except:
        print("could not save to {}".format(SAVE_DIR))



def python_fu_butano_256_regular_bg(img, drawable):
    python_fu_butano_export(img, drawable, 256, "regular_bg")
register(
    "python_fu_butano_256_regular_bg",
    "Flatten and Export butano regular_bg (256 colours)",
    "Flatten and Export butano regular_bg (256 colours)",
    "BreadMakesYouFull",
    "BreadMakesYouFull",
    "2024",
    "<Image>/Butano/Flatten and Export butano regular_bg (256 colours)",
    "*",  # Image type
    [],
    [],
    python_fu_butano_256_regular_bg
)


def python_fu_butano_16_regular_bg(img, drawable):
    python_fu_butano_export(img, drawable, 16, "regular_bg")
register(
    "python_fu_butano_16_regular_bg",
    "Flatten and Export butano regular_bg (16 colours)",
    "Flatten and Export butano regular_bg (16 colours)",
    "BreadMakesYouFull",
    "BreadMakesYouFull",
    "2024",
    "<Image>/Butano/Flatten and Export butano regular_bg (16 colours)",
    "*",  # Image type
    [],
    [],
    python_fu_butano_16_regular_bg
)

def python_fu_butano_256_sprite(img, drawable):
    python_fu_butano_export(img, drawable, 256, "sprite")
register(
    "python_fu_butano_256_sprite",
    "Flatten and Export butano sprite (256 colours)",
    "Flatten and Export butano sprite (256 colours)",
    "BreadMakesYouFull",
    "BreadMakesYouFull",
    "2024",
    "<Image>/Butano/Flatten and Export butano sprite (256 colours)",
    "*",  # Image type
    [],
    [],
    python_fu_butano_256_sprite
)

def python_fu_butano_16_sprite(img, drawable):
    python_fu_butano_export(img, drawable, 16, "sprite")
register(
    "python_fu_butano_16_sprite",
    "Flatten and Export butano sprite (16 colours)",
    "Flatten and Export butano sprite (16 colours)",
    "BreadMakesYouFull",
    "BreadMakesYouFull",
    "2024",
    "<Image>/Butano/Flatten and Export butano sprite (16 colours)",
    "*",  # Image type
    [],
    [],
    python_fu_butano_16_sprite
)

main()
