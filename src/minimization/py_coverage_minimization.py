#! /usr/bin/env python

import rospy
import matplotlib.pyplot as plt
import matplotlib as mpl
from matplotlib.patches import Polygon, Rectangle, Circle
import numpy as np
import math
import time
from py_coverage.grid_map import GridMap
from py_coverage.grid_based_sweep_coverage_path_planner import planning
from py_coverage.tools import define_polygon, polygon_contains_point



if __name__ == '__main__':
	rospy.init_node('test_node')