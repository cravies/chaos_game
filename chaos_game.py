import random
import numpy as np
from matplotlib import pyplot as plt
from typing import List

NUM_POINTS=100000

def make_points_square(upper: float, lower: float, start=np.array([0.5,0.5]), jump_frac=0.5) -> np.ndarray[List[float]]:
    """
    Generate fractal points
    Arguments:
        upper: upper bound of square
        lower: lower bound of square
        start: initial midpoint to start iterating from
        jump_frac: when we iterate, jumping part of the way from point to random vertex,
        what fraction of the distance do we jump?
    Returns:
        points: a np array of [x,y] points that define the fractal
    """
    #define vertices of square
    vertices = np.array([
        (lower,lower),(lower,upper),
        (upper,lower),(upper,upper)
        ])
    points=[]
    #initial point
    mid=start
    prev=vertices[0]
    vertex=vertices[1]
    #iterate
    for i in range(NUM_POINTS):
        vertex = random.choice(vertices)
        if np.array_equal(vertex,prev)==False:
            mid = jump_frac*(vertex + mid)
            points.append(mid)
            prev = vertex
    return np.array(points)

def plot_points(points: np.ndarray[List[float]]) -> None:
    """
    Plots a set of points
    Arguments:
        points: an array of [x,y] points
    Returns: 
        None
    """
    plt.scatter(points[:,0], points[:,1], s=1, marker='x', color='black')
    plt.savefig('result.png')

if __name__=="__main__":
    # sierpinski square
    points = make_points_square(0,1)
    plot_points(points)