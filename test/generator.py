#!/usr/bin/env python3
"""Small script for generating test cases"""

import math
import datetime

path = "test/text/"
scale = 1e12  # scaling factor for coordinates (to allow precise storage)
n = 100000  # number of points in the circle


def make_points(n: int, phase: float = 0, x: float = 0, y: float = 0) -> iter:
    a = 2 * math.pi / n
    return ((scale *(math.cos(phase + i * a) + x), scale * (math.sin(phase + i * a) + y))
            for i in range(n))


def write_polygon(fileobj, name: str, points: iter):
    fileobj.write("polygon {}".format(name))
    for point in points:
        fileobj.write(" {:.3f} {:.3f}".format(*point))
    fileobj.write('\n\n')


def write_header(fileobj, description: str):
    fileobj.write("# test file automatically created by {} ({})\n".format(__file__, datetime.datetime.now()))
    fileobj.write("# description: {}\n".format(description))
    fileobj.write("# config: n = {}\n\n".format(n))


with open(path + "circle-rot.txt", 'w') as file:
    write_header(file, description="a circle and a small rotation thereof")
    write_polygon(file, "circ", make_points(n))
    write_polygon(file, "circ-rot", make_points(n, math.pi / n / 2))


with open("examples/intersection/in.txt", 'w') as file:
    n = 1000
    write_header(file, description="a circle and a translation thereof")
    write_polygon(file, "circle", make_points(n))
    write_polygon(file, "circle-transl", make_points(n, x=0.7))

    file.write("intersection inters circle circle-transl\n")
    file.write("setcol circle 1 0 0\n")
    file.write("setcol circle-transl 0 0 1\n")
    file.write("setcol inters 0.7 0 0.7\n")
    file.write("draw circles.png circle circle-transl inters\n")

