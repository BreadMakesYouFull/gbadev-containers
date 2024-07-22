# Graphics

Image folder

* BMP only
* no compression
* no color space information
* colours MUST be indexed
* first colour in indexed colour map will be transparency
* 16 or 256 colors
* GBA can only use 16xpalettes of 16 colours, OR 1xpalette of 256

Docs for butano:

[Further reading importing assets](https://gvaliente.github.io/butano/import.html#import_image)
[Further reading FAQ](https://gvaliente.github.io/butano/faq.html#faq_color)

**Remember that the first pixel in the colour palette is considered the transparent colour!**

Scripts to help convert gba and hex colour values for reference:
```
# hex to gba/butano
./scripts/hex_to_gba.py ff0000
# Result: 31 0 0

# gba/butano to hex
./scripts/gba_to_hex.py 31 0 0
# Result: ff0000

# This will be a lossy conversion (colours will not be 1-1)
```

## Gimp export plugin for butano (experimental)

A gimp plugin is provided for ``regular_bg`` and ``sprite`` of either 256 or 16 colors.

```
# From the gbadev-containers folder open gimp:
make gimp

# Opens in ``/in`` inside the container (mounted from this project/folder)
# Create your bitmap matching butano requirements (resolution included)
# Use the "butano > {export option}" to flatten and save images and .json file to ``/in/graphics``
# Remember to rename the result on file and in your code
# Remove any unused bmps (particularly invalid bmps)
#
# Also follow the butano import and faq docs, you may do this process manually instead from gimp.
```

In general, the GIMP workflow is:

* Correct resolution
* Flatten
* Set colors to indexed
* Remove colourspace information
* Create a json metadata file

**You will likely need to tweak the result to suit your needs!**

Slate pixel editor is also provided:
```
make slate
# bmp images will need to be post processed for butano!
# Example swatch files are provided for reference in ``/opt/slate``
```
