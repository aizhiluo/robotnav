#!/usr/bin/env python

import os
import sys

import numpy as np

from voxel_space import *
from object_lib import *
from env_gen import *

def test_voxel():
    print "test voxel"
    v = Voxel(1, 2, 3)
    v.print_info()
    print "---------------------\n"


def test_space():
    print "test space"
    s = Space(2, 2, 2)
    print "empty space:"
    s.print_info()
    s.get_2d_map().print_info()
    print "\nadded obstacles:"
    s.add_obstacles()
    s.get_2d_map().print_info()
    print "---------------------\n"


def test_objects():
    print "test objects"
    cuboid = Cuboid(0, 0, 2, 2, 2)
    cuboid.print_info()
    print "---------------------\n"


def test_envgen():
    env = EnvGen()
    env.set_env_size(15,15,15)
    env.generate_space()
    env.show_space()


def main():
    print "started unit tests: \n"

    # test_voxel()
    # test_objects()
    # test_space()

    test_envgen()

# Standard boilerplate to call the main() function to begin
# the program.
if __name__ == '__main__':
    main()