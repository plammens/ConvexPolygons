#!/usr/bin/env python3

import math
import datetime


scale = 1e6
path = "text/"
n = 10000


def make_points(n: int, offset: float = 0) -> iter:
    a = math.tau / n
    return ((scale*math.cos(offset + i*a), scale*math.sin(offset + i*a)) for i in range(n))


def write_polygon(fileobj, name: str, points: iter):
    fileobj.write("polygon {}".format(name))
    for point in points:
        fileobj.write(" {:.3f} {:.3f}".format(*point))
    fileobj.write('\n\n')


def write_header(fileobj, description: str):
    fileobj.write("# test file automatically created by {} ({})\n".format(__file__, datetime.datetime.now()))
    fileobj.write("# description: {}\n".format(description))
    fileobj.write("# config: n = {}\n\n".format(n))


with open(path + "test.txt", 'w') as file:
    write_header(file, description="a circle and a small rotation thereof")
    write_polygon(file, "circ", make_points(n))
    write_polygon(file, "circ-rot", make_points(n, math.tau/n/4))
