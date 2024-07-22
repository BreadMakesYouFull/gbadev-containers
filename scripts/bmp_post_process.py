#!/usr/bin/env python
"""bmp post process

* Strip colourspace header
* quantize to 256 or 16 bit indexed colours
* reserve #ff00ff as transparency

Usage:

    # Process a bmp for a  16 colour palatte
    ./bmp_post_process.py 16 input.bmp output.bmp

    # Process a bmp for a  256 colour palatte
    ./bmp_post_process.py 256 input.bmp output.bmp

Requirements:

    pillow (PIL)
    python 3

"""

import sys


try:
    from PIL import Image
except:
    print("PIL not installed")
    sys.exit()


def convert_to_indexed3(colours, input_path, output_path):
    # Open the input BMP image
    img = Image.open(input_path)
    # Convert the image to P mode with ``colours - 1`` number of colors
    # This is so we can reserve #ff00ff for transparent
    quantized_image = img.quantize(colors=colours)
    # Get the palette of the quantized image
    palette = quantized_image.getpalette()
    # Create a new palette with pink #ff00ff for transparency
    new_palette = [255, 0, 255] 
    # Add the remaining colors from the original palette
    new_palette.extend(palette[:(colours-1)*3])
    # Ensure the new palette has exactly 768 entries (256 colors)
    while len(new_palette) < colours * 3:
        new_palette.extend([0, 0, 0])
    # Create new palette image
    palette_img = Image.new('P', (1,1))
    palette_img.putpalette(new_palette)
    # Convert input image to new palette and save
    # https://pillow.readthedocs.io/en/stable/reference/Image.html
    # https://stackoverflow.com/questions/29433243/
    # https://stackoverflow.com/questions/75874680
    img_rgb = img.convert("RGB")
    img_rgb.load()
    palette_img.load()
    img_convert = img_rgb.im.convert("P", 0, palette_img.im)
    newimage = img_rgb._new(img_convert)
    newimage.save(output_path)


if __name__ == "__main__":
    colours = int(sys.argv[-3])
    input_bmp_path = sys.argv[-2]
    output_bmp_path = sys.argv[-1]
    print("converting {} to {} with {} colours palette".format(input_bmp_path, output_bmp_path, colours))
    convert_to_indexed3(colours, input_bmp_path, output_bmp_path)
