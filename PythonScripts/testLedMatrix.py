
from luma.core.interface.serial import spi, noop
from luma.core.render import canvas
from luma.led_matrix.device import max7219
from PIL import ImageFont
import random
import time
import os.path

portId = 0;
deviceId = 0;
MATRIX_WIDTH = 8
MATRIX_HEIGHT = 8
CASCADED = None
ROTATE = 0
BLOCK_ORIENTATION = 0
BLOCKS_IN_REVERSE = False
CONTRAST = 112
serial = spi(port=portId, device=deviceId, gpio=noop())
device = max7219(serial, MATRIX_WIDTH, MATRIX_HEIGHT, CASCADED, ROTATE, BLOCK_ORIENTATION, BLOCKS_IN_REVERSE, CONTRAST)

line_start = (0,0)
line_end = (0,0)
lines = [(line_start, line_end)]
for i in range(MATRIX_WIDTH):
    lines.append((line_start, line_end))

time_step = .15
current = time.time()

def changeLines():
    lines.clear()
    for i in range(MATRIX_WIDTH):
        line_start = (i, 0)
        line_end = (i, random.randrange(0, MATRIX_HEIGHT-1))
        lines.append((line_start, line_end))
    return lines

def canBeActive(processName):
    return os.path.isfile(os.path.abspath("." + processName))

while canBeActive("testLedMatrix"):
    target_time = current + time_step
    if time.time() >= target_time:
        current = time.time()
        lines = changeLines()

    with canvas(device) as draw:
        for line in lines:
            draw.line(line, width=1, fill="red")
