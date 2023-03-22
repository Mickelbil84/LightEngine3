"""
-------------------------------------------------------
Tool:           png2xpm

Description:    Convert a png image to the xpm 
                (header) format. To be used as toolbar
                icons in the editor UI.

Usage:          python png2xpm.py <input_filename>
                # The output will be the same filename,
                # but with the *.xpm extension.
-------------------------------------------------------
"""
import os
import cv2
import argparse

XPM_EXTENSION = "xpm"
XPM_HEADER_COMMENT = "/* XPM */\n"
XPM_HEADER = "static const char *const {}[] = {{\n"
XPM_VALUES_COMMENT = "/* Values */\n"
XPM_COLORS_COMMENT = "/* Colors */\n"
XPM_PIXELS_COMMENT = "/* Pixels */\n"
XPM_FOOTER = "};\n"

ALLOWED_CHARACTERS = ' !@#$%^&*()-=+_1234567890qQwWeErRtTyYuUiIoOpP[{}]aAsSdDfFgGhHjJkKlL;:|`~zZxXcCvVbBnNmM,<.>/?'
MAX_COLORS_ALLOWED = len(ALLOWED_CHARACTERS)

def num2hex(num):
    num = hex(int(num)).replace('0x', '')
    if len(num) < 2:
        num = '0' + num
    return num

def color2hex(color):
    r, g, b, a = color;
    if a < 255:
        return 'None'
    r = num2hex(r)
    g = num2hex(g)
    b = num2hex(b)
    return '#{}{}{}'.format(r, g, b)

def create_colors_table(img):
    colors = []
    height, width, _ = img.shape
    for i in range(height):
        for j in range(width):
            color = color2hex(img[i, j, :])
            if color not in colors:
                colors.append(color)
    if len(colors) > MAX_COLORS_ALLOWED:
        raise ValueError("Too many colors in image. Please try to reduct the pallate")

    color_table = {}
    curr_c = 0
    for color in colors:
        color_table[color] = ALLOWED_CHARACTERS[curr_c]
        curr_c += 1
    
    return color_table


def png2xpm(img, filename):
    height, width, _ = img.shape

    color_table = create_colors_table(img)
    output = ""
    output += XPM_HEADER_COMMENT
    output += XPM_HEADER.format(filename)

    output += XPM_VALUES_COMMENT
    output += '"{} {} {} {}",\n'.format(width, height, len(color_table), 1)

    output += XPM_COLORS_COMMENT
    for color, c in color_table.items():
        output += '"{} c {}",\n'.format(c, color)
    
    output += XPM_PIXELS_COMMENT
    for i in range(height):
        row = '"'
        for j in range(width):
            row += color_table[color2hex(img[i, j])]
        row += '"'
        if i < height - 1:
            row += ','
        row += '\n'
        output += row
    output += XPM_FOOTER

    return output


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        prog="png2xpm",
        description="Convert a png image to the xpm (header) format. To be used as toolbar icons in the editor UI.")
    parser.add_argument('input_filename')
    args = parser.parse_args()
    path = args.input_filename

    filedir, filename = os.path.split(path)
    new_filename = filename.split('.')[0] + '.' + XPM_EXTENSION
    new_path = os.path.join(filedir, new_filename)

    img = cv2.imread(path, cv2.IMREAD_UNCHANGED)
    img = cv2.cvtColor(img, cv2.COLOR_BGRA2RGBA)
    xpm = png2xpm(img, filename.split('.')[0])

    with open(new_path, "w") as fp:
        fp.write(xpm)




